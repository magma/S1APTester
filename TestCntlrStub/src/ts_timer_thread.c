/*
 * timer_thread.h
 * Source file for timer thread
 * The main job of timer thread is to wake up periodically to check
 * out the queues and to see if some timers fires for the stuffs in
 * the queue. If so, do the sth and remove the object from the queue.
 * Sep 26, 2013
 * root@davejingtian.org
 * http://davejingtian.org
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "ts_timer_queue.h"
#include "ts_timer_thread.h"

extern pthread_mutex_t timer_queue_mutex;
extern void tsSendPeriodicTau(unsigned char ueId);

/* Methods */
void *timer_thread_main(void *data)
{
   int i;
   int j;
   timer_queue_msg *tqm;

   while (1)
   {
      /* Lock */
      pthread_mutex_lock(&timer_queue_mutex);
      /*printf("timer thread: got the timer queue lock [%lu]\n", time(NULL));*/

      /* Go thru the queues */
      for (i = 0; i < TIMER_QUEUE_NUM_MAX; i++)
      {
         tqm = tq_get_head_msg(i);
         for (j = 0; j < tq_get_msg_num(i); j++)
         {
            if (tqm[j].timer <= time(NULL))
            {
               /*printf("timer thread: remove the msg at time [%lu] in queue [%d]\n", time(NULL), i);*/
               if(tqm[j].callbk != NULL)
                  tqm[j].callbk(tqm[j].ueId);
               tq_display_msg(&(tqm[j]));
#ifndef UNUSED
               if (tqm[j].type == TIMER_QUEUE_MSG_TYPE_MAC)
                  tq_del_msg_on_str(tqm[j].type, tqm[j].mac, i);
               else
                  tq_del_msg_on_str(tqm[j].type, tqm[j].ipv4, i);
#else
               tq_del_msg_on_str(0, NULL, i);
#endif
            }
            else
               break;
         }
      }

      /* Unlock */
      pthread_mutex_unlock(&timer_queue_mutex);
      /*printf("timer thread: released the timer queue lock [%lu]\n", time(NULL));*/

#ifndef UNUSED
      sleep(TIMER_THREAD_WAKEUP_TIME);
#else
      sleep(1);
#endif
   }
}
