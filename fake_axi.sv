// fake_axi.sv

`timescale 1ns/1ns
`include "dpi_config.sv"

import dpi_config::*;

module fake_axi (
    
    clk,
    rst,
    
    // master
    // write address channel
    m_wr_addr,
    // write data channel
    m_wr_data,
    m_wr_strb,
    // write response channel
    m_wr_resp,
    // read address channel
    m_rd_addr,
    // read response channel
    m_rd_data,
    m_rd_resp,
    
    // slave
    // write address channel
    s_wr_addr,
    // write data channel
    s_wr_data,
    s_wr_strb,
    // write response channel
    s_wr_resp,
    // read address channel
    s_rd_addr,
    // read response channel
    s_rd_data,
    s_rd_resp
    );   
    
    // typedef enum reg [1:0] {OKAY, EXOKAY, SLVERR, DECERR} resp_type;
    
    //
    input   bit         clk;
    input   bit         rst;
    // master
    // write address channel
    input   reg [31:0]  m_wr_addr;
    // write data channel
    input   reg [31:0]  m_wr_data;
    input   reg [3:0]   m_wr_strb;
    // write response channel
    output  resp_type   m_wr_resp;
    // read address channel
    input   reg [31:0]  m_rd_addr;
    // read response channel
    output  reg [31:0]  m_rd_data;
    output  resp_type   m_rd_resp;
    
    // slave
    // write address channel
    output  reg [31:0]  s_wr_addr;
    // write data channel
    output  reg [31:0]  s_wr_data;
    output  reg [3:0]   s_wr_strb;
    // write response channel
    input   resp_type   s_wr_resp;
    // read address channel
    output  reg [31:0]  s_rd_addr;
    // read response channel
    input   reg [31:0]  s_rd_data;
    input   resp_type   s_rd_resp;
    
    always@(posedge clk)
    begin
        if (rst) 
        begin
            m_wr_resp <= OKAY;
            m_rd_data <= 0;
            m_rd_resp <= OKAY;
            s_wr_addr <= 0;
            s_wr_data <= 0;
            s_wr_strb <= 0;
            s_rd_addr <= 0;
        end
        else 
        begin
            m_wr_resp <= s_wr_resp;
            m_rd_data <= s_rd_data;
            m_rd_resp <= s_rd_resp;
            s_wr_addr <= m_wr_addr;
            s_wr_data <= m_wr_data;
            s_wr_strb <= m_wr_strb;
            s_rd_addr <= m_rd_addr;
        end
    end
    
endmodule