`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/29/2020 10:44:06 AM
// Design Name: 
// Module Name: Add_1_bit
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module Add_1_bit #(WIDTH = 16)(
    input  [WIDTH-1:0] operand_1,
    input  [WIDTH-1:0] operand_2,
    output [WIDTH-1:0] Res
    );
    
    wire [WIDTH-1:0] carry;
    
    genvar i;
    generate
        for (i = 0; i < WIDTH; i = i + 1) begin
            bit_propagate A(operand_1[i], operand_2[i], ((i >= 2)? carry[i-2]: 1'b0), ((i >= 3)? carry[i-3]: 1'b0), Res[i], carry[i]);
        end
    endgenerate

endmodule


