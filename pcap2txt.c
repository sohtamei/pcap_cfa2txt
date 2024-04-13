#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>


#define GotoError(err) { fprintf(stdout, "%s(%d):%s\n", __FUNCTION__, __LINE__, err); goto Error; }
#define PrintError(err) { fprintf(stdout, "%s(%d):%s\n", __FUNCTION__, __LINE__, err); }
#define GetB32(a) (((a)[0]<<24)|((a)[1]<<16)|((a)[2]<<8)|((a)[3]<<0))
#define GetB16(a) (((a)[0]<<8)|((a)[1]<<0))
#define GetL32(a) (((a)[0]<<0)|((a)[1]<<8)|((a)[2]<<16)|((a)[3]<<24))

struct index2mes{
	int index;
	char mes[64];
};

static const struct index2mes cmd_table[] = {

{0x0104, "INQUIRY"},
{0x0204, "INQUIRY_CANCEL"},
{0x0304, "PERIODIC_INQUIRY"},
{0x0404, "EXIT_PERIODIC_INQUIRY"},
{0x0504, "CREATE_CONN"},
{0x0604, "DISCONNECT"},
{0x0704, "ADD_SCO"},
{0x0804, "CREATE_CONN_CANCEL"},
{0x0904, "ACCEPT_CONN_REQ"},
{0x0A04, "REJECT_CONN_REQ"},
{0x0B04, "LINK_KEY_REPLY"},
{0x0C04, "LINK_KEY_NEG_REPLY"},
{0x0D04, "PIN_CODE_REPLY"},
{0x0E04, "PIN_CODE_NEG_REPLY"},
{0x0F04, "SET_CONN_PTYPE"},
{0x1104, "AUTH_REQUESTED"},
{0x1304, "SET_CONN_ENCRYPT"},
{0x1504, "CHANGE_CONN_LINK_KEY"},
{0x1704, "MASTER_LINK_KEY"},
{0x1904, "REMOTE_NAME_REQ"},
{0x1A04, "REMOTE_NAME_REQ_CANCEL"},
{0x1B04, "READ_REMOTE_FEATURES"},
{0x1C04, "READ_REMOTE_EXT_FEATURES"},
{0x1D04, "READ_REMOTE_VERSION"},
{0x1F04, "READ_CLOCK_OFFSET"},
{0x2004, "READ_LMP_HANDLE"},
{0x2804, "SETUP_SYNC_CONN"},
{0x2904, "ACCEPT_SYNC_CONN_REQ"},
{0x2A04, "REJECT_SYNC_CONN_REQ"},
{0x2B04, "IO_CAPABILITY_REPLY"},
{0x2C04, "USER_CONFIRM_REPLY"},
{0x2D04, "USER_CONFIRM_NEG_REPLY"},
{0x2E04, "USER_PASSKEY_REPLY"},
{0x2F04, "USER_PASSKEY_NEG_REPLY"},
{0x3004, "REMOTE_OOB_DATA_REPLY"},
{0x3304, "REMOTE_OOB_DATA_NEG_REPLY"},
{0x3404, "IO_CAPABILITY_NEG_REPLY"},

/* Link Policy */

{0x0108, "HOLD_MODE"},
{0x0308, "SNIFF_MODE"},
{0x0408, "EXIT_SNIFF_MODE"},
{0x0508, "PARK_MODE"},
{0x0608, "EXIT_PARK_MODE"},
{0x0708, "QOS_SETUP"},
{0x0908, "ROLE_DISCOVERY"},
{0x0B08, "SWITCH_ROLE"},
{0x0C08, "READ_LINK_POLICY"},
{0x0D08, "WRITE_LINK_POLICY"},
{0x0E08, "READ_DEFAULT_LINK_POLICY"},
{0x0F08, "WRITE_DEFAULT_LINK_POLICY"},
{0x1008, "FLOW_SPECIFICATION"},
{0x1108, "SNIFF_SUBRATING"},

/* Host Controller and Baseband */

{0x010C, "SET_EVENT_MASK"},
{0x030C, "RESET"},
{0x050C, "SET_EVENT_FLT"},
{0x080C, "FLUSH"},
{0x090C, "READ_PIN_TYPE"},
{0x0A0C, "WRITE_PIN_TYPE"},
{0x0B0C, "CREATE_NEW_UNIT_KEY"},
{0x0D0C, "READ_STORED_LINK_KEY"},
{0x110C, "WRITE_STORED_LINK_KEY"},
{0x120C, "DELETE_STORED_LINK_KEY"},
{0x130C, "CHANGE_LOCAL_NAME"},
{0x140C, "READ_LOCAL_NAME"},
{0x150C, "READ_CONN_ACCEPT_TIMEOUT"},
{0x160C, "WRITE_CONN_ACCEPT_TIMEOUT"},
{0x170C, "READ_PAGE_TIMEOUT"},
{0x180C, "WRITE_PAGE_TIMEOUT"},
{0x190C, "READ_SCAN_ENABLE"},
{0x1A0C, "WRITE_SCAN_ENABLE"},
{0x1B0C, "READ_PAGE_ACTIVITY"},
{0x1C0C, "WRITE_PAGE_ACTIVITY"},
{0x1D0C, "READ_INQ_ACTIVITY"},
{0x1E0C, "WRITE_INQ_ACTIVITY"},
{0x1F0C, "READ_AUTH_ENABLE"},
{0x200C, "WRITE_AUTH_ENABLE"},
{0x210C, "READ_ENCRYPT_MODE"},
{0x220C, "WRITE_ENCRYPT_MODE"},
{0x230C, "READ_CLASS_OF_DEV"},
{0x240C, "WRITE_CLASS_OF_DEV"},
{0x250C, "READ_VOICE_SETTING"},
{0x260C, "WRITE_VOICE_SETTING"},
{0x270C, "READ_AUTOMATIC_FLUSH_TIMEOUT"},
{0x280C, "WRITE_AUTOMATIC_FLUSH_TIMEOUT"},
{0x290C, "READ_NUM_BROADCAST_RETRANS"},
{0x2A0C, "WRITE_NUM_BROADCAST_RETRANS"},
{0x2B0C, "READ_HOLD_MODE_ACTIVITY"},
{0x2C0C, "WRITE_HOLD_MODE_ACTIVITY"},
{0x2D0C, "READ_TRANSMIT_POWER_LEVEL"},
{0x2E0C, "READ_SYNC_FLOW_ENABLE"},
{0x2F0C, "WRITE_SYNC_FLOW_ENABLE"},
{0x310C, "SET_CONTROLLER_TO_HOST_FC"},
{0x330C, "HOST_BUFFER_SIZE"},
{0x350C, "HOST_NUM_COMP_PKTS"},
{0x360C, "READ_LINK_SUPERVISION_TIMEOUT"},
{0x370C, "WRITE_LINK_SUPERVISION_TIMEOUT"},
{0x380C, "READ_NUM_SUPPORTED_IAC"},
{0x390C, "READ_CURRENT_IAC_LAP"},
{0x3A0C, "WRITE_CURRENT_IAC_LAP"},
{0x3B0C, "READ_PAGE_SCAN_PERIOD_MODE"},
{0x3C0C, "WRITE_PAGE_SCAN_PERIOD_MODE"},
{0x3D0C, "READ_PAGE_SCAN_MODE"},
{0x3E0C, "WRITE_PAGE_SCAN_MODE"},
{0x3F0C, "SET_AFH_CLASSIFICATION"},
{0x420C, "READ_INQUIRY_SCAN_TYPE"},
{0x430C, "WRITE_INQUIRY_SCAN_TYPE"},
{0x440C, "READ_INQUIRY_MODE"},
{0x450C, "WRITE_INQUIRY_MODE"},
{0x460C, "READ_PAGE_SCAN_TYPE"},
{0x470C, "WRITE_PAGE_SCAN_TYPE"},
{0x480C, "READ_AFH_MODE"},
{0x490C, "WRITE_AFH_MODE"},
{0x510C, "READ_EXT_INQUIRY_RESPONSE"},
{0x520C, "WRITE_EXT_INQUIRY_RESPONSE"},
{0x530C, "REFRESH_ENCRYPTION_KEY"},
{0x550C, "READ_SIMPLE_PAIRING_MODE"},
{0x560C, "WRITE_SIMPLE_PAIRING_MODE"},
{0x570C, "READ_LOCAL_OOB_DATA"},
{0x580C, "READ_INQ_RESPONSE_TX_POWER_LEVEL"},
{0x580C, "READ_INQUIRY_TRANSMIT_POWER_LEVEL"},
{0x590C, "WRITE_INQUIRY_TRANSMIT_POWER_LEVEL"},
{0x5A0C, "READ_DEFAULT_ERROR_DATA_REPORTING"},
{0x5B0C, "WRITE_DEFAULT_ERROR_DATA_REPORTING"},
{0x5F0C, "ENHANCED_FLUSH"},
{0x600C, "SEND_KEYPRESS_NOTIFY"},

/* Informational Parameters */

{0x0110, "READ_LOCAL_VERSION"},
{0x0210, "READ_LOCAL_COMMANDS"},
{0x0310, "READ_LOCAL_FEATURES"},
{0x0410, "READ_LOCAL_EXT_FEATURES"},
{0x0510, "READ_BUFFER_SIZE"},
{0x0710, "READ_COUNTRY_CODE"},
{0x0910, "READ_BD_ADDR"},

/* Status params */

{0x0114, "READ_FAILED_CONTACT_COUNTER"},
{0x0214, "RESET_FAILED_CONTACT_COUNTER"},
{0x0314, "READ_LINK_QUALITY"},
{0x0514, "READ_RSSI"},
{0x0614, "READ_AFH_MAP"},
{0x0714, "READ_CLOCK"},
{0x0814, "READ_ENCRYPTION_KEY_SIZE"},
{0x0914, "READ_LOCAL_AMP_INFO"},
{0x0A14, "READ_LOCAL_AMP_ASSOC"},
{0x0B14, "WRITE_REMOTE_AMP_ASSOC"},
{0x0C14, "GET_MWS_TRANSPORT_LAYER_CONFIGURATION"},
{0x0D14, "SET_TRIGGERED_CLOCK_CAPTURE"},

/* Testing commands */

{0x01F8, "READ_LOOPBACK_MODE"},
{0x02F8, "WRITE_LOOPBACK_MODE"},
{0x03F8, "ENABLE_DEVICE_UNDER_TEST_MODE"},
{0x04F8, "WRITE_SIMPLE_PAIRING_DEBUG_MODE"},

/* LE commands */
{0x0120, "LE_SET_EVENT_MASK"},
{0x0220, "LE_READ_BUFFER_SIZE"},
{0x0320, "LE_READ_LOCAL_SUPPORTED_FEATURES"},
{0x0520, "LE_SET_RANDOM_ADDRESS"},
{0x0620, "LE_SET_ADVERTISING_PARAMETERS"},
{0x0720, "LE_READ_ADVERTISING_CHANNEL_TX_POWER"},
{0x0820, "LE_SET_ADVERTISING_DATA"},
{0x0920, "LE_SET_SCAN_RESPONSE_DATA"},
{0x0A20, "LE_SET_ADVERTISE_ENABLE"},
{0x0B20, "LE_SET_SCAN_PARAMETERS"},
{0x0C20, "LE_SET_SCAN_ENABLE"},
{0x0D20, "LE_CREATE_CONN"},
{0x0E20, "LE_CREATE_CONN_CANCEL"},
{0x0F20, "LE_READ_WHITE_LIST_SIZE"},
{0x1020, "LE_CLEAR_WHITE_LIST"},
{0x1120, "LE_ADD_DEVICE_TO_WHITE_LIST"},
{0x1220, "LE_REMOVE_DEVICE_FROM_WHITE_LIST"},
{0x1320, "LE_CONN_UPDATE"},
{0x1420, "LE_SET_HOST_CHANNEL_CLASSIFICATION"},
{0x1520, "LE_READ_CHANNEL_MAP"},
{0x1620, "LE_READ_REMOTE_USED_FEATURES"},
{0x1720, "LE_ENCRYPT"},
{0x1820, "LE_RAND"},
{0x1920, "LE_START_ENCRYPTION"},
{0x1A20, "LE_LTK_REPLY"},
{0x1B20, "LE_LTK_NEG_REPLY"},
{0x1C20, "LE_READ_SUPPORTED_STATES"},
{0x1D20, "LE_RECEIVER_TEST"},
{0x1E20, "LE_TRANSMITTER_TEST"},
{0x1F20, "LE_TEST_END"},
{0x2020, "LE_REMOTE_CONNECTION_PARAMETER_REQUEST_REPLY"},
{0x2120, "LE_REMOTE_CONNECTION_PARAMETER_REQUEST_NEGATIVE_REPLY"},
{0x2220, "LE_SET_DATA_LENGTH"},
{0x2320, "LE_READ_SUGGESTED_DEFAULT_DATA_LENGTH"},
{0x2420, "LE_WRITE_SUGGESTED_DEFAULT_DATA_LENGTH"},
{0x2520, "LE_READ_LOCAL_P256_PUBLIC_KEY"},
{0x2620, "LE_GENERATE_DHKEY"},
{0x2720, "LE_ADD_DEVICE_TO_RESOLVING_LIST"},
{0x2820, "LE_REMOVE_DEVICE_FROM_RESOLVING_LIST"},
{0x2920, "LE_CLEAR_RESOLVING_LIST"},
{0x2A20, "LE_READ_RESOLVING_LIST_SIZE"},
{0x2B20, "LE_READ_PEER_RESOLVABLE_ADDRESS"},
{0x2C20, "LE_READ_LOCAL_RESOLVABLE_ADDRESS"},
{0x2D20, "LE_SET_ADDRESS_RESOLUTION_ENABLE"},
{0x2E20, "LE_SET_RESOLVABLE_PRIVATE_ADDRESS_TIMEOUT"},
{0x2F20, "LE_READ_MAXIMUM_DATA_LENGTH"},
};

