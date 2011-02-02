vlib work
vlog -incr "../build/project.v" "../plasma_TB.v" "glbl.v"
vsim -t 1ps -L simprims_ver -L unisims_ver -L xilinxcorelib_ver   plasma_TB_v glbl
view wave
do wave1.do
#add wave *
view structure
view signals
run 16us
