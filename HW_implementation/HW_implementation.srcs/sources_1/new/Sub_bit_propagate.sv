`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/08/2021 03:29:08 PM
// Design Name: 
// Module Name: Sub_bit_propagate
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


module Sub_bit_propagate(
    input op1,
    input op2,
    input carryIn1,
    input carryIn2,
    input carryIn3,
    output sum,
    output carryOut
    );
    
    
    assign sum = op1 ^ op2 ^ carryIn1 ^ carryIn2 ^ carryIn3;
    assign carryOut = op1 * op2 + op1 * carryIn1 + op1 * carryIn2  + op1 * carryIn3 + op2 * carryIn1 + op2 * carryIn2 + op2 * carryIn3 + carryIn1 * carryIn2;


endmodule