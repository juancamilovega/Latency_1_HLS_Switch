

//Necessary Imports


#include "switch.h"

//constants

#define DEST_WIDTH (INCLUDE_DEST+DEST_IN_DATA)
#define KEEP_WIDTH DATA_WIDTH/8

//Verify the parameter inputs (Error checking)
//If any of the #error are reachable then the inputs are incorrect

#if DEST_IN_DATA != 0 and INCLUDE_DEST!=0
#error "Can not parse two conflicting dests"
#endif
#if DATA_WIDTH < 0
#error "Data width must be positive"
#endif
#ifdef NUMBER_OF_OUT_PORTS
#if NUMBER_OF_OUT_PORTS < 1
#error "Number of out ports must be a positive non zero value"
#endif
#endif
#if NUMBER_OF_IN_PORTS < 1
#error "Number of in ports must be a positive non zero value"
#endif
#if KEEP_WIDTH*8!=DATA_WIDTH
#error "data not a multiple of 8"
#endif
#if NUMBER_OF_IN_PORTS > 16
#error "Number of In ports exceeds allowable 16 ports"
#endif
#if NUMBER_OF_OUT_PORTS > 16
#error "Number of Out ports exceeds allowable 16 ports"
#endif
struct AXIS_RAW
{
	//data structure representing external interface
	//widths and what is included depend on parameters
#if DATA_WIDTH != 0
    ap_uint<DATA_WIDTH> data;
#if INCLUDE_STRB != 0
    ap_uint<INCLUDE_STRB> strb;
#endif
#if INCLUDE_KEEP != 0
    ap_uint<KEEP_WIDTH> keep;
#endif
#endif
#if INCLUDE_LAST != 0
    ap_uint<1> last;
#endif
#if INCLUDE_ID != 0
    ap_uint<INCLUDE_ID> id;
#endif
#if INCLUDE_DEST != 0
    ap_uint<INCLUDE_DEST> dest;
#endif
#if INCLUDE_USER != 0
    ap_uint<INCLUDE_USER> user;
#endif
    ap_uint<1> valid;
};

const struct AXIS_RAW DUMMY =
{
	//data structure representing external interface
	//widths and what is included depend on parameters
#if DATA_WIDTH != 0
    0,//data
#if INCLUDE_STRB != 0
    0,//strb
#endif
#if INCLUDE_KEEP != 0
    0,//keep
#endif
#endif
#if INCLUDE_LAST != 0
    0,//last
#endif
#if INCLUDE_ID != 0
    0,//ID
#endif
#if INCLUDE_DEST != 0
    0,//DEST
#endif
#if INCLUDE_USER != 0
    0,//USER
#endif
    0//valid
};

