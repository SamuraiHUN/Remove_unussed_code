search this and delete:

extern int openid_server;

and this:

void CInputDB::AuthLoginOpenID(LPDESC d, const char* c_pData)
{
	if (!d)
		return;

	BYTE bResult = *(BYTE*)c_pData;

	TPacketGCAuthSuccessOpenID ptoc;

	ptoc.bHeader = HEADER_GC_AUTH_SUCCESS_OPENID;

	if (bResult)
	{
		// Panama ľĎČŁČ­ ĆŃżˇ ÇĘżäÇŃ Ĺ° ş¸ł»±â
		SendPanamaList(d);
		ptoc.dwLoginKey = d->GetLoginKey();

		// NOTE: AuthSucessş¸´Ů ¸ŐŔú ş¸ł»ľßÁö ľČ±×·Ż¸é PHASE Close°ˇ µÇĽ­ ş¸ł»ÁöÁö ľĘ´Â´Ů.-_-
		// Send Client Package CryptKey
		{
			DESC_MANAGER::instance().SendClientPackageCryptKey(d);
			DESC_MANAGER::instance().SendClientPackageSDBToLoadMap(d, MAPNAME_DEFAULT);
		}
	}
	else
	{
		ptoc.dwLoginKey = 0;
	}

	strcpy(ptoc.login, d->GetLogin().c_str());

	ptoc.bResult = bResult;

	d->Packet(&ptoc, sizeof(TPacketGCAuthSuccessOpenID));
	sys_log(0, "AuthLogin result %u key %u", bResult, d->GetLoginKey());
}

this change:

	case HEADER_DG_AUTH_LOGIN:
		if (openid_server)
			AuthLoginOpenID(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
		else
			AuthLogin(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
		break;

to:

	case HEADER_DG_AUTH_LOGIN:
		AuthLogin(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
		break;