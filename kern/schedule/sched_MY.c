#include <types.h>
#include <list.h>
#include <heap.h>
#include <proc.h>
#include <assert.h>
#include <sched_MY.h>
#include <stdlib.h>
#include <stdio.h>

static process_heap_t *heap;

static void
MY_init(struct run_queue *rq) {
    heap = heap_init();
    rq->proc_num = 0;
}

static void
MY_enqueue(struct run_queue *rq, struct proc_struct *proc) {
    proc->rq = rq;		//	running queue that contains process
    rq->proc_num ++;

    // heap part
    heap_entry_t elm;
    elm.proc = (int *)proc;
    elm.x = proc->pt;
    heap_push(heap, elm);
}

static void
MY_dequeue(struct run_queue *rq, struct proc_struct *proc) {
    assert(!heap_empty(heap) && proc->rq == rq);
    rq->proc_num --;

    // heap part
    heap_entry_t elm;
    if (!heap_empty(heap))
    	elm = heap_pop(heap);
}

// called when current proc neeeds reschedule is true
static struct proc_struct *
MY_pick_next(struct run_queue *rq) {
    if (heap_empty(heap))
    	panic("sched_MY.c pick_next: heap is empty!\n");
	// heap part
	heap_entry_t elm = heap_gettop(heap);
	struct proc_struct *heapNext = (struct proc_struct *)elm.proc;
    return heapNext;
}

// do 2 things
// 1. decrese pt of all RT procs
// 2. increase ct of current proc
static void
MY_proc_tick(struct run_queue *rq, struct proc_struct *proc) {
	if (proc->isRT == FALSE)
		proc->need_resched = TRUE;
	else {
		if (proc->ct < proc->compute_time) {
			proc->ct ++;		// current proc executing
			proc->pt --;	// decrease pt of current proc here, because it isn't in run queue
		}
		if (proc->pt == 0 && proc->ct < proc->compute_time) {
			panic("pt of proc %d == 0 but ct == %d (current process)", proc->pid, proc->ct);
		}
		if (proc->ct == proc->compute_time)	{	// done with this one. Can reschedule
			proc->need_resched = TRUE;
			proc->ct = 0;		// start from beginning the next time it is scheduled
			proc->pt += proc->period_time;		// deadline for next cycle
		}
	}

	tick_decrease_pt_heap(heap);
	if(heap_exist_earlier_deadline(heap, proc->pt))
		proc->need_resched = TRUE;
}

// check if there is a RT process in run queue with earlier deadline
// necessary on each tick, because at any time a new process may have joined
// combine with tick_decrease_RT_pt eventually
bool rq_exist_earlier_deadline(struct run_queue *rq, int deadline) {
	struct proc_struct *proc;			// proc iterator
	list_entry_t *le;					// list iterator
	list_entry_t *start = list_next(&(rq->run_list));	// temporary use
	for(le = list_next(&(rq->run_list)); le->next != start; le = list_next(le)) {
		proc = le2proc(le, run_link);
			if (proc->isRT) {
				if (proc->pt < deadline)
					return TRUE;
			}
	}
	return FALSE;
}

bool heap_exist_earlier_deadline(process_heap_t *heap, int deadline) {
	heap_entry_t elm = heap_gettop(heap);
	return (elm.x < deadline) ? TRUE : FALSE;
}

void tick_decrease_pt_heap(process_heap_t *heap) {
	struct proc_struct *proc;			// proc iterator
	int i;
	int *p;
	for (i = 0; i < heap->size; ++i) {
		heap->entry[i].x --;		// deadline
		p = heap->entry[i].proc;
		proc = (struct proc_struct *)p;
		proc->pt--;		// for all RT procs the pt has decreased one!
		if (proc->pt == 0 && proc->ct  < proc->compute_time)
			panic("pt of proc %d == 0 but ct == %d (process in run queue)", proc->pid, proc->ct);
		if (proc->pt < 0)
			panic("pt of RT proc %d < 0! RT schedule failure!", proc->pid);
	}
}

// decrease the pt of all RT procs in runqueue
// assume all process are RT
void tick_decrease_RT_pt(struct run_queue *rq, struct proc_struct *currentproc) {
	struct proc_struct *proc;			// proc iterator
	list_entry_t *le;					// list iterator
	list_entry_t *start = list_next(&(rq->run_list));	// temporary use
	bool noRTprocs = TRUE;		// see if there are still RT procs in the run queue. Otherwise exist. Helps debugging
	for(le = list_next(&(rq->run_list)); le->next != start; le = list_next(le)) {
		proc = le2proc(le, run_link);
		if (proc->isRT) {
			noRTprocs = FALSE;
			proc->pt--;		// for all RT procs the pt has decreased one!
			if (proc->pt == 0 && proc->ct  < proc->compute_time)
				panic("pt of proc %d == 0 but ct == %d (process in run queue)", proc->pid, proc->ct);
			if (proc->pt < 0)
				panic("pt of RT proc %d < 0! RT schedule failure!", proc->pid);
		}
	}
	//if (noRTprocs && currentproc->isRT == FALSE)		// init proc
//		panic("no RT procs left. Exiting");
}

struct sched_class MY_sched_class = {
    .name = "MY_scheduler",
    .init = MY_init,
    .enqueue = MY_enqueue,
    .dequeue = MY_dequeue,
    .pick_next = MY_pick_next,
    .proc_tick = MY_proc_tick,
};

