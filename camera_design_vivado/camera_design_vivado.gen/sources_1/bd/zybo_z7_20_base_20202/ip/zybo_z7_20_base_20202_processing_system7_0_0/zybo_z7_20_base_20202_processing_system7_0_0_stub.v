// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.2 (lin64) Build 3064766 Wed Nov 18 09:12:47 MST 2020
// Date        : Sun Nov 27 13:37:00 2022
// Host        : CS423 running 64-bit Ubuntu 22.04.1 LTS
// Command     : write_verilog -force -mode synth_stub
//               /media/cole/XilinxShare/camera_design_vivado/camera_design_vivado/camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ip/zybo_z7_20_base_20202_processing_system7_0_0/zybo_z7_20_base_20202_processing_system7_0_0_stub.v
// Design      : zybo_z7_20_base_20202_processing_system7_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z020clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "processing_system7_v5_5_processing_system7,Vivado 2020.2" *)
module zybo_z7_20_base_20202_processing_system7_0_0(USB0_PORT_INDCTL, USB0_VBUS_PWRSELECT, 
  USB0_VBUS_PWRFAULT, M_AXI_GP1_ARVALID, M_AXI_GP1_AWVALID, M_AXI_GP1_BREADY, 
  M_AXI_GP1_RREADY, M_AXI_GP1_WLAST, M_AXI_GP1_WVALID, M_AXI_GP1_ARID, M_AXI_GP1_AWID, 
  M_AXI_GP1_WID, M_AXI_GP1_ARBURST, M_AXI_GP1_ARLOCK, M_AXI_GP1_ARSIZE, M_AXI_GP1_AWBURST, 
  M_AXI_GP1_AWLOCK, M_AXI_GP1_AWSIZE, M_AXI_GP1_ARPROT, M_AXI_GP1_AWPROT, M_AXI_GP1_ARADDR, 
  M_AXI_GP1_AWADDR, M_AXI_GP1_WDATA, M_AXI_GP1_ARCACHE, M_AXI_GP1_ARLEN, M_AXI_GP1_ARQOS, 
  M_AXI_GP1_AWCACHE, M_AXI_GP1_AWLEN, M_AXI_GP1_AWQOS, M_AXI_GP1_WSTRB, M_AXI_GP1_ACLK, 
  M_AXI_GP1_ARREADY, M_AXI_GP1_AWREADY, M_AXI_GP1_BVALID, M_AXI_GP1_RLAST, 
  M_AXI_GP1_RVALID, M_AXI_GP1_WREADY, M_AXI_GP1_BID, M_AXI_GP1_RID, M_AXI_GP1_BRESP, 
  M_AXI_GP1_RRESP, M_AXI_GP1_RDATA, IRQ_F2P, FCLK_CLK0, FCLK_RESET0_N, MIO, DDR_CAS_n, DDR_CKE, 
  DDR_Clk_n, DDR_Clk, DDR_CS_n, DDR_DRSTB, DDR_ODT, DDR_RAS_n, DDR_WEB, DDR_BankAddr, DDR_Addr, 
  DDR_VRN, DDR_VRP, DDR_DM, DDR_DQ, DDR_DQS_n, DDR_DQS, PS_SRSTB, PS_CLK, PS_PORB)
