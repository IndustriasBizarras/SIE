vlib work
vlog   -incr "../build/project.v" "../sram_bus_TB.v" "glbl.v"
vsim -t 1ps -L simprims_ver -L unisims_ver -L xilinxcorelib_ver   sram_bus_TB glbl
view wave
#do wave.do
add wave *
view structure
view signals
run 5us
