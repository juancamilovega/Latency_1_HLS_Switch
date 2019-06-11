print "\nFile Preparation Script:\n"
#Open the helper files
clock_file = open("ClockPeriod.txt","w+")
header = open("switch.h","w+")
name = open ("Namefile.txt","w+")
print "\nEnter the number of input ports to configure\n"
#Check for non-int input by catching errors in try except blocks, only accept good ints
bad_input = True;
while (bad_input):
	try:
		input_ports= int(raw_input().strip().lower(),0)
		bad_input=False
		break
	except KeyboardInterrupt:
		raise
	except:
		print "Value entered is not an integer, try again"
		bad_input=True
while ((input_ports<1) or (input_ports>16)):
	#retry until value in range and is an int
	print "Invalid number of input ports, must be positive value less than 16, try again"
	bad_input=True
	while (bad_input):
		try:
			input_ports= int(raw_input().strip().lower(),0)
			bad_input=False
			break
		except KeyboardInterrupt:
			raise
		except:
			print "Value entered is not an integer, try again"
			bad_input=True
#add the include statements
header.write("#include \"ap_int.h\"\n\n")
#add arbitration strategy
arbitration_strategy = "Garbage"
fixed_length_writes = 0
while (arbitration_strategy != "PRIORITY") and (arbitration_strategy != "ROUNDROBIN"):
	print "Which Arbitration strategy do you want to use (ROUNDROBIN(1) or PRIORITY(0) or HELP(2))\n"
	arbitration_strategy=raw_input().strip().upper()
	if (arbitration_strategy=="0"):
		arbitration_strategy = "PRIORITY"
	elif (arbitration_strategy=="1"):
		arbitration_strategy = "ROUNDROBIN"
	elif (arbitration_strategy=="HELP" or arbitration_strategy=="2"):
		print "In PRIORITY arbitration, the packets coming in from lower port numbers will be serviced first (in port 0 has greatest priority)\nIn ROUNDROBIN arbitration, the priority of the ports is rotated each cycle allowing for more fair arbitration.\nNOTE:PRIORITY arbitration has better performance and will allow a higher frequency clock than ROUNDROBIN"
if arbitration_strategy == "ROUNDROBIN":
	fixed_length_writes+=1
header.write("#define ")
header.write(arbitration_strategy)
header.write("_ARBITRATION\n#define NUMBER_OF_IN_PORTS %d" %(input_ports))
#add DEST_IN_DATA and INCLUDE_DEST. Recall that one of the two must be zero
text_input="Garbage"
while (text_input != "NO") and (text_input != "YES"):
	print "Is the dest information located in the data (YES(1) or NO(0) or HELP(2))\n"
	text_input=raw_input().strip().upper()
	if (text_input=="0"):
		text_input="NO"
	elif (text_input=="1"):
		text_input="YES"
	elif (text_input=="2" or text_input=="HELP"):
		print "Dest info in data specifies that the first n bits of each payload carry the dest information used for routing. In multi flit packets, dest information is collected from the first flit of the packet\n"
if text_input == "YES":
	print "Enter the number of bits of your dest\n"
	bad_input=True
	while (bad_input):
		try:
			DEST_IN_DATA=str(int(raw_input().strip().lower(),0))
			bad_input=False
			break
		except KeyboardInterrupt:
			raise
		except:
			print "Value entered is not an integer, try again"
			bad_input=True
	INCLUDE_DEST="0"
	fixed_length_writes+=16
else:
	text_input="garbage"
	DEST_IN_DATA = "0"
	while (text_input != "NO") and (text_input != "YES"):
		print "Is there a sideband DEST channel? (YES(1) or NO(0) or HELP(2))\n"
		text_input=raw_input().strip().upper()
		if (text_input=="0"):
			text_input="NO"
		elif (text_input=="1"):
			text_input="YES"
		elif (text_input=="HELP" or text_input=="2"):
			print "A sideband dest channel would be added of the specified bit width, if output parsing is enabled, this is used for routing."
	if text_input=="YES":
		print "Enter the number of bits of your dest\n"
		INCLUDE_DEST=raw_input().strip().upper()
		bad_input=True
		while (bad_input):
			try:
				INCLUDE_DEST=str(int(raw_input().strip().lower(),0))
				bad_input=False
				break
			except KeyboardInterrupt:
				raise
			except:
				print "Value entered is not an integer, try again"
				bad_input=True
	else:
		INCLUDE_DEST="0"
