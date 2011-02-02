iverilog -o ps2_interface_TF ps2_interface_TF.v ps2_interface.v kb_ps2.v ps2_rx.v ps2_tx.v pulse_expander.v sync.v writePulseGenerator.v
vvp ps2_interface_TF
gtkwave ps2_interface_TF.vcd