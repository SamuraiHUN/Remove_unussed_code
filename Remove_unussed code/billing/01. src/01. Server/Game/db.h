search and remove this:

	QID_BILLING_GET_TIME,
	QID_BILLING_CHECK,

search and remove this:

	BYTE bBillType;

search and remove this:

typedef std::map<std::string, CLoginData*> LDBillingMap;

search this:

	void LoginPrepare(BYTE bBillType, DWORD dwBillID, long lRemainSecs, LPDESC d, DWORD* pdwClientKey, int* paiPremiumTimes = NULL);
	
modify to:

	void LoginPrepare(LPDESC d, DWORD* pdwClientKey, int* paiPremiumTimes = NULL);

search and remove this:

	void SetBilling(DWORD dwKey, bool bOn, bool bSkipPush = false);
	void PushBilling(CLoginData* pkLD);
	void FlushBilling(bool bForce = false);
	void CheckBilling();

	void StopAllBilling(); // 20050503.ipkn.DB-AUTH Á˘ĽÓ Áľ·á˝Ă şô¸µ Ĺ×ŔĚşí ¸đµÎ Áöżě±â (Ŕçż¬°á˝Ă şą±¸ÇÔ)

search and remove this:

	LDBillingMap mapLDBilling;

search and remove this:

extern void SendBillingExpire(const char* c_pszLogin, BYTE bBillType, int iSecs, CLoginData* pkLD);

