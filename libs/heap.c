#include <heap.h>
#include <stdlib.h>

static process_heap_t process_heap = {{0}};

int main() {
	heap_init();
}

static process_heap_t* heap_init() {
	process_heap.size = 0;
	return &(process_heap);
}

// insert element into heap
static void heap_add(process_heap_t *heap, heap_entry_t elm) {
	int pos = heap->size++;
	if (pos >= MAX_HEAP_SIZE)
		panic("process heap has reached MAX_HEAP_SIZE!");
	heap->entry[pos] = elm;
	heap->size++;
}

// pop element from heap
static heap_entry_t heap_pop(struct process_heap *heap);

// is it empty
static bool heap_empty(struct process_heap *heap);