/* ---- HCI Events ---- */

static const struct index2mes event_table[] = {

{0x01, "INQUIRY_COMPLETE"},
{0x02, "INQUIRY_RESULT"},
{0x03, "CONN_COMPLETE"},
{0x04, "CONN_REQUEST"},
{0x05, "DISCONN_COMPLETE"},
{0x06, "AUTH_COMPLETE"},
{0x07, "REMOTE_NAME_REQ_COMPLETE"},
{0x08, "ENCRYPT_CHANGE"},
{0x09, "CHANGE_CONN_LINK_KEY_COMPLETE"},
{0x0A, "MASTER_LINK_KEY_COMPLETE"},
{0x0B, "READ_REMOTE_FEATURES_COMPLETE"},
{0x0C, "READ_REMOTE_VERSION_COMPLETE"},
{0x0D, "QOS_SETUP_COMPLETE"},
{0x0E, "CMD_COMPLETE "},
{0x0F, "CMD_STATUS "},
{0x10, "HARDWARE_ERROR"},
{0x11, "FLUSH_OCCURRED"},
{0x12, "ROLE_CHANGE"},
{0x13, "NUM_COMP_PKTS"},
{0x14, "MODE_CHANGE"},
{0x15, "RETURN_LINK_KEYS"},
{0x16, "PIN_CODE_REQ"},
{0x17, "LINK_KEY_REQ"},
{0x18, "LINK_KEY_NOTIFY"},
{0x19, "LOOPBACK_COMMAND"},
{0x1A, "DATA_BUFFER_OVERFLOW"},
{0x1B, "MAX_SLOTS_CHANGE"},
{0x1C, "READ_CLOCK_OFFSET_COMPLETE"},
{0x1D, "CONN_PTYPE_CHANGED"},
{0x1E, "QOS_VIOLATION"},
{0x20, "PSCAN_REP_MODE_CHANGE"},
{0x21, "FLOW_SPEC_COMPLETE"},
{0x22, "INQUIRY_RESULT_WITH_RSSI"},
{0x23, "READ_REMOTE_EXT_FEATURES_COMPLETE"},
{0x2C, "SYNC_CONN_COMPLETE"},
{0x2D, "SYNC_CONN_CHANGED"},
{0x2E, "SNIFF_SUBRATING"},
{0x2F, "EXTENDED_INQUIRY_RESULT"},
{0x30, "ENCRYPTION_KEY_REFRESH_COMPLETE"},
{0x31, "IO_CAPABILITY_REQUEST"},
{0x32, "IO_CAPABILITY_RESPONSE"},
{0x33, "USER_CONFIRM_REQUEST"},
{0x34, "USER_PASSKEY_REQUEST"},
{0x35, "REMOTE_OOB_DATA_REQUEST"},
{0x36, "SIMPLE_PAIRING_COMPLETE"},
{0x38, "LINK_SUPERVISION_TIMEOUT_CHANGED"},
{0x39, "ENHANCED_FLUSH_COMPLETE"},
{0x3B, "USER_PASSKEY_NOTIFY"},
{0x3C, "KEYPRESS_NOTIFY"},
{0x3D, "REMOTE_HOST_FEATURES_NOTIFY"},
{0x3E, "LE_META_EVENT"},
};

