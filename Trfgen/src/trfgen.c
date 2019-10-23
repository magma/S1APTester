#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sysexits.h>
#include <stdint.h>
#include <sys/types.h>          
#include <sys/socket.h>

#include <iperf_api.h>
#include <iperf_util.h>
#include <iperf.h>
#include <locale.h>
#include <units.h>
#include "trfgen.x"

struct_test tstcfg[MAX_TEST_CFG+1];
static struct_processIds procIds;

void trfgen_init(void)
{
   int cnt;
   for(cnt=0; cnt<MAX_TEST_CFG+1; cnt++)
      memset(tstcfg,0,sizeof(struct_test));
}

void trfgen_configure_test(int test_id, struct_test test_parms)
{
   if(test_id > MAX_TEST_CFG){
      printf("\nERROR: Test id cannot be more than %d", MAX_TEST_CFG);
      return;
   }

   tstcfg[test_id].test_id = test_id;
   tstcfg[test_id].trfgen_type = test_parms.trfgen_type;
   tstcfg[test_id].traffic_type = test_parms.traffic_type;
   tstcfg[test_id].server_timeout = test_parms.server_timeout;
   tstcfg[test_id].duration = test_parms.duration;
}

void *start_server(void *test)
{
   /* start timer - server */
   /* execute server */
   /* timeout: return fail */
   /* print status */
   /* exit thread */
   /*int consecutive_errors;*/
   /*consecutive_errors = 0;*/
   /*    for (;;) {*/
   if ( iperf_run_server( test ) < 0 ) {
      printf("\n ERROR - %s\n\n", iperf_strerror( i_errno ) );}
   /*        ++consecutive_errors;
             if (consecutive_errors >= 5) {
             printf("ERROR: too many errors, exiting\n");
             break;
             }
             }else
             consecutive_errors = 0;
             */
   iperf_reset_test( test ); 
   /*    break;
         }
         */
   iperf_free_test( test );
   return NULL;
   }

void *start_client(void *test)
{
   /* execute client */
   /* print status */
   /* exit thread */

   if ( iperf_run_client( test ) < 0 ) {
      printf("\n ERROR - %s\n", iperf_strerror( i_errno ) );
      /*exit( EXIT_FAILURE );*/
   }
   iperf_reset_test( test );
   iperf_free_test( test );
   return NULL;
}

#ifdef TRFGEN_RESULTS
/**************************************************************************/

/**
 * iperf_stats_callback -- handles the statistic gathering for both the client and server
 *
 * XXX: This function needs to be updated to reflect the new code
 */


void
trfgen_iperf_stats_callback(struct iperf_test *test)
{
    struct iperf_stream *sp;
    struct iperf_stream_result *rp = NULL;
    struct iperf_interval_results *irp, temp;

    temp.omitted = test->omitting;
    SLIST_FOREACH(sp, &test->streams, streams) {
        rp = sp->result;

	temp.bytes_transferred = test->sender ? rp->bytes_sent_this_interval : rp->bytes_received_this_interval;
     
	irp = TAILQ_LAST(&rp->interval_results, irlisthead);
        /* result->end_time contains timestamp of previous interval */
        if ( irp != NULL ) /* not the 1st interval */
            memcpy(&temp.interval_start_time, &rp->end_time, sizeof(struct timeval));
        else /* or use timestamp from beginning */
            memcpy(&temp.interval_start_time, &rp->start_time, sizeof(struct timeval));
        /* now save time of end of this interval */
        gettimeofday(&rp->end_time, NULL);
        memcpy(&temp.interval_end_time, &rp->end_time, sizeof(struct timeval));
        temp.interval_duration = timeval_diff(&temp.interval_start_time, &temp.interval_end_time);
        //temp.interval_duration = timeval_diff(&temp.interval_start_time, &temp.interval_end_time);
	if (test->protocol->id == Ptcp) {
	    if ( has_tcpinfo()) {
		save_tcpinfo(sp, &temp);
		if (test->sender && test->sender_has_retransmits) {
		    long total_retrans = get_total_retransmits(&temp);
		    temp.interval_retrans = total_retrans - rp->stream_prev_total_retrans;
		    rp->stream_retrans += temp.interval_retrans;
		    rp->stream_prev_total_retrans = total_retrans;

		    temp.snd_cwnd = get_snd_cwnd(&temp);
		}
	    }
	} else {
	    if (irp == NULL) {
		temp.interval_packet_count = sp->packet_count;
		temp.interval_outoforder_packets = sp->outoforder_packets;
		temp.interval_cnt_error = sp->cnt_error;
	    } else {
		temp.interval_packet_count = sp->packet_count - irp->packet_count;
		temp.interval_outoforder_packets = sp->outoforder_packets - irp->outoforder_packets;
		temp.interval_cnt_error = sp->cnt_error - irp->cnt_error;
	    }
	    temp.packet_count = sp->packet_count;
	    temp.jitter = sp->jitter;
	    temp.outoforder_packets = sp->outoforder_packets;
	    temp.cnt_error = sp->cnt_error;
	}
        add_to_interval_list(rp, &temp);
        rp->bytes_sent_this_interval = rp->bytes_received_this_interval = 0;
    }
}

