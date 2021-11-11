search and delete this:

#include "../../common/billing.h"

search and delete this:

	mapLDBilling.erase(pkLD->GetLogin());

search and delete this:

void DBManager::SetBilling(DWORD dwKey, bool bOn, bool bSkipPush)
{
	std::map<DWORD, CLoginData*>::iterator it = m_map_pkLoginData.find(dwKey);

	if (it == m_map_pkLoginData.end())
	{
		sys_err("cannot find login key %u", dwKey);
		return;
	}

	CLoginData* ld = it->second;

	LDBillingMap::const_iterator it2 = mapLDBilling.find(ld->GetLogin());

	if (it2 != mapLDBilling.end())
		if (it2->second != ld)
			DeleteLoginData(it2->second);

	mapLDBilling.insert(std::make_pair(ld->GetLogin(), ld));

	if (ld->IsBilling() && !bOn && !bSkipPush)
		PushBilling(ld);

	SendLoginPing(ld->GetLogin());
	ld->SetBilling(bOn);
}

void DBManager::PushBilling(CLoginData* pkLD)
{
	TUseTime t;

	t.dwUseSec = (get_dword_time() - pkLD->GetLogonTime()) / 1000;

	if (t.dwUseSec <= 0)
		return;

	pkLD->SetLogonTime();
	long lRemainSecs = pkLD->GetRemainSecs() - t.dwUseSec;
	pkLD->SetRemainSecs(MAX(0, lRemainSecs));

	t.dwLoginKey = pkLD->GetKey();
	t.bBillType = pkLD->GetBillType();

	sys_log(0, "BILLING: PUSH %s %u type %u", pkLD->GetLogin(), t.dwUseSec, t.bBillType);

	if (t.bBillType == BILLING_IP_FREE || t.bBillType == BILLING_IP_TIME || t.bBillType == BILLING_IP_DAY)
		snprintf(t.szLogin, sizeof(t.szLogin), "%u", pkLD->GetBillID());
	else
		strlcpy(t.szLogin, pkLD->GetLogin(), sizeof(t.szLogin));

	strlcpy(t.szIP, pkLD->GetIP(), sizeof(t.szIP));

	m_vec_kUseTime.push_back(t);
}

