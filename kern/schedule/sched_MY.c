#include <types.h>
#include <list.h>
#include <proc.h>
#include <assert.h>
#include <sched_MY.h>
#include <stdlib.h>
#include <stdio.h>


static void
MY_init(struct run_queue *rq) {
    list_init(&(rq->run_list));		// also init with a list
    rq->proc_num = 0;
}

static void
MY_enqueue(struct run_queue *rq, struct proc_struct *proc) {
    assert(list_empty(&(proc->run_link)));
    list_add_before(&(rq->run_list), &(proc->run_link));	// add current process
    // we should not be needing time_slice
    if (proc->time_slice == 0 || proc->time_slice > rq->max_time_slice) {
        proc->time_slice = rq->max_time_slice;
    }
    proc->rq = rq;		//	running queue that contains process
    rq->proc_num ++;
}

static void
MY_dequeue(struct run_queue *rq, struct proc_struct *proc) {
    assert(!list_empty(&(proc->run_link)) && proc->rq == rq);
    list_del_init(&(proc->run_link));
    rq->proc_num --;
}

// called when current proc neeeds reschedule is true
static struct proc_struct *
MY_pick_next(struct run_queue *rq) {
    struct proc_struct *proc;			// to save the proc we get from list elm, temporary use
    list_entry_t *le;					// temporary use when iterating through list
    list_entry_t *start = list_next(&(rq->run_list));	// temporary use
    struct proc_struct *pickNext = NULL;		// the one with closest deadline, will return this one

    if (list_empty(&(rq->run_list)))
    	panic("sched_MY.c pick_next: list is empty!\n");

    int ed = PROC_MAX_DEADLINE;		// earliest deadline
    // pick the one with earliest deadline
	for(le = list_next(&(rq->run_list)); le->next != start; le = list_next(le)) {
		proc = le2proc(le, run_link);
		//cprintf("pid %d pt %d\n", proc->pid, proc->pt);
		if (proc->pt <= ed) {		// pick a RT proc only! has earlier deadline
			ed = proc->pt;
			pickNext = proc;
		}
	}
	cprintf("pickNext pid = %d ct %d pt %d isRT %d\n", pickNext->pid, pickNext->ct, pickNext->pt, pickNext->isRT);
	if (pickNext == NULL)
		panic("no pickNext found! Is this an issue?");
    return pickNext;
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
	tick_decrease_RT_pt(rq, proc);		// decrease pt of all RT procs in rq
	if(rq_exist_earlier_deadline(rq, proc->pt))
		proc->need_resched = TRUE;
}

// check if there is a RT process in run queue with earlier deadline
// necessary on each tick, because at any time a new process may have joined
// combine with tick_decrease_RT_pt eventually
static bool
rq_exist_earlier_deadline(struct run_queue *rq, int deadline) {
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

// decrease the pt of all RT procs in runqueue
// assume all process are RT
static void tick_decrease_RT_pt(struct run_queue *rq, struct proc_struct *currentproc) {
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

