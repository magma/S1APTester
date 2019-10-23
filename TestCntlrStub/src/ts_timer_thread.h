/*
 * ts_timer_thread.h
 * Header file for timer thread
 * Sep 25, 2013
 * root@davejingtian.org
 * http://davejingtian.org
 */

#ifndef TIMER_THREAD_INCLUDE
#define TIMER_THREAD_INCLUDE

/* Defines */
#define TIMER_THREAD_BLACKLIST_IPV4		0
#define TIMER_THREAD_BLACKLIST_MAC		1
#define TIMER_THREAD_WAKEUP_TIME		1 // seconds
#define TIMER_THREAD_BLACKLIST_BLOCK_TIME	20 // seconds

/* Methods */
void *timer_thread_main(void *data);

#endif
