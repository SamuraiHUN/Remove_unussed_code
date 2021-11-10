Search and remove this:

void CClientManager::QUERY_SMS(CPeer* pkPeer, TPacketGDSMS* pack)
{
	char szQuery[QUERY_MAX_LEN];

	char szMsg[256 + 1];
	//unsigned long len = CDBManager::instance().EscapeString(szMsg, pack->szMsg, strlen(pack->szMsg), SQL_ACCOUNT);
	unsigned long len = CDBManager::instance().EscapeString(szMsg, pack->szMsg, strlen(pack->szMsg));
	szMsg[len] = '\0';

	snprintf(szQuery, sizeof(szQuery),
		"INSERT INTO sms_pool (server, sender, receiver, mobile, msg) VALUES(%d, '%s', '%s', '%s', '%s')",
		(m_iPlayerIDStart + 2) / 3, pack->szFrom, pack->szTo, pack->szMobile, szMsg);

	CDBManager::instance().AsyncQuery(szQuery);
}


Search and remove this:

		case HEADER_GD_SMS:
			QUERY_SMS(peer, (TPacketGDSMS*)data);
			break;