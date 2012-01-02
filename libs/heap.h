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

process_heap_t*  heap_init();

void heap_print(process_heap_t *heap);

// insert element into heap
void heap_push(process_heap_t *heap, heap_entry_t elm);

// pop element from heap
heap_entry_t heap_pop(process_heap_t *heap);

// only get the first element, but don't pop
heap_entry_t heap_gettop(process_heap_t *heap);

// is it empty
bool heap_empty(process_heap_t *heap);



/* private usage functions */
void __rearrange_topdown(process_heap_t *heap);		// filter large value down
void __rearrange_bottomup(process_heap_t *heap);	// filter small value up

int __get_father(int x);
int __get_lc(int x);		// left child
int __get_rc(int x);	// right child
void __exchange(process_heap_t *heap, int x, int y);	// exchange
int __min(int x, int y, int lc_pos);		// return child position whose value is smaller


#endif
