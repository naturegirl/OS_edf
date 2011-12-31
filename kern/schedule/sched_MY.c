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
    if (proc->deadline <= 0 || proc->deadline > PROC_MAX_DEADLINE) {
    	panic("deadline of pid %d is %d!!", proc->pid, proc->deadline);
    }
    //cprintf("enqueue %d\n", proc->deadline);
    proc->rq = rq;		//	running queue that contains process
    rq->proc_num ++;
}

static void
MY_dequeue(struct run_queue *rq, struct proc_struct *proc) {
    assert(!list_empty(&(proc->run_link)) && proc->rq == rq);
    list_del_init(&(proc->run_link));
    rq->proc_num --;
}

static struct proc_struct *
MY_pick_next(struct run_queue *rq) {
    struct proc_struct *proc;			// to save the proc we get from list elm, temporary use
    list_entry_t *le;					// temporary use when iterating through list
    list_entry_t *start = list_next(&(rq->run_list));	// temporary use
    struct proc_struct *pickNext;		// the one with closest deadline, will return this one

    if (list_empty(&(rq->run_list)))
    	panic("sched_MY.c pick_next: list is empty!\n");

    int closestDeadline = PROC_MAX_DEADLINE;
	for(le = list_next(&(rq->run_list)); le->next != start; le = list_next(le)) {
		proc = le2proc(le, run_link);
		if (proc->deadline <= closestDeadline)		// has closer deadline
			pickNext = proc;
	}
	cprintf("sched_MY: picked next PID %d deadline %d\n", pickNext->pid, pickNext->deadline);
    return pickNext;
}

static void
MY_proc_tick(struct run_queue *rq, struct proc_struct *proc) {
    if (proc->time_slice > 0) {
        proc->time_slice --;
    }
    if (proc->time_slice == 0) {
        proc->need_resched = 1;
    }
}

struct sched_class MY_sched_class = {
    .name = "MY_scheduler",
    .init = MY_init,
    .enqueue = MY_enqueue,
    .dequeue = MY_dequeue,
    .pick_next = MY_pick_next,
    .proc_tick = MY_proc_tick,
};

