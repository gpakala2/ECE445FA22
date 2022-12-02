vlib work
vlib riviera

vlib riviera/xilinx_vip
vlib riviera/xpm
vlib riviera/axi_infrastructure_v1_1_0
vlib riviera/axi_vip_v1_1_8
vlib riviera/processing_system7_vip_v1_0_10
vlib riviera/xil_defaultlib
vlib riviera/lib_cdc_v1_0_2
vlib riviera/proc_sys_reset_v5_0_13
vlib riviera/xlconcat_v2_1_4

vmap xilinx_vip riviera/xilinx_vip
vmap xpm riviera/xpm
vmap axi_infrastructure_v1_1_0 riviera/axi_infrastructure_v1_1_0
vmap axi_vip_v1_1_8 riviera/axi_vip_v1_1_8
vmap processing_system7_vip_v1_0_10 riviera/processing_system7_vip_v1_0_10
vmap xil_defaultlib riviera/xil_defaultlib
vmap lib_cdc_v1_0_2 riviera/lib_cdc_v1_0_2
vmap proc_sys_reset_v5_0_13 riviera/proc_sys_reset_v5_0_13
vmap xlconcat_v2_1_4 riviera/xlconcat_v2_1_4

vlog -work xilinx_vip  -sv2k12 "+incdir+/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/include" \
"/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
"/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
"/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xpm  -sv2k12 "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/ec67/hdl" "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/34f8/hdl" "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/d0f7" "+incdir+/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/include" \
"/tools/Xilinx/Vivado/2020.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \

vcom -work xpm -93 \
"/tools/Xilinx/Vivado/2020.2/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work axi_infrastructure_v1_1_0  -v2k5 "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/ec67/hdl" "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/34f8/hdl" "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/d0f7" "+incdir+/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/include" \
"../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_vip_v1_1_8  -sv2k12 "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/ec67/hdl" "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/34f8/hdl" "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/d0f7" "+incdir+/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/include" \
"../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/94c3/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work processing_system7_vip_v1_0_10  -sv2k12 "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/ec67/hdl" "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/34f8/hdl" "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/d0f7" "+incdir+/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/include" \
"../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/34f8/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/ec67/hdl" "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/34f8/hdl" "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/d0f7" "+incdir+/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/include" \
"../../../bd/zybo_z7_20_base_20202/ip/zybo_z7_20_base_20202_processing_system7_0_0/sim/zybo_z7_20_base_20202_processing_system7_0_0.v" \
"../../../bd/zybo_z7_20_base_20202/ip/zybo_z7_20_base_20202_clk_wiz_0_0/zybo_z7_20_base_20202_clk_wiz_0_0_clk_wiz.v" \
"../../../bd/zybo_z7_20_base_20202/ip/zybo_z7_20_base_20202_clk_wiz_0_0/zybo_z7_20_base_20202_clk_wiz_0_0.v" \

vcom -work lib_cdc_v1_0_2 -93 \
"../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work proc_sys_reset_v5_0_13 -93 \
"../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/zybo_z7_20_base_20202/ip/zybo_z7_20_base_20202_proc_sys_reset_0_0/sim/zybo_z7_20_base_20202_proc_sys_reset_0_0.vhd" \
"../../../bd/zybo_z7_20_base_20202/ip/zybo_z7_20_base_20202_proc_sys_reset_0_1/sim/zybo_z7_20_base_20202_proc_sys_reset_0_1.vhd" \
"../../../bd/zybo_z7_20_base_20202/ip/zybo_z7_20_base_20202_proc_sys_reset_1_0/sim/zybo_z7_20_base_20202_proc_sys_reset_1_0.vhd" \

vlog -work xlconcat_v2_1_4  -v2k5 "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/ec67/hdl" "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/34f8/hdl" "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/d0f7" "+incdir+/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/include" \
"../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/4b67/hdl/xlconcat_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/ec67/hdl" "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/34f8/hdl" "+incdir+../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/d0f7" "+incdir+/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/include" \
"../../../bd/zybo_z7_20_base_20202/ip/zybo_z7_20_base_20202_xlconcat_0_0/sim/zybo_z7_20_base_20202_xlconcat_0_0.v" \
"../../../bd/zybo_z7_20_base_20202/sim/zybo_z7_20_base_20202.v" \

vlog -work xil_defaultlib \
"glbl.v"

