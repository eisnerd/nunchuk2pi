/* by xerpi (c) 2013 */

#include "nunchuk.h"
#include "rfm.h"

static int rfm_initiated = 0;
static int rfm_run_thread     = 0;
static pthread_t rfm_thread;

void nunchuk_try_callback(int read_succes);

#define rfm_return_not_initiated() \
	if(!rfm_initiated) {    \
		return -2;             \
	}	

int rfm_read_data(struct nunchuk* n)
{
	rfm69_receive();
	char l = rfm69_getDataLen();
	//printf("recv %d %d\n", l, sizeof(struct nunchuk));
	if (l == sizeof(struct nunchuk)) {
		rfm69_getData((void*)n);
		//printf("recv %d %d\n", n->X, n->Y);
		nunchuk_try_callback(1);
	}
	else
		printf("awaiting data over rfm\n");
	return 1;
}

int rfm_init_rfm()
{
	rfm_return_not_initiated();

	rfm69_initialize(FREQUENCY, NODEID, NETWORKID);
	rfm69_encrypt(CRYPTPASS);
	rfm69_setPowerLevel(TXPOWER);

	return 1;
}

void* rfm_loop(void* n)
{
	rfm_init_rfm();
	while(rfm_run_thread) {
		if(rfm_read_data(n) > 0) {
			usleep(rfm_request_period);
		} else {
			while((rfm_init_rfm() < 0) && rfm_run_thread) {
				usleep(rfm_request_period * 100);
			}
		}
	}
	return n;
}

int rfm_init(struct nunchuk* n)
{
	if(rfm_initiated) {
		return 2;
	}

	rfm_run_thread = 1;	
	pthread_create(&rfm_thread, NULL, rfm_loop, (void*) n);
	
	rfm_initiated = 1;
	usleep(100);
	return 1;
}

int rfm_exit()
{
	rfm_return_not_initiated();
	rfm_run_thread = 0;
	pthread_cancel(rfm_thread);
	pthread_join(rfm_thread, NULL);
	rfm_initiated = 0;
	printf("rfm finished\n");
	return 1;
}


