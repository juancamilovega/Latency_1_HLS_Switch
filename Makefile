all: Prepare_the_files hls_make_SWITCH iterate hls_make_SWITCH2 iterate2 hls_make_SWITCH3 print_report get_results

no_prep: hls_make_SWITCH iterate hls_make_SWITCH2 iterate2 hls_make_SWITCH3 print_report get_results

Prepare_the_files:
	python file_preparation.py

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

iterate:
	python get_timing_info.py

iterate2:
	python get_timing_info.py

print_report:
	cat switch_Lat1/solution1/syn/report/AXIS_switch_csynth.rpt

get_results:
	cp switch_Lat1/solution1/impl/ip/*.zip ip_file.zip
	python get_final_timing_info.py
clean:
	rm -f ClockPeriod.txt
	rm -f switch.h
	rm -f vivado_hls.log
	rm -f Namefile.txt
	rm -rf switch_Lat1
	rm -f ip_file.zip
