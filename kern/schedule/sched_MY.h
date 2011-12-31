#ifndef __KERN_SCHEDULE_SCHED_MY_H__
#define __KERN_SCHEDULE_SCHED_MY_H__

#include <sched.h>

extern struct sched_class MY_sched_class;

static void tick_decrease_RT_pt(struct run_queue *rq);		// decrease the current pt (deadline) of all running RT procs

#endif /* !__KERN_SCHEDULE_SCHED_MY_H__ */

