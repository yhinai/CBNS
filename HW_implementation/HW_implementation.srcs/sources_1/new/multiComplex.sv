`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/09/2021 08:15:26 AM
// Design Name: 
// Module Name: multiComplex
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


module multiComplex#(WIDTH = 16)(
    input  [WIDTH-1:0] operand_1,
    input  [WIDTH-1:0] operand_2,
    output [(2*WIDTH)-1:0] Res
    );
    
    wire [(2*WIDTH)-1:0] op1 = {{(WIDTH){1'b0}}, operand_1};
    wire [(2*WIDTH)-1:0] carry [0:WIDTH-1];
    
    assign carry[0] = (operand_2[0])? op1 : 0;
    
    assign Res = carry[WIDTH-1];
        
    genvar i;   generate
        for (i = 1; i < WIDTH; i = i + 1) begin
            addComplex #(2*WIDTH) A( carry[i-1], {(operand_2[i])? {op1,{(i){1'b0}}} : 0}, carry[i]);
        end
    endgenerate


endmodule


