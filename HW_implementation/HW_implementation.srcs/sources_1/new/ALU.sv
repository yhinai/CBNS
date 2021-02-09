`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/08/2021 10:30:58 AM
// Design Name: 
// Module Name: ALU
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


module ALU#(WIDTH = 16)(
    input operation,
    input [WIDTH-1:0] operand_1,
    input [WIDTH-1:0] operand_2,
    output [WIDTH-1:0] Res
    );
    
    wire [WIDTH-1:0] addComplexRes;
    wire [WIDTH-1:0] multiComplexRes;
    
    assign Res = (operation)? multiComplexRes : addComplexRes;

    
    addComplex  #(WIDTH) A1 (
    .operand_1(operand_1),
    .operand_2(operand_2),
    .Res(addComplexRes)
    );
    
    multiComplex  #(WIDTH) A2 (
    .operand_1(operand_1),
    .operand_2(operand_2),
    .Res(multiComplexRes)
    );
    
endmodule