void DBManager::FlushBilling(bool bForce)
{
	if (bForce)
	{
		std::map<DWORD, CLoginData*>::iterator it = m_map_pkLoginData.begin();

		while (it != m_map_pkLoginData.end())
		{
			CLoginData* pkLD = (it++)->second;

			if (pkLD->IsBilling())
				PushBilling(pkLD);
		}
	}

	if (!m_vec_kUseTime.empty())
	{
		DWORD dwCount = 0;

		std::vector<TUseTime>::iterator it = m_vec_kUseTime.begin();

		while (it != m_vec_kUseTime.end())
		{
			TUseTime* p = &(*(it++));

			// DISABLE_OLD_BILLING_CODE
			if (!g_bBilling)
			{
				++dwCount;
				continue;
			}

			Query("INSERT GameTimeLog (login, type, logon_time, logout_time, use_time, ip, server) "
				"VALUES('%s', %u, DATE_SUB(NOW(), INTERVAL %u SECOND), NOW(), %u, '%s', '%s')",
				p->szLogin, p->bBillType, p->dwUseSec, p->dwUseSec, p->szIP, g_stHostname.c_str());
			// DISABLE_OLD_BILLING_CODE_END

			switch (p->bBillType)
			{
			case BILLING_FREE:
			case BILLING_IP_FREE:
				break;

			case BILLING_DAY:
			{
				if (!bForce)
				{
					TUseTime* pInfo = M2_NEW TUseTime;
					memcpy(pInfo, p, sizeof(TUseTime));
					ReturnQuery(QID_BILLING_CHECK, 0, pInfo,
						"SELECT UNIX_TIMESTAMP(LimitDt)-UNIX_TIMESTAMP(NOW()),LimitTime FROM GameTime WHERE UserID='%s'", p->szLogin);
				}
			}
			break;

			case BILLING_TIME:
			{
				Query("UPDATE GameTime SET LimitTime=LimitTime-%u WHERE UserID='%s'", p->dwUseSec, p->szLogin);

				if (!bForce)
				{
					TUseTime* pInfo = M2_NEW TUseTime;
					memcpy(pInfo, p, sizeof(TUseTime));
					ReturnQuery(QID_BILLING_CHECK, 0, pInfo,
						"SELECT UNIX_TIMESTAMP(LimitDt)-UNIX_TIMESTAMP(NOW()),LimitTime FROM GameTime WHERE UserID='%s'", p->szLogin);
				}
			}
			break;

			case BILLING_IP_DAY:
			{
				if (!bForce)
				{
					TUseTime* pInfo = M2_NEW TUseTime;
					memcpy(pInfo, p, sizeof(TUseTime));
					ReturnQuery(QID_BILLING_CHECK, 0, pInfo,
						"SELECT UNIX_TIMESTAMP(LimitDt)-UNIX_TIMESTAMP(NOW()),LimitTime FROM GameTimeIP WHERE ipid=%s", p->szLogin);
				}
			}
			break;

			case BILLING_IP_TIME:
			{
				Query("UPDATE GameTimeIP SET LimitTime=LimitTime-%u WHERE ipid=%s", p->dwUseSec, p->szLogin);

				if (!bForce)
				{
					TUseTime* pInfo = M2_NEW TUseTime;
					memcpy(pInfo, p, sizeof(TUseTime));
					ReturnQuery(QID_BILLING_CHECK, 0, pInfo,
						"SELECT UNIX_TIMESTAMP(LimitDt)-UNIX_TIMESTAMP(NOW()),LimitTime FROM GameTimeIP WHERE ipid=%s", p->szLogin);
				}
			}
			break;
			}

			if (!bForce && ++dwCount >= 1000)
				break;
		}

		if (dwCount < m_vec_kUseTime.size())
		{
			int nNewSize = m_vec_kUseTime.size() - dwCount;
			memcpy(&m_vec_kUseTime[0], &m_vec_kUseTime[dwCount], sizeof(TUseTime) * nNewSize);
			m_vec_kUseTime.resize(nNewSize);
		}
		else
			m_vec_kUseTime.clear();

		sys_log(0, "FLUSH_USE_TIME: count %u", dwCount);
	}

	if (m_vec_kUseTime.size() < 10240)
	{
		DWORD dwCurTime = get_dword_time();

		std::map<DWORD, CLoginData*>::iterator it = m_map_pkLoginData.begin();

		while (it != m_map_pkLoginData.end())
		{
			CLoginData* pkLD = (it++)->second;

			if (!pkLD->IsBilling())
				continue;

			switch (pkLD->GetBillType())
			{
			case BILLING_IP_FREE:
			case BILLING_FREE:
				break;

			case BILLING_IP_DAY:
			case BILLING_DAY:
			case BILLING_IP_TIME:
			case BILLING_TIME:
				if (pkLD->GetRemainSecs() < 0)
				{
					DWORD dwSecsConnected = (dwCurTime - pkLD->GetLogonTime()) / 1000;

					if (dwSecsConnected % 10 == 0)
						SendBillingExpire(pkLD->GetLogin(), BILLING_DAY, 0, pkLD);
				}
				else if (pkLD->GetRemainSecs() <= 600) // if remain seconds lower than 10 minutes
				{
					DWORD dwSecsConnected = (dwCurTime - pkLD->GetLogonTime()) / 1000;

					if (dwSecsConnected >= 60) // 60 second cycle
					{
						sys_log(0, "BILLING 1 %s remain %d connected secs %u",
							pkLD->GetLogin(), pkLD->GetRemainSecs(), dwSecsConnected);
						PushBilling(pkLD);
					}
				}
				else
				{
					DWORD dwSecsConnected = (dwCurTime - pkLD->GetLogonTime()) / 1000;

					if (dwSecsConnected > (DWORD)(pkLD->GetRemainSecs() - 600) || dwSecsConnected >= 600)
					{
						sys_log(0, "BILLING 2 %s remain %d connected secs %u",
							pkLD->GetLogin(), pkLD->GetRemainSecs(), dwSecsConnected);
						PushBilling(pkLD);
					}
				}
				break;
			}
		}
	}

}

