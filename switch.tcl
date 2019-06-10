open_project switch_Lat1
set_top AXIS_switch
set infile [open "Namefile.txt" r]
set name_append [gets $infile]
close $infile
set infile2 [open "ClockPeriod.txt" r]
set clock_period [gets $infile2]
close $infile2
add_files switch.cpp
add_files switch.h
open_solution "solution1"
set_part {xczu19eg-ffvc1760-2-i} -tool vivado
create_clock -period $clock_period
config_rtl -reset all -reset_level low -prefix $name_append
csynth_design
export_design -rtl verilog
