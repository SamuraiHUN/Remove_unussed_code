search and delete:

	void SetBillType(BYTE bType);
	DWORD GetBillID();

	void SetBillID(DWORD dwID);
	BYTE GetBillType();

	void SetBilling(bool bOn);
	bool IsBilling();

	void SetRemainSecs(long l);
	long GetRemainSecs();

search and delete:

	BYTE m_bBillType;
	DWORD m_dwBillID;
	bool m_bBilling;
	long m_lRemainSecs;