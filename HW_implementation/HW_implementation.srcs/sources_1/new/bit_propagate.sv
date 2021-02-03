`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/01/2021 06:48:05 PM
// Design Name: 
// Module Name: bit_propagate
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


module bit_propagate (
    input op1,
    input op2,
    input carryIn1,
    input carryIn2,
    output sum,
    output carryOut
    );
    
    
    assign sum = op1 ^ op2 ^ carryIn1 ^ carryIn2;
    assign carryOut = op1 * op2 + op1 * carryIn1 + op1 * carryIn2 + op2 * carryIn1 + op2 * carryIn2 + carryIn1 * carryIn2;


endmodule