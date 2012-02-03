onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -format Logic /deb_main_TB_v/clk
add wave -noupdate -format Logic /deb_main_TB_v/reset
add wave -noupdate -format Logic /deb_main_TB_v/PB_1
add wave -noupdate -format Logic /glbl/GSR
add wave -noupdate -format Literal -radix hexadecimal /blink_TB_v/uut/counter
add wave -noupdate -format Logic /glbl/GSR
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {17827 ps} 0}
configure wave -namecolwidth 218
configure wave -valuecolwidth 40
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
WaveRestoreZoom {0 ps} {240328 ps}
