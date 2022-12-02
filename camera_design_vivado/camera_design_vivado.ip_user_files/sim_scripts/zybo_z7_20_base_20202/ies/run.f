-makelib ies_lib/xilinx_vip -sv \
  "/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
  "/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
  "/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
  "/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
  "/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
  "/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
  "/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
  "/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
  "/tools/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/rst_vip_if.sv" \
-endlib
-makelib ies_lib/xpm -sv \
  "/tools/Xilinx/Vivado/2020.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
-endlib
-makelib ies_lib/xpm \
  "/tools/Xilinx/Vivado/2020.2/data/ip/xpm/xpm_VCOMP.vhd" \
-endlib
-makelib ies_lib/axi_infrastructure_v1_1_0 \
  "../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \
-endlib
-makelib ies_lib/axi_vip_v1_1_8 -sv \
  "../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/94c3/hdl/axi_vip_v1_1_vl_rfs.sv" \
-endlib
-makelib ies_lib/processing_system7_vip_v1_0_10 -sv \
  "../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/34f8/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/zybo_z7_20_base_20202/ip/zybo_z7_20_base_20202_processing_system7_0_0/sim/zybo_z7_20_base_20202_processing_system7_0_0.v" \
  "../../../bd/zybo_z7_20_base_20202/ip/zybo_z7_20_base_20202_clk_wiz_0_0/zybo_z7_20_base_20202_clk_wiz_0_0_clk_wiz.v" \
  "../../../bd/zybo_z7_20_base_20202/ip/zybo_z7_20_base_20202_clk_wiz_0_0/zybo_z7_20_base_20202_clk_wiz_0_0.v" \
-endlib
-makelib ies_lib/lib_cdc_v1_0_2 \
  "../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \
-endlib
-makelib ies_lib/proc_sys_reset_v5_0_13 \
  "../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/zybo_z7_20_base_20202/ip/zybo_z7_20_base_20202_proc_sys_reset_0_0/sim/zybo_z7_20_base_20202_proc_sys_reset_0_0.vhd" \
  "../../../bd/zybo_z7_20_base_20202/ip/zybo_z7_20_base_20202_proc_sys_reset_0_1/sim/zybo_z7_20_base_20202_proc_sys_reset_0_1.vhd" \
  "../../../bd/zybo_z7_20_base_20202/ip/zybo_z7_20_base_20202_proc_sys_reset_1_0/sim/zybo_z7_20_base_20202_proc_sys_reset_1_0.vhd" \
-endlib
-makelib ies_lib/xlconcat_v2_1_4 \
  "../../../../camera_design_vivado.gen/sources_1/bd/zybo_z7_20_base_20202/ipshared/4b67/hdl/xlconcat_v2_1_vl_rfs.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/zybo_z7_20_base_20202/ip/zybo_z7_20_base_20202_xlconcat_0_0/sim/zybo_z7_20_base_20202_xlconcat_0_0.v" \
  "../../../bd/zybo_z7_20_base_20202/sim/zybo_z7_20_base_20202.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  glbl.v
-endlib