static const struct index2mes bleSubEvent_table[] = {

{0x01, "LE_Connection_Complete"},
{0x02, "LE_Advertising_Report"},
{0x03, "LE_Connection_Update_Complete"},
{0x04, "LE_Read_Remote_Used_Features_Complete"},
{0x05, "LE_Long_Term_Key_Request"},
{0x06, "LE_Remote_Connection_Parameter_Request"},
{0x07, "LE_Data_Length_Change"},
{0x08, "LE_Read_Local_P-256_Public_Key_Complete"},
{0x09, "LE_Generate_DHKey_Complete"},
{0x0a, "LE_Enhanced_Connection_Complete"},
{0x0b, "LE_Direct_Advertising_Report"},

};

#define SP1		0x100

struct index2mes2{
	int index;
	int num[16];
	char mes[64];
};
static const struct index2mes2 l2cap_table[] = {

/*
R:80200c0008000100 02 11 0400 0100 4000							L2CAP_CONN_REQ:psm src
W:802010000c000100 03 11 0800 4400 4000 0000 0000				L2CAP_CONN_RSP:dst src result status
R:802010000c000100 04 12 0800 4400 0000 01 02 0004			L2CAP_CONF_REQ:dst flags        type size MTU
W:802012000e000100 05 12 0a00 4000 0000 0000 01 02 0004			L2CAP_CONF_RSP:src flags result type size MTU
W:802010000c000100 04 12 0800 4000 0000 01 02 0010			L2CAP_CONF_REQ:dst flags        type size MTU
R:802012000e000100 05 12 0a00 4400 0000 0000 01 02 0004			L2CAP_CONF_RSP:src flags result type size MTU
R:80200c0008000100 06 13 0400 4400 4000							L2CAP_DISCONN_REQ:dst src
W:80200c0008000100 07 13 0400 4400 4000							L2CAP_DISCONN_RSP:dst src
R:80200a0006000100 0a 02 0200 0200								L2CAP_INFO_REQ:ExtFeatures
W:80200c0008000100 0b 02 0400 0200 0100 						L2CAP_INFO_RSP:ExtFeatures NotSupported
*/

{0x02, {8,1,1,2,2,2},			"L2CAP_CONN_REQ:psm src"},
{0x03, {8,1,1,2,2,2, 2,2},		"L2CAP_CONN_RSP:dst src result status"},
{0x04, {8,1,1,2,2,2,1,1,2},	"L2CAP_CONF_REQ:dst flags type size MTU"},
{0x05, {8,1,1,2,2,2, 2,1,1,2},	"L2CAP_CONF_RSP:src flags result"},// type size MTU"},
{0x06, {8,1,1,2,2,2},			"L2CAP_DISCONN_REQ:dst src"},
{0x07, {8,1,1,2,2,2},			"L2CAP_DISCONN_RSP:dst src"},
{0x0a, {8,1,1,2,2},				"L2CAP_INFO_REQ:ExtFeatures"},
{0x0b, {8,1,1,2,2,2},			"L2CAP_INFO_RSP:ExtFeatures NotSupported"},

};