name.write(str(int(DEST_IN_DATA,0)+int(INCLUDE_DEST,0))+"_")
header.write("\n#define INCLUDE_DEST ")
header.write(INCLUDE_DEST)
header.write("\n#define DEST_IN_DATA ")
header.write(DEST_IN_DATA)
#add STRB
text_input="Garbage"
while (text_input != "NO") and (text_input != "YES"):
	print "Is there a sideband STRB channel (YES(1) or NO (0) or HELP(2))\n"
	text_input=raw_input().strip().upper()
	if (text_input=="0"):
		text_input="NO"
	elif (text_input=="1"):
		text_input="YES"
	elif (text_input=="HELP" or text_input=="2"):
		print "If selected a sideband STRB port will be added of the specified width"
if text_input == "YES":
	print "Enter the number of bits of your strb\n"
	bad_input=True
	while (bad_input):
		try:
			INCLUDE_STRB=str(int(raw_input().strip().lower(),0))
			bad_input=False
			break
		except KeyboardInterrupt:
			raise
		except:
			print "Value entered is not an integer, try again"
			bad_input=True
else:
	INCLUDE_STRB="0"
header.write("\n#define INCLUDE_STRB ")
header.write(INCLUDE_STRB)
name.write(INCLUDE_STRB+"_")
#add ID
text_input="Garbage"
while (text_input != "NO") and (text_input != "YES"):
	print "Is there a sideband ID channel (YES(1) or NO (0) or HELP(2))\n"
	text_input=raw_input().strip().upper()
	if (text_input=="0"):
		text_input="NO"
	elif (text_input=="1"):
		text_input="YES"
	elif (text_input=="HELP" or text_input=="2"):
		print "If selected a sideband ID port will be added of the specified width"
if text_input == "YES":
	print "Enter the number of bits of your id\n"
	bad_input=True
	while (bad_input):
		try:
			INCLUDE_ID=str(int(raw_input().strip().lower(),0))
			bad_input=False
			break
		except KeyboardInterrupt:
			raise
		except:
			print "Value entered is not an integer, try again"
			bad_input=True
else:
	INCLUDE_ID="0"
header.write("\n#define INCLUDE_ID ")
header.write(INCLUDE_ID)
name.write(INCLUDE_ID+"_")
text_input="Garbage"
#add keep
while (text_input != "NO") and (text_input != "YES"):
	print "Is there a sideband KEEP channel (YES(1) or NO (0) or HELP(2))\n"
	text_input=raw_input().strip().upper()
	if (text_input=="0"):
		text_input="NO"
	elif (text_input=="1"):
		text_input="YES"
	elif (text_input=="HELP" or text_input=="2"):
		print "If selected a sideband KEEP port will be added that will be 1/8 the side of the data width"
if text_input == "YES":
	INCLUDE_KEEP="1"
	fixed_length_writes+=2
else:
	INCLUDE_KEEP="0"
header.write("\n#define INCLUDE_KEEP ")
header.write(INCLUDE_KEEP)
#add USER
text_input="Garbage"
while (text_input != "NO") and (text_input != "YES"):
	print "Is there a sideband USER channel (YES(1) or NO (0) or HELP(2))\n"
	text_input=raw_input().strip().upper()
	if (text_input=="0"):
		text_input="NO"
	elif (text_input=="1"):
		text_input="YES"
	elif (text_input=="HELP" or text_input=="2"):
		print "If selected a sideband USER port will be added of the specified width"
if text_input == "YES":
	print "Enter the number of bits of your user\n"
	bad_input=True
	while (bad_input):
		try:
			INCLUDE_USER=str(int(raw_input().strip().lower(),0))
			bad_input=False
			break
		except KeyboardInterrupt:
			raise
		except:
			print "Value entered is not an integer, try again"
			bad_input=True
else:
	INCLUDE_USER="0"
header.write("\n#define INCLUDE_USER ")
header.write(INCLUDE_USER)
name.write(INCLUDE_USER+"_")
#add LAST
text_input="Garbage"
while (text_input != "NO") and (text_input != "YES"):
	print "Is there a sideband LAST channel (YES(1) or NO (0) or HELP(2))\n"
	text_input=raw_input().strip().upper()
	if (text_input=="0"):
		text_input="NO"
	elif (text_input=="1"):
		text_input="YES"
	elif (text_input=="HELP" or text_input=="2"):
		print "If selected a sideband LAST port will be added, if added it is used to specify the end of a packet. Arbitration is only done after a packet has fully passed."
if text_input == "YES":
	INCLUDE_LAST="1"
	fixed_length_writes += 4
else:
	INCLUDE_LAST="0"
header.write("\n#define INCLUDE_LAST ")
header.write(INCLUDE_LAST)
#get the data width
print "What is the data width\n"
bad_input=True
while (bad_input):
	try:
		DATA_WIDTH=str(int(raw_input().strip().lower(),0))
		bad_input=False
		break
	except KeyboardInterrupt:
		raise
	except:
		print "Value entered is not an integer, try again"
		bad_input=True
