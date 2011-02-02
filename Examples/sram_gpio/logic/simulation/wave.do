onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -format Logic -radix hexadecimal /sram_bus_TB_v/clk
add wave -noupdate -format Literal -radix hexadecimal /sram_bus_TB_v/addr
add wave -noupdate -format Logic -radix hexadecimal /sram_bus_TB_v/nwe
add wave -noupdate -format Logic -radix hexadecimal /sram_bus_TB_v/ncs
add wave -noupdate -format Logic -radix hexadecimal /sram_bus_TB_v/noe
add wave -noupdate -format Logic -radix hexadecimal /sram_bus_TB_v/reset
add wave -noupdate -format Logic -radix hexadecimal /sram_bus_TB_v/led
add wave -noupdate -format Literal -radix hexadecimal {/sram_bus_TB_v/sram_data$inout$reg}
add wave -noupdate -format Logic -radix hexadecimal /sram_bus_TB_v/sram_data
add wave -noupdate -format Literal -radix hexadecimal /sram_bus_TB_v/data_tx
add wave -noupdate -format Logic -radix hexadecimal /glbl/GSR
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {154070 ps} 0}
configure wave -namecolwidth 323
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
WaveRestoreZoom {0 ps} {656250 ps}