static const struct index2mes2 sdp_table[] = {

/*
R:802011000d004600 02 0000 0008 350319_1200 0015 00				SDP_SVC_SEARCH_REQ:UUID MaxCount Continuation
W:802012000e004200 03 0000 0009 0001 0001 00010001 00			SDP_SVC_SEARCH_RSP:total current handles Continuation
R:8020170013004600 04 0001 000e 00010001 0290 35050a_0000_ffff 00	SDP_SVC_ATTR_REQ:handle MaxCount D_list Continuation
W:8020340030004200 05 0001 002b 0026 3600680900000a000100010900013503191200090004350d3506190100090001350319000109 020026
R:8120180014004a00 06 0000 000f 350319_1200 0290 35050a_0000_ffff 00	SDP_SVC_SEARCH_ATTR_REQ:UUID MaxCount D_list Continuation
W:8120340030004600 07 0000 002b 0026 36006b3600680900000a000100010900013503191200090004350d3506190100090001350319 020026

*/

{0x02, {8,1,2,2,3,2,2,},		"SDP_SVC_SEARCH_REQ:UUID MaxCount Continuation"},
{0x03, {8,1,2,2,2,2,4,},		"SDP_SVC_SEARCH_RSP:total current handles Continuation"},
{0x04, {8,1,2,2,4,2,SP1,},		"SDP_SVC_ATTR_REQ:handle MaxCount D_list Continuation"},
{0x05, {8,1,2,2,2,SP1},			"SDP_SVC_ATTR_RSP"},
{0x06, {8,1,2,2,SP1,2,SP1,},	"SDP_SVC_SEARCH_ATTR_REQ:UUID MaxCount D_list Continuation"},
{0x07, {8,1,2,2,2,SP1},			"SDP_SVC_SEARCH_ATTR_RSP"},
};
#define SDP_SVC_SEARCH_ATTR_REQ 0x06
#define SDP_SVC_SEARCH_ATTR_RSP 0x07

