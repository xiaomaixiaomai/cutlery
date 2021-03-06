#ifndef HEAP_H
#define HEAP_H

#include<stdio.h>
#include<stdlib.h>

#include<array.h>
#include<bucket.h>

#define push    push_heap
#define pop     pop_heap
#define get_top get_top_heap

typedef enum heap_type heap_type;
enum heap_type
{
	MIN_HEAP,
	MAX_HEAP
};

typedef struct heap heap;
struct heap
{
	// the type of heap, a heap can be a min heap or a max heap
	// as a MIN_HEAP or MAX_HEAP
	heap_type type;

	// compare keys and returns 0 if they are same, else non-zero
	// it returns 0 if they are same, >0 if key0 is greater than key1 else it must return <0 value
	int (*key_compare)(const void* key1, const void* key2);

	// number of buckets in the heap
	unsigned long long int heap_size;

	// array of buckets in heap
	array* heap_holder;
};

// build and get a new heap, with expected size, and of the given heap type (either MIN_HEAP or MAX_HEAP)
void* get_heap(unsigned long long int expected_size, heap_type type, int (*key_compare)(const void* key0, const void* key1));

// push a new bucket to the heap
// O(log(N)) operation
void push(heap* heap_p, const void* key, const void* value);

// returns pointer to the value of the bucket, whose key is either minimum for MIN_HEAP (or maxinum if it is a MAX_HEAP)
// O(1) operation
const void* get_top(const heap* heap_p, const void** returned_key);

// pop the top bucket from the heap
// O(log(N)) operation
void pop(heap* heap_p);

// delete heap and heap_holder array, along with all its buckets
void delete_heap(heap* heap_p);

// print, heap and all the elements of the heap
void print_heap(heap* heap_p, void (*print_key)(const void* key), void (*print_value)(const void* value));

#undef push
#undef pop
#undef get_top

#endif