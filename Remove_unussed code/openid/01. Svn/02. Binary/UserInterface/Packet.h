Search and delete this:

	HEADER_CG_LOGIN5_OPENID = 116, // OpenID : ˝ÇÇŕ˝Ă ąŢŔş ŔÎÁőĹ°¸¦ Ľ­ąöżˇ ş¸łż.

and this.

	HEADER_GC_AUTH_SUCCESS_OPENID = 154,

and this:

	OPENID_AUTHKEY_LEN = 32,

and this:

typedef struct command_login5
{
	BYTE	header;
	char	authKey[OPENID_AUTHKEY_LEN + 1];
	DWORD	adwClientKey[4];
} TPacketCGLogin5;

aand this:

typedef struct packet_auth_success_openid
{
	BYTE        bHeader;
	DWORD       dwLoginKey;
	BYTE        bResult;
	char		login[ID_MAX_NUM + 1];
} TPacketGCAuthSuccessOpenID;