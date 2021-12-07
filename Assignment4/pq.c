/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Jake Statz
 * Email: statzj@oregonstate.edu
 */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "pq.h"
#include "dynarray.h"

struct elements{
    int priority;
    void* value;
};

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */

struct pq{
    struct dynarray* array;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */

struct pq* pq_create(){

    struct pq* pq = malloc(sizeof(struct pq));
    assert(pq);
    pq->array = dynarray_create();
    return pq;
}

/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */

void pq_free(struct pq* pq){

    dynarray_free(pq->array);
    free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */

int pq_isempty(struct pq* pq){

    if (dynarray_size(pq->array) == 0)
        return 1;
    else
        return 0;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */

void pq_insert(struct pq* pq, void* value, int priority){

    int idx_1;
    int idx_2;
    struct elements* temp1;
    struct elements* temp2;
    struct elements* element = malloc(sizeof(struct elements));
    assert(element);

    element->value = value;
    element->priority = priority;

    dynarray_insert(pq->array, element);

    idx_2 = dynarray_size(pq->array) - 1;
    idx_1 = (idx_2 - 1) / 2;

    while (idx_2 != 0){
            temp1 = dynarray_get(pq->array, idx_1);
            temp2 = dynarray_get(pq->array, idx_2);

        if (temp1->priority > temp2->priority){
            temp1 = dynarray_get(pq->array, idx_1);
            temp2 = dynarray_get(pq->array, idx_2);

            dynarray_set(pq->array, idx_1, temp2);
            dynarray_set(pq->array, idx_2, temp1);
        }

        idx_2 = idx_1;
        idx_1 = (idx_2 - 1) / 2;
    }
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */

void* pq_first(struct pq* pq){

    struct elements* element;
    void* value;

    element = dynarray_get(pq->array, 0);
    value = element->value;

    return value;
}

/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */

int pq_first_priority(struct pq* pq){

    struct elements* element;
    int priority;

    element = dynarray_get(pq->array, 0);
    priority = element->priority;

    return priority;
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */

void* pq_remove_first(struct pq* pq){

    void* lastElementVal;
    struct elements* firstElementVal;
    struct elements* temp1, * temp2;
    struct elements* leftElement;
    struct elements* rightElement;
    struct elements* minElement;

    int lastChild;
    int leftChild = 1;
    int rightChild = 2;
    int x = 0;
    int min = x;

    lastChild = dynarray_size(pq->array) - 1;
    firstElementVal = dynarray_get(pq->array, 0);
    lastElementVal = dynarray_get(pq->array, lastChild);

    dynarray_set(pq->array, 0, lastElementVal);
    dynarray_remove(pq->array, lastChild);

    while (leftChild < dynarray_size(pq->array)){
        leftElement = dynarray_get(pq->array, leftChild);
        minElement = dynarray_get(pq->array, min);

        if (rightChild >= dynarray_size(pq->array)){
            if (leftElement->priority < minElement->priority){
                min = leftChild;
            }
        }

        else{
            rightElement = dynarray_get(pq->array, rightChild);

            if (leftElement->priority < minElement->priority && leftElement->priority <= rightElement->priority) {
                min = leftChild;
            }
            if (rightElement->priority < minElement->priority && leftElement->priority > rightElement->priority) {
                min = rightChild;
            }
        }

        if (min == x){
            break;
        }

        else{
            temp1 = dynarray_get(pq->array, x);
            temp2 = dynarray_get(pq->array, min);

            dynarray_set(pq->array, x, temp2);
            dynarray_set(pq->array, min, temp1);

            x = min;
            leftChild = (x * 2) + 1;
            rightChild = (x * 2) + 2;
        }
    }

    void *num = firstElementVal->value;
    free(firstElementVal);

    return num;
}