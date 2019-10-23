#include "../src/trfgen.x"

extern void trfgen_init(void);
extern void trfgen_configure_test(int test_id, struct_test test_parms);
extern void trfgen_start_test(int test_id, char *host_ip, char *host_port);


void main(void)
{
	struct_test test_parms;
        int i;
	
        trfgen_init();

	test_parms.test_id = 1;
	test_parms.duration = 15;
	test_parms.trfgen_type = SERVER;
	test_parms.traffic_type = TCP;
		
	trfgen_configure_test(test_parms.test_id,test_parms);

	test_parms.test_id = 2;
	test_parms.duration = 5;
	test_parms.trfgen_type = CLIENT;
	test_parms.traffic_type = TCP;

	trfgen_configure_test(test_parms.test_id,test_parms);
	
	for(i=0;i<3;i++){	
        	trfgen_start_test(1,"10.0.2.15","2000");
        	sleep(3); /* Waiting for servers to be started before starting clients*/
		trfgen_start_test(2,"10.0.2.15","2000");
       		sleep(10); /* waiting for the test to complete */
	}
}
