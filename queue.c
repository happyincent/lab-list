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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));

    /* check if malloc returns NULL */
    if (q == NULL) {
        return NULL;
    }

    /* clear allocated struct */
    memset(q, 0, sizeof(queue_t));

    INIT_LIST_HEAD(&(q->q_head));

    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* check if the q is NULL */
    if (q == NULL) {
        return;
    }

    struct list_head *li = NULL, *lis = NULL;
    list_ele_t *item;

    list_for_each_safe(li, lis, &(q->q_head))
    {
        item = list_entry(li, list_ele_t, list);
        if (item->value != NULL) {
            free(item->value);
            item->value = NULL;
        }
        list_del(&(item->list));
        free(item);
        item = NULL;
    }

    /* Free queue structure */
    free(q);
    q = NULL;
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
    /* check if the q is NULL */
    if (q != NULL) {
        /* allocate space for the new list element */
        list_ele_t *item = malloc(sizeof(list_ele_t));

        /* check if malloc returns NULL */
        if (item != NULL) {
            memset(item, 0, sizeof(list_ele_t));

            /* allocate space for the string */
            size_t len = strlen(s);
            item->value = malloc((len + 1) * sizeof(char));

            /* check if malloc returns NULL */
            if (item->value != NULL) {
                /* copy the string */
                memcpy(item->value, s, len);
                *(item->value + len) = '\0';

                /* insert head */
                list_add(&(item->list), &(q->q_head));

                /* increase size with 1 */
                ++q->q_size;

                // cppcheck-suppress memleak
                return true;
            }

            free(item);
            item = NULL;
        }
    }

    return false;
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
    /* check if the q is NULL */
    if (q != NULL) {
        /* allocate space for the new list element */
        list_ele_t *item = malloc(sizeof(list_ele_t));

        /* check if malloc returns NULL */
        if (item != NULL) {
            memset(item, 0, sizeof(list_ele_t));

            /* allocate space for the string */
            size_t len = strlen(s);
            item->value = malloc((len + 1) * sizeof(char));

            /* check if malloc returns NULL */
            if (item->value != NULL) {
                /* copy the string */
                memcpy(item->value, s, len);
                *(item->value + len) = '\0';

                /* insert tail */
                list_add_tail(&(item->list), &(q->q_head));

                /* increase size with 1 */
                ++q->q_size;

                // cppcheck-suppress memleak
                return true;
            }

            free(item);
            item = NULL;
        }
    }

    return false;
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
    if (q == NULL || list_empty(&q->q_head))
        return false;

    list_ele_t *item = list_first_entry(&(q->q_head), list_ele_t, list);

    if (item->value != NULL) {
        if (sp != NULL) {
            memset(sp, 0, bufsize);
            memcpy(sp, item->value, bufsize - 1);
        }
        free(item->value);
        item->value = NULL;
    }

    list_del(&(item->list));
    free(item);
    item = NULL;

    --q->q_size;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* Remember: It should operate in O(1) time */
    return (q == NULL) ? 0 : q->q_size;
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
    /* check if q is NULL or empty */
    if (q == NULL || list_empty(&q->q_head))
        return;

    /* iterate the queue to reverse each node's next and prev */
    struct list_head *li = NULL, *lis = NULL, *tmp = &(q->q_head);

    list_for_each_safe(li, lis, &(q->q_head))
    {
        li->prev = lis;
        li->next = tmp;
        tmp = li;
    }

    q->q_head.prev = q->q_head.next;
    q->q_head.next = tmp;
}