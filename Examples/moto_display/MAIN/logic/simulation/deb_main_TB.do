vlib work
vlog  +acc  "../deb_main.v"
vlog  +acc  "../deb_main_TB.v"
vlog  +acc  "../deb.v"
vlog  +acc  "glbl.v"

vsim -t 1ps -L simprims_ver -L unisims_ver -L xilinxcorelib_ver deb_main_TB_v glbl
view wave
#do wave.do
add wave *
add wave /glbl/GSR
view structure
view signals
run 15ms