void DBManager::CheckBilling()
{
	std::vector<DWORD> vec;
	vec.push_back(0); // Ä«żîĆ®¸¦ Ŕ§ÇŘ ąĚ¸® şńżöµĐ´Ů.

	//sys_log(0, "CheckBilling: map size %d", m_map_pkLoginData.size());

	std::map<DWORD, CLoginData*>::iterator it = m_map_pkLoginData.begin();

	while (it != m_map_pkLoginData.end())
	{
		CLoginData* pkLD = (it++)->second;

		if (pkLD->IsBilling())
		{
			sys_log(0, "BILLING: CHECK %u", pkLD->GetKey());
			vec.push_back(pkLD->GetKey());
		}
	}

	vec[0] = vec.size() - 1; // şńżöµĐ °÷żˇ »çŔĚÁî¸¦ łÖ´Â´Ů, »çŔĚÁî ŔÚ˝ĹŔş Á¦żÜÇŘľß ÇĎąÇ·Î -1
	db_clientdesc->DBPacket(HEADER_GD_BILLING_CHECK, 0, &vec[0], sizeof(DWORD) * vec.size());
}

search and delete this:

	ptod.bBillType = pkLD->GetBillType();
	ptod.dwBillID = pkLD->GetBillID();

search this:

void DBManager::LoginPrepare(BYTE bBillType, DWORD dwBillID, long lRemainSecs, LPDESC d, DWORD* pdwClientKey, int* paiPremiumTimes)

modify to:

void DBManager::LoginPrepare(LPDESC d, DWORD * pdwClientKey, int * paiPremiumTimes)

search and remove this too:

	pkLD->SetBillType(bBillType);
	pkLD->SetBillID(dwBillID);
	pkLD->SetRemainSecs(lRemainSecs);

search and remove this:

bool GetGameTimeIP(MYSQL_RES* pRes, BYTE& bBillType, DWORD& dwBillID, int& seconds, const char* c_pszIP)
{
	if (!pRes)
		return true;

	MYSQL_ROW row = mysql_fetch_row(pRes);
	int col = 0;

	str_to_number(dwBillID, row[col++]);

	int ip_start = 0;
	str_to_number(ip_start, row[col++]);

	int ip_end = 0;
	str_to_number(ip_end, row[col++]);

	int type = 0;
	str_to_number(type, row[col++]);

	str_to_number(seconds, row[col++]);

	int day_seconds = 0;
	str_to_number(day_seconds, row[col++]);

	char szIP[MAX_HOST_LENGTH + 1];
	strlcpy(szIP, c_pszIP, sizeof(szIP));

	char* p = strrchr(szIP, '.');
	++p;

	int ip_postfix = 0;
	str_to_number(ip_postfix, p);
	int valid_ip = false;

	if (ip_start <= ip_postfix && ip_end >= ip_postfix)
		valid_ip = true;

	bBillType = BILLING_NONE;

	if (valid_ip)
	{
		if (type == -1)
			return false;

		if (type == 0)
			bBillType = BILLING_IP_FREE;
		else if (day_seconds > 0)
		{
			bBillType = BILLING_IP_DAY;
			seconds = day_seconds;
		}
		else if (seconds > 0)
			bBillType = BILLING_IP_TIME;
	}

	return true;
}

bool GetGameTime(MYSQL_RES* pRes, BYTE& bBillType, int& seconds)
{
	if (!pRes)
		return true;

	MYSQL_ROW row = mysql_fetch_row(pRes);
	sys_log(1, "GetGameTime %p %p %p", row[0], row[1], row[2]);

	int type = 0;
	str_to_number(type, row[0]);
	str_to_number(seconds, row[1]);
	int day_seconds = 0;
	str_to_number(day_seconds, row[2]);
	bBillType = BILLING_NONE;

	if (type == -1)
		return false;
	else if (type == 0)
		bBillType = BILLING_FREE;
	else if (day_seconds > 0)
	{
		bBillType = BILLING_DAY;
		seconds = day_seconds;
	}
	else if (seconds > 0)
		bBillType = BILLING_TIME;

	if (!g_bBilling)
		bBillType = BILLING_FREE;

	return true;
}