/*
00000008 00000008 00000001 00000000 00E25473 DC8FFED7	0413050132000100
00000011 00000011 00000001 00000000 00E25473 DC900419	0232200C00080001000217040001004C00
00000015 00000015 00000000 00000000 00E25473 DC90058E	02320010000C0001000317080042004C0000000000

*/

int printSP(int* depth, unsigned char** dpp, int size)
{
	int len;
	int ret;
	unsigned char** dpp2 = dpp;
	unsigned char* dp2;
	int i;

	switch((*dpp2)[0]) {
	case 0x36:
		len = GetB16(*dpp2+1) + 3;
		printf("%02x%02x%02x_", (*dpp2)[0], (*dpp2)[1], (*dpp2)[2]);
		dp2 = *dpp2+3;
		goto _structPrint;

	case 0x35:	// 構造体
		len = (*dpp2)[1] + 2;
		printf("%02x%02x_", (*dpp2)[0], (*dpp2)[1]);
		dp2 = *dpp2+2;
_structPrint:
		(*depth)++;
		if(*depth <= 2) printf("\n");
		i = 0;
		while(dp2 < *dpp2+len) {
			ret = printSP(depth, &dp2, *dpp2+len - dp2);
			if(ret) break;
			if(*depth < 2 || (*depth == 2 && (i&1) == 1))
				printf("\n");
			i++;
		}
		*dpp2 = dp2;
		(*depth)--;
		break;
	case 0x08:
	case 0x18:
	case 0x28:	len = 1;	goto dumpBuf;	// 1byte
	case 0x09:
	case 0x19:
	case 0x29:	len = 2;	goto dumpBuf;	// 2byte
	case 0x0a:
	case 0x1a:
	case 0x2a:	len = 4;	goto dumpBuf;	// 4byte
	case 0x1c:	len = 16;					// 16byte
dumpBuf:
		for(i = 0; i < 1+len; i++) {
			printf("%02x", (*dpp2)[i]);
			if(i == 0) printf("_");
		}
		printf(" ");
		*dpp2 += 1+len;
		break;
	case 0x25:	// array
		len = (*dpp2)[1];
		printf("%02x%02x_", (*dpp2)[0], (*dpp2)[1]);
		for(i = 0; i < len; i++)
			printf("%02x", (*dpp2)[2+i]);
		printf(" ");
		*dpp2 += 2+len;
		break;
	default:
		if(size) {
			printf("?");
			for(i = 0; i < *dpp+size - *dpp2; i++)
				printf("%02x", (*dpp2)[i]);
			printf(" ");
			*dpp2 = *dpp+size;
		}
		return -1;
	}
	return 0;
}

