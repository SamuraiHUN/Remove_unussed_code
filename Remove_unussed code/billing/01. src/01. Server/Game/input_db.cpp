search and delete:

////////////////////////////////////////////////////////////////////
// Billing
////////////////////////////////////////////////////////////////////
void CInputDB::BillingRepair(const char* c_pData)
{
	DWORD dwCount = *(DWORD*)c_pData;
	c_pData += sizeof(DWORD);

	TPacketBillingRepair* p = (TPacketBillingRepair*)c_pData;

	for (DWORD i = 0; i < dwCount; ++i, ++p)
	{
		CLoginData* pkLD = M2_NEW CLoginData;

		pkLD->SetKey(p->dwLoginKey);
		pkLD->SetLogin(p->szLogin);
		pkLD->SetIP(p->szHost);

		sys_log(0, "BILLING: REPAIR %s host %s", p->szLogin, p->szHost);
	}
}

void CInputDB::BillingExpire(const char* c_pData)
{
	TPacketBillingExpire* p = (TPacketBillingExpire*)c_pData;

	LPDESC d = DESC_MANAGER::instance().FindByLoginName(p->szLogin);

	if (!d)
		return;

	LPCHARACTER ch = d->GetCharacter();

	if (p->dwRemainSeconds <= 60)
	{
		int i = MAX(5, p->dwRemainSeconds);
		sys_log(0, "BILLING_EXPIRE: %s %u", p->szLogin, p->dwRemainSeconds);
		d->DelayedDisconnect(i);
	}
	else
	{
		if ((p->dwRemainSeconds - d->GetBillingExpireSecond()) > 60)
		{
			d->SetBillingExpireSecond(p->dwRemainSeconds);

			if (ch)
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("°áŔç±â°ŁŔĚ %dşĐ ČÄ ¸¸·á µË´Ď´Ů."), (p->dwRemainSeconds / 60));
		}
	}
}

void CInputDB::BillingLogin(const char* c_pData)
{
	if (NULL == c_pData)
		return;

	TPacketBillingLogin* p;

	DWORD dwCount = *(DWORD*)c_pData;
	c_pData += sizeof(DWORD);

	p = (TPacketBillingLogin*)c_pData;

	for (DWORD i = 0; i < dwCount; ++i, ++p)
	{
		DBManager::instance().SetBilling(p->dwLoginKey, p->bLogin);
	}
}

void CInputDB::BillingCheck(const char* c_pData)
{
	DWORD size = *(DWORD*)c_pData;
	c_pData += sizeof(DWORD);

	for (DWORD i = 0; i < size; ++i)
	{
		DWORD dwKey = *(DWORD*)c_pData;
		c_pData += sizeof(DWORD);

		sys_log(0, "BILLING: NOT_LOGIN %u", dwKey);
		DBManager::instance().SetBilling(dwKey, 0, true);
	}
}

search and delete:

	case HEADER_DG_BILLING_REPAIR:
		BillingRepair(c_pData);
		break;

	case HEADER_DG_BILLING_EXPIRE:
		BillingExpire(c_pData);
		break;

	case HEADER_DG_BILLING_LOGIN:
		BillingLogin(c_pData);
		break;

	case HEADER_DG_BILLING_CHECK:
		BillingCheck(c_pData);
		break;