void SendBillingExpire(const char* c_pszLogin, BYTE bBillType, int iSecs, CLoginData* pkLD)
{
	TPacketBillingExpire ptod;

	strlcpy(ptod.szLogin, c_pszLogin, sizeof(ptod.szLogin));
	ptod.bBillType = bBillType;
	ptod.dwRemainSeconds = MAX(0, iSecs);
	db_clientdesc->DBPacket(HEADER_GD_BILLING_EXPIRE, 0, &ptod, sizeof(TPacketBillingExpire));
	sys_log(0, "BILLING: EXPIRE %s type %d sec %d ptr %p", c_pszLogin, bBillType, iSecs, pkLD);
}

search this (2x):

				if (!g_bBilling)
				{
					LoginPrepare(BILLING_FREE, 0, 0, d, pinfo->adwClientKey, aiPremiumTimes);
					// By SeMinZ
					M2_DELETE(pinfo);
					break;
				}

and change to:

				LoginPrepare(d, pinfo->adwClientKey, aiPremiumTimes);
				M2_DELETE(pinfo);


search and remove this:

	case QID_BILLING_GET_TIME:
	{
		TPacketCGLogin3* pinfo = (TPacketCGLogin3*)qi->pvData;
		LPDESC d = DESC_MANAGER::instance().FindByLoginKey(qi->dwIdent);

		sys_log(0, "QID_BILLING_GET_TIME: START ident %u d %p", qi->dwIdent, get_pointer(d));

		if (d)
		{
			if (pMsg->Get()->uiNumRows == 0)
			{
				if (g_bBilling)
					LoginFailure(d, "NOBILL");
				else
					LoginPrepare(BILLING_FREE, 0, 0, d, pinfo->adwClientKey);
			}
			else
			{
				int seconds = 0;
				BYTE bBillType = BILLING_NONE;

				if (!GetGameTime(pMsg->Get()->pSQLResult, bBillType, seconds))
				{
					sys_log(0, "QID_BILLING_GET_TIME: BLOCK");
					LoginFailure(d, "BLOCK");
				}
				else if (bBillType == BILLING_NONE)
				{
					LoginFailure(d, "NOBILL");
					sys_log(0, "QID_BILLING_GET_TIME: NO TIME");
				}
				else
				{
					LoginPrepare(bBillType, 0, seconds, d, pinfo->adwClientKey);
					sys_log(0, "QID_BILLING_GET_TIME: SUCCESS");
				}
			}
		}
		M2_DELETE(pinfo);
	}
	break;

	case QID_BILLING_CHECK:
	{
		TUseTime* pinfo = (TUseTime*)qi->pvData;
		int iRemainSecs = 0;

		CLoginData* pkLD = NULL;

		if (pMsg->Get()->uiNumRows > 0)
		{
			MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);

			int iLimitDt = 0;
			str_to_number(iLimitDt, row[0]);

			int iLimitTime = 0;
			str_to_number(iLimitTime, row[1]);

			pkLD = GetLoginData(pinfo->dwLoginKey);

			if (pkLD)
			{
				switch (pkLD->GetBillType())
				{
				case BILLING_TIME:
					if (iLimitTime <= 600 && iLimitDt > 0)
					{
						iRemainSecs = iLimitDt;
						pkLD->SetBillType(BILLING_DAY);
						pinfo->bBillType = BILLING_DAY;
					}
					else
						iRemainSecs = iLimitTime;
					break;

				case BILLING_IP_TIME:
					if (iLimitTime <= 600 && iLimitDt > 0)
					{
						iRemainSecs = iLimitDt;
						pkLD->SetBillType(BILLING_IP_DAY);
						pinfo->bBillType = BILLING_IP_DAY;
					}
					else
						iRemainSecs = iLimitTime;
					break;

				case BILLING_DAY:
				case BILLING_IP_DAY:
					iRemainSecs = iLimitDt;
					break;
				}

				pkLD->SetRemainSecs(iRemainSecs);
			}
		}

		SendBillingExpire(pinfo->szLogin, pinfo->bBillType, MAX(0, iRemainSecs), pkLD);
		M2_DELETE(pinfo);
	}
	break;

search and remove this:

void DBManager::StopAllBilling()
{
	std::map<DWORD, CLoginData*>::iterator it;
	for (it = m_map_pkLoginData.begin(); it != m_map_pkLoginData.end(); ++it)
	{
		SetBilling(it->first, false);
	}
}
