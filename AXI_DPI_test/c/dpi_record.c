// dpi_record.c

#include <stdio.h>
#include <stdlib.h>
#include "dpi_record.h"
//#include "svdpi.h"
#include "dpiheader.h"

// get data functions
svLogicVecVal *get_wr_addr(const record_data *record, size_t index) {
    return record->wr_addr_array[index%3];
}

svLogicVecVal *get_wr_data(const record_data *record, size_t index) {
    return record->wr_data_array[index%3];
}

svLogicVecVal *get_wr_strb(const record_data *record, size_t index) {
    return record->wr_strb_array[index%3];
}

svLogicVecVal *get_wr_resp(const record_data *record, size_t index) {
    return record->wr_resp_array[index%3];
}

svLogicVecVal *get_rd_addr(const record_data *record, size_t index) {
    return record->rd_addr_array[index%3];
}

svLogicVecVal *get_rd_data(const record_data *record, size_t index) {
    return record->rd_data_array[index%3];
}

svLogicVecVal *get_rd_resp(const record_data *record, size_t index) {
    return record->rd_resp_array[index%3];
}

// put data functions

void put_wr_addr(record_data *record, size_t index, svLogicVecVal *data) {
    record->wr_addr_array[index%3] = data;
}

void put_wr_data(record_data *record, size_t index, svLogicVecVal *data) {
    record->wr_data_array[index%3] = data;
}

void put_wr_strb(record_data *record, size_t index, svLogicVecVal *data) {
    record->wr_strb_array[index%3] = data;
}

void put_wr_resp(record_data *record, size_t index, svLogicVecVal *data) {
    record->wr_resp_array[index%3] = data;
}

void put_rd_addr(record_data *record, size_t index, svLogicVecVal *data) {
    record->rd_addr_array[index%3] = data;
}

void put_rd_data(record_data *record, size_t index, svLogicVecVal *data) {
    record->rd_data_array[index%3] = data;
}

void put_rd_resp(record_data *record, size_t index, svLogicVecVal *data) {
    record->rd_resp_array[index%3] = data;
}