void arbitration_function(
#ifdef ROUNDROBIN_ARBITRATION
    ap_uint<4> &roundrobin_stage,
#endif
	ap_uint<1> &arbiter,
	ap_uint<5> &output_sw_reg,
	AXIS_RAW in_port_0,
#if NUMBER_OF_IN_PORTS > 1
    AXIS_RAW in_port_1,
#if NUMBER_OF_IN_PORTS > 2
    AXIS_RAW in_port_2,
#if NUMBER_OF_IN_PORTS > 3
    AXIS_RAW in_port_3,
#if NUMBER_OF_IN_PORTS > 4
    AXIS_RAW in_port_4,
#if NUMBER_OF_IN_PORTS > 5
    AXIS_RAW in_port_5,
#if NUMBER_OF_IN_PORTS > 6
    AXIS_RAW in_port_6,
#if NUMBER_OF_IN_PORTS > 7
    AXIS_RAW in_port_7,
#if NUMBER_OF_IN_PORTS > 8
    AXIS_RAW in_port_8,
#if NUMBER_OF_IN_PORTS > 9
    AXIS_RAW in_port_9,
#if NUMBER_OF_IN_PORTS > 10
    AXIS_RAW in_port_10,
#if NUMBER_OF_IN_PORTS > 11
    AXIS_RAW in_port_11,
#if NUMBER_OF_IN_PORTS > 12
    AXIS_RAW in_port_12,
#if NUMBER_OF_IN_PORTS > 13
    AXIS_RAW in_port_13,
#if NUMBER_OF_IN_PORTS > 14
    AXIS_RAW in_port_14,
#if NUMBER_OF_IN_PORTS > 15
    AXIS_RAW in_port_15,
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#if OUTPUT_PARSING_ENABLE==1
	ap_uint<DEST_WIDTH> &dest_needed,
	ap_uint<DEST_WIDTH> &dest_needed_reg,
#endif
	ap_uint<5> &output_sw,
	AXIS_RAW output_reg_last_valid,
	ap_uint<4> offset
)
{
#pragma HLS inline
#if INCLUDE_LAST !=0
    //if there is no last, then arbitration is done every cycle so there is no if statement
    //use previous input value to determine if we should switch the source
    if ((output_reg_last_valid.last & output_reg_last_valid.valid)| arbiter)
    {
#endif
#ifdef ROUNDROBIN_ARBITRATION
    roundrobin_stage=(roundrobin_stage+1)%NUMBER_OF_IN_PORTS;
#endif
    	//Find the highest priority port with a valid stage
        if (in_port_0.valid)
        {
#if OUTPUT_PARSING_ENABLE == 1
#if dest_mask == 0
#if DEST_IN_DATA==0
        	dest_needed=in_port_0.dest;
        	dest_needed_reg = in_port_0.dest;
#else
        	dest_needed=in_port_0.data.range(511,496);
        	dest_needed_reg=in_port_0.data.range(511,496);
#endif
#else
#if DEST_IN_DATA==0
        	dest_needed=in_port_0.dest& dest_mask;
        	dest_needed_reg = in_port_0.dest& dest_mask;
#else
        	dest_needed=in_port_0.data.range(511,496)& dest_mask;
        	dest_needed_reg=in_port_0.data.range(511,496)& dest_mask;
#endif
#endif
#endif
            output_sw = (offset)%NUMBER_OF_IN_PORTS;
            arbiter = 0;
            output_sw_reg = (offset)%NUMBER_OF_IN_PORTS;
        }
#if NUMBER_OF_IN_PORTS > 1
        else if (in_port_1.valid)
        {
#if OUTPUT_PARSING_ENABLE == 1
#if dest_mask == 0
#if DEST_IN_DATA==0
        	dest_needed=in_port_1.dest;
        	dest_needed_reg = in_port_1.dest;
#else
        	dest_needed=in_port_1.data.range(511,496);
        	dest_needed_reg=in_port_1.data.range(511,496);
#endif
#else
#if DEST_IN_DATA==0
        	dest_needed=in_port_1.dest& dest_mask;
        	dest_needed_reg = in_port_1.dest& dest_mask;
#else
        	dest_needed=in_port_1.data.range(511,496)& dest_mask;
        	dest_needed_reg=in_port_1.data.range(511,496)& dest_mask;
#endif
#endif
#endif
            output_sw = (1+offset)%NUMBER_OF_IN_PORTS;
            arbiter = 0;
            output_sw_reg = (1+offset)%NUMBER_OF_IN_PORTS;
        }
#endif
#if NUMBER_OF_IN_PORTS > 2
        else if (in_port_2.valid)
        {
#if OUTPUT_PARSING_ENABLE == 1
#if dest_mask == 0
#if DEST_IN_DATA==0
        	dest_needed=in_port_2.dest;
        	dest_needed_reg = in_port_2.dest;
#else
        	dest_needed=in_port_2.data.range(511,496);
        	dest_needed_reg=in_port_2.data.range(511,496);
#endif
#else
#if DEST_IN_DATA==0
        	dest_needed=in_port_2.dest& dest_mask;
        	dest_needed_reg = in_port_2.dest& dest_mask;
#else
        	dest_needed=in_port_2.data.range(511,496)& dest_mask;
        	dest_needed_reg=in_port_2.data.range(511,496)& dest_mask;
#endif
#endif
#endif
            output_sw = (2+offset)%NUMBER_OF_IN_PORTS;
            arbiter = 0;
            output_sw_reg = (2+offset)%NUMBER_OF_IN_PORTS;;
        }
#endif
#if NUMBER_OF_IN_PORTS > 3
        else if (in_port_3.valid)
        {
#if OUTPUT_PARSING_ENABLE == 1
#if dest_mask == 0
#if DEST_IN_DATA==0
        	dest_needed=in_port_3.dest;
        	dest_needed_reg = in_port_3.dest;
#else
        	dest_needed=in_port_3.data.range(511,496);
        	dest_needed_reg=in_port_3.data.range(511,496);
#endif
#else
#if DEST_IN_DATA==0
        	dest_needed=in_port_3.dest& dest_mask;
        	dest_needed_reg = in_port_3.dest& dest_mask;
#else
        	dest_needed=in_port_3.data.range(511,496)& dest_mask;
        	dest_needed_reg=in_port_3.data.range(511,496)& dest_mask;
#endif
#endif
#endif
            output_sw = (3+offset)%NUMBER_OF_IN_PORTS;
            arbiter = 0;
            output_sw_reg = (3+offset)%NUMBER_OF_IN_PORTS;
        }
#endif
#if NUMBER_OF_IN_PORTS > 4
        else if (in_port_4.valid)
        {
#if OUTPUT_PARSING_ENABLE == 1
#if dest_mask == 0
#if DEST_IN_DATA==0
        	dest_needed=in_port_4.dest;
        	dest_needed_reg = in_port_4.dest;
#else
        	dest_needed=in_port_4.data.range(511,496);
        	dest_needed_reg=in_port_4.data.range(511,496);
#endif
#else
#if DEST_IN_DATA==0
        	dest_needed=in_port_4.dest& dest_mask;
        	dest_needed_reg = in_port_4.dest& dest_mask;
#else
        	dest_needed=in_port_4.data.range(511,496)& dest_mask;
        	dest_needed_reg=in_port_4.data.range(511,496)& dest_mask;
#endif
#endif
#endif
            output_sw = (4+offset)%NUMBER_OF_IN_PORTS;
            arbiter = 0;
            output_sw_reg = (4+offset)%NUMBER_OF_IN_PORTS;
        }
#endif
#if NUMBER_OF_IN_PORTS > 5
        else if (in_port_5.valid)
        {
#if OUTPUT_PARSING_ENABLE == 1
#if dest_mask == 0
#if DEST_IN_DATA==0
        	dest_needed=in_port_5.dest;
        	dest_needed_reg = in_port_5.dest;
#else
        	dest_needed=in_port_5.data.range(511,496);
        	dest_needed_reg=in_port_5.data.range(511,496);
#endif
#else
#if DEST_IN_DATA==0
        	dest_needed=in_port_5.dest& dest_mask;
        	dest_needed_reg = in_port_5.dest& dest_mask;
#else
        	dest_needed=in_port_5.data.range(511,496)& dest_mask;
        	dest_needed_reg=in_port_5.data.range(511,496)& dest_mask;
#endif
#endif
#endif
            output_sw = (5+offset)%NUMBER_OF_IN_PORTS;
            arbiter = 0;
            output_sw_reg = (5+offset)%NUMBER_OF_IN_PORTS;
        }
#endif
#if NUMBER_OF_IN_PORTS > 6
        else if (in_port_6.valid)
        {
#if OUTPUT_PARSING_ENABLE == 1
#if dest_mask == 0
#if DEST_IN_DATA==0
        	dest_needed=in_port_6.dest;
        	dest_needed_reg = in_port_6.dest;
#else
        	dest_needed=in_port_6.data.range(511,496);
        	dest_needed_reg=in_port_6.data.range(511,496);
#endif
#else
#if DEST_IN_DATA==0
        	dest_needed=in_port_6.dest& dest_mask;
        	dest_needed_reg = in_port_6.dest& dest_mask;
#else
        	dest_needed=in_port_6.data.range(511,496)& dest_mask;
        	dest_needed_reg=in_port_6.data.range(511,496)& dest_mask;
#endif
#endif
#endif
            output_sw = (6+offset)%NUMBER_OF_IN_PORTS;
            arbiter = 0;
            output_sw_reg = (6+offset)%NUMBER_OF_IN_PORTS;
        }
#endif
#if NUMBER_OF_IN_PORTS > 7
        else if (in_port_7.valid)
        {
#if OUTPUT_PARSING_ENABLE == 1
#if dest_mask == 0
#if DEST_IN_DATA==0
        	dest_needed=in_port_7.dest;
        	dest_needed_reg = in_port_7.dest;
#else
        	dest_needed=in_port_7.data.range(511,496);
        	dest_needed_reg=in_port_7.data.range(511,496);
#endif
#else
#if DEST_IN_DATA==0
        	dest_needed=in_port_7.dest& dest_mask;
        	dest_needed_reg = in_port_7.dest& dest_mask;
#else
        	dest_needed=in_port_7.data.range(511,496)& dest_mask;
        	dest_needed_reg=in_port_7.data.range(511,496)& dest_mask;
#endif
#endif
#endif
            output_sw = (7+offset)%NUMBER_OF_IN_PORTS;
            arbiter = 0;
            output_sw_reg = (7+offset)%NUMBER_OF_IN_PORTS;
        }
#endif
#if NUMBER_OF_IN_PORTS > 8
        else if (in_port_8.valid)
        {
#if OUTPUT_PARSING_ENABLE == 1
#if dest_mask == 0
#if DEST_IN_DATA==0
        	dest_needed=in_port_8.dest;
        	dest_needed_reg = in_port_8.dest;
#else
        	dest_needed=in_port_8.data.range(511,496);
        	dest_needed_reg=in_port_8.data.range(511,496);
#endif
#else
#if DEST_IN_DATA==0
        	dest_needed=in_port_8.dest& dest_mask;
        	dest_needed_reg = in_port_8.dest& dest_mask;
#else
        	dest_needed=in_port_8.data.range(511,496)& dest_mask;
        	dest_needed_reg=in_port_8.data.range(511,496)& dest_mask;
#endif
#endif
#endif
            output_sw = (8+offset)%NUMBER_OF_IN_PORTS;
            arbiter = 0;
            output_sw_reg = (8+offset)%NUMBER_OF_IN_PORTS;
        }
#endif
#if NUMBER_OF_IN_PORTS > 9
        else if (in_port_9.valid)
        {
#if OUTPUT_PARSING_ENABLE == 1
#if dest_mask == 0
#if DEST_IN_DATA==0
        	dest_needed=in_port_9.dest;
        	dest_needed_reg = in_port_9.dest;
#else
        	dest_needed=in_port_9.data.range(511,496);
        	dest_needed_reg=in_port_9.data.range(511,496);
#endif
#else
#if DEST_IN_DATA==0
        	dest_needed=in_port_9.dest& dest_mask;
        	dest_needed_reg = in_port_9.dest& dest_mask;
#else
        	dest_needed=in_port_9.data.range(511,496)& dest_mask;
        	dest_needed_reg=in_port_9.data.range(511,496)& dest_mask;
#endif
#endif
#endif
            output_sw = (9+offset)%NUMBER_OF_IN_PORTS;
            arbiter = 0;
            output_sw_reg = (9+offset)%NUMBER_OF_IN_PORTS;
        }
#endif
#if NUMBER_OF_IN_PORTS > 10
        else if (in_port_10.valid)
        {
#if OUTPUT_PARSING_ENABLE == 1
#if dest_mask == 0
#if DEST_IN_DATA==0
        	dest_needed=in_port_10.dest;
        	dest_needed_reg = in_port_10.dest;
#else
        	dest_needed=in_port_10.data.range(511,496);
        	dest_needed_reg=in_port_10.data.range(511,496);
#endif
#else
#if DEST_IN_DATA==0
        	dest_needed=in_port_10.dest& dest_mask;
        	dest_needed_reg = in_port_10.dest& dest_mask;
#else
        	dest_needed=in_port_10.data.range(511,496)& dest_mask;
        	dest_needed_reg=in_port_10.data.range(511,496)& dest_mask;
#endif
#endif
#endif
            output_sw = (10+offset)%NUMBER_OF_IN_PORTS;
            arbiter = 0;
            output_sw_reg = (10+offset)%NUMBER_OF_IN_PORTS;
        }
#endif
#if NUMBER_OF_IN_PORTS > 11
        else if (in_port_11.valid)
        {
#if OUTPUT_PARSING_ENABLE == 1
#if dest_mask == 0
#if DEST_IN_DATA==0
        	dest_needed=in_port_11.dest;
        	dest_needed_reg = in_port_11.dest;
#else
        	dest_needed=in_port_11.data.range(511,496);
        	dest_needed_reg=in_port_11.data.range(511,496);
#endif
#else
#if DEST_IN_DATA==0
        	dest_needed=in_port_11.dest& dest_mask;
        	dest_needed_reg = in_port_11.dest& dest_mask;
#else
        	dest_needed=in_port_11.data.range(511,496)& dest_mask;
        	dest_needed_reg=in_port_11.data.range(511,496)& dest_mask;
#endif
#endif
#endif
            output_sw = (11+offset)%NUMBER_OF_IN_PORTS;
            arbiter = 0;
            output_sw_reg = (11+offset)%NUMBER_OF_IN_PORTS;
        }
#endif
#if NUMBER_OF_IN_PORTS > 12
        else if (in_port_12.valid)
        {
#if OUTPUT_PARSING_ENABLE == 1
#if dest_mask == 0
#if DEST_IN_DATA==0
        	dest_needed=in_port_12.dest;
        	dest_needed_reg = in_port_12.dest;
#else
        	dest_needed=in_port_12.data.range(511,496);
        	dest_needed_reg=in_port_12.data.range(511,496);
#endif
#else
#if DEST_IN_DATA==0
        	dest_needed=in_port_12.dest& dest_mask;
        	dest_needed_reg = in_port_12.dest& dest_mask;
#else
        	dest_needed=in_port_12.data.range(511,496)& dest_mask;
        	dest_needed_reg=in_port_12.data.range(511,496)& dest_mask;
#endif
#endif
#endif
            output_sw = (12+offset)%NUMBER_OF_IN_PORTS;
            arbiter = 0;
            output_sw_reg = (12+offset)%NUMBER_OF_IN_PORTS;
        }
#endif
#if NUMBER_OF_IN_PORTS > 13
        else if (in_port_13.valid)
        {
#if OUTPUT_PARSING_ENABLE == 1
#if dest_mask == 0
#if DEST_IN_DATA==0
        	dest_needed=in_port_13.dest;
        	dest_needed_reg = in_port_13.dest;
#else
        	dest_needed=in_port_13.data.range(511,496);
        	dest_needed_reg=in_port_13.data.range(511,496);
#endif
#else
#if DEST_IN_DATA==0
        	dest_needed=in_port_13.dest& dest_mask;
        	dest_needed_reg = in_port_13.dest& dest_mask;
#else
        	dest_needed=in_port_13.data.range(511,496)& dest_mask;
        	dest_needed_reg=in_port_13.data.range(511,496)& dest_mask;
#endif
#endif
#endif
            output_sw = (13+offset)%NUMBER_OF_IN_PORTS;
            arbiter = 0;
            output_sw_reg = (13+offset)%NUMBER_OF_IN_PORTS;
        }
#endif
#if NUMBER_OF_IN_PORTS > 14
        else if (in_port_14.valid)
        {
#if OUTPUT_PARSING_ENABLE == 1
#if dest_mask == 0
#if DEST_IN_DATA==0
        	dest_needed=in_port_14.dest;
        	dest_needed_reg = in_port_14.dest;
#else
        	dest_needed=in_port_14.data.range(511,496);
        	dest_needed_reg=in_port_14.data.range(511,496);
#endif
#else
#if DEST_IN_DATA==0
        	dest_needed=in_port_14.dest& dest_mask;
        	dest_needed_reg = in_port_14.dest& dest_mask;
#else
        	dest_needed=in_port_14.data.range(511,496)& dest_mask;
        	dest_needed_reg=in_port_14.data.range(511,496)& dest_mask;
#endif
#endif
#endif
            output_sw = (14+offset)%NUMBER_OF_IN_PORTS;
            arbiter = 0;
            output_sw_reg = (14+offset)%NUMBER_OF_IN_PORTS;
        }
#endif
#if NUMBER_OF_IN_PORTS > 15
        else if (in_port_15.valid)
        {
#if OUTPUT_PARSING_ENABLE == 1
#if dest_mask == 0
#if DEST_IN_DATA==0
        	dest_needed=in_port_15.dest;
        	dest_needed_reg = in_port_15.dest;
#else
        	dest_needed=in_port_15.data.range(511,496);
        	dest_needed_reg=in_port_15.data.range(511,496);
#endif
#else
#if DEST_IN_DATA==0
        	dest_needed=in_port_15.dest& dest_mask;
        	dest_needed_reg = in_port_15.dest& dest_mask;
#else
        	dest_needed=in_port_15.data.range(511,496)& dest_mask;
        	dest_needed_reg=in_port_15.data.range(511,496)& dest_mask;
#endif
#endif
#endif
            output_sw = (15+offset)%NUMBER_OF_IN_PORTS;
            arbiter = 0;
            output_sw_reg = (15+offset)%NUMBER_OF_IN_PORTS;
        }
#endif
        else
        {
        	//no candidate found
        	//keep the switch as it is
            output_sw = output_sw_reg;
            //indicate we should re-check next stage
            arbiter = 1;
#if OUTPUT_PARSING_ENABLE == 1
            dest_needed = dest_needed_reg;
#endif
        }
#if INCLUDE_LAST !=0
    }
    else
    {
    	//Indicates there is a last and it was not 1. We are in the middle of a packet
    	//keep the switch as it is
    	output_sw = output_sw_reg;
#if OUTPUT_PARSING_ENABLE == 1
    	dest_needed = dest_needed_reg;
#endif
    }
#endif
}



