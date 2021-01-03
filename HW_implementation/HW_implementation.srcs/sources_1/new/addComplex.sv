`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/29/2020 10:42:16 AM
// Design Name: 
// Module Name: addComplex
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


module addComplex #(WIDTH = 16)(
    input  [WIDTH-1:0] operand_1,
    input  [WIDTH-1:0] operand_2,
    output [WIDTH-1:0] Res
    );
        
    wire [WIDTH-1:0] carry [0:WIDTH-1]; 
    
    
    
    assign Res = carry[WIDTH-1];
    
    genvar i;
    generate
        for (i = 0; i < WIDTH ; i = i + 1) begin
            Add_1_bit#(WIDTH) A( ((i == 0)? operand_1 :carry[i-1]), {{WIDTH-1-i{1'b0}}, operand_2[i], {i{1'b0}}}, carry[i] );
        end
    endgenerate
    
        
        
endmodule
