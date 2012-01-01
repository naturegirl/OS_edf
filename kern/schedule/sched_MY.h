#ifndef __KERN_SCHEDULE_SCHED_MY_H__
#define __KERN_SCHEDULE_SCHED_MY_H__

#include <sched.h>

extern struct sched_class MY_sched_class;

static bool rq_exist_earlier_deadline(struct run_queue *rq, int deadline);
static void tick_decrease_RT_pt(struct run_queue *rq, struct proc_struct *currentproc);		// decrease the current pt (deadline) of all running RT procs

#endif /* !__KERN_SCHEDULE_SCHED_MY_H__ */

