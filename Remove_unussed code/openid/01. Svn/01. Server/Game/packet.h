search this and delete:

	HEADER_CG_LOGIN5_OPENID = 116, // OpenID : Ĺ¬¶óŔĚľđĆ®·ÎşÎĹÍ OpenID ŔÎÁőĹ°¸¦ ąŢ´Â´Ů.

	HEADER_GC_AUTH_SUCCESS_OPENID = 154,

and delete this:

typedef struct command_login5
{
	BYTE header;
	char authKey[OPENID_AUTHKEY_LEN + 1];
	DWORD adwClientKey[4];
} TPacketCGLogin5;


and this.

typedef struct packet_auth_success_openid
{
	BYTE bHeader;
	DWORD dwLoginKey;
	BYTE bResult;
	char login[LOGIN_MAX_LEN + 1];
} TPacketGCAuthSuccessOpenID;