void AXIS_switch
(
	//Include the input ports
    ap_uint<1> &in_port_0_ready,
#if NUMBER_OF_IN_PORTS > 1
    AXIS_RAW in_port_1,
    ap_uint<1> &in_port_1_ready,
#if NUMBER_OF_IN_PORTS > 2
    AXIS_RAW in_port_2,
    ap_uint<1> &in_port_2_ready,
#if NUMBER_OF_IN_PORTS > 3
    AXIS_RAW in_port_3,
    ap_uint<1> &in_port_3_ready,
#if NUMBER_OF_IN_PORTS > 4
    AXIS_RAW in_port_4,
    ap_uint<1> &in_port_4_ready,
#if NUMBER_OF_IN_PORTS > 5
    AXIS_RAW in_port_5,
    ap_uint<1> &in_port_5_ready,
#if NUMBER_OF_IN_PORTS > 6
    AXIS_RAW in_port_6,
    ap_uint<1> &in_port_6_ready,
#if NUMBER_OF_IN_PORTS > 7
    AXIS_RAW in_port_7,
    ap_uint<1> &in_port_7_ready,
#if NUMBER_OF_IN_PORTS > 8
    AXIS_RAW in_port_8,
    ap_uint<1> &in_port_8_ready,
#if NUMBER_OF_IN_PORTS > 9
    AXIS_RAW in_port_9,
    ap_uint<1> &in_port_9_ready,
#if NUMBER_OF_IN_PORTS > 10
    AXIS_RAW in_port_10,
    ap_uint<1> &in_port_10_ready,
#if NUMBER_OF_IN_PORTS > 11
    AXIS_RAW in_port_11,
    ap_uint<1> &in_port_11_ready,
#if NUMBER_OF_IN_PORTS > 12
    AXIS_RAW in_port_12,
    ap_uint<1> &in_port_12_ready,
#if NUMBER_OF_IN_PORTS > 13
    AXIS_RAW in_port_13,
    ap_uint<1> &in_port_13_ready,
#if NUMBER_OF_IN_PORTS > 14
    AXIS_RAW in_port_14,
    ap_uint<1> &in_port_14_ready,
#if NUMBER_OF_IN_PORTS > 15
    AXIS_RAW in_port_15,
    ap_uint<1> &in_port_15_ready,
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
	//include the output ports
#if OUTPUT_PARSING_ENABLE == 1
	AXIS_RAW &out_port_0,
	ap_uint<1> out_port_0_ready,
#if NUMBER_OF_OUT_PORTS > 1
	AXIS_RAW &out_port_1,
	ap_uint<1> out_port_1_ready,
#endif
#if NUMBER_OF_OUT_PORTS > 2
	AXIS_RAW &out_port_2,
	ap_uint<1> out_port_2_ready,
#endif
#if NUMBER_OF_OUT_PORTS > 3
	AXIS_RAW &out_port_3,
	ap_uint<1> out_port_3_ready,
#endif
#if NUMBER_OF_OUT_PORTS > 4
	AXIS_RAW &out_port_4,
	ap_uint<1> out_port_4_ready,
#endif
#if NUMBER_OF_OUT_PORTS > 5
	AXIS_RAW &out_port_5,
	ap_uint<1> out_port_5_ready,
#endif
#if NUMBER_OF_OUT_PORTS > 6
	AXIS_RAW &out_port_6,
	ap_uint<1> out_port_6_ready,
#endif
#if NUMBER_OF_OUT_PORTS > 7
	AXIS_RAW &out_port_7,
	ap_uint<1> out_port_7_ready,
#endif
#if NUMBER_OF_OUT_PORTS > 8
	AXIS_RAW &out_port_8,
	ap_uint<1> out_port_8_ready,
#endif
#if NUMBER_OF_OUT_PORTS > 9
	AXIS_RAW &out_port_9,
	ap_uint<1> out_port_9_ready,
#endif
#if NUMBER_OF_OUT_PORTS > 10
	AXIS_RAW &out_port_10,
	ap_uint<1> out_port_10_ready,
#endif
#if NUMBER_OF_OUT_PORTS > 11
	AXIS_RAW &out_port_11,
	ap_uint<1> out_port_11_ready,
#endif
#if NUMBER_OF_OUT_PORTS > 12
	AXIS_RAW &out_port_12,
	ap_uint<1> out_port_12_ready,
#endif
#if NUMBER_OF_OUT_PORTS > 13
	AXIS_RAW &out_port_13,
	ap_uint<1> out_port_13_ready,
#endif
#if NUMBER_OF_OUT_PORTS > 14
	AXIS_RAW &out_port_14,
	ap_uint<1> out_port_14_ready,
#endif
#if NUMBER_OF_OUT_PORTS > 15
	AXIS_RAW &out_port_15,
	ap_uint<1> out_port_15_ready,
#endif
	//Include the default port
	AXIS_RAW &out_port_default,
	ap_uint<1> out_port_default_ready,
#else
    AXIS_RAW &out_port,
    ap_uint<1> out_port_ready,
#endif
	ap_uint<1> &DEBUG_arbiter,
	ap_uint<4> &DEBUG_roundrobin_stage,
	ap_uint<5> &DEBUG_output_sw_reg,
	AXIS_RAW &DEBUG_output_reg_last_valid,
    AXIS_RAW in_port_0
)
{
//Set the function as dataflow with no start signal
#pragma HLS DATAFLOW
#pragma HLS INTERFACE ap_ctrl_none port=return
//Tell HLS to not treat any of the ports in any special way, gives us full control
#if OUTPUT_PARSING_ENABLE == 1
#pragma HLS INTERFACE ap_none port=out_port_0
#pragma HLS INTERFACE ap_none port=out_port_default
#if NUMBER_OF_OUT_PORTS > 1
#pragma HLS INTERFACE ap_none port=out_port_1
#endif
#if NUMBER_OF_OUT_PORTS > 2
#pragma HLS INTERFACE ap_none port=out_port_2
#endif
#if NUMBER_OF_OUT_PORTS > 3
#pragma HLS INTERFACE ap_none port=out_port_3
#endif
#if NUMBER_OF_OUT_PORTS > 4
#pragma HLS INTERFACE ap_none port=out_port_4
#endif
#if NUMBER_OF_OUT_PORTS > 5
#pragma HLS INTERFACE ap_none port=out_port_5
#endif
#if NUMBER_OF_OUT_PORTS > 6
#pragma HLS INTERFACE ap_none port=out_port_6
#endif
#if NUMBER_OF_OUT_PORTS > 7
#pragma HLS INTERFACE ap_none port=out_port_7
#endif
#if NUMBER_OF_OUT_PORTS > 8
#pragma HLS INTERFACE ap_none port=out_port_8
#endif
#if NUMBER_OF_OUT_PORTS > 9
#pragma HLS INTERFACE ap_none port=out_port_9
#endif
#if NUMBER_OF_OUT_PORTS > 10
#pragma HLS INTERFACE ap_none port=out_port_10
#endif
#if NUMBER_OF_OUT_PORTS > 11
#pragma HLS INTERFACE ap_none port=out_port_11
#endif
#if NUMBER_OF_OUT_PORTS > 12
#pragma HLS INTERFACE ap_none port=out_port_12
#endif
#if NUMBER_OF_OUT_PORTS > 13
#pragma HLS INTERFACE ap_none port=out_port_13
#endif
#if NUMBER_OF_OUT_PORTS > 14
#pragma HLS INTERFACE ap_none port=out_port_14
#endif
#if NUMBER_OF_OUT_PORTS > 15
#pragma HLS INTERFACE ap_none port=out_port_15
#endif
#else
#pragma HLS INTERFACE ap_none port=out_port
#endif
#pragma HLS INTERFACE ap_none port=in_port_0
#pragma HLS INTERFACE ap_none port=in_port_0_ready
#if NUMBER_OF_IN_PORTS>1
#pragma HLS INTERFACE ap_none port=in_port_1
#pragma HLS INTERFACE ap_none port=in_port_1_ready
#if NUMBER_OF_IN_PORTS>2
#pragma HLS INTERFACE ap_none port=in_port_2
#pragma HLS INTERFACE ap_none port=in_port_2_ready
#if NUMBER_OF_IN_PORTS>3
#pragma HLS INTERFACE ap_none port=in_port_3
#pragma HLS INTERFACE ap_none port=in_port_3_ready
#if NUMBER_OF_IN_PORTS>4
#pragma HLS INTERFACE ap_none port=in_port_4
#pragma HLS INTERFACE ap_none port=in_port_4_ready
#if NUMBER_OF_IN_PORTS>5
#pragma HLS INTERFACE ap_none port=in_port_5
#pragma HLS INTERFACE ap_none port=in_port_5_ready
#if NUMBER_OF_IN_PORTS>6
#pragma HLS INTERFACE ap_none port=in_port_6
#pragma HLS INTERFACE ap_none port=in_port_6_ready
#if NUMBER_OF_IN_PORTS>7
#pragma HLS INTERFACE ap_none port=in_port_7
#pragma HLS INTERFACE ap_none port=in_port_7_ready
#if NUMBER_OF_IN_PORTS>8
#pragma HLS INTERFACE ap_none port=in_port_8
#pragma HLS INTERFACE ap_none port=in_port_8_ready
#if NUMBER_OF_IN_PORTS>9
#pragma HLS INTERFACE ap_none port=in_port_9
#pragma HLS INTERFACE ap_none port=in_port_9_ready
#if NUMBER_OF_IN_PORTS>10
#pragma HLS INTERFACE ap_none port=in_port_10
#pragma HLS INTERFACE ap_none port=in_port_10_ready
#if NUMBER_OF_IN_PORTS>11
#pragma HLS INTERFACE ap_none port=in_port_11
#pragma HLS INTERFACE ap_none port=in_port_11_ready
#if NUMBER_OF_IN_PORTS>12
#pragma HLS INTERFACE ap_none port=in_port_12
#pragma HLS INTERFACE ap_none port=in_port_12_ready
#if NUMBER_OF_IN_PORTS>13
#pragma HLS INTERFACE ap_none port=in_port_13
#pragma HLS INTERFACE ap_none port=in_port_13_ready
#if NUMBER_OF_IN_PORTS>14
#pragma HLS INTERFACE ap_none port=in_port_14
#pragma HLS INTERFACE ap_none port=in_port_14_ready
#if NUMBER_OF_IN_PORTS>15
#pragma HLS INTERFACE ap_none port=in_port_15
#pragma HLS INTERFACE ap_none port=in_port_15_ready
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
	//set up the variables
#ifdef ROUNDROBIN_ARBITRATION
	static ap_uint<4> roundrobin_stage = 0;
	DEBUG_roundrobin_stage = roundrobin_stage;
#endif
	ap_uint<5> output_sw;//switch value this time
    static ap_uint<5> output_sw_reg = 0;//switch value last time
    DEBUG_output_sw_reg=output_sw_reg;
    static AXIS_RAW output_reg = DUMMY;//register holding the previous input value
    static AXIS_RAW output_reg_last_valid = DUMMY;
    DEBUG_output_reg_last_valid = output_reg_last_valid;
    static ap_uint<1> arbiter = 1;//indicates we should arbitrate this cycle
    DEBUG_arbiter=arbiter;
    //Write previous input value to the output
#if OUTPUT_PARSING_ENABLE == 1
    ap_uint<1> out_port_ready;
    ap_uint<DEST_WIDTH> dest_needed;
    static ap_uint<DEST_WIDTH> dest_needed_reg=0;
#if dest_mask == 0
    ap_uint<DEST_WIDTH> out_dest_to_use = dest_needed_reg;
#else
    ap_uint<DEST_WIDTH> out_dest_to_use = dest_needed_reg & dest_mask;
#endif
    //TODO: set other ports to dummy
    //write output_reg to the port selected this time
    //write dummy to all other ports
    switch (out_dest_to_use)
    {
    case out_port_0_dest_address:
    	out_port_0=output_reg;
    	out_port_default=DUMMY;
#if NUMBER_OF_OUT_PORTS > 1
    	out_port_1=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 2
    	out_port_2=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 3
    	out_port_3=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 4
    	out_port_4=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 5
    	out_port_5=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 6
    	out_port_6=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 7
    	out_port_7=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 8
    	out_port_8=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 9
    	out_port_9=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 10
    	out_port_10=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 11
    	out_port_11=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 12
    	out_port_12=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 13
    	out_port_13=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 14
    	out_port_14=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 15
    	out_port_15=DUMMY;
#endif
    	break;
#if NUMBER_OF_OUT_PORTS > 1
    case out_port_1_dest_address:
    	out_port_1=output_reg;
    	out_port_0=DUMMY;
    	out_port_default=DUMMY;
#if NUMBER_OF_OUT_PORTS > 2
    	out_port_2=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 3
    	out_port_3=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 4
    	out_port_4=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 5
    	out_port_5=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 6
    	out_port_6=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 7
    	out_port_7=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 8
    	out_port_8=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 9
    	out_port_9=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 10
    	out_port_10=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 11
    	out_port_11=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 12
    	out_port_12=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 13
    	out_port_13=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 14
    	out_port_14=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 15
    	out_port_15=DUMMY;
#endif
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 2
    case out_port_2_dest_address:
    	out_port_2=output_reg;
    	out_port_0=DUMMY;
    	out_port_default=DUMMY;
#if NUMBER_OF_OUT_PORTS > 1
    	out_port_1=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 3
    	out_port_3=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 4
    	out_port_4=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 5
    	out_port_5=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 6
    	out_port_6=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 7
    	out_port_7=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 8
    	out_port_8=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 9
    	out_port_9=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 10
    	out_port_10=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 11
    	out_port_11=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 12
    	out_port_12=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 13
    	out_port_13=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 14
    	out_port_14=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 15
    	out_port_15=DUMMY;
#endif
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 3
    case out_port_3_dest_address:
    	out_port_3=output_reg;
    	out_port_0=DUMMY;
    	out_port_default=DUMMY;
#if NUMBER_OF_OUT_PORTS > 1
    	out_port_1=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 2
    	out_port_2=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 4
    	out_port_4=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 5
    	out_port_5=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 6
    	out_port_6=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 7
    	out_port_7=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 8
    	out_port_8=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 9
    	out_port_9=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 10
    	out_port_10=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 11
    	out_port_11=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 12
    	out_port_12=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 13
    	out_port_13=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 14
    	out_port_14=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 15
    	out_port_15=DUMMY;
#endif
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 4
    case out_port_4_dest_address:
    	out_port_4=output_reg;
    	out_port_0=DUMMY;
    	out_port_default=DUMMY;
#if NUMBER_OF_OUT_PORTS > 1
    	out_port_1=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 2
    	out_port_2=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 3
    	out_port_3=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 5
    	out_port_5=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 6
    	out_port_6=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 7
    	out_port_7=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 8
    	out_port_8=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 9
    	out_port_9=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 10
    	out_port_10=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 11
    	out_port_11=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 12
    	out_port_12=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 13
    	out_port_13=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 14
    	out_port_14=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 15
    	out_port_15=DUMMY;
#endif
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 5
    case out_port_5_dest_address:
    	out_port_5=output_reg;
    	break;
#if NUMBER_OF_OUT_PORTS > 1
    	out_port_1=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 2
    	out_port_2=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 3
    	out_port_3=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 4
    	out_port_4=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 6
    	out_port_6=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 7
    	out_port_7=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 8
    	out_port_8=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 9
    	out_port_9=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 10
    	out_port_10=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 11
    	out_port_11=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 12
    	out_port_12=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 13
    	out_port_13=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 14
    	out_port_14=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 15
    	out_port_15=DUMMY;
#endif
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 6
    case out_port_6_dest_address:
    	out_port_6=output_reg;
    	out_port_0=DUMMY;
    	out_port_default=DUMMY;
#if NUMBER_OF_OUT_PORTS > 1
    	out_port_1=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 2
    	out_port_2=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 3
    	out_port_3=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 4
    	out_port_4=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 5
    	out_port_5=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 7
    	out_port_7=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 8
    	out_port_8=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 9
    	out_port_9=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 10
    	out_port_10=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 11
    	out_port_11=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 12
    	out_port_12=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 13
    	out_port_13=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 14
    	out_port_14=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 15
    	out_port_15=DUMMY;
#endif
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 7
    case out_port_7_dest_address:
    	out_port_7=output_reg;
    	out_port_0=DUMMY;
    	out_port_default=DUMMY;
#if NUMBER_OF_OUT_PORTS > 1
    	out_port_1=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 2
    	out_port_2=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 3
    	out_port_3=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 4
    	out_port_4=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 5
    	out_port_5=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 6
    	out_port_6=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 8
    	out_port_8=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 9
    	out_port_9=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 10
    	out_port_10=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 11
    	out_port_11=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 12
    	out_port_12=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 13
    	out_port_13=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 14
    	out_port_14=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 15
    	out_port_15=DUMMY;
#endif
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 8
    case out_port_8_dest_address:
    	out_port_8=output_reg;
    	out_port_0=DUMMY;
    	out_port_default=DUMMY;
#if NUMBER_OF_OUT_PORTS > 1
    	out_port_1=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 2
    	out_port_2=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 3
    	out_port_3=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 4
    	out_port_4=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 5
    	out_port_5=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 6
    	out_port_6=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 7
    	out_port_7=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 9
    	out_port_9=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 10
    	out_port_10=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 11
    	out_port_11=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 12
    	out_port_12=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 13
    	out_port_13=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 14
    	out_port_14=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 15
    	out_port_15=DUMMY;
#endif
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 9
    case out_port_9_dest_address:
    	out_port_9=output_reg;
    	out_port_0=DUMMY;
    	out_port_default=DUMMY;
#if NUMBER_OF_OUT_PORTS > 1
    	out_port_1=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 2
    	out_port_2=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 3
    	out_port_3=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 4
    	out_port_4=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 5
    	out_port_5=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 6
    	out_port_6=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 7
    	out_port_7=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 8
    	out_port_8=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 10
    	out_port_10=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 11
    	out_port_11=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 12
    	out_port_12=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 13
    	out_port_13=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 14
    	out_port_14=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 15
    	out_port_15=DUMMY;
#endif
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 10
    case out_port_10_dest_address:
    	out_port_10=output_reg;
    	out_port_0=DUMMY;
    	out_port_default=DUMMY;
#if NUMBER_OF_OUT_PORTS > 1
    	out_port_1=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 2
    	out_port_2=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 3
    	out_port_3=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 4
    	out_port_4=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 5
    	out_port_5=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 6
    	out_port_6=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 7
    	out_port_7=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 8
    	out_port_8=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 9
    	out_port_9=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 11
    	out_port_11=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 12
    	out_port_12=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 13
    	out_port_13=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 14
    	out_port_14=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 15
    	out_port_15=DUMMY;
#endif
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 11
    case out_port_11_dest_address:
    	out_port_11=output_reg;
    	out_port_0=DUMMY;
    	out_port_default=DUMMY;
#if NUMBER_OF_OUT_PORTS > 1
    	out_port_1=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 2
    	out_port_2=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 3
    	out_port_3=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 4
    	out_port_4=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 5
    	out_port_5=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 6
    	out_port_6=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 7
    	out_port_7=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 8
    	out_port_8=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 9
    	out_port_9=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 10
    	out_port_10=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 12
    	out_port_12=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 13
    	out_port_13=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 14
    	out_port_14=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 15
    	out_port_15=DUMMY;
#endif
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 12
    case out_port_12_dest_address:
    	out_port_12=output_reg;
    	out_port_0=DUMMY;
    	out_port_default=DUMMY;
#if NUMBER_OF_OUT_PORTS > 1
    	out_port_1=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 2
    	out_port_2=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 3
    	out_port_3=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 4
    	out_port_4=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 5
    	out_port_5=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 6
    	out_port_6=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 7
    	out_port_7=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 8
    	out_port_8=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 9
    	out_port_9=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 10
    	out_port_10=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 11
    	out_port_11=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 13
    	out_port_13=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 14
    	out_port_14=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 15
    	out_port_15=DUMMY;
#endif
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 13
    case out_port_13_dest_address:
    	out_port_13=output_reg;
    	out_port_0=DUMMY;
    	out_port_default=DUMMY;
#if NUMBER_OF_OUT_PORTS > 1
    	out_port_1=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 2
    	out_port_2=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 3
    	out_port_3=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 4
    	out_port_4=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 5
    	out_port_5=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 6
    	out_port_6=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 7
    	out_port_7=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 8
    	out_port_8=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 9
    	out_port_9=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 10
    	out_port_10=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 11
    	out_port_11=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 12
    	out_port_12=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 14
    	out_port_14=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 15
    	out_port_15=DUMMY;
#endif
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 14
    case out_port_14_dest_address:
    	out_port_14=output_reg;
    	out_port_0=DUMMY;
    	out_port_default=DUMMY;
#if NUMBER_OF_OUT_PORTS > 1
    	out_port_1=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 2
    	out_port_2=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 3
    	out_port_3=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 4
    	out_port_4=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 5
    	out_port_5=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 6
    	out_port_6=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 7
    	out_port_7=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 8
    	out_port_8=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 9
    	out_port_9=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 10
    	out_port_10=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 11
    	out_port_11=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 12
    	out_port_12=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 13
    	out_port_13=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 15
    	out_port_15=DUMMY;
#endif
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 15
    case out_port_15_dest_address:
    	out_port_15=output_reg;
    	out_port_0=DUMMY;
    	out_port_default=DUMMY;
#if NUMBER_OF_OUT_PORTS > 1
    	out_port_1=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 2
    	out_port_2=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 3
    	out_port_3=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 4
    	out_port_4=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 5
    	out_port_5=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 6
    	out_port_6=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 7
    	out_port_7=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 8
    	out_port_8=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 9
    	out_port_9=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 10
    	out_port_10=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 11
    	out_port_11=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 12
    	out_port_12=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 13
    	out_port_13=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 14
    	out_port_14=DUMMY;
#endif
    	break;
#endif
    default:
    	out_port_default=output_reg;
    	out_port_0=DUMMY;
#if NUMBER_OF_OUT_PORTS > 1
    	out_port_1=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 2
    	out_port_2=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 3
    	out_port_3=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 4
    	out_port_4=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 5
    	out_port_5=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 6
    	out_port_6=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 7
    	out_port_7=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 8
    	out_port_8=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 9
    	out_port_9=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 10
    	out_port_10=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 11
    	out_port_11=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 12
    	out_port_12=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 13
    	out_port_13=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 14
    	out_port_14=DUMMY;
#endif
#if NUMBER_OF_OUT_PORTS > 15
    	out_port_15=DUMMY;
#endif
    	break;
    }
#else
    out_port=output_reg;
#endif
#ifdef PRIORITY_ARBITRATION
    arbitration_function(
    arbiter,
	output_sw_reg,
	in_port_0,
#if NUMBER_OF_IN_PORTS > 1
    in_port_1,
#if NUMBER_OF_IN_PORTS > 2
    in_port_2,
#if NUMBER_OF_IN_PORTS > 3
    in_port_3,
#if NUMBER_OF_IN_PORTS > 4
    in_port_4,
#if NUMBER_OF_IN_PORTS > 5
    in_port_5,
#if NUMBER_OF_IN_PORTS > 6
    in_port_6,
#if NUMBER_OF_IN_PORTS > 7
    in_port_7,
#if NUMBER_OF_IN_PORTS > 8
    in_port_8,
#if NUMBER_OF_IN_PORTS > 9
    in_port_9,
#if NUMBER_OF_IN_PORTS > 10
    in_port_10,
#if NUMBER_OF_IN_PORTS > 11
    in_port_11,
#if NUMBER_OF_IN_PORTS > 12
    in_port_12,
#if NUMBER_OF_IN_PORTS > 13
    in_port_13,
#if NUMBER_OF_IN_PORTS > 14
    in_port_14,
#if NUMBER_OF_IN_PORTS > 15
    in_port_15,
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#if OUTPUT_PARSING_ENABLE==1
	dest_needed,
	dest_needed_reg,
#endif
	output_sw,
	output_reg_last_valid,
	0
    );

#else
#ifdef ROUNDROBIN_ARBITRATION

    switch(roundrobin_stage)
    {
    case 0:
        arbitration_function(
		#ifdef ROUNDROBIN_ARBITRATION
        		roundrobin_stage,
		#endif
        		arbiter,
				output_sw_reg,
        		in_port_0,
			#if NUMBER_OF_IN_PORTS > 1
				in_port_1,
			#if NUMBER_OF_IN_PORTS > 2
				in_port_2,
			#if NUMBER_OF_IN_PORTS > 3
				in_port_3,
			#if NUMBER_OF_IN_PORTS > 4
				in_port_4,
			#if NUMBER_OF_IN_PORTS > 5
				in_port_5,
			#if NUMBER_OF_IN_PORTS > 6
				in_port_6,
			#if NUMBER_OF_IN_PORTS > 7
				in_port_7,
			#if NUMBER_OF_IN_PORTS > 8
				in_port_8,
			#if NUMBER_OF_IN_PORTS > 9
				in_port_9,
			#if NUMBER_OF_IN_PORTS > 10
				in_port_10,
			#if NUMBER_OF_IN_PORTS > 11
				in_port_11,
			#if NUMBER_OF_IN_PORTS > 12
				in_port_12,
			#if NUMBER_OF_IN_PORTS > 13
				in_port_13,
			#if NUMBER_OF_IN_PORTS > 14
				in_port_14,
			#if NUMBER_OF_IN_PORTS > 15
				in_port_15,
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#if OUTPUT_PARSING_ENABLE==1
				dest_needed,
				dest_needed_reg,
			#endif
				output_sw,
				output_reg_last_valid,
				0
        	);
        break;
#if NUMBER_OF_IN_PORTS > 1
    case 1:
        arbitration_function(
		#ifdef ROUNDROBIN_ARBITRATION
				roundrobin_stage,
		#endif
        		arbiter,
				output_sw_reg,
			#if NUMBER_OF_IN_PORTS > 1
				in_port_1,
			#if NUMBER_OF_IN_PORTS > 2
				in_port_2,
			#if NUMBER_OF_IN_PORTS > 3
				in_port_3,
			#if NUMBER_OF_IN_PORTS > 4
				in_port_4,
			#if NUMBER_OF_IN_PORTS > 5
				in_port_5,
			#if NUMBER_OF_IN_PORTS > 6
				in_port_6,
			#if NUMBER_OF_IN_PORTS > 7
				in_port_7,
			#if NUMBER_OF_IN_PORTS > 8
				in_port_8,
			#if NUMBER_OF_IN_PORTS > 9
				in_port_9,
			#if NUMBER_OF_IN_PORTS > 10
				in_port_10,
			#if NUMBER_OF_IN_PORTS > 11
				in_port_11,
			#if NUMBER_OF_IN_PORTS > 12
				in_port_12,
			#if NUMBER_OF_IN_PORTS > 13
				in_port_13,
			#if NUMBER_OF_IN_PORTS > 14
				in_port_14,
			#if NUMBER_OF_IN_PORTS > 15
				in_port_15,
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
			#endif
				in_port_0,
			#if OUTPUT_PARSING_ENABLE==1
				dest_needed,
				dest_needed_reg,
			#endif
				output_sw,
				output_reg_last_valid,
				1
        	);
        break;
#endif
#if NUMBER_OF_IN_PORTS > 2
    case 2:
        arbitration_function(
			#ifdef ROUNDROBIN_ARBITRATION
					roundrobin_stage,
			#endif
        		arbiter,
				output_sw_reg,
			#if NUMBER_OF_IN_PORTS > 2
				in_port_2,
			#endif
			#if NUMBER_OF_IN_PORTS > 3
				in_port_3,
			#endif
			#if NUMBER_OF_IN_PORTS > 4
				in_port_4,
			#endif
			#if NUMBER_OF_IN_PORTS > 5
				in_port_5,
			#endif
			#if NUMBER_OF_IN_PORTS > 6
				in_port_6,
			#endif
			#if NUMBER_OF_IN_PORTS > 7
				in_port_7,
			#endif
			#if NUMBER_OF_IN_PORTS > 8
				in_port_8,
			#endif
			#if NUMBER_OF_IN_PORTS > 9
				in_port_9,
			#endif
			#if NUMBER_OF_IN_PORTS > 10
				in_port_10,
			#endif
			#if NUMBER_OF_IN_PORTS > 11
				in_port_11,
			#endif
			#if NUMBER_OF_IN_PORTS > 12
				in_port_12,
			#endif
			#if NUMBER_OF_IN_PORTS > 13
				in_port_13,
			#endif
			#if NUMBER_OF_IN_PORTS > 14
				in_port_14,
			#endif
			#if NUMBER_OF_IN_PORTS > 15
				in_port_15,
			#endif
				in_port_0,
			#if NUMBER_OF_IN_PORTS > 1
				in_port_1,
			#endif
			#if OUTPUT_PARSING_ENABLE==1
				dest_needed,
				dest_needed_reg,
			#endif
				output_sw,
				output_reg_last_valid,
				2
        	);
        break;
#endif
#if NUMBER_OF_IN_PORTS > 3
    case 3:
        arbitration_function(
			#ifdef ROUNDROBIN_ARBITRATION
					roundrobin_stage,
			#endif
        		arbiter,
				output_sw_reg,
			#if NUMBER_OF_IN_PORTS > 3
				in_port_3,
			#endif
			#if NUMBER_OF_IN_PORTS > 4
				in_port_4,
			#endif
			#if NUMBER_OF_IN_PORTS > 5
				in_port_5,
			#endif
			#if NUMBER_OF_IN_PORTS > 6
				in_port_6,
			#endif
			#if NUMBER_OF_IN_PORTS > 7
				in_port_7,
			#endif
			#if NUMBER_OF_IN_PORTS > 8
				in_port_8,
			#endif
			#if NUMBER_OF_IN_PORTS > 9
				in_port_9,
			#endif
			#if NUMBER_OF_IN_PORTS > 10
				in_port_10,
			#endif
			#if NUMBER_OF_IN_PORTS > 11
				in_port_11,
			#endif
			#if NUMBER_OF_IN_PORTS > 12
				in_port_12,
			#endif
			#if NUMBER_OF_IN_PORTS > 13
				in_port_13,
			#endif
			#if NUMBER_OF_IN_PORTS > 14
				in_port_14,
			#endif
			#if NUMBER_OF_IN_PORTS > 15
				in_port_15,
			#endif
				in_port_0,
			#if NUMBER_OF_IN_PORTS > 1
				in_port_1,
			#endif
			#if NUMBER_OF_IN_PORTS > 2
				in_port_2,
			#endif
			#if OUTPUT_PARSING_ENABLE==1
				dest_needed,
				dest_needed_reg,
			#endif
				output_sw,
				output_reg_last_valid,
				3
        	);
        break;
#endif
#if NUMBER_OF_IN_PORTS > 4
    case 4:
        arbitration_function(
			#ifdef ROUNDROBIN_ARBITRATION
					roundrobin_stage,
			#endif
        		arbiter,
				output_sw_reg,
			#if NUMBER_OF_IN_PORTS > 4
				in_port_4,
			#endif
			#if NUMBER_OF_IN_PORTS > 5
				in_port_5,
			#endif
			#if NUMBER_OF_IN_PORTS > 6
				in_port_6,
			#endif
			#if NUMBER_OF_IN_PORTS > 7
				in_port_7,
			#endif
			#if NUMBER_OF_IN_PORTS > 8
				in_port_8,
			#endif
			#if NUMBER_OF_IN_PORTS > 9
				in_port_9,
			#endif
			#if NUMBER_OF_IN_PORTS > 10
				in_port_10,
			#endif
			#if NUMBER_OF_IN_PORTS > 11
				in_port_11,
			#endif
			#if NUMBER_OF_IN_PORTS > 12
				in_port_12,
			#endif
			#if NUMBER_OF_IN_PORTS > 13
				in_port_13,
			#endif
			#if NUMBER_OF_IN_PORTS > 14
				in_port_14,
			#endif
			#if NUMBER_OF_IN_PORTS > 15
				in_port_15,
			#endif
				in_port_0,
			#if NUMBER_OF_IN_PORTS > 1
				in_port_1,
			#endif
			#if NUMBER_OF_IN_PORTS > 2
				in_port_2,
			#endif
			#if NUMBER_OF_IN_PORTS > 3
				in_port_3,
			#endif
			#if OUTPUT_PARSING_ENABLE==1
				dest_needed,
				dest_needed_reg,
			#endif
				output_sw,
				output_reg_last_valid,
				4
        	);
        break;
#endif
#if NUMBER_OF_IN_PORTS > 5
    case 5:
        arbitration_function(
			#ifdef ROUNDROBIN_ARBITRATION
					roundrobin_stage,
			#endif
        		arbiter,
				output_sw_reg,
			#if NUMBER_OF_IN_PORTS > 5
				in_port_5,
			#endif
			#if NUMBER_OF_IN_PORTS > 6
				in_port_6,
			#endif
			#if NUMBER_OF_IN_PORTS > 7
				in_port_7,
			#endif
			#if NUMBER_OF_IN_PORTS > 8
				in_port_8,
			#endif
			#if NUMBER_OF_IN_PORTS > 9
				in_port_9,
			#endif
			#if NUMBER_OF_IN_PORTS > 10
				in_port_10,
			#endif
			#if NUMBER_OF_IN_PORTS > 11
				in_port_11,
			#endif
			#if NUMBER_OF_IN_PORTS > 12
				in_port_12,
			#endif
			#if NUMBER_OF_IN_PORTS > 13
				in_port_13,
			#endif
			#if NUMBER_OF_IN_PORTS > 14
				in_port_14,
			#endif
			#if NUMBER_OF_IN_PORTS > 15
				in_port_15,
			#endif
				in_port_0,
			#if NUMBER_OF_IN_PORTS > 1
				in_port_1,
			#endif
			#if NUMBER_OF_IN_PORTS > 2
				in_port_2,
			#endif
			#if NUMBER_OF_IN_PORTS > 3
				in_port_3,
			#endif
			#if NUMBER_OF_IN_PORTS > 4
				in_port_4,
			#endif
			#if OUTPUT_PARSING_ENABLE==1
				dest_needed,
				dest_needed_reg,
			#endif
				output_sw,
				output_reg_last_valid,
				5
        	);
        break;
#endif
#if NUMBER_OF_IN_PORTS > 6
    case 6:
        arbitration_function(
			#ifdef ROUNDROBIN_ARBITRATION
					roundrobin_stage,
			#endif
        		arbiter,
				output_sw_reg,
			#if NUMBER_OF_IN_PORTS > 6
				in_port_6,
			#endif
			#if NUMBER_OF_IN_PORTS > 7
				in_port_7,
			#endif
			#if NUMBER_OF_IN_PORTS > 8
				in_port_8,
			#endif
			#if NUMBER_OF_IN_PORTS > 9
				in_port_9,
			#endif
			#if NUMBER_OF_IN_PORTS > 10
				in_port_10,
			#endif
			#if NUMBER_OF_IN_PORTS > 11
				in_port_11,
			#endif
			#if NUMBER_OF_IN_PORTS > 12
				in_port_12,
			#endif
			#if NUMBER_OF_IN_PORTS > 13
				in_port_13,
			#endif
			#if NUMBER_OF_IN_PORTS > 14
				in_port_14,
			#endif
			#if NUMBER_OF_IN_PORTS > 15
				in_port_15,
			#endif
				in_port_0,
			#if NUMBER_OF_IN_PORTS > 1
				in_port_1,
			#endif
			#if NUMBER_OF_IN_PORTS > 2
				in_port_2,
			#endif
			#if NUMBER_OF_IN_PORTS > 3
				in_port_3,
			#endif
			#if NUMBER_OF_IN_PORTS > 4
				in_port_4,
			#endif
			#if NUMBER_OF_IN_PORTS > 5
				in_port_5,
			#endif
			#if OUTPUT_PARSING_ENABLE==1
				dest_needed,
				dest_needed_reg,
			#endif
				output_sw,
				output_reg_last_valid,
				6
        	);
        break;
#endif
#if NUMBER_OF_IN_PORTS > 7
    case 7:
        arbitration_function(
			#ifdef ROUNDROBIN_ARBITRATION
					roundrobin_stage,
			#endif
        		arbiter,
				output_sw_reg,
			#if NUMBER_OF_IN_PORTS > 7
				in_port_7,
			#endif
			#if NUMBER_OF_IN_PORTS > 8
				in_port_8,
			#endif
			#if NUMBER_OF_IN_PORTS > 9
				in_port_9,
			#endif
			#if NUMBER_OF_IN_PORTS > 10
				in_port_10,
			#endif
			#if NUMBER_OF_IN_PORTS > 11
				in_port_11,
			#endif
			#if NUMBER_OF_IN_PORTS > 12
				in_port_12,
			#endif
			#if NUMBER_OF_IN_PORTS > 13
				in_port_13,
			#endif
			#if NUMBER_OF_IN_PORTS > 14
				in_port_14,
			#endif
			#if NUMBER_OF_IN_PORTS > 15
				in_port_15,
			#endif
				in_port_0,
			#if NUMBER_OF_IN_PORTS > 1
				in_port_1,
			#endif
			#if NUMBER_OF_IN_PORTS > 2
				in_port_2,
			#endif
			#if NUMBER_OF_IN_PORTS > 3
				in_port_3,
			#endif
			#if NUMBER_OF_IN_PORTS > 4
				in_port_4,
			#endif
			#if NUMBER_OF_IN_PORTS > 5
				in_port_5,
			#endif
			#if NUMBER_OF_IN_PORTS > 6
				in_port_6,
			#endif
			#if OUTPUT_PARSING_ENABLE==1
				dest_needed,
				dest_needed_reg,
			#endif
				output_sw,
				output_reg_last_valid,
				7
        	);
        break;
#endif
#if NUMBER_OF_IN_PORTS > 8
    case 8:
        arbitration_function(
			#ifdef ROUNDROBIN_ARBITRATION
					roundrobin_stage,
			#endif
        		arbiter,
				output_sw_reg,
			#if NUMBER_OF_IN_PORTS > 8
				in_port_8,
			#endif
			#if NUMBER_OF_IN_PORTS > 9
				in_port_9,
			#endif
			#if NUMBER_OF_IN_PORTS > 10
				in_port_10,
			#endif
			#if NUMBER_OF_IN_PORTS > 11
				in_port_11,
			#endif
			#if NUMBER_OF_IN_PORTS > 12
				in_port_12,
			#endif
			#if NUMBER_OF_IN_PORTS > 13
				in_port_13,
			#endif
			#if NUMBER_OF_IN_PORTS > 14
				in_port_14,
			#endif
			#if NUMBER_OF_IN_PORTS > 15
				in_port_15,
			#endif
				in_port_0,
			#if NUMBER_OF_IN_PORTS > 1
				in_port_1,
			#endif
			#if NUMBER_OF_IN_PORTS > 2
				in_port_2,
			#endif
			#if NUMBER_OF_IN_PORTS > 3
				in_port_3,
			#endif
			#if NUMBER_OF_IN_PORTS > 4
				in_port_4,
			#endif
			#if NUMBER_OF_IN_PORTS > 5
				in_port_5,
			#endif
			#if NUMBER_OF_IN_PORTS > 6
				in_port_6,
			#endif
			#if NUMBER_OF_IN_PORTS > 7
				in_port_7,
			#endif
			#if OUTPUT_PARSING_ENABLE==1
				dest_needed,
				dest_needed_reg,
			#endif
				output_sw,
				output_reg_last_valid,
				8
        	);
        break;
#endif
#if NUMBER_OF_IN_PORTS > 9
    case 9:
        arbitration_function(
			#ifdef ROUNDROBIN_ARBITRATION
					roundrobin_stage,
			#endif
        		arbiter,
				output_sw_reg,
			#if NUMBER_OF_IN_PORTS > 9
				in_port_9,
			#endif
			#if NUMBER_OF_IN_PORTS > 10
				in_port_10,
			#endif
			#if NUMBER_OF_IN_PORTS > 11
				in_port_11,
			#endif
			#if NUMBER_OF_IN_PORTS > 12
				in_port_12,
			#endif
			#if NUMBER_OF_IN_PORTS > 13
				in_port_13,
			#endif
			#if NUMBER_OF_IN_PORTS > 14
				in_port_14,
			#endif
			#if NUMBER_OF_IN_PORTS > 15
				in_port_15,
			#endif
				in_port_0,
			#if NUMBER_OF_IN_PORTS > 1
				in_port_1,
			#endif
			#if NUMBER_OF_IN_PORTS > 2
				in_port_2,
			#endif
			#if NUMBER_OF_IN_PORTS > 3
				in_port_3,
			#endif
			#if NUMBER_OF_IN_PORTS > 4
				in_port_4,
			#endif
			#if NUMBER_OF_IN_PORTS > 5
				in_port_5,
			#endif
			#if NUMBER_OF_IN_PORTS > 6
				in_port_6,
			#endif
			#if NUMBER_OF_IN_PORTS > 7
				in_port_7,
			#endif
			#if NUMBER_OF_IN_PORTS > 8
				in_port_8,
			#endif
			#if OUTPUT_PARSING_ENABLE==1
				dest_needed,
				dest_needed_reg,
			#endif
				output_sw,
				output_reg_last_valid,
				9
        	);
        break;
#endif
#if NUMBER_OF_IN_PORTS > 10
    case 10:
        arbitration_function(
			#ifdef ROUNDROBIN_ARBITRATION
					roundrobin_stage,
			#endif
        		arbiter,
				output_sw_reg,
			#if NUMBER_OF_IN_PORTS > 10
				in_port_10,
			#endif
			#if NUMBER_OF_IN_PORTS > 11
				in_port_11,
			#endif
			#if NUMBER_OF_IN_PORTS > 12
				in_port_12,
			#endif
			#if NUMBER_OF_IN_PORTS > 13
				in_port_13,
			#endif
			#if NUMBER_OF_IN_PORTS > 14
				in_port_14,
			#endif
			#if NUMBER_OF_IN_PORTS > 15
				in_port_15,
			#endif
				in_port_0,
			#if NUMBER_OF_IN_PORTS > 1
				in_port_1,
			#endif
			#if NUMBER_OF_IN_PORTS > 2
				in_port_2,
			#endif
			#if NUMBER_OF_IN_PORTS > 3
				in_port_3,
			#endif
			#if NUMBER_OF_IN_PORTS > 4
				in_port_4,
			#endif
			#if NUMBER_OF_IN_PORTS > 5
				in_port_5,
			#endif
			#if NUMBER_OF_IN_PORTS > 6
				in_port_6,
			#endif
			#if NUMBER_OF_IN_PORTS > 7
				in_port_7,
			#endif
			#if NUMBER_OF_IN_PORTS > 8
				in_port_8,
			#endif
			#if NUMBER_OF_IN_PORTS > 9
				in_port_9,
			#endif
			#if OUTPUT_PARSING_ENABLE==1
				dest_needed,
				dest_needed_reg,
			#endif
				output_sw,
				output_reg_last_valid,
				10
        	);
        break;
#endif
#if NUMBER_OF_IN_PORTS > 11
    case 11:
        arbitration_function(
			#ifdef ROUNDROBIN_ARBITRATION
					roundrobin_stage,
			#endif
        		arbiter,
				output_sw_reg,
			#if NUMBER_OF_IN_PORTS > 11
				in_port_11,
			#endif
			#if NUMBER_OF_IN_PORTS > 12
				in_port_12,
			#endif
			#if NUMBER_OF_IN_PORTS > 13
				in_port_13,
			#endif
			#if NUMBER_OF_IN_PORTS > 14
				in_port_14,
			#endif
			#if NUMBER_OF_IN_PORTS > 15
				in_port_15,
			#endif
				in_port_0,
			#if NUMBER_OF_IN_PORTS > 1
				in_port_1,
			#endif
			#if NUMBER_OF_IN_PORTS > 2
				in_port_2,
			#endif
			#if NUMBER_OF_IN_PORTS > 3
				in_port_3,
			#endif
			#if NUMBER_OF_IN_PORTS > 4
				in_port_4,
			#endif
			#if NUMBER_OF_IN_PORTS > 5
				in_port_5,
			#endif
			#if NUMBER_OF_IN_PORTS > 6
				in_port_6,
			#endif
			#if NUMBER_OF_IN_PORTS > 7
				in_port_7,
			#endif
			#if NUMBER_OF_IN_PORTS > 8
				in_port_8,
			#endif
			#if NUMBER_OF_IN_PORTS > 9
				in_port_9,
			#endif
			#if NUMBER_OF_IN_PORTS > 10
				in_port_10,
			#endif
			#if OUTPUT_PARSING_ENABLE==1
				dest_needed,
				dest_needed_reg,
			#endif
				output_sw,
				output_reg_last_valid,
				11
        	);
        break;
#endif
#if NUMBER_OF_IN_PORTS > 12
    case 12:
        arbitration_function(
			#ifdef ROUNDROBIN_ARBITRATION
					roundrobin_stage,
			#endif
        		arbiter,
				output_sw_reg,
			#if NUMBER_OF_IN_PORTS > 12
				in_port_12,
			#endif
			#if NUMBER_OF_IN_PORTS > 13
				in_port_13,
			#endif
			#if NUMBER_OF_IN_PORTS > 14
				in_port_14,
			#endif
			#if NUMBER_OF_IN_PORTS > 15
				in_port_15,
			#endif
				in_port_0,
			#if NUMBER_OF_IN_PORTS > 1
				in_port_1,
			#endif
			#if NUMBER_OF_IN_PORTS > 2
				in_port_2,
			#endif
			#if NUMBER_OF_IN_PORTS > 3
				in_port_3,
			#endif
			#if NUMBER_OF_IN_PORTS > 4
				in_port_4,
			#endif
			#if NUMBER_OF_IN_PORTS > 5
				in_port_5,
			#endif
			#if NUMBER_OF_IN_PORTS > 6
				in_port_6,
			#endif
			#if NUMBER_OF_IN_PORTS > 7
				in_port_7,
			#endif
			#if NUMBER_OF_IN_PORTS > 8
				in_port_8,
			#endif
			#if NUMBER_OF_IN_PORTS > 9
				in_port_9,
			#endif
			#if NUMBER_OF_IN_PORTS > 10
				in_port_10,
			#endif
			#if NUMBER_OF_IN_PORTS > 11
				in_port_11,
			#endif
			#if OUTPUT_PARSING_ENABLE==1
				dest_needed,
				dest_needed_reg,
			#endif
				output_sw,
				output_reg_last_valid,
				12
        	);
        break;
#endif
#if NUMBER_OF_IN_PORTS > 13
    case 13:
        arbitration_function(
			#ifdef ROUNDROBIN_ARBITRATION
					roundrobin_stage,
			#endif
        		arbiter,
				output_sw_reg,
			#if NUMBER_OF_IN_PORTS > 13
				in_port_13,
			#endif
			#if NUMBER_OF_IN_PORTS > 14
				in_port_14,
			#endif
			#if NUMBER_OF_IN_PORTS > 15
				in_port_15,
			#endif
				in_port_0,
			#if NUMBER_OF_IN_PORTS > 1
				in_port_1,
			#endif
			#if NUMBER_OF_IN_PORTS > 2
				in_port_2,
			#endif
			#if NUMBER_OF_IN_PORTS > 3
				in_port_3,
			#endif
			#if NUMBER_OF_IN_PORTS > 4
				in_port_4,
			#endif
			#if NUMBER_OF_IN_PORTS > 5
				in_port_5,
			#endif
			#if NUMBER_OF_IN_PORTS > 6
				in_port_6,
			#endif
			#if NUMBER_OF_IN_PORTS > 7
				in_port_7,
			#endif
			#if NUMBER_OF_IN_PORTS > 8
				in_port_8,
			#endif
			#if NUMBER_OF_IN_PORTS > 9
				in_port_9,
			#endif
			#if NUMBER_OF_IN_PORTS > 10
				in_port_10,
			#endif
			#if NUMBER_OF_IN_PORTS > 11
				in_port_11,
			#endif
			#if NUMBER_OF_IN_PORTS > 12
				in_port_12,
			#endif
			#if OUTPUT_PARSING_ENABLE==1
				dest_needed,
				dest_needed_reg,
			#endif
				output_sw,
				output_reg_last_valid,
				13
        	);
        break;
#endif
#if NUMBER_OF_IN_PORTS > 14
    case 14:
        arbitration_function(
			#ifdef ROUNDROBIN_ARBITRATION
					roundrobin_stage,
			#endif
        		arbiter,
				output_sw_reg,
			#if NUMBER_OF_IN_PORTS > 14
				in_port_14,
			#endif
			#if NUMBER_OF_IN_PORTS > 15
				in_port_15,
			#endif
				in_port_0,
			#if NUMBER_OF_IN_PORTS > 1
				in_port_1,
			#endif
			#if NUMBER_OF_IN_PORTS > 2
				in_port_2,
			#endif
			#if NUMBER_OF_IN_PORTS > 3
				in_port_3,
			#endif
			#if NUMBER_OF_IN_PORTS > 4
				in_port_4,
			#endif
			#if NUMBER_OF_IN_PORTS > 5
				in_port_5,
			#endif
			#if NUMBER_OF_IN_PORTS > 6
				in_port_6,
			#endif
			#if NUMBER_OF_IN_PORTS > 7
				in_port_7,
			#endif
			#if NUMBER_OF_IN_PORTS > 8
				in_port_8,
			#endif
			#if NUMBER_OF_IN_PORTS > 9
				in_port_9,
			#endif
			#if NUMBER_OF_IN_PORTS > 10
				in_port_10,
			#endif
			#if NUMBER_OF_IN_PORTS > 11
				in_port_11,
			#endif
			#if NUMBER_OF_IN_PORTS > 12
				in_port_12,
			#endif
			#if NUMBER_OF_IN_PORTS > 13
				in_port_13,
			#endif
			#if OUTPUT_PARSING_ENABLE==1
				dest_needed,
				dest_needed_reg,
			#endif
				output_sw,
				output_reg_last_valid,
				14
        	);
        break;
#endif
#if NUMBER_OF_IN_PORTS > 15
    case 15:
        arbitration_function(
			#ifdef ROUNDROBIN_ARBITRATION
					roundrobin_stage,
			#endif
        		arbiter,
				output_sw_reg,
			#if NUMBER_OF_IN_PORTS > 15
				in_port_15,
			#endif
				in_port_0,
			#if NUMBER_OF_IN_PORTS > 1
				in_port_1,
			#endif
			#if NUMBER_OF_IN_PORTS > 2
				in_port_2,
			#endif
			#if NUMBER_OF_IN_PORTS > 3
				in_port_3,
			#endif
			#if NUMBER_OF_IN_PORTS > 4
				in_port_4,
			#endif
			#if NUMBER_OF_IN_PORTS > 5
				in_port_5,
			#endif
			#if NUMBER_OF_IN_PORTS > 6
				in_port_6,
			#endif
			#if NUMBER_OF_IN_PORTS > 7
				in_port_7,
			#endif
			#if NUMBER_OF_IN_PORTS > 8
				in_port_8,
			#endif
			#if NUMBER_OF_IN_PORTS > 9
				in_port_9,
			#endif
			#if NUMBER_OF_IN_PORTS > 10
				in_port_10,
			#endif
			#if NUMBER_OF_IN_PORTS > 11
				in_port_11,
			#endif
			#if NUMBER_OF_IN_PORTS > 12
				in_port_12,
			#endif
			#if NUMBER_OF_IN_PORTS > 13
				in_port_13,
			#endif
			#if NUMBER_OF_IN_PORTS > 14
				in_port_14,
			#endif
			#if OUTPUT_PARSING_ENABLE==1
				dest_needed,
				dest_needed_reg,
			#endif
				output_sw,
				output_reg_last_valid,
				15
        	);
        break;
#endif
    }

#endif
#endif

#if OUTPUT_PARSING_ENABLE==1
    //If no output parsing, recall out_port_ready is taken as an input wire so it
    //does not need to be assigned
    switch (dest_needed)
    {
    case out_port_0_dest_address:
    	out_port_ready = out_port_0_ready;
    	break;
#if NUMBER_OF_OUT_PORTS > 1
    case out_port_1_dest_address:
    	out_port_ready = out_port_1_ready;
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 2
    case out_port_2_dest_address:
    	out_port_ready = out_port_2_ready;
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 3
    case out_port_3_dest_address:
    	out_port_ready = out_port_3_ready;
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 4
    case out_port_4_dest_address:
    	out_port_ready = out_port_4_ready;
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 5
    case out_port_5_dest_address:
    	out_port_ready = out_port_5_ready;
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 6
    case out_port_6_dest_address:
    	out_port_ready = out_port_6_ready;
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 7
    case out_port_7_dest_address:
    	out_port_ready = out_port_7_ready;
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 8
    case out_port_8_dest_address:
    	out_port_ready = out_port_8_ready;
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 9
    case out_port_9_dest_address:
    	out_port_ready = out_port_9_ready;
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 10
    case out_port_10_dest_address:
    	out_port_ready = out_port_10_ready;
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 11
    case out_port_11_dest_address:
    	out_port_ready = out_port_11_ready;
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 12
    case out_port_12_dest_address:
    	out_port_ready = out_port_12_ready;
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 13
    case out_port_13_dest_address:
    	out_port_ready = out_port_13_ready;
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 14
    case out_port_14_dest_address:
    	out_port_ready = out_port_14_ready;
    	break;
#endif
#if NUMBER_OF_OUT_PORTS > 15
    case out_port_15_dest_address:
    	out_port_ready = out_port_15_ready;
    	break;
#endif
    default:
    	out_port_ready = out_port_default_ready;
    	break;
    }
#endif
    //record the current input values into previous value for next stage.
    //use current switch position to decide which input to use
    if (out_port_ready)
    {
		switch (output_sw)
		{
		case 0:
			output_reg=in_port_0;
			output_reg_last_valid=in_port_0;
			break;
	#if NUMBER_OF_IN_PORTS>1
		case 1:
			output_reg=in_port_1;
			output_reg_last_valid=in_port_1;
			break;
	#endif
	#if NUMBER_OF_IN_PORTS>2
		case 2:
			output_reg=in_port_2;
			output_reg_last_valid=in_port_2;
			break;
	#endif
	#if NUMBER_OF_IN_PORTS>3
		case 3:
			output_reg=in_port_3;
			output_reg_last_valid=in_port_3;
			break;
	#endif
	#if NUMBER_OF_IN_PORTS>4
		case 4:
			output_reg=in_port_4;
			output_reg_last_valid=in_port_4;
			break;
	#endif
	#if NUMBER_OF_IN_PORTS>5
		case 5:
			output_reg=in_port_5;
			output_reg_last_valid=in_port_5;
			break;
	#endif
	#if NUMBER_OF_IN_PORTS>6
		case 6:
			output_reg=in_port_6;
			output_reg_last_valid=in_port_6;
			break;
	#endif
	#if NUMBER_OF_IN_PORTS>7
		case 7:
			output_reg=in_port_7;
			output_reg_last_valid=in_port_7;
			break;
	#endif
	#if NUMBER_OF_IN_PORTS>8
		case 8:
			output_reg=in_port_8;
			output_reg_last_valid=in_port_8;
			break;
	#endif
	#if NUMBER_OF_IN_PORTS>9
		case 9:
			output_reg=in_port_9;
			output_reg_last_valid=in_port_9;
			break;
	#endif
	#if NUMBER_OF_IN_PORTS>10
		case 10:
			output_reg=in_port_10;
			output_reg_last_valid=in_port_10;
			break;
	#endif
	#if NUMBER_OF_IN_PORTS>11
		case 11:
			output_reg=in_port_11;
			output_reg_last_valid=in_port_11;
			break;
	#endif
	#if NUMBER_OF_IN_PORTS>12
		case 12:
			output_reg=in_port_12;
			output_reg_last_valid=in_port_12;
			break;
	#endif
	#if NUMBER_OF_IN_PORTS>13
		case 13:
			output_reg=in_port_13;
			output_reg_last_valid=in_port_13;
			break;
	#endif
	#if NUMBER_OF_IN_PORTS>14
		case 14:
			output_reg=in_port_14;
			output_reg_last_valid=in_port_14;
			break;
	#endif
	#if NUMBER_OF_IN_PORTS>15
		case 15:
			output_reg=in_port_15;
			output_reg_last_valid=in_port_15;
			break;
	#endif
		}
    }
    else
    {
    	output_reg=DUMMY;
    }
    //save the current switch position as the previous switch position for next cycle
    //set the ready signal if the port is active and the output is ready (otherwise we are stalled
    //ahead so we should apply backpressure).
    in_port_0_ready = (output_sw==0) & out_port_ready;
#if NUMBER_OF_IN_PORTS>1
    in_port_1_ready = (output_sw==1) & out_port_ready;
#endif
#if NUMBER_OF_IN_PORTS>2
    in_port_2_ready = (output_sw==2) & out_port_ready;
#endif
#if NUMBER_OF_IN_PORTS>3
    in_port_3_ready = (output_sw==3) & out_port_ready;
#endif
#if NUMBER_OF_IN_PORTS>4
    in_port_4_ready = (output_sw==4) & out_port_ready;
#endif
#if NUMBER_OF_IN_PORTS>5
    in_port_5_ready = (output_sw==5) & out_port_ready;
#endif
#if NUMBER_OF_IN_PORTS>6
    in_port_6_ready = (output_sw==6) & out_port_ready;
#endif
#if NUMBER_OF_IN_PORTS>7
    in_port_7_ready = (output_sw==7) & out_port_ready;
#endif
#if NUMBER_OF_IN_PORTS>8
    in_port_8_ready = (output_sw==8) & out_port_ready;
#endif
#if NUMBER_OF_IN_PORTS>9
    in_port_9_ready = (output_sw==9) & out_port_ready;
#endif
#if NUMBER_OF_IN_PORTS>10
    in_port_10_ready = (output_sw==10) & out_port_ready;
#endif
#if NUMBER_OF_IN_PORTS>11
    in_port_11_ready = (output_sw==11) & out_port_ready;
#endif
#if NUMBER_OF_IN_PORTS>12
    in_port_12_ready = (output_sw==12) & out_port_ready;
#endif
#if NUMBER_OF_IN_PORTS>13
    in_port_13_ready = (output_sw==13) & out_port_ready;
#endif
#if NUMBER_OF_IN_PORTS>14
    in_port_14_ready = (output_sw==14) & out_port_ready;
#endif
#if NUMBER_OF_IN_PORTS>15
    in_port_15_ready = (output_sw==15) & out_port_ready;
#endif
}
