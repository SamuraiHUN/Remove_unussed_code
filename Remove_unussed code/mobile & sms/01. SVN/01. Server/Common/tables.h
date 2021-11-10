Search and remove this:

	char szMobile[MOBILE_MAX_LEN + 1];


Search and remove this:

typedef struct SPacketGDSMS
{
	char szFrom[CHARACTER_NAME_MAX_LEN + 1];
	char szTo[CHARACTER_NAME_MAX_LEN + 1];
	char szMobile[MOBILE_MAX_LEN + 1];
	char szMsg[SMS_MAX_LEN + 1];
} TPacketGDSMS;

Search and remove this:

	HEADER_GD_SMS = 45,