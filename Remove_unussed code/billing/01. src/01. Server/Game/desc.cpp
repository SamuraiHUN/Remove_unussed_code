search and remove this:

	m_dwBillingExpireSecond = 0;

search and remove this too:

void DESC::SetBillingExpireSecond(DWORD dwSec)
{
	m_dwBillingExpireSecond = dwSec;
}

DWORD DESC::GetBillingExpireSecond()
{
	return m_dwBillingExpireSecond;
}
