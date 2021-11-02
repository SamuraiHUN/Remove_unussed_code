search and delete this:

extern bool g_bNoPasspod;

and this:

//Áß±ą passpod Ŕüżë ÇÔĽö 
bool CheckPasspod(const char* account)
{
	char szQuery[1024];

	snprintf(szQuery, sizeof(szQuery), "SELECT ID FROM passpod WHERE Login='%s'", account);
	SQLMsg* pMsg = DBManager::instance().DirectQuery(szQuery);

	if (!pMsg)
	{
		//fprintf(stderr, "cannot get the MATRIX\n");
		sys_log(0, "cannot get the PASSPOD");
		delete pMsg;
		return false;
	}

	if (pMsg->Get()->uiNumRows == 0)
	{
		puts(szQuery);
		sys_log(0, "[PASSPOD]DirectQuery failed(%s)", szQuery);

		delete pMsg;
		return false;
	}

	delete pMsg;

	return true;
}

search this:

void DBManager::LoginPrepare(BYTE bBillType, DWORD dwBillID, long lRemainSecs, LPDESC d, DWORD* pdwClientKey, int* paiPremiumTimes)
{
	const TAccountTable& r = d->GetAccountTable();

	CLoginData* pkLD = M2_NEW CLoginData;

	pkLD->SetKey(d->GetLoginKey());
	pkLD->SetLogin(r.login);
	pkLD->SetBillType(bBillType);
	pkLD->SetBillID(dwBillID);
	pkLD->SetRemainSecs(lRemainSecs);
	pkLD->SetIP(d->GetHostName());
	pkLD->SetClientKey(pdwClientKey);

	if (paiPremiumTimes)
		pkLD->SetPremium(paiPremiumTimes);

	InsertLoginData(pkLD);

	if (*d->GetMatrixCode())
	{
		unsigned long rows = 0, cols = 0;
		MatrixCardRndCoordinate(rows, cols);

		d->SetMatrixCardRowsAndColumns(rows, cols);

		TPacketGCMatrixCard pm;

		pm.bHeader = HEADER_GC_MATRIX_CARD;
		pm.dwRows = rows;
		pm.dwCols = cols;

		d->Packet(&pm, sizeof(TPacketGCMatrixCard));

		sys_log(0, "MATRIX_QUERY: %s %c%d %c%d %c%d %c%d %s",
			r.login,
			MATRIX_CARD_ROW(rows, 0) + 'A',
			MATRIX_CARD_COL(cols, 0) + 1,
			MATRIX_CARD_ROW(rows, 1) + 'A',
			MATRIX_CARD_COL(cols, 1) + 1,
			MATRIX_CARD_ROW(rows, 2) + 'A',
			MATRIX_CARD_COL(cols, 2) + 1,
			MATRIX_CARD_ROW(rows, 3) + 'A',
			MATRIX_CARD_COL(cols, 3) + 1,
			d->GetMatrixCode());
	}
	else
	{
		if (LC_IsNewCIBN())
		{
			if (!g_bNoPasspod)
			{
				if (CheckPasspod(r.login))
				{
					BYTE id = HEADER_GC_REQUEST_PASSPOD;
					d->Packet(&id, sizeof(BYTE));
					sys_log(0, "%s request passpod", r.login);
				}
				else
				{
					SendAuthLogin(d);

				}
			}
			else
			{
				SendAuthLogin(d);
			}
		}
		else
			SendAuthLogin(d);
	}
}

change to:

void DBManager::LoginPrepare(BYTE bBillType, DWORD dwBillID, long lRemainSecs, LPDESC d, DWORD* pdwClientKey, int* paiPremiumTimes)
{
	const TAccountTable& r = d->GetAccountTable();

	CLoginData* pkLD = M2_NEW CLoginData;

	pkLD->SetKey(d->GetLoginKey());
	pkLD->SetLogin(r.login);
	pkLD->SetBillType(bBillType);
	pkLD->SetBillID(dwBillID);
	pkLD->SetRemainSecs(lRemainSecs);
	pkLD->SetIP(d->GetHostName());
	pkLD->SetClientKey(pdwClientKey);

	if (paiPremiumTimes)
		pkLD->SetPremium(paiPremiumTimes);

	InsertLoginData(pkLD);

	if (*d->GetMatrixCode())
	{
		unsigned long rows = 0, cols = 0;
		MatrixCardRndCoordinate(rows, cols);

		d->SetMatrixCardRowsAndColumns(rows, cols);

		TPacketGCMatrixCard pm;

		pm.bHeader = HEADER_GC_MATRIX_CARD;
		pm.dwRows = rows;
		pm.dwCols = cols;

		d->Packet(&pm, sizeof(TPacketGCMatrixCard));

		sys_log(0, "MATRIX_QUERY: %s %c%d %c%d %c%d %c%d %s",
			r.login,
			MATRIX_CARD_ROW(rows, 0) + 'A',
			MATRIX_CARD_COL(cols, 0) + 1,
			MATRIX_CARD_ROW(rows, 1) + 'A',
			MATRIX_CARD_COL(cols, 1) + 1,
			MATRIX_CARD_ROW(rows, 2) + 'A',
			MATRIX_CARD_COL(cols, 2) + 1,
			MATRIX_CARD_ROW(rows, 3) + 'A',
			MATRIX_CARD_COL(cols, 3) + 1,
			d->GetMatrixCode());
	}

	SendAuthLogin(d);
}