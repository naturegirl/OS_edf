#ifndef __LIBS_HEAP_H__
#define __LIBS_HEAP_H__

#include <types.h>

#define MAX_HEAP_SIZE 1024

/* simple binary heap implementation
 * for priority scheduling of processes
 * with earliest deadline first algorithm
 * Note: the heap is ordered top small bottom big
 */

struct heap_entry {
	int *proc;		// heap for procs, this is really ugly but as I cannot access proc_struct int pointer will just do
					// need to convert back
	int x;		// deadline of proc, seperately save in here too
};

struct process_heap {
	struct heap_entry entry[MAX_HEAP_SIZE];
	int size;
};

typedef struct heap_entry heap_entry_t;
typedef struct process_heap process_heap_t;

static process_heap_t*  heap_init();

static void heap_print(process_heap_t *heap);

// insert element into heap
static void heap_push(process_heap_t *heap, heap_entry_t elm);

// pop element from heap
static heap_entry_t heap_pop(process_heap_t *heap);

// is it empty
static bool heap_empty(process_heap_t *heap);

/* private usage functions */
static void __rearrange_topdown(process_heap_t *heap);		// filter large value down
static void __rearrange_bottomup(process_heap_t *heap);	// filter small value up

static int __get_father(int x);
static int __get_lc(int x);		// left child
static int __get_rc(int x);	// right child
static void __exchange(process_heap_t *heap, int x, int y);	// exchange
static int __min(int x, int y, int lc_pos);		// return child position whose value is smaller


#endif
