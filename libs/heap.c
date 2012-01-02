#include <heap.h>
#include <stdlib.h>
#include <stdio.h>


static process_heap_t process_heap;		// global static variable

static process_heap_t* heap_init() {
	process_heap.size = 0;
	return &(process_heap);
}

static void heap_print(process_heap_t *heap) {
	int i;
	cprintf("heap_print(): ");
	for (i = 0; i < heap->size; ++i) {
		cprintf("%d ", heap->entry[i].x);	// i hope this is right...
	}
	cprintf("\n");
}

// insert element into heap
static void heap_push(process_heap_t *heap, heap_entry_t elm) {
	int pos = heap->size;
	if (pos >= MAX_HEAP_SIZE) {
		cprintf("heap.c: process heap has reached MAX_HEAP_SIZE!\n");
		while(1);		// cant panic, so just loop here =.=
	}
	heap->entry[pos] = elm;
	heap->size++;
	// re-arrange, filter bottom element up
	__rearrange_bottomup(heap);
}

// pop element from heap
// returns NULL when empty
// preferably test before calling
static heap_entry_t heap_pop(struct process_heap *heap) {
	if (heap_empty(heap)) {
		cprintf("process heap is empty!\n");
	}
	heap_entry_t ret = heap->entry[0];
	if (heap->size > 1)
		heap->entry[0] = heap->entry[heap->size-1];		// move last element to first
	heap->size--;
	// re-arrange, filter top element down
	__rearrange_topdown(heap);
	return ret;
}

// is it empty
static bool heap_empty(struct process_heap *heap) {
	return (heap->size == 0);
}

// after each pop and push we want to re-arrange
// so that it still maintains heap order
static void __rearrange_topdown(process_heap_t *heap) {
	int father_pos = 0;
	int father_val = heap->entry[father_pos].x;
	int lc_pos, lc_val, rc_pos, rc_val;
	int chosen_pos;
	while((lc_pos = __get_lc(father_pos)) < heap->size-1) {		// rc_pos < heap->size
		rc_pos = lc_pos+1;
		lc_val = heap->entry[lc_pos].x;
		rc_val = heap->entry[rc_pos].x;
		chosen_pos = __min(lc_val, rc_val, lc_pos);
		if (father_val > heap->entry[chosen_pos].x) {
			__exchange(heap, father_pos, chosen_pos);
		}
		else
			break;		// break in the middle
		father_pos = chosen_pos;
	}
	if (lc_pos == heap->size-1) {	// only possibility that only one child is end
		if (father_val > heap->entry[lc_pos].x)
			__exchange(heap, father_pos, lc_pos);
	}
	// hopefully down
}

static void __rearrange_bottomup(process_heap_t *heap) {
	int father_pos;
	int father_val;
	int son_pos = heap->size-1;
	int son_val = heap->entry[son_pos].x;
	while((father_pos = __get_father(son_pos)) != son_pos) {	// son pos not 0 yet
		father_val = heap->entry[father_pos].x;
		if (father_val > son_val)
			__exchange(heap, father_pos, son_pos);
		else
			break;		// done
		son_pos = father_pos;	// new node
	}
}
// check boundaries before calling
static int __get_father(int x) {
	return (int) (x-1)/2;
}

static int __get_lc(int x) {
	return 2*x+1;
}

static int __get_rc(int x) {
	return 2*x+2;
}

// exchange the two positions x and y
// also exchange pointer to proc
// must be guaranteed that they exist!
static void __exchange(process_heap_t *heap, int x, int y) {
	int tmp = heap->entry[y].x;
	int *p = heap->entry[y].proc;

	heap->entry[y].x = heap->entry[x].x;
	heap->entry[x].x = tmp;
	// exchange pointers to proc
	heap->entry[y].proc = heap->entry[x].proc;
	heap->entry[x].proc = p;
}
// x is lc_val, y is rc_val
static int __min(int x, int y, int lc_pos) {
	return (x < y) ? lc_pos : lc_pos+1;
}


