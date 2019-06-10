all: Prepare_the_files hls_make_SWITCH iterate hls_make_SWITCH2 iterate2 hls_make_SWITCH3 print_report get_results
#same as make all but without running prepare the files if the user wants to write them by hand or import them externally
no_prep: hls_make_SWITCH iterate hls_make_SWITCH2 iterate2 hls_make_SWITCH3 print_report get_results
#run the user questionare and use the answers to create switch.h and Namefile.txt. Also create ClockPeriod.txt containing
#just the number 10 so that the first iteration uses a clock speed of 10ns
Prepare_the_files:
	python file_preparation.py
#each one for a different iteration of the run (makefile requires each part run a maximum of 1 time)
#create the project directory and source the tcl script which uses the files from file_preparation.py to configure the run
hls_make_SWITCH2:
	rm -rf switch_Lat1
	mkdir -p switch_Lat1
	vivado_hls switch.tcl
	rm -f vivado_hls.log

hls_make_SWITCH:
	rm -rf switch_Lat1
	mkdir -p switch_Lat1
	vivado_hls switch.tcl
	rm -f vivado_hls.log

hls_make_SWITCH3:
	rm -rf switch_Lat1
	mkdir -p switch_Lat1
	vivado_hls switch.tcl
	rm -f vivado_hls.log
#iterate reads the output products from an HLS run and modifies ClockPeriod.txt to put tighter requirements on the clock
iterate:
	python get_timing_info.py

iterate2:
	python get_timing_info.py
#print the utilization report
print_report:
	cat switch_Lat1/solution1/syn/report/AXIS_switch_csynth.rpt
#export the ip file and print out final clock values
get_results:
	cp switch_Lat1/solution1/impl/ip/*.zip ip_file.zip
	python get_final_timing_info.py
#remove the temporary files
clean:
	rm -f ClockPeriod.txt
	rm -f switch.h
	rm -f vivado_hls.log
	rm -f Namefile.txt
	rm -rf switch_Lat1
	rm -f ip_file.zip
