/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = (queue_t*)malloc(sizeof(queue_t));
    if(q != NULL){
        q->tail = NULL;
    	q->head = NULL;
    	q->size = 0;
    }
    return q;
}

static list_ele_t *elem_free(list_ele_t *e) {
  if (!e) {
    return NULL;
  }
  free(e->value);
  list_ele_t *next_e = e->next;
  free(e);
  return next_e;
}
/* Free all storage used by queue */
void q_free(queue_t *q)
{
	if(q == NULL) return;
	while(q->head != NULL){
		q->head = elem_free(q->head);
	}
	free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
	list_ele_t *newh = (list_ele_t*)malloc(sizeof(list_ele_t));
	if(newh == NULL){
		return false;
	}
	
	size_t length = strlen(s);
	newh->value = malloc((length+1) * sizeof(char));

	if(newh->value == NULL){
		free(newh);
		return false;
	}

	strcpy(newh->value, s);
	newh->value[length] = 0;

	newh->next = q->head;
	
	if(q->head == NULL){
		q->tail = newh;
	}

	q->head = newh;
	q->size++;
	return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
	
	if(q == NULL){
		return false;
	}

	list_ele_t *newt = (list_ele_t*)malloc(sizeof(list_ele_t));
	if(newt == NULL){
		return false;
	}

	size_t length = strlen(s);
	newt->value = (char*)malloc((length+1) * sizeof(char));

	if(newt->value == NULL){
		free(newt);
		return false;
	}

	strcpy(newt->value, s);	
	newt->value[length] = 0;
	newt->next = NULL;

	if(q->head == NULL){
		q->head = newt;
		q->tail = newt;
	}else{
		q->tail->next = newt;
		q->tail = newt;
	}
	q->size++;
	return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
	if(q == NULL || q->size <= 0) return false;
	
	if(bufsize > 0){
		size_t output_length = strlen(q->head->value)+1;
		strncpy(sp, q->head->value, (output_length <= bufsize) ? output_length : bufsize);		
	}
	
	q->head = elem_free(q->head);
	q->size--;

	return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q){
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{	
	if(q == NULL) return;

	list_ele_t* next = NULL;
	list_ele_t* last_valid = NULL;
	list_ele_t* current = q->head;

	while(current){	
		next = current->next;
		current->next = last_valid;
		last_valid = current;
		current = next;
	}
	q->tail = q->head;
	q->head = last_valid;
}

