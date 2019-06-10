import xml.etree.ElementTree as ET
#parse the xml file as an element tree
document = ET.parse("switch_Lat1/solution1/syn/report/csynth.xml")
doc_root = document.getroot()
clock_file = open("ClockPeriod.txt","w+")
#find out what the maximum allowed clock speed is and then set the target to be slightly higher than this value. This will 
#gurantee that Vivado will still be able to find a II=1 solution but will force it to try harder to find a better solution
for j in doc_root.findall("PerformanceEstimates"):
    for i in j.findall("SummaryOfTimingAnalysis"):
        clock_Period = float(i.find("EstimatedClockPeriod").text)
        print("Current Estimated Clock period is " + str(clock_Period/0.865))
        clock_file.write(str(round(clock_Period/0.865,3)))
clock_file.close()
