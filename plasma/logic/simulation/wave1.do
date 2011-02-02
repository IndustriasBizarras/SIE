onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -format Logic /plasma_TB_v/clk
add wave -noupdate -format Logic /plasma_TB_v/reset
add wave -noupdate -format Event /plasma_TB_v/reset_done_trigger
add wave -noupdate -format Literal -radix hexadecimal /plasma_TB_v/uut/cpu_data_w
add wave -noupdate -format Literal -radix hexadecimal /plasma_TB_v/uut/cpu_data_r
add wave -noupdate -format Literal -radix binary -expand /plasma_TB_v/uut/byte_we_next
add wave -noupdate -format Logic /plasma_TB_v/uut/U_RxD
add wave -noupdate -format Logic /plasma_TB_v/uut/U_TxD
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {138039444 ps} 0}
configure wave -namecolwidth 240
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
WaveRestoreZoom {132508776 ps} {136643152 ps}
