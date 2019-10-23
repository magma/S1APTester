/*
 * timer_queue.c
 * Source file for timer queue implementation
 * Sep 26, 2013
 * Added pthread mutex for thread safing
 * Sep 24, 2013
 * root@davejingtian.org
 * http://davejingtian.org
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include "ts_timer_queue.h"

/* Global var (queue) */
static unsigned char *timer_queue[TIMER_QUEUE_NUM_MAX];
static unsigned char *timer_queue_ptr[TIMER_QUEUE_NUM_MAX];	/* Always points to the next available space */
/* To avoid potential race conditions, only one mutex is used here */
pthread_mutex_t timer_queue_mutex;
/* NOTE: the lock/unlock operations are NOT implemented
in these timer queue functions as the application may have
a better granuality to define how to use the locks.
Sep 26, 2013
-daveti
*/

/* Methods */
#define TIMER_QUEUE_CHECK_INDEX_VOID(queue_index)					\
	do {										\
		if (tq_validate_queue_index(queue_index) != 1) {			\
			printf("Error: invalid queue index [%d]\n", queue_index);	\
               		return; }							\
        } while(0);						


/* Check if the index of queue is valid */
/* 1 - valid; 0 otherwise */
int tq_validate_queue_index(int queue_index)
{
	if (queue_index >= 0 && queue_index < TIMER_QUEUE_NUM_MAX)
		return 1;
	return 0;
}

/* Display the tiemr queue msg */
void tq_display_msg(timer_queue_msg *tqm)
{
#ifndef UNUSED
	char *ptr;
	if (tqm->type == TIMER_QUEUE_MSG_TYPE_IPV4)
		ptr = tqm->ipv4;
	else if (tqm->type == TIMER_QUEUE_MSG_TYPE_MAC)
		ptr = tqm->mac;
	else
	{
		printf("Error: invalid msg type [%d]\n", tqm->type);
		return;
	}
	printf("type [%d], content [%s], timer [%lu]\n",
		tqm->type, ptr, tqm->timer);
#else 
	printf("ueId [%d], timer [%lu]\n",
		tqm->ueId, tqm->timer);
#endif    
}

/* Display the whole queue */
void tq_display_queue(int queue_index)
{
	int i;
	int total;
	timer_queue_msg *tqm;

	TIMER_QUEUE_CHECK_INDEX_VOID(queue_index);
	total = tq_get_msg_num(queue_index);
	printf("timer queue [%d] has [%d] msgs in total\n", queue_index, total);

	tqm = (timer_queue_msg *)timer_queue[queue_index];
	for (i = 0; i < total; i++)
	{
		tq_display_msg(&(tqm[i]));
	}
}

/* Display the whole queue all */
void tq_display_queue_all(void)
{
	int i;
	for (i = 0; i < TIMER_QUEUE_NUM_MAX; i++)
	{
		tq_display_queue(i);
	}
}

/* Init the timer queue all */
void tq_init_queue_all(void)
{
	int i;
	for (i = 0; i < TIMER_QUEUE_NUM_MAX; i++)
	{
		tq_init_queue(i);
	}

	/* Init the mutex */
	pthread_mutex_init(&timer_queue_mutex, NULL);
}

/* Free the memory of queue all */
void tq_destroy_queue_all(void)
{
	int i;
	for (i = 0; i < TIMER_QUEUE_NUM_MAX; i++)
	{
		tq_destroy_queue(i);
	}

	/* Destroy the mutex */
	pthread_mutex_destroy(&timer_queue_mutex);
}

/* Clear all the msg in the queue all */
void tq_clear_queue_all(void)
{
	int i;
	for (i = 0; i < TIMER_QUEUE_NUM_MAX; i++)
	{
		tq_clear_queue(i);
	}
}

/* Init the timer queue */
void tq_init_queue(int queue_index)
{
	TIMER_QUEUE_CHECK_INDEX_VOID(queue_index);
	timer_queue[queue_index] = (unsigned char *)malloc(TIMER_QUEUE_SIZE);
	timer_queue_ptr[queue_index] = timer_queue[queue_index];
}

/* Free the memory of queue */
void tq_destroy_queue(int queue_index)
{
	TIMER_QUEUE_CHECK_INDEX_VOID(queue_index);
	if (timer_queue[queue_index] != NULL)
		free(timer_queue[queue_index]);
}

/* Clear all the msgs in the queue */
void tq_clear_queue(int queue_index)
{
	TIMER_QUEUE_CHECK_INDEX_VOID(queue_index);
	timer_queue_ptr[queue_index] = timer_queue[queue_index];
}

/* Add msg into queue */
int tq_add_msg(timer_queue_msg *tqm, int queue_index)
{
	if (tq_validate_queue_index(queue_index) == 0)
	{
		printf("Error: invalid queue index [%d]\n", queue_index);
		return -1;
	}

	if (tq_get_msg_num(queue_index) != TIMER_QUEUE_MSG_NUM_MAX)
	{
		memcpy(timer_queue_ptr[queue_index], (void *)tqm, TIMER_QUEUE_MSG_LEN);
		timer_queue_ptr[queue_index] += TIMER_QUEUE_MSG_LEN;
		return 0;
	}
	else
	{
		printf("Error: timer queue [%d] is full (unable to add new msg)\n", queue_index);
		return -1;
	}
}

