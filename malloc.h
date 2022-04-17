#include<stdio.h>
#include<stddef.h>

char heap[10000];

struct block
{
    size_t size;
    int free;
    struct block *next;
};

struct block*freeList=(struct block*)heap;

void initialize();//Initializing the block
void split(struct block *fitting_slot,size_t size);
void *allocate(size_t noofBytes);
void merge();
void deallocate(void* ptr);
void printSize();
