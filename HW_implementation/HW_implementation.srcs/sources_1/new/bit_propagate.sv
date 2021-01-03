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
    input operand_1,
    input operand_2,
    input carryIn_0,
    input carryIn_1,
    output out,
    output carryOut
    );
    
    
    assign out = operand_1 ^ operand_2 ^ carryIn_0 ^ carryIn_1;
    assign carryOut = operand_1 * operand_2 + operand_1 * carryIn_0 + operand_1 * carryIn_1 + operand_2 * carryIn_0 + operand_2 * carryIn_1 + carryIn_0 * carryIn_1;


endmodule