onbreak {quit -f}
onerror {quit -f}

vsim -lib xil_defaultlib zybo_z7_20_base_20202_opt

do {wave.do}

view wave
view structure
view signals

do {zybo_z7_20_base_20202.udo}

run -all

quit -force
