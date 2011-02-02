vlib work
vlog   -incr "../build/project.v" "../blink_TB.v" "glbl.v"
vsim -t 1ps -L simprims_ver -L unisims_ver -L xilinxcorelib_ver   blink_TB_v glbl
view wave
#do wave.do
add wave *
add wave /glbl/GSR
view structure
view signals
run 15ms
