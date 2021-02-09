`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/08/2021 03:27:01 PM
// Design Name: 
// Module Name: Sub_bit
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


module Sub_bit #(WIDTH = 16)(
    input  [WIDTH-1:0] operand_1,
    input  [WIDTH-1:0] operand_2,
    output [WIDTH-1:0] Res
    );
    
    wire [WIDTH-1:0] carryOut1;
    wire [WIDTH-1:0] carryOut2;
    
    genvar i;
    generate
        for (i = 0; i < WIDTH; i = i + 1) begin
            Sub_bit_propagate A(operand_1[i], operand_2[i], ((i >= 2)? carryOut1[i-2]: 1'b0), ((i >= 3)? carryOut1[i-3]: 1'b0), Res[i], carryOut1, carryOut2);
        end
    endgenerate

endmodule