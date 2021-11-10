search and delete:

	m_bBillType = 0;
	m_dwBillID = 0;
	m_bBilling = false;

search and delete:

void CLoginData::SetBillType(BYTE bType)
{
	m_bBillType = bType;
}

DWORD CLoginData::GetBillID()
{
	return m_dwBillID;
}

void CLoginData::SetBillID(DWORD dwID)
{
	m_dwBillID = dwID;
}

BYTE CLoginData::GetBillType()
{
	return m_bBillType;
}


search this:

void CLoginData::SetRemainSecs(long l)
{
	m_lRemainSecs = l;
	sys_log(0, "SetRemainSecs %s %d type %u", m_stLogin.c_str(), m_lRemainSecs, m_bBillType);
}

modify to:

void CLoginData::SetRemainSecs(long l)
{
	m_lRemainSecs = l;
	sys_log(0, "SetRemainSecs %s %d type %u", m_stLogin.c_str(), m_lRemainSecs);
}

search this and delete:

void CLoginData::SetBilling(bool bOn)
{
	if (bOn)
	{
		sys_log(0, "BILLING: ON %s key %u ptr %p", m_stLogin.c_str(), m_dwKey, this);
		SetLogonTime();
	}
	else
		sys_log(0, "BILLING: OFF %s key %u ptr %p", m_stLogin.c_str(), m_dwKey, this);

	m_bBilling = bOn;
}

bool CLoginData::IsBilling()
{
	return m_bBilling;
}
