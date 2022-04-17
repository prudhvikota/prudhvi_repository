#include<stdio.h>
#include<stddef.h>
#include "malloc.h"


void initialize()
{
    freeList->size=10000-sizeof(struct block*);
    freeList->free=1;
    freeList->next=NULL;
}

void split(struct block *fitting_slot,size_t size)
{
    struct block *new=(void*)((void*)fitting_slot+size+sizeof(struct block*));
    new->size=(fitting_slot->size)-size-sizeof(struct block*);
    new->free=1;
    new->next=fitting_slot->next;
    fitting_slot->size=size;
    fitting_slot->free=0;
    fitting_slot->next=new;
}


void *allocate(size_t noofBytes)//using the first fit algorithm
//First fit algorithm:-In the first fit, the partition is allocated which is first sufficient from the top of Main Memory.
{
    struct block *curr,*prev;
    void *result;
    if(!(freeList->size)){
    initialize();
    printf("Memory initialized\n");
    }
    curr=freeList;
    while((((curr->size)<noofBytes)||((curr->free)==0))&&(curr->next!=NULL))
    {
        prev=curr;
        curr=curr->next;
        printf("One block checked\n");
    }
    if((curr->size)==noofBytes)
    {
        curr->free=0;
        result=(void*)(++curr);
        printf("Exact fitting block allocated\n");
        return result;
    }
    else if((curr->size)>(noofBytes+sizeof(struct block*)))
    {
        split(curr,noofBytes);
        result=(void*)(++curr);
        printf("Fitting block allocated with a split using the split function\n");
        return result;
    }
    else
    {
        result=NULL;
        printf("Sorry. No sufficient memory to allocate\n");
        return result;
    }
}

void merge()
{
    struct block *curr,*prev;
    curr=freeList;
    while((curr->next)!=NULL)
    {
        if((curr->free) && (curr->next->free))
        {
        curr->size+=(curr->next->size)+sizeof(struct block*);
        curr->next=curr->next->next;
        }
        prev=curr;
        curr=curr->next;
    }
}

void deallocate(void* ptr)
{
    if(((void*)heap<=ptr)&&(ptr<=(void*)(heap+10000)))
    {
    struct block* curr=ptr;
    curr--;
    curr->free=1;
    merge();
    }
    else
    {
        printf("Please provide a valid pointer allocated by allocate\n");
    } 
}


void printSize()
{
        struct block*curr=freeList;
        printf("\n The size of the filled blocks in the List:");
        while(curr->next!=NULL)
        {
            printf("%zu ",curr->size);
            curr=curr->next;
        }
        
    
}