void parse_btdongle(int endp, uint8_t* buf, int size);
void parse_meshbridge(int endp, uint8_t* buf, int size);
int main(int argc, char* argv[])
{
	FILE* fp = NULL;
	unsigned char buf[65536];
	int ret;
	int result = 1;

	if(argc <= 1) {
		printf("usage: pcap2txt filename [0-normal, 1-don't parse] \n");
		return 1;
	}
	int mode = 0;
	enum {
		MODE_BTDONGLE = 0,
		MODE_MESHBRIDGE,
	};
	if(argc >= 3)
		mode = strtoul(argv[2], NULL, 0);

	fp = fopen(argv[1], "rb");
	if(!fp) GotoError("");
	
	// file header
	ret = fread(buf, 1, 24, fp);
	if(ret <= 0) GotoError("");

	

	while(1) {
		int size;

		// 28byte
		//  0 1 2 3 4 5 6 7 8 9 a b c d e f10 1 2 3 4 5 6 7 8 9 a b
		// 2CBC9A5F13C40B002100000021000000000000000000000000DAD0F1 

		// 27byte
		//  0 1 2 3 4 5 6 7 8 9 a b c d e f10 1 2 3 4 5 6 7 8 9 a
		// 1B0060DA993584CAFFFF0000000009000101000100830306000000
		// 1c00a0f9fd2f84caffff000000001a000001000100000208000000 00
		// 1c00a0f9fd2f84caffff0000000008000101000100000204000000 01
	
		// line header
		ret = fread(buf, 1, 0x1c+0x1b, fp);
		if(ret <= 0) goto Error;
		unsigned char setup = 1;
		if(buf[0x1c+0] == 0x1c) fread(&setup, 1, 1, fp);

		size = GetL32(buf+0x1c+0x17);
		int endp = buf[0x1c+0x15];	// 03:cmd 83:event
	//	for(i=0;i<0x1c+0x1b;i++) printf("%02x",buf[i]); printf("\n");
		if(size >= sizeof(buf)) { GotoError("");}
		if(size == 0) continue;
		ret = fread(buf, 1, size, fp);
		if(ret <= 0) GotoError("");
		size = ret;
	//	h4 = (h4<<8)|buf[0];
	//	for(i=0;i<size;i++) printf("%02x",buf[i]); printf("\n");

		if(setup!=1) continue;

		switch(mode) {
		case MODE_BTDONGLE:
		default:
			parse_btdongle(endp, buf, size);
			break;

		case MODE_MESHBRIDGE:
			parse_meshbridge(endp, buf, size);
			break;
		}
/*
			if(mode == MODE_DONT_PARSE) {
				for(i = 0; i < size; i++) printf("%02x", dp[i]);
				break;
			}
*/
	}
Error:
	if(fp) fclose(fp);
	return result;
}

