print "File Preparation Python\n"
print "Enter the number of input ports to configure\n"
clock_file = open("ClockPeriod.txt","w+")
header = open("switch.h","w+")
name = open ("Namefile.txt","w+")
input_ports= int(raw_input().strip())
header.write("#include \"ap_int.h\"\n\n")
arbitration_strategy = "Garbage"
fixed_length_writes = 0
while (arbitration_strategy != "PRIORITY") and (arbitration_strategy != "ROUNDROBIN"):
	print "Which Arbitration strategy do you want to use (ROUNDROBIN or PRIORITY)\n"
	arbitration_strategy=raw_input().strip()
if arbitration_strategy == "ROUNDROBIN":
	fixed_length_writes+=1
header.write("#define ")
header.write(arbitration_strategy)
header.write("_ARBITRATION\n#define NUMBER_OF_IN_PORTS %d" %(input_ports))

text_input="Garbage"
while (text_input != "no") and (text_input != "yes"):
	print "Is the dest information located in the data (yes or no)\n"
	text_input=raw_input().strip()
if text_input == "yes":
	print "Enter the number of bits of your dest\n"
	DEST_IN_DATA=raw_input().strip()
	INCLUDE_DEST="0"
	fixed_length_writes+=16
else:
	text_input="garbage"
	DEST_IN_DATA = "0"
	while (text_input != "no") and (text_input != "yes"):
		print "Is there a sideband DEST channel? (yes or no)\n"
		text_input=raw_input().strip()
	if text_input=="yes":
		print "Enter the number of bits of your dest\n"
		INCLUDE_DEST=raw_input().strip()
	else:
		INCLUDE_DEST="0"
name.write(str(int(DEST_IN_DATA)+int(INCLUDE_DEST))+"_")
header.write("\n#define INCLUDE_DEST ")
header.write(INCLUDE_DEST)
header.write("\n#define DEST_IN_DATA ")
header.write(DEST_IN_DATA)
text_input="Garbage"
while (text_input != "no") and (text_input != "yes"):
	print "Is there a sideband STRB channel (yes or no)\n"
	text_input=raw_input().strip()
if text_input == "yes":
	print "Enter the number of bits of your strb\n"
	INCLUDE_STRB=raw_input().strip()
else:
	INCLUDE_STRB="0"
header.write("\n#define INCLUDE_STRB ")
header.write(INCLUDE_STRB)
name.write(INCLUDE_STRB+"_")
text_input="Garbage"
while (text_input != "no") and (text_input != "yes"):
	print "Is there a sideband ID channel (yes or no)\n"
	text_input=raw_input().strip()
if text_input == "yes":
	print "Enter the number of bits of your id\n"
	INCLUDE_ID=raw_input().strip()
else:
	INCLUDE_ID="0"
header.write("\n#define INCLUDE_ID ")
header.write(INCLUDE_ID)
name.write(INCLUDE_ID+"_")
text_input="Garbage"
while (text_input != "no") and (text_input != "yes"):
	print "Is there a sideband KEEP channel (yes or no)\n"
	text_input=raw_input().strip()
if text_input == "yes":
	INCLUDE_KEEP="1"
	fixed_length_writes+=2
else:
	INCLUDE_KEEP="0"
header.write("\n#define INCLUDE_KEEP ")
header.write(INCLUDE_KEEP)
text_input="Garbage"
while (text_input != "no") and (text_input != "yes"):
	print "Is there a sideband USER channel (yes or no)\n"
	text_input=raw_input().strip()
if text_input == "yes":
	print "Enter the number of bits of your user\n"
	INCLUDE_USER=raw_input().strip()
else:
	INCLUDE_USER="0"
header.write("\n#define INCLUDE_USER ")
header.write(INCLUDE_USER)
name.write(INCLUDE_USER+"_")
text_input="Garbage"
while (text_input != "no") and (text_input != "yes"):
	print "Is there a sideband LAST channel (yes or no)\n"
	text_input=raw_input().strip()
if text_input == "yes":
	INCLUDE_LAST="1"
	fixed_length_writes += 4
else:
	INCLUDE_LAST="0"
header.write("\n#define INCLUDE_LAST ")
header.write(INCLUDE_LAST)
print "What is the data width\n"
DATA_WIDTH=raw_input().strip()
while (int(DATA_WIDTH)%8!=0):
	print "Invalid Data Width, must be a multiple of 8\n"
	DATA_WIDTH=raw_input().strip()
header.write("\n#define DATA_WIDTH ")
header.write(DATA_WIDTH)
name.write(INCLUDE_LAST+"_")
if (INCLUDE_DEST!="0") or (DEST_IN_DATA!="0"):
	text_input="Garbage"
	while (text_input != "no") and (text_input != "yes"):
		print "Is output parsing required (yes or no)\n"
		text_input=raw_input().strip()
	if text_input == "yes":
		header.write("\n#define OUTPUT_PARSING_ENABLE 1")
		fixed_length_writes+=8
		text_input="Garbage"
		while (text_input != "no") and (text_input != "yes"):
			print "Is masking enabled?\n"
			text_input=raw_input().strip()
		header.write("\n#define dest_mask ")
		if (text_input=="yes"):
			print "What is the mask?"
			mask_number = raw_input().strip()
			header.write(mask_number)
			name.write(mask_number+"_")
		else:
			header.write("0")
			name.write("0_")
		print "enter the number of output ports \n"
		NUMBER_OF_OUT_PORTS = int(raw_input().strip())
		header.write("\n#define NUMBER_OF_OUT_PORTS ")
		header.write(str(NUMBER_OF_OUT_PORTS))
		fixed_length_writes=(NUMBER_OF_OUT_PORTS)*32
		Current_Port = 0
		while (Current_Port < NUMBER_OF_OUT_PORTS):
			print "Enter the dest for port number %d\n" %(Current_Port)
			DEST_NUMBER=raw_input().strip()
			header.write("\n#define out_port_%d_dest_address " %(Current_Port))
			header.write(DEST_NUMBER)
			name.write(DEST_NUMBER+"_")
			Current_Port=Current_Port+1
	else:
		header.write("\n#define OUTPUT_PARSING_ENABLE 0")
name.write(str(fixed_length_writes))
clock_file.write("10")
clock_file.close()
header.close()
name.close()
