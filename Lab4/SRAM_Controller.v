/*****************************************************************************
 *                                                                           *
 * Module:       SRAM_Controller                                             *
 * Description:                                                              *
 *      This module is used for the sram controller for 3TB4 lab 4           *
 *                                                                           *
 *****************************************************************************/

module SRAM_Controller (
input           clk,
input				 reset_n,
input		[17:0]	address,
input				chipselect,
input		[1:0]	byte_enable,
input				read,
input				write,
input		[15:0]	write_data,

// Bidirectionals
inout		[15:0]	SRAM_DQ,

// Outputs
output		[15:0]	read_data,

output		[17:0]	SRAM_ADDR,

output				SRAM_CE_N,
output				SRAM_WE_N,
output				SRAM_OE_N,
output				SRAM_UB_N,
output				SRAM_LB_N
);

// Add your code here




endmodule

