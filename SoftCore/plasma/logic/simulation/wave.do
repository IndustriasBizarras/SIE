onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -format Logic /tbench/clk_in
add wave -noupdate -format Logic /tbench/rst_in
add wave -noupdate -format Literal /tbench/addr
add wave -noupdate -format Literal /tbench/sram_data
add wave -noupdate -format Logic /tbench/nwe
add wave -noupdate -format Logic /tbench/noe
add wave -noupdate -format Logic /tbench/ncs
add wave -noupdate -format Logic /tbench/led
add wave -noupdate -format Logic /tbench/txd
add wave -noupdate -format Logic /tbench/rxd
add wave -noupdate -format Literal /tbench/u1_plasma/address_next
add wave -noupdate -format Literal /tbench/u1_plasma/byte_we_next
add wave -noupdate -format Literal /tbench/u1_plasma/cpu_address
add wave -noupdate -format Literal /tbench/u1_plasma/cpu_byte_we
add wave -noupdate -format Literal /tbench/u1_plasma/cpu_data_w
add wave -noupdate -format Literal /tbench/u1_plasma/cpu_data_r
add wave -noupdate -format Literal /tbench/u1_plasma/data_read_uart
add wave -noupdate -format Literal /tbench/u1_plasma/data_read_pic
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {999999246 ps} 0}
configure wave -namecolwidth 150
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
update
WaveRestoreZoom {999999050 ps} {1000000050 ps}
