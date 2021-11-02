search and delete this:

void CInputDB::VCard(const char* c_pData)
{
	TPacketGDVCard* p = (TPacketGDVCard*)c_pData;

	sys_log(0, "VCARD: %u %s %s %s %s", p->dwID, p->szSellCharacter, p->szSellAccount, p->szBuyCharacter, p->szBuyAccount);

	std::unique_ptr<SQLMsg> pmsg(DBManager::instance().DirectQuery("SELECT sell_account, buy_account, time FROM vcard WHERE id=%u", p->dwID));
	if (pmsg->Get()->uiNumRows != 1)
	{
		sys_log(0, "VCARD_FAIL: no data");
		return;
	}

	MYSQL_ROW row = mysql_fetch_row(pmsg->Get()->pSQLResult);

	if (strcmp(row[0], p->szSellAccount))
	{
		sys_log(0, "VCARD_FAIL: sell account differ %s", row[0]);
		return;
	}

	if (!row[1] || *row[1])
	{
		sys_log(0, "VCARD_FAIL: buy account already exist");
		return;
	}

	int time = 0;
	str_to_number(time, row[2]);

	if (!row[2] || time < 0)
	{
		sys_log(0, "VCARD_FAIL: time null");
		return;
	}

	std::unique_ptr<SQLMsg> pmsg1(DBManager::instance().DirectQuery("UPDATE GameTime SET LimitTime=LimitTime+%d WHERE UserID='%s'", time, p->szBuyAccount));

	if (pmsg1->Get()->uiAffectedRows == 0 || pmsg1->Get()->uiAffectedRows == (uint32_t)-1)
	{
		sys_log(0, "VCARD_FAIL: cannot modify GameTime table");
		return;
	}

	std::unique_ptr<SQLMsg> pmsg2(DBManager::instance().DirectQuery("UPDATE vcard,GameTime SET sell_pid='%s', buy_pid='%s', buy_account='%s', sell_time=NOW(), new_time=GameTime.LimitTime WHERE vcard.id=%u AND GameTime.UserID='%s'", p->szSellCharacter, p->szBuyCharacter, p->szBuyAccount, p->dwID, p->szBuyAccount));

	if (pmsg2->Get()->uiAffectedRows == 0 || pmsg2->Get()->uiAffectedRows == (uint32_t)-1)
	{
		sys_log(0, "VCARD_FAIL: cannot modify vcard table");
		return;
	}

	sys_log(0, "VCARD_SUCCESS: %s %s", p->szBuyAccount, p->szBuyCharacter);
}

and this:

	case HEADER_DG_VCARD:
		VCard(c_pData);
		break;