int wSize = 0;
int wCount = 0;
void parse_meshbridge(int endp, uint8_t* buf, int size)
{
	int i;
	switch(endp) {
	case 0x01:
		if(wCount) {
			if(wCount == 6) printf("W:");
			for(i = 0; i < size; i++) printf("%02x", buf[i]);
CountCheck:
			wCount += size;
			if(wCount >= wSize) {
				wCount = 0;
				printf("\n");
			}
			return;
		} else if(buf[0] == 0x18) {
			wSize = buf[2] + (buf[3]<<8) + 6;
			printf("W:");
			for(i = 0; i < size; i++) {
				if(i == 6) printf("\nW:");
				printf("%02x", buf[i]);
			}
			if(i == 6) printf("\n");
			goto CountCheck;
		}
		printf("W:");
		break;
	case 0x81:
		printf("R:");
		break;
	default:
		printf("%02x:", endp);
		break;
	}
	for(i = 0; i < size; i++) printf("%02x", buf[i]);
	printf("\n");
}

unsigned char sdp[65536];
int sdp_size = 0;
int sdp_count = 0;

unsigned short psmR[65536] = {0};
unsigned short psmW[65536] = {0};
int psm01R = 0, psm01W = 0;
int psm03R = 0, psm03W = 0;
int psm17R = 0, psm17W = 0;
int psm = 0;

