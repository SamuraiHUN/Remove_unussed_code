Search and delete this:

	HEADER_GG_MESSENGER_MOBILE = 14,

Search and delete this:

	HEADER_CG_SMS = 107,

Search and delete this:

typedef struct SMessengerData
{
	char szMobile[MOBILE_MAX_LEN + 1];
} TMessengerData;

Search and delete this:

typedef struct SPacketGGMessengerMobile
{
	BYTE bHeader;
	char szName[CHARACTER_NAME_MAX_LEN + 1];
	char szMobile[MOBILE_MAX_LEN + 1];
} TPacketGGMessengerMobile;

Search:

	MESSENGER_SUBHEADER_GC_LIST,
	MESSENGER_SUBHEADER_GC_LOGIN,
	MESSENGER_SUBHEADER_GC_LOGOUT,
	MESSENGER_SUBHEADER_GC_INVITE,
	MESSENGER_SUBHEADER_GC_MOBILE

Modify to:

	MESSENGER_SUBHEADER_GC_LIST,
	MESSENGER_SUBHEADER_GC_LOGIN,
	MESSENGER_SUBHEADER_GC_LOGOUT,
	MESSENGER_SUBHEADER_GC_INVITE