void
trfgen_print_results(struct iperf_test *test)
{
#if 1   
    int total_retransmits = 0;
    int total_packets = 0, lost_packets = 0;
    char ubuf[UNIT_LEN];
    char nbuf[UNIT_LEN];
    /*struct stat sb;*/
    char sbuf[UNIT_LEN];
    struct iperf_stream *sp = NULL;
    iperf_size_t bytes_sent, total_sent = 0;
    iperf_size_t bytes_received, total_received = 0;
    double start_time, end_time, avg_jitter = 0.0, lost_percent;
    double bandwidth;

    /* print final summary for all intervals */

    start_time = 0.;
    sp = SLIST_FIRST(&test->streams);
    end_time = timeval_diff(&sp->result->start_time, &sp->result->end_time);
    SLIST_FOREACH(sp, &test->streams, streams) {
        bytes_sent = sp->result->bytes_sent;
        bytes_received = sp->result->bytes_received;
        total_sent += bytes_sent;
        total_received += bytes_received;

        if (test->protocol->id == Ptcp) {
	    if (test->sender_has_retransmits) {
		total_retransmits += sp->result->stream_retrans;
	    }
	} else {
            total_packets += (sp->packet_count - sp->omitted_packet_count);
            lost_packets += sp->cnt_error;
            avg_jitter += sp->jitter;
        }

	unit_snprintf(ubuf, UNIT_LEN, (double) bytes_sent, 'A');
	bandwidth = (double) bytes_sent / (double) end_time;
	unit_snprintf(nbuf, UNIT_LEN, bandwidth, test->settings->unit_format);
	if (test->protocol->id == Ptcp) {
	    if (test->sender_has_retransmits) {
		/* Summary, TCP with retransmits. */
		    iprintf(test, report_bw_retrans_format, sp->socket, start_time, end_time, ubuf, nbuf, sp->result->stream_retrans, report_sender);
	    } else {
		/* Summary, TCP without retransmits. */
		    iprintf(test, report_bw_format, sp->socket, start_time, end_time, ubuf, nbuf, report_sender);
	    }
	} else {
	    /* Summary, UDP. */
	    lost_percent = 100.0 * sp->cnt_error / (sp->packet_count - sp->omitted_packet_count);
		iprintf(test, report_bw_udp_format, sp->socket, start_time, end_time, ubuf, nbuf, sp->jitter * 1000.0, sp->cnt_error, (sp->packet_count - sp->omitted_packet_count), lost_percent, "");
		if (test->role == 'c')
		    iprintf(test, report_datagrams, sp->socket, (sp->packet_count - sp->omitted_packet_count));
		if (sp->outoforder_packets > 0)
		    iprintf(test, report_sum_outoforder, start_time, end_time, sp->cnt_error);
	}

	unit_snprintf(ubuf, UNIT_LEN, (double) bytes_received, 'A');
	bandwidth = (double) bytes_received / (double) end_time;
	unit_snprintf(nbuf, UNIT_LEN, bandwidth, test->settings->unit_format);
	if (test->protocol->id == Ptcp) {
		iprintf(test, report_bw_format, sp->socket, start_time, end_time, ubuf, nbuf, report_receiver);
	}
    }
    if (test->num_streams > 1 || test->json_output) {
        unit_snprintf(ubuf, UNIT_LEN, (double) total_sent, 'A');
	bandwidth = (double) total_sent / (double) end_time;
        unit_snprintf(nbuf, UNIT_LEN, bandwidth, test->settings->unit_format);
        if (test->protocol->id == Ptcp) {
	    if (test->sender_has_retransmits) {
		/* Summary sum, TCP with retransmits. */
		if (test->json_output)
		    cJSON_AddItemToObject(test->json_end, "sum_sent", iperf_json_printf("start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f  retransmits: %d", (double) start_time, (double) end_time, (double) end_time, (int64_t) total_sent, bandwidth * 8, (int64_t) total_retransmits));
		else
		    iprintf(test, report_sum_bw_retrans_format, start_time, end_time, ubuf, nbuf, total_retransmits, report_sender);
	    } else {
		/* Summary sum, TCP without retransmits. */
		if (test->json_output)
		    cJSON_AddItemToObject(test->json_end, "sum_sent", iperf_json_printf("start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f", (double) start_time, (double) end_time, (double) end_time, (int64_t) total_sent, bandwidth * 8));
		else
		    iprintf(test, report_sum_bw_format, start_time, end_time, ubuf, nbuf, report_sender);
	    }
            unit_snprintf(ubuf, UNIT_LEN, (double) total_received, 'A');
	    bandwidth = (double) total_received / (double) end_time;
            unit_snprintf(nbuf, UNIT_LEN, bandwidth, test->settings->unit_format);
	    if (test->json_output)
		cJSON_AddItemToObject(test->json_end, "sum_received", iperf_json_printf("start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f", (double) start_time, (double) end_time, (double) end_time, (int64_t) total_received, bandwidth * 8));
	    else
		iprintf(test, report_sum_bw_format, start_time, end_time, ubuf, nbuf, report_receiver);
        } else {
	    /* Summary sum, UDP. */
            avg_jitter /= test->num_streams;
	    lost_percent = 100.0 * lost_packets / total_packets;
	    if (test->json_output)
		cJSON_AddItemToObject(test->json_end, "sum", iperf_json_printf("start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f  jitter_ms: %f  lost_packets: %d  packets: %d  lost_percent: %f", (double) start_time, (double) end_time, (double) end_time, (int64_t) total_sent, bandwidth * 8, (double) avg_jitter * 1000.0, (int64_t) lost_packets, (int64_t) total_packets, (double) lost_percent));
	    else
		iprintf(test, report_sum_bw_udp_format, start_time, end_time, ubuf, nbuf, avg_jitter * 1000.0, lost_packets, total_packets, lost_percent, "");
        }
    }

    if (test->json_output)
	cJSON_AddItemToObject(test->json_end, "cpu_utilization_percent", iperf_json_printf("host_total: %f  host_user: %f  host_system: %f  remote_total: %f  remote_user: %f  remote_system: %f", (double) test->cpu_util[0], (double) test->cpu_util[1], (double) test->cpu_util[2], (double) test->remote_cpu_util[0], (double) test->remote_cpu_util[1], (double) test->remote_cpu_util[2]));
    else {
	if (test->verbose) {
	    iprintf(test, report_cpu, report_local, test->sender?report_sender:report_receiver, test->cpu_util[0], test->cpu_util[1], test->cpu_util[2], report_remote, test->sender?report_receiver:report_sender, test->remote_cpu_util[0], test->remote_cpu_util[1], test->remote_cpu_util[2]);
	}

	/* Print server output if we're on the client and it was requested/provided */
	if (test->role == 'c' && iperf_get_test_get_server_output(test)) {
	    if (test->json_server_output) {
		iprintf(test, "\nServer JSON output:\n%s\n", cJSON_Print(test->json_server_output));
		cJSON_Delete(test->json_server_output);
		test->json_server_output = NULL;
	    }
	    if (test->server_output_text) {
		iprintf(test, "\nServer output:\n%s\n", test->server_output_text);
		test->server_output_text = NULL;
	    }
	}
    }
#endif
}

