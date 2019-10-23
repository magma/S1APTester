
#define MAX_TEST_CFG 10
#define TCP_OMIT 0 /*omit the first n seconds (to ignore TCP slowstart)*/
#define UNIT_LEN 32
#define MAX_PROCESS 352 /*Max Ue is 32 and Max IP per Ue is 11*/
#if 0
#define TRFGEN_RESULTS
#endif

typedef enum Trfgen_type{
	SERVER=0,
	CLIENT
}trfgen_type;

typedef enum Trf_type{
	TCP=0,
	UDP
}trf_type;

typedef struct _struct_test{

	int test_id;
	trfgen_type trfgen_type;
	trf_type traffic_type;
	int duration;
	int server_timeout;
} struct_test;	
typedef struct _struct_processIds{

	int pids[MAX_PROCESS];
        int noOfPids; 
} struct_processIds;

/**< Api function declaration */

void trfgen_init(void);
void trfgen_configure_test(int test_id, struct_test test_parms);
void trfgen_start_test(int test_id, char *host_ip, char *bind_ip, char *host_port);
void cleaningAllProcessIds(void);
