// dpi.sv

`timescale 1ns/1ns
`include "dpi_config.sv"

import dpi_config::*;

module dpi();

// typedef enum reg [1:0] {OKAY=2'b00, EXOKAY=2'b01, SLVERR=2'b10, DECERR=2'b11} resp_type;

// ====================================
// inputs
bit                   clk;
bit                   rst;
// master
logic     [31:0]    AXI1_master_wr_addr;
logic     [31:0]    AXI1_master_wr_data;
logic     [3:0]     AXI1_master_wr_strb;
logic     [31:0]    AXI1_master_rd_addr;
// slave
resp_type           AXI2_slave_wr_resp;
logic     [31:0]    AXI2_slave_rd_data;
resp_type           AXI2_slave_rd_resp;

// ......
// ====================================
// outputs
// master
logic     [31:0]    AXI2_slave_wr_addr;
logic     [31:0]    AXI2_slave_wr_data;
logic     [3:0]     AXI2_slave_wr_strb;
logic     [31:0]    AXI2_slave_rd_addr;
// slave
resp_type           AXI1_master_wr_resp;
logic     [31:0]    AXI1_master_rd_data;
resp_type           AXI1_master_rd_resp;

// ......
// wires
// ......


// ====================================
// Instantiate AXI
// AXI1_master
fake_axi DUT (
    .clk (clk),
    .rst (rst),
    // master
    // write address channel
    .m_wr_addr (AXI1_master_wr_addr),
    // write data channel
    .m_wr_data (AXI1_master_wr_data),
    .m_wr_strb (AXI1_master_wr_strb),
    // write response channel
    .m_wr_resp (AXI1_master_wr_resp),
    // read address channel
    .m_rd_addr (AXI1_master_rd_addr),
    // read response channel
    .m_rd_data (AXI1_master_rd_data),
    .m_rd_resp (AXI1_master_rd_resp),
    
    // slave
    // write address channel
    .s_wr_addr (AXI2_slave_wr_addr),
    // write data channel
    .s_wr_data (AXI2_slave_wr_data),
    .s_wr_strb (AXI2_slave_wr_strb),
    // write response channel
    .s_wr_resp (AXI2_slave_wr_resp),
    // read address channel
    .s_rd_addr (AXI2_slave_rd_addr),
    // read response channel
    .s_rd_data (AXI2_slave_rd_data),
    .s_rd_resp (AXI2_slave_rd_resp)
    );

// AXI2_slave


// ====================================
// import "DPI-C"
// Communicate with AXI
import "DPI-C" function void init();

import "DPI-C" function void AXI2_slave(
    // AXI ports:
    // write address channel
    input   logic [31:0]  wr_addr,
    // write data channel
    input   logic [31:0]  wr_data,
    input   logic [3:0]   wr_strb,
    // write response channel
    output  resp_type     wr_resp,
    // read address channel
    input   logic [31:0]  rd_addr,
    // read response channel
    output  logic [31:0]  rd_data,
    output  resp_type     rd_resp  
    // ......
    );

import "DPI-C" function void AXI1_master(
    // AXI ports:
    // write address channel
    output  logic [31:0]  wr_addr,
    // write data channel
    output  logic [31:0]  wr_data,
    output  logic [3:0]   wr_strb,
    // write response channel
    input   resp_type     wr_resp,
    // read address channel
    output  logic [31:0]  rd_addr,
    // read response channel
    input   logic [31:0]  rd_data,
    input   resp_type     rd_resp
    // ......
    );

// ====================================
// export "DPI-C"
// Display function
export "DPI-C" function dpi_print;
function void dpi_print(input string msg);
    $display("%t :: %s", $time, msg);
endfunction : dpi_print

// Get simulation time
export "DPI-C" function sim_time;
function int sim_time();
    sim_time = $time;
endfunction : sim_time

// Read from AXI
// export "DPI-C" function void QEMU_read;





// ====================================
// initialization
initial
begin
    init();
	rst <= 1;
    #20 rst <= 0; 
    #30 $finish;
end

// clock generation
always
begin
	#2 clk = !clk;
end

always@(posedge clk)
begin

    begin
        AXI1_master(
            AXI1_master_wr_addr,
            AXI1_master_wr_data,
            AXI1_master_wr_strb,
            AXI1_master_wr_resp,
            AXI1_master_rd_addr,
            AXI1_master_rd_data,
            AXI1_master_rd_resp);
        
        AXI2_slave(		
            AXI2_slave_wr_addr,
            AXI2_slave_wr_data,
            AXI2_slave_wr_strb,
            AXI2_slave_wr_resp,
            AXI2_slave_rd_addr,
            AXI2_slave_rd_data,
            AXI2_slave_rd_resp);
            
        // dpi_print(QEMU_read());
    end
end

endmodule