void parse_btdongle(int endp, uint8_t* buf, int size)
{
	int h4;
	int i,j,k;

	switch(endp) {
	case 0x00:	h4 = 0x0001;	break;	// C
	case 0x83:	h4 = 0x0104;	break;	// E
	case 0x81:	h4 = 0x0104;	break;	// E
	case 0x03:	h4 = 0x0002;	break;	// W
	case 0x02:	h4 = 0x0002;	break;	// W
	case 0x82:	h4 = 0x0102;	break;	// R
	default:	h4 = 0x0000;	break;
	}
//	printf("%02x %04x ", endp, h4);

	unsigned char* dp = buf;
//	dp++;
//	size--;
	int data;
	int cont;

	switch(h4) {
	case 0x0001:	// cmd
		printf("C:");
		for(i = 0; i < size; i++) {
			if(i == 3) printf(" ");
			printf("%02x", dp[i]);
		}
		data = GetB16(dp);
		for(i = 0; i < sizeof(cmd_table)/sizeof(cmd_table[0]); i++) {
			if(data == cmd_table[i].index) {
				printf("\t%s", cmd_table[i].mes);
				break;
			}
		}
		break;

	case 0x0104:	// event
		if(dp[0] == 0x13) return;
		printf("E:");

		for(i = 0; i < size; i++) {
			if(i == 2) printf(" ");
			printf("%02x", dp[i]);
		}
		if(dp[0] == 0x3E) {
			for(i = 0; i < sizeof(bleSubEvent_table)/sizeof(bleSubEvent_table[0]); i++) {
				if(dp[2] == bleSubEvent_table[i].index) {
					printf("\t%s", bleSubEvent_table[i].mes);
					break;
				}
			}
		} else {
			for(i = 0; i < sizeof(event_table)/sizeof(event_table[0]); i++) {
				if(dp[0] == event_table[i].index) {
					printf("\t%s", event_table[i].mes);
					break;
				}
			}
		}
		break;

	case 0x0102:	// ACL
	case 0x0002: {
		printf(h4 == 0x0102 ? "R:": "W:");
		const struct index2mes2* table;
		int table_num;

		// header
		data = GetB16(dp+6);
		if(data == 0x0100) {
			table = l2cap_table;
			table_num = sizeof(l2cap_table)/sizeof(l2cap_table[0]);
			switch(dp[8]) {
			case 0x02:		// L2CAP_CONN_REQ:psm src
				psm = GetB16(dp+12);
				if(psm == 0x0100) {
					psmR[GetB16(dp+14)] = 0x0100;
				}
				break;
			case 0x03:		// L2CAP_CONN_RSP:dst src result status
				if(psm == 0x0100) {
					psmW[GetB16(dp+12)] = 0x0100;
				}
				break;
			}
		} else if(psmR[data] == 0x0100 || psmW[data] == 0x0100) {
			table = sdp_table;
			table_num = sizeof(sdp_table)/sizeof(sdp_table[0]);
			if(dp[8] == SDP_SVC_SEARCH_ATTR_RSP) {
				int dataLen = GetB16(dp+13);
				for(i = 0; i < size; i++) {
					if(i == 8 || i == 9 || i == 11 || i == 13 || i == 15 || i == 15+dataLen) printf(" ");
					printf("%02x", dp[i]);
				}

				switch(size - (15+dataLen)) {
				case 1:
					cont = dp[15+dataLen];
					break;
				case 2:
					cont = GetB16(dp+15+dataLen);
					if(cont == 0x0101) sdp_count = 0;
					break;
				case 3:
					cont = GetB16(dp+15+dataLen+1);
					if(dp[15+dataLen] == 2 && cont == dataLen) {
						sdp_count = 0;
					}
					break;
				default:
					cont = 0xFF;
					PrintError("");
					break;
				}

				memcpy(sdp+sdp_count, dp+15, dataLen);
				sdp_count += dataLen;

				if(cont == 0) {
					unsigned char* dp2 = sdp;
					int depth = 0;
					printf("\n");
					printSP(&depth, &dp2, sdp_count);
					sdp_count = 0;
				}
				printf("\n");
				return;
			}

		} else {
			table = NULL;
			table_num = 0;
		}

		// search index from table
		int index;
		for(index = 0; index < table_num; index++) {
			if(dp[8] == table[index].index) break;
		}

		if(index < table_num) {
			int offset = 0;
			int num;

			for(i = 0; i < sizeof(table[index].num)/sizeof(int); i++) {
				num = table[index].num[i];
				if(num == 0) break;
				if(num == SP1) {
					unsigned char* dp2 = dp+offset;
					int depth = 3;
					printSP(&depth, &dp2, 0);
					offset = dp2 - dp;
				} else {
					for(j = 0; j < num && offset+j < size; j++) printf("%02x", dp[offset+j]);
					offset += num;
					printf(" ");
				}
			}
			if(table == sdp_table && dp[8] == SDP_SVC_SEARCH_ATTR_REQ) {
				switch(size - offset) {
				case 1:
					cont = dp[offset];
					break;
				case 2:
					cont = GetB16(dp+offset);
					break;
				case 3:
					cont = GetB16(dp+offset+1);
					break;
				default:
					cont = 0xFF; PrintError("");
					break;
				}
			//	printf("cont=%d, %d, %d\n", cont, size, offset);
			//	if(cont == 0) sdp_count = 0;
			}
			for(j = offset; j < size; j++) printf("%02x", dp[j]);

			printf("\t%s", table[index].mes);
		} else {
			for(i = 0; i < size; i++) {
				if(i == 8) printf(" ");
				printf("%02x", dp[i]);
			}
		}
		break;
	}
	default:
		printf("?:");
		for(i = 0; i < size; i++) printf("%02x", dp[i]);
		break;
	}
	printf("\n");
	return;
}
