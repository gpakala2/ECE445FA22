onbreak {quit -f}
onerror {quit -f}

vsim -voptargs="+acc" -L xilinx_vip -L xpm -L axi_infrastructure_v1_1_0 -L axi_vip_v1_1_8 -L processing_system7_vip_v1_0_10 -L xil_defaultlib -L lib_cdc_v1_0_2 -L proc_sys_reset_v5_0_13 -L xlconcat_v2_1_4 -L xilinx_vip -L unisims_ver -L unimacro_ver -L secureip -lib xil_defaultlib xil_defaultlib.zybo_z7_20_base_20202 xil_defaultlib.glbl

do {wave.do}

view wave
view structure
view signals

do {zybo_z7_20_base_20202.udo}

run -all

quit -force