/**************************************************************************/

/**
 * iperf_reporter_callback -- handles the report printing
 *
 */

void trfgen_iperf_reporter_callback(struct iperf_test *test)
{
   switch (test->state) {
      case TEST_RUNNING:
      case STREAM_RUNNING:
         /* print interval results for each stream 
            iperf_print_intermediate(test);
            */
         break;
      case DISPLAY_RESULTS:
         /*
            iperf_print_intermediate(test);
            */
         trfgen_print_results(test);
         break;
   } 
}
#endif

void trfgen_start_test(int test_id, char *host_ip, char *bind_ip, char *host_port)
{
   int port;
/*   int s; */
#ifndef SRV_FRM_API
   char cmd[100];
   memset(cmd,'\0',100);
   int pid;
#endif
   /* create iperf test config structure */
   struct iperf_test *test;
#if 0
   pthread_t exec_thr;
   pthread_attr_t attr;
#endif
   port = atoi(host_port);

   test = iperf_new_test();
   if ( test == NULL ) {
      printf( "\nfailed to create test\n");
      return;
   }
   iperf_defaults( test );
#ifdef TRFGEN_RESULTS
   test->reporter_callback = trfgen_iperf_reporter_callback;
   test->stats_callback = trfgen_iperf_stats_callback;
#endif
   iperf_set_verbose( test, 0 );

   if(tstcfg[test_id].traffic_type == TCP)
      set_protocol(test, Ptcp);
   else if (tstcfg[test_id].traffic_type == UDP)
      set_protocol(test, Pudp);
   else
      printf("\n Error: protocol type is not supported");

   if(tstcfg[test_id].trfgen_type == SERVER){
#if 0
      iperf_set_test_role( test, 's' );
      iperf_set_test_bind_address(test, bind_ip);
      iperf_set_test_server_port( test, port );
      iperf_set_test_duration( test, tstcfg[test_id].duration);

      /* create server thread */
      pthread_attr_init(&attr);
      /* mt021.201 - Addition to set stack size */
      pthread_attr_setstacksize(&attr, (size_t)0);
      pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
      pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
      if((s = pthread_create(&exec_thr, &attr, start_server, (void*)test))!=0){
         printf("\n Error: Thread creation failed");
         return;
      }
#endif
      pid = fork();
      procIds.pids[procIds.noOfPids++] = pid;
      if(pid == 0)
      {
         iperf_set_test_role( test, 's' );
         iperf_set_test_bind_address(test, bind_ip);
         iperf_set_test_server_port( test, port );
         iperf_set_test_duration( test, tstcfg[test_id].duration);
         start_server((void*)test);
         exit(0);
      }
      else if(pid < 0)
      {
         printf("\nfailed to fork server\n");
      }

   }
   else if (tstcfg[test_id].trfgen_type == CLIENT){
      iperf_set_test_server_hostname( test, host_ip);
      iperf_set_test_bind_address(test, bind_ip);
      iperf_set_test_server_port( test, port );
      iperf_set_test_role( test, 'c' );

      iperf_set_test_omit( test, TCP_OMIT );
      iperf_set_test_duration( test, tstcfg[test_id].duration);
      iperf_set_test_reporter_interval( test, tstcfg[test_id].duration );
      iperf_set_test_stats_interval( test, tstcfg[test_id].duration );
      if(tstcfg[test_id].traffic_type == UDP)
      {
         iperf_set_test_rate(test, 500000);
         iperf_set_test_blksize( test, 1000 );
      }
      else
      {
         iperf_set_test_rate(test, 5000);
         iperf_set_test_socket_bufsize(test,200);
      }
#if 0
      /* create client thread */
      pthread_attr_init(&attr);
      /* mt021.201 - Addition to set stack size */
      pthread_attr_setstacksize(&attr, (size_t)0);
      pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
      pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

      if((s = pthread_create(&exec_thr, &attr, start_client, (void*)test))!=0){
         printf("\n Error: Thread creation failed");
         return;
      }
#endif
      pid = fork();
      procIds.pids[procIds.noOfPids++] = pid;
      if(pid == 0)
      {
         start_client((void*)test);
         exit(0);
      }
      else if(pid < 0)
      {
         printf("\nfailed to fork client\n");
      }
   }
   else
      printf("\n Error: Invalid Traffic gen type");
 return ;
}

void cleaningAllProcessIds(void)
{
   char cmd[20];
   
   while(procIds.noOfPids)
   {
      /*kill process;*/
      memset(cmd,'\0', 20);
      sprintf(cmd, "kill -9 %d", procIds.pids[procIds.noOfPids - 1]);
      system(cmd);
      procIds.noOfPids--;
   }
}
