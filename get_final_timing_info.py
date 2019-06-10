import xml.etree.ElementTree as ET
#use element tree to parse the xml file
document = ET.parse("switch_Lat1/solution1/syn/report/csynth.xml")
doc_root = document.getroot()
clock_file = open("ClockPeriod.txt","r")
#find the appropriate file and read the max clock from the synthesis run, add clock uncertainty to this value
#Uncertainty is defined in HLS as 12.5% of target clock period, use ClockPeriod.txt to determine what the target clock was
for j in doc_root.findall("PerformanceEstimates"):
    for i in j.findall("SummaryOfTimingAnalysis"):
        clock_Period = float(i.find("EstimatedClockPeriod").text)
        max_clock = round(float(clock_file.readline())*0.125+clock_Period,3)
        print("Final Max Clock Period is: " + str(max_clock)+ " (Estimated is " + str(clock_Period) + " + clock uncertainty)")
        print("Connect it to a clock with a frequency of " + str(1000.0/max_clock) + "MHz or less")
#close the xml file
clock_file.close()
