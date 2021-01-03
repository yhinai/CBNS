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

    reg  ap_clk = 0;
    reg  ap_rst = 0;
    
    reg [15:0] operand_1;
    reg [15:0] operand_2;
    wire [15:0] Res;
        
    addComplex #(16) A
    (
    .operand_1  (operand_1),
    .operand_2  (operand_2),
    .Res  (Res)
    );
        
    always #5 ap_clk = ~ap_clk;
    
    initial begin
        ap_clk = 0;
        ap_rst = 1;
        #10 ap_rst = 0;
        
        #5 operation(16'hF,16'hF);
        #5 operation(16'hFF,16'hFF);
        #5 operation(16'hFFF,16'hFFF);
        #5 operation(16'hFFFF,16'hFFFF);
        #5 operation(16'h1C,16'hA);
        #5 operation(16'hCE,16'h88);
        #5 operation(16'hC3E,16'hD8);
        #5 operation(16'h23A,16'hAE);
        #5 operation(16'hC,16'hC);
        #5 operation(16'hBE,16'h6);

        $finish;
    end
    

    task operation;      
        input reg [15:0] OP1;
        input reg [15:0] OP2;
        
        begin 
            operand_1 = OP1;
            operand_2 = OP2;
            #5 $display ("(%h + %h = %h)\n", operand_1, operand_2, Res);            
        end
    endtask



endmodule