/* Get the number of msg in the queue */
int tq_get_msg_num(int queue_index)
{
	if (tq_validate_queue_index(queue_index) == 0)
	{
		printf("Error: invalid queue index [%d]\n", queue_index);
		return -1;
	}
	return (timer_queue_ptr[queue_index] - timer_queue[queue_index])/TIMER_QUEUE_MSG_LEN;
}

/* Get the first msg in the queue */
timer_queue_msg *tq_get_head_msg(int queue_index)
{
	if (tq_validate_queue_index(queue_index) == 0)
	{
		printf("Error: invalid queue index [%d]\n", queue_index);
		return NULL;
	}

	if (tq_get_msg_num(queue_index) == 0)
		return NULL;

	return (timer_queue_msg *)timer_queue[queue_index];
}

/* Remove the first msg in the queue */
void tq_del_head_msg(int queue_index)
{
	TIMER_QUEUE_CHECK_INDEX_VOID(queue_index);
	if (timer_queue_ptr[queue_index] != timer_queue[queue_index])
	{
		memmove(timer_queue[queue_index],
			(timer_queue[queue_index] + TIMER_QUEUE_MSG_LEN),
			(timer_queue_ptr[queue_index] - timer_queue[queue_index] - TIMER_QUEUE_MSG_LEN));
		timer_queue_ptr[queue_index] -= TIMER_QUEUE_MSG_LEN;
	}
}

#ifndef UNUSED
/* Get the msg in the queue based on IPv4/MAC */
timer_queue_msg *tq_get_msg_on_str(int type, char *str, int queue_index)
{
	int i;
	timer_queue_msg *tqm;

	if (type != TIMER_QUEUE_MSG_TYPE_IPV4 && type != TIMER_QUEUE_MSG_TYPE_MAC)
	{
		printf("Error: invalid msg type [%d]\n", type);
		return NULL;
	}

	if (tq_validate_queue_index(queue_index) == 0)
	{
		printf("Error: invalid queue index [%d]\n", queue_index);
		return NULL;
	}

	tqm = (timer_queue_msg *)timer_queue[queue_index];
	for (i = 0; i < tq_get_msg_num(queue_index); i++)
	{
		if (type == TIMER_QUEUE_MSG_TYPE_IPV4)
		{
			if (strcasecmp(tqm[i].ipv4, str) == 0)
				return tqm;
		}
		else
		{
			if (strcasecmp(tqm[i].mac, str) == 0)
				return tqm;
		}
	}

	return NULL;
}
#endif

/* Remove the msg in the queue based on IPv4/MAC */
/* The reason we do not use msg index is that it may change
in the multi-thread env. Always try to find the msg directly
instead of using msg index!
-daveti
*/
void tq_del_msg_on_str(int type, char *str, int queue_index)
{
#ifndef UNUSED
        int i;
#endif
        timer_queue_msg *tqm;
#ifndef UNUSED
        if (type != TIMER_QUEUE_MSG_TYPE_IPV4 && type != TIMER_QUEUE_MSG_TYPE_MAC)
        {
                printf("Error: invalid msg type [%d]\n", type);
                return;
        }
#endif
	TIMER_QUEUE_CHECK_INDEX_VOID(queue_index);

        tqm = (timer_queue_msg *)timer_queue[queue_index];
#ifndef UNUSED
        for (i = 0; i < tq_get_msg_num(queue_index); i++)
        {
                if (type == TIMER_QUEUE_MSG_TYPE_IPV4)
                {
                        if (strcasecmp(tqm[i].ipv4, str) == 0)
			{
				memmove((void *)tqm,
					(void *)(tqm + TIMER_QUEUE_MSG_LEN),
					(timer_queue_ptr[queue_index] - (unsigned char *)tqm - TIMER_QUEUE_MSG_LEN));
				timer_queue_ptr[queue_index] -= TIMER_QUEUE_MSG_LEN;
				return;
			}
                }
                else
                {
                        if (strcasecmp(tqm[i].mac, str) == 0)
                        {
                                memmove((void *)tqm,
                                        (void *)(tqm + TIMER_QUEUE_MSG_LEN),
                                        (timer_queue_ptr[queue_index] - (unsigned char *)tqm - TIMER_QUEUE_MSG_LEN));
                                timer_queue_ptr[queue_index] -= TIMER_QUEUE_MSG_LEN;
				return;
                        }
                }
        }
#else
	memmove((void *)tqm,
	(void *)(tqm + TIMER_QUEUE_MSG_LEN),
	(timer_queue_ptr[queue_index] - (unsigned char *)tqm - TIMER_QUEUE_MSG_LEN));
	timer_queue_ptr[queue_index] -= TIMER_QUEUE_MSG_LEN;
	return;
#endif
}
