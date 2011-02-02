vlib work
vmap work
vcom -93 -work work ../mlite_pack.vhd
vcom -93 -work work ../plasma.vhd
vcom -93 -work work ../alu.vhd
vcom -93 -work work ../control.vhd 
vcom -93 -work work ../mem_ctrl.vhd 
vcom -93 -work work ../mult.vhd 
vcom -93 -work work ../shifter.vhd 
vcom -93 -work work ../bus_mux.vhd 
vcom -93 -work work ../ddr_ctrl.vhd  
vcom -93 -work work ../mlite_cpu.vhd
vcom -93 -work work ../pc_next.vhd 
vcom -93 -work work ../cache.vhd 
vcom -93 -work work ../pipeline.vhd 
vcom -93 -work work ../reg_bank.vhd
vcom -93 -work work ../uart.vhd 
vcom -93 -work work ../ram_image.vhd
vcom -93 -work work ../plasma_TB.vhd

vsim -t 1ps plasma_tb 
#view wave
add wave *
do wave.do

view structure
view signals
run 1ms
