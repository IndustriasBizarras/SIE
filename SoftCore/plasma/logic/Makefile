##########################################################
### WARNING YOU MUST SET THE VARIABLE XILINX FIRST      ##
### /install_dir/Xilinx/10.1/ISE/
##########################################################
DESIGN          = plasma
PINS           = $(DESIGN).ucf
DEVICE          = xc3s100e-VQ100-4
BGFLAGS         = -g TdoPin:PULLNONE -g DonePin:PULLUP \
                  -g CRC:enable -g StartUpClk:CCLK

SIM_CMD = /opt/cad/modeltech/bin/vsim 
SIM_COMP_SCRIPT = simulation/$(DESIGN)_TB.do
SIMGEN_OPTIONS = -p $(FPGA_ARCH) -lang $(LANGUAGE)

SIMTOP               = $(DESIGN)_tb
GHDL_SIM_OPT         = --stop-time=1ms
SIMDIR               = simu
GHDL_CMD             = ghdl
GHDL_SIMU_FLAGS      = --ieee=synopsys -P$$XILINX/ghdl/unisim   --warn-no-vital-generic
GHDL_SYNTHESIS_FLAGS = --ieee=synopsys -P$$XILINX/ghdl/unisim   --warn-no-vital-generic
GHDL_PANDR_FLAGS     = --ieee=synopsys -P$$XILINX/ghdl/simprim  --warn-no-vital-generic
VIEW_CMD             = gtkwave
TESTBENCH_FILE       = $(DESIGN)_TB.vhd 
SYNT_TESTBENCH_FILE  = $(DESIGN)_TB_syn.vhd 
SYNTHESIS_FILE       = simu/$(DESIGN)_synt.vhd
LIBRARY_FILE         = mlite_pack.vhd

SRC_HDL             = mlite_pack.vhd plasma.vhd ram_image.vhd alu.vhd control.vhd mem_ctrl.vhd mult.vhd shifter.vhd bus_mux.vhd  mlite_cpu.vhd pc_next.vhd pipeline.vhd reg_bank.vhd uart.vhd 
 
all:            bits

remake:         clean-build all

clean:
	rm -rf *~ */*~ a.out *.log *.key *.edf *.ps trace.dat
	rm -rf *.bit rm -rf simulation/work simulation/*wlf
	rm -rf simulation/transcript 

clean-build:
	rm -rf build

cleanall:   clean clean_ghdl
	rm -rf build work $(DESIGN).bit

bits:           $(DESIGN).bit

#
# Synthesis
#
build/project.src:
	@[ -d build ] || mkdir build
	@rm -f $@
	for i in $(SRC); do echo verilog work ../$$i >> $@; done
	for i in $(SRC_HDL); do echo VHDL work ../$$i >> $@; done

build/project.xst: build/project.src
	echo "run" > $@
	echo "-top $(DESIGN) " >> $@
	echo "-p $(DEVICE)" >> $@
	echo "-opt_mode Area" >> $@
	echo "-opt_level 1" >> $@
	echo "-ifn project.src" >> $@
	echo "-ifmt mixed" >> $@
	echo "-ofn project.ngc" >> $@
	echo "-ofmt NGC" >> $@
	echo "-rtlview yes" >> $@

build/project.ngc: build/project.xst $(SRC)
	cd build && xst -ifn project.xst -ofn project.log

build/project.ngd: build/project.ngc $(PINS)
	cd build && ngdbuild -p $(DEVICE) project.ngc  -uc ../$(PINS)

build/project.ncd: build/project.ngd
	cd build && map -pr b -p $(DEVICE) project

build/project_r.ncd: build/project.ncd
	cd build && par -w project project_r.ncd

build/project_r.twr: build/project_r.ncd
	cd build && trce -v 25 project_r.ncd project.pcf

$(DESIGN).bit:  build/project_r.ncd build/project_r.twr
	cd build && bitgen project_r.ncd -l -w $(BGFLAGS)
	@mv -f build/project_r.bit $@

build/project.vhd: build/project.ngc
	cd build &&  netgen -w -ofmt vhdl project.ngc project.vhd

sim: 
	cd simulation; $(SIM_CMD) -do $(DESIGN)_TB.do

ghdl-simu      : ghdl-compil ghdl-run ghdl-view

ghdl-synthesis : ghdl-compil-synthesis ghdl-run ghdl-view

ghdl-compil :
	mkdir -p simu
	$(GHDL_CMD) -i $(GHDL_SIMU_FLAGS) --workdir=simu --work=work $(TESTBENCH_FILE) $(LIBRARY_FILE) $(SRC_HDL)
	$(GHDL_CMD) -m $(GHDL_SIMU_FLAGS) -fexplicit --workdir=simu --work=work $(SIMTOP)
	@mv $(SIMTOP) simu/$(SIMTOP)

ghdl-compil-synthesis: build/project.vhd
	mkdir -p simu
	cp build/project.vhd simu/$(DESIGN)_synt.vhd
	$(GHDL_CMD) -i $(GHDL_SYNTHESIS_FLAGS) --workdir=simu --work=work $(SYNT_TESTBENCH_FILE) $(SYNTHESIS_FILE)
	$(GHDL_CMD) -m $(GHDL_SYNTHESIS_FLAGS)  --workdir=simu --work=work $(SIMTOP)
	@mv $(SIMTOP) simu/$(SIMTOP)

ghdl-run : 
	@$(SIMDIR)/$(SIMTOP) $(GHDL_SIM_OPT) --vcdgz=$(SIMDIR)/$(SIMTOP).vcdgz

ghdl-view: 
	gunzip --stdout $(SIMDIR)/$(SIMTOP).vcdgz | $(VIEW_CMD) --vcd

clean_ghdl :
	$(GHDL_CMD) --clean --workdir=simu 
	-rm -rf simu
 
