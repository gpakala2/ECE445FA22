// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.2 (lin64) Build 3064766 Wed Nov 18 09:12:47 MST 2020
// Date        : Sun Nov 13 02:02:22 2022
// Host        : CS423 running 64-bit Ubuntu 22.04.1 LTS
// Command     : write_verilog -force -mode synth_stub
//               /home/cole/Desktop/camera_design_vivado/camera_design_vivado/camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ip/zybo_z7_20_base_20202_clk_wiz_0_0/zybo_z7_20_base_20202_clk_wiz_0_0_stub.v
// Design      : zybo_z7_20_base_20202_clk_wiz_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z020clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
module zybo_z7_20_base_20202_clk_wiz_0_0(clk_out1, clk_out2, clk_out3, resetn, locked, 
  clk_in1)
/* synthesis syn_black_box black_box_pad_pin="clk_out1,clk_out2,clk_out3,resetn,locked,clk_in1" */;
  output clk_out1;
  output clk_out2;
  output clk_out3;
  input resetn;
  output locked;
  input clk_in1;
endmodule
