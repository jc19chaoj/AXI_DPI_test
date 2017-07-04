// dpi.c

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "dpi_record.h"
// #include "dpi.h"
// #include "svdpi.h"
#include "dpiheader.h"

// data structure for saving data temporary (defined in dpi_record.h)
record_data *record_1 = NULL;

void init() {
    int i = 0;
    record_1 = calloc(1, sizeof(*record_1));
    for (i=0; i<3; i++) {
        record_1->wr_addr_array[i] = calloc(1, sizeof(svLogicVecVal*));
        record_1->wr_data_array[i] = calloc(1, sizeof(svLogicVecVal*));
        record_1->wr_strb_array[i] = calloc(1, sizeof(svLogicVecVal*));
        record_1->wr_resp_array[i] = calloc(1, sizeof(svLogicVecVal*));
        record_1->rd_addr_array[i] = calloc(1, sizeof(svLogicVecVal*));
        record_1->rd_data_array[i] = calloc(1, sizeof(svLogicVecVal*));
        record_1->rd_resp_array[i] = calloc(1, sizeof(svLogicVecVal*));
    }
}

// random data generator with limitation
uint32_t random_data(int size) {
	srand(sim_time()+time(NULL));
	int max_value = 0;
	max_value = (int) pow(2.0, (double) size);
	return rand()%max_value;
}

// convert response data to string
char* interpret_response(const svLogicVecVal* response) {
    switch(response->aval) {
        case 0: return "OKAY";
        case 1: return "EXOKAY";
        case 2: return "SLVERR";
        case 3: return "DECERR";
        default: return "Error: Invalid response.";
    }
}

void set_dpi_signal(svLogicVecVal *signal, uint32_t data, int size) {
    // int size_temp = size;
    uint32_t mask = 0;
    if (size >= 32) {
        mask = 0xFFFFFFFF;
    } 
    else {
        mask = ~(0xFFFFFFFF << size);
    }   
    signal->aval = data & mask;
    signal->bval = 0x0;
}

void AXI1_master  (	svLogicVecVal		*wr_addr,
					svLogicVecVal		*wr_data,
					svLogicVecVal		*wr_strb,
					const svLogicVecVal	*wr_resp,
					svLogicVecVal		*rd_addr,
					const svLogicVecVal	*rd_data,
					const svLogicVecVal	*rd_resp 
					) 
{
	set_dpi_signal(wr_addr, random_data(32), 32);
	set_dpi_signal(wr_data, random_data(32), 32);
	set_dpi_signal(wr_strb, random_data(4), 4);
	set_dpi_signal(rd_addr, random_data(32), 32);
    
    // print sent data
    char wr_addr_msg[100] = {0};
	char wr_data_msg[100] = {0};
	char wr_strb_msg[100] = {0};
	char rd_addr_msg[100] = {0};
	sprintf(wr_addr_msg, "Write address is: 0x%08x", wr_addr->aval);
	sprintf(wr_data_msg, "Write data is: %d", wr_data->aval);
	sprintf(wr_strb_msg, "Write strobe is: %d", wr_strb->aval);
	sprintf(rd_addr_msg, "Read address is: 0x%08x", rd_addr->aval);
    dpi_print("Sent:");
	dpi_print(wr_addr_msg);
	dpi_print(wr_data_msg);
	dpi_print(wr_strb_msg);
	dpi_print(rd_addr_msg);
    
    // record sent data
    put_wr_addr(record_1, sim_time(), wr_addr);
    put_wr_data(record_1, sim_time(), wr_data);
    put_wr_strb(record_1, sim_time(), wr_strb);
    put_rd_addr(record_1, sim_time(), rd_addr);
    
    // print received data
    char wr_resp_msg[100] = {0};
	char rd_data_msg[100] = {0};
	char rd_resp_msg[100] = {0};
	sprintf(wr_resp_msg, "write response is: %s ----- Expected value is: %s ", interpret_response(wr_resp), interpret_response(get_wr_resp(record_1,sim_time()-2)));
	sprintf(rd_data_msg, "Read data is: %d ----- Expected value is: %d", rd_data->aval, get_rd_data(record_1,sim_time()-2)->aval);
	sprintf(rd_resp_msg, "Read response is: %s ----- Expected value is: %s", interpret_response(rd_resp), interpret_response(get_rd_resp(record_1,sim_time()-2)));
    dpi_print("Received:");
	dpi_print(wr_resp_msg);
	dpi_print(rd_data_msg);
	dpi_print(rd_resp_msg);
}

void AXI2_slave   (	const svLogicVecVal	*wr_addr,
					const svLogicVecVal	*wr_data,
					const svLogicVecVal	*wr_strb,
					svLogicVecVal		*wr_resp,
					const svLogicVecVal	*rd_addr,
					svLogicVecVal		*rd_data,
					svLogicVecVal		*rd_resp 
					) 
{
    set_dpi_signal(wr_resp, random_data(2), 2);
	set_dpi_signal(rd_data, random_data(32), 32);
	set_dpi_signal(wr_resp, random_data(2), 2);	
    
    // print sent data
    char wr_resp_msg[100] = {0};
	char rd_data_msg[100] = {0};
	char rd_resp_msg[100] = {0};
	sprintf(wr_resp_msg, "write response is: %s", interpret_response(wr_resp));
	sprintf(rd_data_msg, "Read data is: %d", rd_data->aval);
	sprintf(rd_resp_msg, "Read response is: %s", interpret_response(rd_resp));
    dpi_print("Sent:");
	dpi_print(wr_resp_msg);
	dpi_print(rd_data_msg);
	dpi_print(rd_resp_msg);
    
    // record sent data
    put_wr_resp(record_1, sim_time(), wr_resp);
    put_rd_data(record_1, sim_time(), rd_data);
    put_rd_resp(record_1, sim_time(), rd_resp);
    
    // print received data
	char wr_addr_msg[100] = {0};
	char wr_data_msg[100] = {0};
	char wr_strb_msg[100] = {0};
	char rd_addr_msg[100] = {0};
	sprintf(wr_addr_msg, "Write address is: 0x%08x ----- Expected value is: 0x%08x", wr_addr->aval, get_wr_addr(record_1,sim_time()-2)->aval);
	sprintf(wr_data_msg, "Write data is: %d ----- Expected value is: %d", wr_data->aval, get_wr_data(record_1,sim_time()-2)->aval);
	sprintf(wr_strb_msg, "Write strobe is: %d ----- Expected value is: %d", wr_strb->aval, get_wr_strb(record_1,sim_time()-2)->aval);
	sprintf(rd_addr_msg, "Read address is: 0x%08x ----- Expected value is: 0x%08x", rd_addr->aval, get_rd_addr(record_1,sim_time()-2)->aval);
    dpi_print("Received:");
	dpi_print(wr_addr_msg);
	dpi_print(wr_data_msg);
	dpi_print(wr_strb_msg);
	dpi_print(rd_addr_msg);
}