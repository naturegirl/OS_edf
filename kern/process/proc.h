#ifndef __KERN_PROCESS_PROC_H__
#define __KERN_PROCESS_PROC_H__

#include <types.h>
#include <list.h>
#include <trap.h>
#include <memlayout.h>
#include <unistd.h>

// process's state in his life cycle
enum proc_state {
    PROC_UNINIT = 0,  // uninitialized
    PROC_SLEEPING,    // sleeping
    PROC_RUNNABLE,    // runnable(maybe running)
    PROC_ZOMBIE,      // almost dead, and wait parent proc to reclaim his resource
};

// Saved registers for kernel context switches.
// Don't need to save all the %fs etc. segment registers,
// because they are constant across kernel contexts.
// Save all the regular registers so we don't need to care
// which are caller save, but not the return register %eax.
// (Not saving %eax just simplifies the switching code.)
// The layout of context must match code in switch.S.
struct context {
    uint32_t eip;
    uint32_t esp;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
};

#define PROC_NAME_LEN               15
#define MAX_PROCESS                 4096
#define MAX_PID                     (MAX_PROCESS * 2)
#define PROC_MAX_DEADLINE			70				// max value for period time

extern list_entry_t proc_list;
extern list_entry_t proc_mm_list;

struct proc_struct {
    enum proc_state state;                      // Process state
    int pid;                                    // Process ID
    int runs;                                   // the running times of Proces
    uintptr_t kstack;                           // Process kernel stack
    volatile bool need_resched;                 // bool value: need to be rescheduled to release CPU?, volatile to tell the compiler not to optimize
    struct proc_struct *parent;                 // the parent process
    struct mm_struct *mm;                       // Process's memory management field
    struct context context;                     // Switch here to run process
    struct trapframe *tf;                       // Trap frame for current interrupt
    uintptr_t cr3;                              // CR3 register: the base addr of Page Directroy Table(PDT)
    uint32_t flags;                             // Process flag
    char name[PROC_NAME_LEN + 1];               // Process name
    list_entry_t list_link;                     // Process link list 
    list_entry_t hash_link;                     // Process hash list
    int exit_code;                              // return value when exit
    uint32_t wait_state;                        // Process waiting state: the reason of sleeping
    struct proc_struct *cptr, *yptr, *optr;     // Process's children, yonger sibling, Old sibling
    list_entry_t thread_group;                  // the threads list including this proc which share resource (mem/file/sem...)
    struct run_queue *rq;                       // running queue that contains Process
    list_entry_t run_link;                      // the entry linked in run queue
    int time_slice;                             // time slice for occupying the CPU

    bool isRT;								// is a real time proc. Assume in RT system there are RT and nonRT processes
    int compute_time;			// worst case computation time. Constant!
    int period_time;			// period for arrival of this process. MAX_PROC_DEADLINE
    int ct;				// changing ct. Increases with each period (0~compute_time)
    int pt;				// changing pt to represent deadline. Decreases with each period (period_time~0).
};

#define PF_EXITING                  0x00000001      // getting shutdown

//the wait state
#define WT_CHILD                    (0x00000001 | WT_INTERRUPTED)  // wait child process
#define WT_TIMER                    (0x00000002 | WT_INTERRUPTED)  // wait timer
#define WT_KSWAPD                    0x00000003                    // wait kswapd to free page
#define WT_INTERRUPTED               0x80000000                    // the wait state could be interrupted

#define le2proc(le, member)         \
    to_struct((le), struct proc_struct, member)

extern struct proc_struct *idleproc, *initproc, *current;
extern struct proc_struct *kswapd;

void proc_init(void);
void proc_run(struct proc_struct *proc);
int kernel_thread(int (*fn)(void *), void *arg, uint32_t clone_flags);

char *set_proc_name(struct proc_struct *proc, const char *name);
char *get_proc_name(struct proc_struct *proc);
void cpu_idle(void) __attribute__((noreturn));

struct proc_struct *find_proc(int pid);
void may_killed(void);
int do_fork(uint32_t clone_flags, uintptr_t stack, struct trapframe *tf);
int do_forkRT(uint32_t clone_flags, uintptr_t stack, struct trapframe *tf, int ct, int pt);	// by me
int do_exit(int error_code);
int do_exit_thread(int error_code);
int do_execve(const char *name, size_t len, unsigned char *binary, size_t size);
int do_yield(void);
int do_wait(int pid, int *code_store);
int do_kill(int pid, int error_code);
int do_brk(uintptr_t *brk_store);
int do_sleep(unsigned int time);
int do_mmap(uintptr_t *addr_store, size_t len, uint32_t mmap_flags);
int do_munmap(uintptr_t addr, size_t len);
int do_shmem(uintptr_t *addr_store, size_t len, uint32_t mmap_flags);

#endif /* !__KERN_PROCESS_PROC_H__ */

