// dpi_record.h

#ifndef DPI_RECORD_H
#define DPI_RECORD_H

#include <stdio.h>
#include <stdlib.h>
#include "svdpi.h"

typedef struct {
    svLogicVecVal *wr_addr_array[3];
    svLogicVecVal *wr_data_array[3];
    svLogicVecVal *wr_strb_array[3];
    svLogicVecVal *wr_resp_array[3];
    svLogicVecVal *rd_addr_array[3];
    svLogicVecVal *rd_data_array[3];
    svLogicVecVal *rd_resp_array[3];
} record_data;

// void init_record_data();

svLogicVecVal *get_wr_addr(const record_data *record, size_t index);
svLogicVecVal *get_wr_data(const record_data *record, size_t index);
svLogicVecVal *get_wr_strb(const record_data *record, size_t index);
svLogicVecVal *get_wr_resp(const record_data *record, size_t index);
svLogicVecVal *get_rd_addr(const record_data *record, size_t index);
svLogicVecVal *get_rd_data(const record_data *record, size_t index);
svLogicVecVal *get_rd_resp(const record_data *record, size_t index);

void put_wr_addr(record_data *record, size_t index, svLogicVecVal *data);
void put_wr_data(record_data *record, size_t index, svLogicVecVal *data);
void put_wr_strb(record_data *record, size_t index, svLogicVecVal *data);
void put_wr_resp(record_data *record, size_t index, svLogicVecVal *data);
void put_rd_addr(record_data *record, size_t index, svLogicVecVal *data);
void put_rd_data(record_data *record, size_t index, svLogicVecVal *data);
void put_rd_resp(record_data *record, size_t index, svLogicVecVal *data);


#endif