Search and delete:

	HEADER_GD_VCARD = 105,
	HEADER_DG_VCARD = 131,

and delete this too:

typedef struct SPacketGDVCard
{
	DWORD dwID;
	char szSellCharacter[CHARACTER_NAME_MAX_LEN + 1];
	char szSellAccount[LOGIN_MAX_LEN + 1];
	char szBuyCharacter[CHARACTER_NAME_MAX_LEN + 1];
	char szBuyAccount[LOGIN_MAX_LEN + 1];
} TPacketGDVCard;