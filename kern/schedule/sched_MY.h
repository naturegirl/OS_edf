#ifndef __KERN_SCHEDULE_SCHED_MY_H__
#define __KERN_SCHEDULE_SCHED_MY_H__

#include <sched.h>
#include <heap.h>

extern struct sched_class MY_sched_class;

// queue part
bool rq_exist_earlier_deadline(struct run_queue *rq, int deadline);
void tick_decrease_RT_pt(struct run_queue *rq, struct proc_struct *currentproc);		// decrease the current pt (deadline) of all running RT procs

// heap part
bool heap_exist_earlier_deadline(process_heap_t *heap, int deadline);
void tick_decrease_pt_heap(process_heap_t *heap);

#endif /* !__KERN_SCHEDULE_SCHED_MY_H__ */

