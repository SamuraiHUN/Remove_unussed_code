search and delete:

#include "matrix_card.h"

search this:

void DBManager::LoginPrepare(long lRemainSecs, LPDESC d, DWORD* pdwClientKey, int* paiPremiumTimes)
{
	const TAccountTable& r = d->GetAccountTable();

	CLoginData* pkLD = M2_NEW CLoginData;

	pkLD->SetKey(d->GetLoginKey());
	pkLD->SetLogin(r.login);
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

modify to:

void DBManager::LoginPrepare(long lRemainSecs, LPDESC d, DWORD * pdwClientKey, int * paiPremiumTimes)
{
	const TAccountTable & r = d->GetAccountTable();

	CLoginData * pkLD = M2_NEW CLoginData;

	pkLD->SetKey(d->GetLoginKey());
	pkLD->SetLogin(r.login);
	pkLD->SetRemainSecs(lRemainSecs);
	pkLD->SetIP(d->GetHostName());
	pkLD->SetClientKey(pdwClientKey);

	if (paiPremiumTimes)
		pkLD->SetPremium(paiPremiumTimes);

	InsertLoginData(pkLD);
	SendAuthLogin(d);
}

search and delete this:

			char szMatrixCode[MATRIX_CODE_MAX_LEN + 1];

search and delete this:

			if (!row[col])
			{
				*szMatrixCode = '\0';
				col++;
			}
			else
			{
				strlcpy(szMatrixCode, row[col++], sizeof(szMatrixCode));
			}

search and delete this:

				d->SetMatrixCode(szMatrixCode);

search and delete this:

			char szMatrixCode[MATRIX_CODE_MAX_LEN + 1];


search and delete this:

			if (!row[col])
			{
				*szMatrixCode = '\0';
				col++;
			}
			else
			{
				strlcpy(szMatrixCode, row[col++], sizeof(szMatrixCode));
			}

search and delete this:

				d->SetMatrixCode(szMatrixCode);
