# Latency_1_HLS_Switch
The Latency 1 HLS switch provides AXI Stream Switch functionality allowing routing from N ports to N ports with single cycle latency. Unlike the Xilinx provided switch, it does not add buffer cycles within the data allowing for true II=1 performance. Dest information can exist as a sideband channel or can be embedded in the data. Supports both Round Robin and Fixed Priority arbitration.

# making the switch
- clone the repository to a directory
- run the command make
      
      This will run through a questionare allowing the user to specify the parameters of their AXIS line (data widths, sideband channels, ...) and of their switch implementation (arbitration method, dest location, ...)
      
      At the conclusion it will make the project and report the maximum clock frequency allowed based on those parameters
          -Note, the project will be recursively generated 3 times where it learns based on the synthesis results to modify some internal parameters and generate a better solution
      
      If there are any questions during the questionare, type help when prompted
