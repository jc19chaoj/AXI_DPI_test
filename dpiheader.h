/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                         */
/*  \   \        Copyright (c) 2003-2013 Xilinx, Inc.                 */
/*  /   /        All Right Reserved.                                  */
/* /---/   /\                                                         */
/* \   \  /  \                                                        */
/*  \___\/\___\                                                       */
/**********************************************************************/


/* NOTE: DO NOT EDIT. AUTOMATICALLY GENERATED FILE. CHANGES WILL BE LOST. */

#ifndef DPI_H
#define DPI_H
#ifdef __cplusplus
#define DPI_LINKER_DECL  extern "C" 
#else
#define DPI_LINKER_DECL
#endif

#include "svdpi.h"



/* Imported (by SV) function */
DPI_LINKER_DECL DPI_DLLESPEC 
 void init(
);


/* Imported (by SV) function */
DPI_LINKER_DECL DPI_DLLESPEC 
 void AXI2_slave(
	const svLogicVecVal wr_addr[SV_PACKED_DATA_NELEMS(32)] ,
	const svLogicVecVal wr_data[SV_PACKED_DATA_NELEMS(32)] ,
	const svLogicVecVal wr_strb[SV_PACKED_DATA_NELEMS(4)] ,
	svLogicVecVal wr_resp[SV_PACKED_DATA_NELEMS(2)] ,
	const svLogicVecVal rd_addr[SV_PACKED_DATA_NELEMS(32)] ,
	svLogicVecVal rd_data[SV_PACKED_DATA_NELEMS(32)] ,
	svLogicVecVal rd_resp[SV_PACKED_DATA_NELEMS(2)]);


/* Imported (by SV) function */
DPI_LINKER_DECL DPI_DLLESPEC 
 void AXI1_master(
	svLogicVecVal wr_addr[SV_PACKED_DATA_NELEMS(32)] ,
	svLogicVecVal wr_data[SV_PACKED_DATA_NELEMS(32)] ,
	svLogicVecVal wr_strb[SV_PACKED_DATA_NELEMS(4)] ,
	const svLogicVecVal wr_resp[SV_PACKED_DATA_NELEMS(2)] ,
	svLogicVecVal rd_addr[SV_PACKED_DATA_NELEMS(32)] ,
	const svLogicVecVal rd_data[SV_PACKED_DATA_NELEMS(32)] ,
	const svLogicVecVal rd_resp[SV_PACKED_DATA_NELEMS(2)]);


/* Exported (from SV) function */
extern 
 void dpi_print(
	const char* msg
);


/* Exported (from SV) function */
extern 
 int sim_time(
	);


#endif
