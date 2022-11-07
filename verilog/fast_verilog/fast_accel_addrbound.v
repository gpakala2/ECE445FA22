// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Version: 2022.2
// Copyright (C) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module fast_accel_addrbound (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_continue,
        ap_idle,
        ap_ready,
        p_channel,
        rows,
        cols
);

parameter    ap_ST_fsm_state1 = 3'd1;
parameter    ap_ST_fsm_state2 = 3'd2;
parameter    ap_ST_fsm_state3 = 3'd4;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
input   ap_continue;
output   ap_idle;
output   ap_ready;
output  [21:0] p_channel;
input  [15:0] rows;
input  [15:0] cols;

reg ap_done;
reg ap_idle;
reg ap_ready;
reg[21:0] p_channel;

reg    ap_done_reg;
(* fsm_encoding = "none" *) reg   [2:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg    ap_block_state1;
wire   [21:0] trunc_ln949_fu_51_p1;
reg   [21:0] p_channel_preg;
wire    ap_CS_fsm_state3;
wire   [31:0] trunc_ln949_fu_51_p0;
wire  signed [31:0] grp_fu_55_p2;
wire   [15:0] grp_fu_55_p0;
wire   [15:0] grp_fu_55_p1;
reg    grp_fu_55_ce;
reg   [2:0] ap_NS_fsm;
reg    ap_ST_fsm_state1_blk;
wire    ap_ST_fsm_state2_blk;
wire    ap_ST_fsm_state3_blk;
wire   [31:0] grp_fu_55_p00;
wire   [31:0] grp_fu_55_p10;
wire    ap_ce_reg;

// power-on initialization
initial begin
#0 ap_done_reg = 1'b0;
#0 ap_CS_fsm = 3'd1;
#0 p_channel_preg = 22'd0;
end

fast_accel_mul_mul_16ns_16ns_32_3_1 #(
    .ID( 1 ),
    .NUM_STAGE( 3 ),
    .din0_WIDTH( 16 ),
    .din1_WIDTH( 16 ),
    .dout_WIDTH( 32 ))
mul_mul_16ns_16ns_32_3_1_U206(
    .clk(ap_clk),
    .reset(ap_rst),
    .din0(grp_fu_55_p0),
    .din1(grp_fu_55_p1),
    .ce(grp_fu_55_ce),
    .dout(grp_fu_55_p2)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_done_reg <= 1'b0;
    end else begin
        if ((ap_continue == 1'b1)) begin
            ap_done_reg <= 1'b0;
        end else if ((1'b1 == ap_CS_fsm_state3)) begin
            ap_done_reg <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        p_channel_preg <= 22'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state3)) begin
            p_channel_preg <= trunc_ln949_fu_51_p1;
        end
    end
end

always @ (*) begin
    if (((ap_start == 1'b0) | (ap_done_reg == 1'b1))) begin
        ap_ST_fsm_state1_blk = 1'b1;
    end else begin
        ap_ST_fsm_state1_blk = 1'b0;
    end
end

assign ap_ST_fsm_state2_blk = 1'b0;

assign ap_ST_fsm_state3_blk = 1'b0;

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        ap_done = 1'b1;
    end else begin
        ap_done = ap_done_reg;
    end
end

always @ (*) begin
    if (((ap_start == 1'b0) & (1'b1 == ap_CS_fsm_state1))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state1) & ((ap_start == 1'b0) | (ap_done_reg == 1'b1)))) begin
        grp_fu_55_ce = 1'b0;
    end else begin
        grp_fu_55_ce = 1'b1;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        p_channel = trunc_ln949_fu_51_p1;
    end else begin
        p_channel = p_channel_preg;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if ((~((ap_start == 1'b0) | (ap_done_reg == 1'b1)) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            ap_NS_fsm = ap_ST_fsm_state3;
        end
        ap_ST_fsm_state3 : begin
            ap_NS_fsm = ap_ST_fsm_state1;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

always @ (*) begin
    ap_block_state1 = ((ap_start == 1'b0) | (ap_done_reg == 1'b1));
end

assign grp_fu_55_p0 = grp_fu_55_p00;

assign grp_fu_55_p00 = cols;

assign grp_fu_55_p1 = grp_fu_55_p10;

assign grp_fu_55_p10 = rows;

assign trunc_ln949_fu_51_p0 = grp_fu_55_p2;

assign trunc_ln949_fu_51_p1 = trunc_ln949_fu_51_p0[21:0];

endmodule //fast_accel_addrbound
