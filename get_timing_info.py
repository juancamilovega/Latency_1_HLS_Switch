import xml.etree.ElementTree as ET
document = ET.parse("switch_Lat1/solution1/syn/report/csynth.xml")
doc_root = document.getroot()
clock_file = open("ClockPeriod.txt","w+")
for j in doc_root.findall("PerformanceEstimates"):
    for i in j.findall("SummaryOfTimingAnalysis"):
        clock_Period = float(i.find("EstimatedClockPeriod").text)
        print("Current Estimated Clock period is " + str(clock_Period))
        clock_file.write(str(round(clock_Period/0.865,3)))
clock_file.close()