while (int(DATA_WIDTH,0)%8!=0):
	print "Invalid Data Width, must be a multiple of 8 and positive\n"
	bad_input=True
	while (bad_input):
		try:
			DATA_WIDTH=str(int(raw_input().strip().lower(),0))
			bad_input=False
			break
		except KeyboardInterrupt:
			raise
		except:
			print "Value entered is not an integer, try again"
			bad_input=True
	if (int(DATA_WIDTH,0) < 0):
		DATA_WIDTH="7"
header.write("\n#define DATA_WIDTH ")
header.write(DATA_WIDTH)
name.write(DATA_WIDTH+"_")
#section only needed if there is dest to parse
if (INCLUDE_DEST!="0") or (DEST_IN_DATA!="0"):
	text_input="Garbage"
	while (text_input != "NO") and (text_input != "YES"):
		print "Is output parsing required (YES(1) or NO (0) or HELP(2))\n"
		text_input=raw_input().strip().upper()
		if (text_input=="0"):
			text_input="NO"
		elif (text_input=="1"):
			text_input="YES"
		elif (text_input=="HELP" or text_input=="2"):
			print "Output parsing allows for multiple output ports from the AXIS switch. If enabled, the dest information is used to specify where each packet should go"
	if text_input == "YES":
		header.write("\n#define OUTPUT_PARSING_ENABLE 1")
		fixed_length_writes+=8
		text_input="Garbage"
		while (text_input != "NO") and (text_input != "YES"):
			print "Is masking enabled (YES(1) or NO (0) or HELP(2))?\n"
			text_input=raw_input().strip().upper()
			if (text_input=="0"):
				text_input="NO"
			elif (text_input=="1"):
				text_input="YES"
			elif (text_input=="HELP" or text_input=="2"):
				print "If selected the dest information will be masked by a specified value. This is useful if it is desired that a range of DEST values are sent on a particular port"
		header.write("\n#define dest_mask ")
		if (text_input=="YES"):
			print "What is the mask?"
			bad_input=True
			while (bad_input):
				mask_number_str = raw_input().strip().lower()
				try:
					mask_number=str(int(mask_number_str,0))
					bad_input=False
					break
				except KeyboardInterrupt:
					raise
				except:
					
					print "Value entered is not an integer, try again"
					bad_input=True
			header.write(mask_number)
			name.write(mask_number+"_")
		else:
			header.write("0")
			name.write("0_")
		print "enter the number of output ports \n"
		bad_input=True
		while (bad_input):
			try:
				NUMBER_OF_OUT_PORTS=int(raw_input().strip().lower(),0)
				bad_input=False
				break
			except KeyboardInterrupt:
				raise
			except:
				print "Value entered is not an integer, try again"
				bad_input=True
		while ((NUMBER_OF_OUT_PORTS<1) or (NUMBER_OF_OUT_PORTS>16)):
			print "Invalid number of outports, must be positive value less than 16, try again"
			NUMBER_OF_OUT_PORTS = int(raw_input().strip().upper(),0)
		header.write("\n#define NUMBER_OF_OUT_PORTS ")
		header.write(str(NUMBER_OF_OUT_PORTS))
		fixed_length_writes=(NUMBER_OF_OUT_PORTS)*32
		Current_Port = 0
		while (Current_Port < NUMBER_OF_OUT_PORTS):
			print "Enter the dest for port number %d\n" %(Current_Port)
			bad_input=True
			while (bad_input):
				try:
					DEST_NUMBER=str(int(raw_input().strip().lower(),0))
					bad_input=False
					break
				except KeyboardInterrupt:
					raise
				except:
					print "Value entered is not an integer, try again"
					bad_input=True
			while ((int(DEST_NUMBER,0)).bit_length()>(int(DEST_IN_DATA,0)+int(INCLUDE_DEST,0))):
				print "Invalid DEST does NOt fit in dest bits. Try again\n"
				bad_input=True
				while (bad_input):
					try:
						DEST_NUMBER=str(int(raw_input().strip().lower(),0))
						bad_input=False
						break
					except KeyboardInterrupt:
						raise
					except:
						print "Value entered is not an integer, try again"
						bad_input=True
			header.write("\n#define out_port_%d_dest_address " %(Current_Port))
			header.write(DEST_NUMBER)
			name.write(DEST_NUMBER+"_")
			Current_Port=Current_Port+1
	else:
		header.write("\n#define OUTPUT_PARSING_ENABLE 0")
else:
	print "Since no dest source selected, Output parsing is disabled by default"
name.write(str(fixed_length_writes))
#always initialize clock file with 10, will be updated in future iterations to give tighter requirements
clock_file.write("10")
#close the files
clock_file.close()
header.close()
name.close()
