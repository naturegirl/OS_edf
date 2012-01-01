#ifndef __LIBS_HEAP_H__
#define __LIBS_HEAP_H__

#include <types.h>

#define MAX_HEAP_SIZE 1024

/* simple binary heap implementation
 * for priority scheduling of processes
 * with earliest deadline first algorithm
 */

struct heap_entry {
	struct proc_struct *proc;		// heap for procs
};

struct process_heap {
	struct heap_entry entry[MAX_HEAP_SIZE];
	int size;
};

typedef struct heap_entry heap_entry_t;
typedef struct process_heap process_heap_t;

static process_heap_t*  heap_init();

// insert element into heap
static void heap_add(struct process_heap *heap, heap_entry_t elm);

// pop element from heap
static heap_entry_t heap_pop(struct process_heap *heap);

// is it empty
static bool heap_empty(struct process_heap *heap);


#endif
