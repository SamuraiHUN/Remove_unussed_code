Search and delete:

	MESSENGER_SUBHEADER_GC_MOBILE,

Search and delete:

	MESSENGER_CONNECTED_STATE_MOBILE,

Search and delete:

	HEADER_CG_SMS = 107,

Search and delete:

typedef struct command_sms
{
	BYTE	bHeader;
	WORD	wSize;
	char	szNameTo[CHARACTER_NAME_MAX_LEN + 1];
} TPacketCGSMS;