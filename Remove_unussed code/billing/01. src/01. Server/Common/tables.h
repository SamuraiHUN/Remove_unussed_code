Search and delete this:

	HEADER_GD_BILLING_EXPIRE = 104,
	HEADER_GD_BILLING_CHECK = 106,

search and delete this:

	HEADER_DG_BILLING_REPAIR = 128,
	HEADER_DG_BILLING_EXPIRE = 129,
	HEADER_DG_BILLING_LOGIN = 130,
	HEADER_DG_BILLING_CHECK = 132,
	

search and delete too:

	BYTE bBillType;
	DWORD dwBillID;

search and delete too this:

typedef struct SPacketBillingLogin
{
	DWORD dwLoginKey;
	BYTE bLogin;
} TPacketBillingLogin;

typedef struct SPacketBillingRepair
{
	DWORD dwLoginKey;
	char szLogin[LOGIN_MAX_LEN + 1];
	char szHost[MAX_HOST_LENGTH + 1];
} TPacketBillingRepair;

typedef struct SPacketBillingExpire
{
	char szLogin[LOGIN_MAX_LEN + 1];
	BYTE bBillType;
	DWORD dwRemainSeconds;
} TPacketBillingExpire;