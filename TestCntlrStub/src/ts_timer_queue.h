/*
 * timer_queue.h
 * Header file for timer queue implementation
 * Sep 24, 2013
 * root@davejingtian.org
 * http://davejingtian.org
 */
#ifndef TIMER_QUEUE_INCLUDE
#define TIMER_QUEUE_INCLUDE

#include <time.h>
#ifndef UNUSED
#define TIMER_QUEUE_IPV4_STRING_LEN	sizeof("255.255.255.255")
#define TIMER_QUEUE_MAC_STRING_LEN	sizeof("ff:ff:ff:ff:ff:ff")
#define TIMER_QUEUE_MSG_TYPE_IPV4	0
#define TIMER_QUEUE_MSG_TYPE_MAC	1
#endif
/* Define the timer queue msg */
typedef struct _timer_queue_msg
{
#ifndef UNUSED
	int type;
	union
	{
		char ipv4[TIMER_QUEUE_IPV4_STRING_LEN];
		char mac[TIMER_QUEUE_MAC_STRING_LEN];
	};
#else
        int ueId;
        void (*callbk)(unsigned char );
#endif
	time_t timer;
} timer_queue_msg;

#define TIMER_QUEUE_MSG_LEN		sizeof(timer_queue_msg)
#define TIMER_QUEUE_MSG_NUM_MAX		100
#define TIMER_QUEUE_SIZE		(TIMER_QUEUE_MSG_LEN*TIMER_QUEUE_MSG_NUM_MAX)
#define TIMER_QUEUE_NUM_MAX		100

/* Methods */

/* Check if the index of queue is valid */
/* 1 - valid; 0 otherwise */
int tq_validate_queue_index(int queue_index);

/* Display the tiemr queue msg */
void tq_display_msg(timer_queue_msg *tqm);

/* Display the whole queue */
void tq_display_queue(int queue_index);

/* Display the whole queue all */
void tq_display_queue_all(void);

/* Init the timer queue all */
void tq_init_queue_all(void);

/* Free the memory of queue all */
void tq_destroy_queue_all(void);

/* Clear all the msg in the queue all */
void tq_clear_queue_all(void);

/* Init the timer queue */
void tq_init_queue(int queue_index);

/* Free the memory of queue */
void tq_destroy_queue(int queue_index);

/* Clear all the msgs in the queue */
void tq_clear_queue(int queue_index);

/* Add msg into queue */
int tq_add_msg(timer_queue_msg *tqm, int queue_index);

/* Get the number of msg in the queue */
int tq_get_msg_num(int queue_index);

/* Get the first msg in the queue */
timer_queue_msg *tq_get_head_msg(int queue_index);

/* Remove the first msg in the queue */
void tq_del_head_msg(int queue_index);

/* Get the msg in the queue based on IPv4/MAC */
timer_queue_msg *tq_get_msg_on_str(int type, char *str, int queue_index);

/* Remove the msg in the queue based on IPv4/MAC */
/* The reason we do not use msg index is that it may change
in the multi-thread env. Always try to find the msg directly
instead of using msg index!
-daveti
*/
void tq_del_msg_on_str(int type, char *str, int queue_index);

#endif
