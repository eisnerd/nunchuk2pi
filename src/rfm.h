/* by xerpi (c) 2013 */

#ifndef _RFM_H_
#define _RFM_H_

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include "rfm69.h"

#define FREQUENCY RF69_868MHZ
#define NODEID 2
#define NETWORKID 100
#define TXPOWER 29
// A 16 bit password
#define CRYPTPASS "0123456789054321"
#define rfm_request_period 25

int rfm_init(struct nunchuk* n);
int rfm_exit();

#endif
