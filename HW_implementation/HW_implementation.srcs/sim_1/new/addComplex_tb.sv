`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/03/2021 10:41:41 PM
// Design Name: 
// Module Name: addComplex_tb
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

module addComplex_tb();
    
    localparam WIDTH = 16;
    
    reg  ap_clk = 0;
    reg  ap_rst = 0;
    
    reg  [WIDTH-1:0] op = 0;
    reg  [WIDTH-1:0] operand_1;
    reg  [WIDTH-1:0] operand_2;
    reg  operation;
    wire [WIDTH-1:0] Res;
        
    ALU #(WIDTH) A(
    .operation  (operation),
    .operand_1  (operand_1),
    .operand_2  (operand_2),
    .Res        (Res)
    );
        
    always #5 ap_clk = ~ap_clk;
    
    initial begin
        ap_clk = 0;
        ap_rst = 1;
        #10 ap_rst = 0;
        
        #5 taskOperation(0,16'hF,16'hF);
        #5 taskOperation(0,16'hFF,16'hFF);
        #5 taskOperation(0,16'hFFF,16'hFFF);
        #5 taskOperation(0,16'hFFFF,16'hFFFF);
        #5 taskOperation(0,16'h1C,16'hA);
        #5 taskOperation(0,16'hCE,16'h88);
        #5 taskOperation(0,16'hC3E,16'hD8);
        #5 taskOperation(0,16'h23A,16'hAE);
        #5 taskOperation(0,16'hC,16'hC);
        #5 taskOperation(0,16'hBE,16'h6);


        #5 taskOperation(1,16'hF,16'hF);
        #5 taskOperation(1,16'hFF,16'hFF);
        #5 taskOperation(1,16'hFFF,16'hFFF);
        #5 taskOperation(1,16'hFFFF,16'hFFFF);
        #5 taskOperation(1,16'h1C,16'hA);
        #5 taskOperation(1,16'hCE,16'h88);
        #5 taskOperation(1,16'hC3E,16'hD8);
        #5 taskOperation(1,16'h23A,16'hAE);
        #5 taskOperation(1,16'hC,16'hC);
        #5 taskOperation(1,16'hBE,16'h6);


        $finish;
    end
    

    task taskOperation;      
        input reg op;
        input reg [WIDTH-1:0] OP1;
        input reg [WIDTH-1:0] OP2;
        
        begin 
            operation = op;
            operand_1 = OP1;
            operand_2 = OP2;
            #5 $display ("(%h + %h = %h)\n", operand_1, operand_2, Res);            
        end
    endtask



endmodule

