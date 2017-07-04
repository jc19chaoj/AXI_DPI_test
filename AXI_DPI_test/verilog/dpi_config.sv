// dpi_config.sv

package dpi_config;
    
    typedef enum reg [1:0] {OKAY=2'b00, EXOKAY=2'b01, SLVERR=2'b10, DECERR=2'b11} resp_type;

endpackage: dpi_config