/* synthesis syn_black_box black_box_pad_pin="USB0_PORT_INDCTL[1:0],USB0_VBUS_PWRSELECT,USB0_VBUS_PWRFAULT,M_AXI_GP1_ARVALID,M_AXI_GP1_AWVALID,M_AXI_GP1_BREADY,M_AXI_GP1_RREADY,M_AXI_GP1_WLAST,M_AXI_GP1_WVALID,M_AXI_GP1_ARID[11:0],M_AXI_GP1_AWID[11:0],M_AXI_GP1_WID[11:0],M_AXI_GP1_ARBURST[1:0],M_AXI_GP1_ARLOCK[1:0],M_AXI_GP1_ARSIZE[2:0],M_AXI_GP1_AWBURST[1:0],M_AXI_GP1_AWLOCK[1:0],M_AXI_GP1_AWSIZE[2:0],M_AXI_GP1_ARPROT[2:0],M_AXI_GP1_AWPROT[2:0],M_AXI_GP1_ARADDR[31:0],M_AXI_GP1_AWADDR[31:0],M_AXI_GP1_WDATA[31:0],M_AXI_GP1_ARCACHE[3:0],M_AXI_GP1_ARLEN[3:0],M_AXI_GP1_ARQOS[3:0],M_AXI_GP1_AWCACHE[3:0],M_AXI_GP1_AWLEN[3:0],M_AXI_GP1_AWQOS[3:0],M_AXI_GP1_WSTRB[3:0],M_AXI_GP1_ACLK,M_AXI_GP1_ARREADY,M_AXI_GP1_AWREADY,M_AXI_GP1_BVALID,M_AXI_GP1_RLAST,M_AXI_GP1_RVALID,M_AXI_GP1_WREADY,M_AXI_GP1_BID[11:0],M_AXI_GP1_RID[11:0],M_AXI_GP1_BRESP[1:0],M_AXI_GP1_RRESP[1:0],M_AXI_GP1_RDATA[31:0],IRQ_F2P[0:0],FCLK_CLK0,FCLK_RESET0_N,MIO[53:0],DDR_CAS_n,DDR_CKE,DDR_Clk_n,DDR_Clk,DDR_CS_n,DDR_DRSTB,DDR_ODT,DDR_RAS_n,DDR_WEB,DDR_BankAddr[2:0],DDR_Addr[14:0],DDR_VRN,DDR_VRP,DDR_DM[3:0],DDR_DQ[31:0],DDR_DQS_n[3:0],DDR_DQS[3:0],PS_SRSTB,PS_CLK,PS_PORB" */;
  output [1:0]USB0_PORT_INDCTL;
  output USB0_VBUS_PWRSELECT;
  input USB0_VBUS_PWRFAULT;
  output M_AXI_GP1_ARVALID;
  output M_AXI_GP1_AWVALID;
  output M_AXI_GP1_BREADY;
  output M_AXI_GP1_RREADY;
  output M_AXI_GP1_WLAST;
  output M_AXI_GP1_WVALID;
  output [11:0]M_AXI_GP1_ARID;
  output [11:0]M_AXI_GP1_AWID;
  output [11:0]M_AXI_GP1_WID;
  output [1:0]M_AXI_GP1_ARBURST;
  output [1:0]M_AXI_GP1_ARLOCK;
  output [2:0]M_AXI_GP1_ARSIZE;
  output [1:0]M_AXI_GP1_AWBURST;
  output [1:0]M_AXI_GP1_AWLOCK;
  output [2:0]M_AXI_GP1_AWSIZE;
  output [2:0]M_AXI_GP1_ARPROT;
  output [2:0]M_AXI_GP1_AWPROT;
  output [31:0]M_AXI_GP1_ARADDR;
  output [31:0]M_AXI_GP1_AWADDR;
  output [31:0]M_AXI_GP1_WDATA;
  output [3:0]M_AXI_GP1_ARCACHE;
  output [3:0]M_AXI_GP1_ARLEN;
  output [3:0]M_AXI_GP1_ARQOS;
  output [3:0]M_AXI_GP1_AWCACHE;
  output [3:0]M_AXI_GP1_AWLEN;
  output [3:0]M_AXI_GP1_AWQOS;
  output [3:0]M_AXI_GP1_WSTRB;
  input M_AXI_GP1_ACLK;
  input M_AXI_GP1_ARREADY;
  input M_AXI_GP1_AWREADY;
  input M_AXI_GP1_BVALID;
  input M_AXI_GP1_RLAST;
  input M_AXI_GP1_RVALID;
  input M_AXI_GP1_WREADY;
  input [11:0]M_AXI_GP1_BID;
  input [11:0]M_AXI_GP1_RID;
  input [1:0]M_AXI_GP1_BRESP;
  input [1:0]M_AXI_GP1_RRESP;
  input [31:0]M_AXI_GP1_RDATA;
  input [0:0]IRQ_F2P;
  output FCLK_CLK0;
  output FCLK_RESET0_N;
  inout [53:0]MIO;
  inout DDR_CAS_n;
  inout DDR_CKE;
  inout DDR_Clk_n;
  inout DDR_Clk;
  inout DDR_CS_n;
  inout DDR_DRSTB;
  inout DDR_ODT;
  inout DDR_RAS_n;
  inout DDR_WEB;
  inout [2:0]DDR_BankAddr;
  inout [14:0]DDR_Addr;
  inout DDR_VRN;
  inout DDR_VRP;
  inout [3:0]DDR_DM;
  inout [31:0]DDR_DQ;
  inout [3:0]DDR_DQS_n;
  inout [3:0]DDR_DQS;
  inout PS_SRSTB;
  inout PS_CLK;
  inout PS_PORB;
endmodule
