search and delete this:

extern int openid_server;

and delete this too:

	case QID_AUTH_LOGIN_OPENID:
	{
		TPacketCGLogin3* pinfo = (TPacketCGLogin3*)qi->pvData;
		LPDESC d = DESC_MANAGER::instance().FindByLoginKey(qi->dwIdent);

		if (!d)
		{
			M2_DELETE(pinfo);
			break;
		}
		// Ŕ§Äˇ şŻ°ć - By SeMinZ
		d->SetLogin(pinfo->login);

		sys_log(0, "QID_AUTH_LOGIN_OPENID: START %u %p", qi->dwIdent, get_pointer(d));

		if (pMsg->Get()->uiNumRows == 0)
		{
			if (true == LC_IsBrazil())
			{
				// °čÁ¤ŔĚ ľřŔ¸¸é »ő·Î ¸¸µéľîľß ÇŃ´Ů
				ReturnQuery(QID_BRAZIL_CREATE_ID, qi->dwIdent, pinfo,
					"INSERT INTO account(login, password, social_id, create_time) "
					"VALUES('%s', password('%s'), '0000000', NOW()) ;",
					pinfo->login, pinfo->passwd);

				sys_log(0, "[AUTH_BRAZIL] : Create A new AccountID From OnGame");
			}
			else if (true == LC_IsJapan())
			{
				// °čÁ¤ŔĚ ľřŔ¸¸é »ő·Î ¸¸µéľîľß ÇŃ´Ů
				ReturnQuery(QID_JAPAN_CREATE_ID, qi->dwIdent, pinfo,
					"INSERT INTO account(login, password, social_id, create_time) "
					"VALUES('%s', password('%s'), '0000000', NOW()) ;",
					pinfo->login, "^Aasl@(!$)djl!231fj!&#");

				sys_log(0, "[AUTH_JAPAN] : Create A new AccountID From OGE");
			}
			else
			{
				sys_log(0, "   NOID");
				LoginFailure(d, "NOID");
				M2_DELETE(pinfo);
			}
		}
		else
		{
			MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
			int col = 0;

			// PASSWORD('%s'), password, securitycode, social_id, id, status
			char szEncrytPassword[45 + 1];
			char szPassword[45 + 1];
			char szMatrixCode[MATRIX_CODE_MAX_LEN + 1];
			char szSocialID[SOCIAL_ID_MAX_LEN + 1];
			char szStatus[ACCOUNT_STATUS_MAX_LEN + 1];
			DWORD dwID = 0;

			if (!row[col])
			{
				sys_err("error column %d", col);
				M2_DELETE(pinfo);
				break;
			}
			strlcpy(szEncrytPassword, row[col++], sizeof(szEncrytPassword));

			if (!row[col])
			{
				sys_err("error column %d", col);
				M2_DELETE(pinfo);
				break;
			}
			strlcpy(szPassword, row[col++], sizeof(szPassword));

			if (!row[col])
			{
				*szMatrixCode = '\0';
				col++;
			}
			else
			{
				strlcpy(szMatrixCode, row[col++], sizeof(szMatrixCode));
			}

			if (!row[col])
			{
				sys_err("error column %d", col);
				M2_DELETE(pinfo);
				break;
			}
			strlcpy(szSocialID, row[col++], sizeof(szSocialID));

			if (!row[col])
			{
				sys_err("error column %d", col);
				M2_DELETE(pinfo);
				break;
			}
			str_to_number(dwID, row[col++]);

			if (!row[col])
			{
				sys_err("error column %d", col);
				M2_DELETE(pinfo);
				break;
			}
			strlcpy(szStatus, row[col++], sizeof(szStatus));

			BYTE bNotAvail = 0;
			str_to_number(bNotAvail, row[col++]);

			int aiPremiumTimes[PREMIUM_MAX_NUM];
			memset(&aiPremiumTimes, 0, sizeof(aiPremiumTimes));

			char szCreateDate[256] = "00000000";

			if (!g_iUseLocale)
			{
				str_to_number(aiPremiumTimes[PREMIUM_EXP], row[col++]);
				str_to_number(aiPremiumTimes[PREMIUM_ITEM], row[col++]);
				str_to_number(aiPremiumTimes[PREMIUM_SAFEBOX], row[col++]);
				str_to_number(aiPremiumTimes[PREMIUM_AUTOLOOT], row[col++]);
				str_to_number(aiPremiumTimes[PREMIUM_FISH_MIND], row[col++]);
				str_to_number(aiPremiumTimes[PREMIUM_MARRIAGE_FAST], row[col++]);
				str_to_number(aiPremiumTimes[PREMIUM_GOLD], row[col++]);
			}
			else
			{
				str_to_number(aiPremiumTimes[PREMIUM_EXP], row[col++]);
				str_to_number(aiPremiumTimes[PREMIUM_ITEM], row[col++]);
				str_to_number(aiPremiumTimes[PREMIUM_SAFEBOX], row[col++]);
				str_to_number(aiPremiumTimes[PREMIUM_AUTOLOOT], row[col++]);
				str_to_number(aiPremiumTimes[PREMIUM_FISH_MIND], row[col++]);
				str_to_number(aiPremiumTimes[PREMIUM_MARRIAGE_FAST], row[col++]);
				str_to_number(aiPremiumTimes[PREMIUM_GOLD], row[col++]);

				if (LC_IsEurope() || test_server)
				{
					long retValue = 0;
					str_to_number(retValue, row[col]);

					time_t create_time = retValue;
					struct tm* tm1;
					tm1 = localtime(&create_time);
					strftime(szCreateDate, 255, "%Y%m%d", tm1);

					sys_log(0, "Create_Time %d %s", retValue, szCreateDate);
					sys_log(0, "Block Time %d ", strncmp(szCreateDate, g_stBlockDate.c_str(), 8));
				}
			}

			int nPasswordDiff = strcmp(szEncrytPassword, szPassword);

			if (true == LC_IsBrazil())
			{
				nPasswordDiff = 0; // şę¶óÁú ąöŔüżˇĽ­´Â şńąĐąřČŁ ĂĽĹ©¸¦ ÇĎÁö ľĘ´Â´Ů.
			}

			//OpenID : OpenID ŔÇ °ćżě, şńąĐąřČŁ ĂĽĹ©¸¦ ÇĎÁö ľĘ´Â´Ů.
			if (openid_server)
			{
				nPasswordDiff = 0;
			}

			if (nPasswordDiff)
			{
				LoginFailure(d, "WRONGPWD");
				sys_log(0, "   WRONGPWD");
				M2_DELETE(pinfo);
			}
			else if (bNotAvail)
			{
				LoginFailure(d, "NOTAVAIL");
				sys_log(0, "   NOTAVAIL");
				M2_DELETE(pinfo);
			}
			else if (DESC_MANAGER::instance().FindByLoginName(pinfo->login))
			{
				LoginFailure(d, "ALREADY");
				sys_log(0, "   ALREADY");
				M2_DELETE(pinfo);
			}
			else if (strcmp(szStatus, "OK"))
			{
				LoginFailure(d, szStatus);
				sys_log(0, "   STATUS: %s", szStatus);
				M2_DELETE(pinfo);
			}
			else
			{
				if (LC_IsEurope())
				{
					//stBlockData >= 0 == łŻÂĄ°ˇ BlockDate ş¸´Ů ąĚ·ˇ 
					if (strncmp(szCreateDate, g_stBlockDate.c_str(), 8) >= 0)
					{
						LoginFailure(d, "BLKLOGIN");
						sys_log(0, "   BLKLOGIN");
						M2_DELETE(pinfo);
						break;
					}

					char szQuery[54 + 1];
					snprintf(szQuery, sizeof(szQuery), "UPDATE account SET last_play=NOW() WHERE id=%u", dwID);
					std::unique_ptr<SQLMsg> msg(DBManager::instance().DirectQuery(szQuery));
				}

				TAccountTable& r = d->GetAccountTable();

				r.id = dwID;
				trim_and_lower(pinfo->login, r.login, sizeof(r.login));
				strlcpy(r.passwd, pinfo->passwd, sizeof(r.passwd));
				strlcpy(r.social_id, szSocialID, sizeof(r.social_id));
				sys_log(0, "not connected!");
				DESC_MANAGER::instance().ConnectAccount(r.login, d);
				sys_log(0, "connected!");

				d->SetMatrixCode(szMatrixCode);

				if (!g_bBilling)
				{
					LoginPrepare(BILLING_FREE, 0, 0, d, pinfo->adwClientKey, aiPremiumTimes);
					//By SeMinZ
					M2_DELETE(pinfo);
					break;
				}

				sys_log(0, "QID_AUTH_LOGIN_OPENID: SUCCESS %s", pinfo->login);
			}
		}
	}
	break;

and delete this too:

	case QID_BRAZIL_CREATE_ID:
	{
		TPacketCGLogin3* pinfo = (TPacketCGLogin3*)qi->pvData;

		if (pMsg->Get()->uiAffectedRows == 0 || pMsg->Get()->uiAffectedRows == (uint32_t)-1)
		{
			LPDESC d = DESC_MANAGER::instance().FindByLoginKey(qi->dwIdent);
			sys_log(0, "[AUTH_BRAZIL]   NOID");
			sys_log(0, "[AUTH_BRAZIL] : Failed to create a new account %s", pinfo->login);
			LoginFailure(d, "NOID");
			M2_DELETE(pinfo);
		}
		else
		{
			sys_log(0, "[AUTH_BRAZIL] : Succeed to create a new account %s", pinfo->login);

			ReturnQuery(QID_AUTH_LOGIN, qi->dwIdent, pinfo,
				"SELECT PASSWORD('%s'),password,securitycode,social_id,id,status,availDt - NOW() > 0,"
				"UNIX_TIMESTAMP(silver_expire),"
				"UNIX_TIMESTAMP(gold_expire),"
				"UNIX_TIMESTAMP(safebox_expire),"
				"UNIX_TIMESTAMP(autoloot_expire),"
				"UNIX_TIMESTAMP(fish_mind_expire),"
				"UNIX_TIMESTAMP(marriage_fast_expire),"
				"UNIX_TIMESTAMP(money_drop_rate_expire),"
				"UNIX_TIMESTAMP(create_time)"
				" FROM account WHERE login='%s'",
				pinfo->passwd, pinfo->login);
		}
	}
	break;
	case QID_JAPAN_CREATE_ID:
	{
		TPacketCGLogin3* pinfo = (TPacketCGLogin3*)qi->pvData;

		if (pMsg->Get()->uiAffectedRows == 0 || pMsg->Get()->uiAffectedRows == (uint32_t)-1)
		{
			LPDESC d = DESC_MANAGER::instance().FindByLoginKey(qi->dwIdent);
			sys_log(0, "[AUTH_JAPAN]   NOID");
			sys_log(0, "[AUTH_JAPAN] : Failed to create a new account %s", pinfo->login);
			LoginFailure(d, "NOID");
			M2_DELETE(pinfo);
		}
		else
		{
			sys_log(0, "[AUTH_JAPAN] : Succeed to create a new account %s", pinfo->login);

			ReturnQuery(QID_AUTH_LOGIN_OPENID, qi->dwIdent, pinfo,
				"SELECT PASSWORD('%s'),password,securitycode,social_id,id,status,availDt - NOW() > 0,"
				"UNIX_TIMESTAMP(silver_expire),"
				"UNIX_TIMESTAMP(gold_expire),"
				"UNIX_TIMESTAMP(safebox_expire),"
				"UNIX_TIMESTAMP(autoloot_expire),"
				"UNIX_TIMESTAMP(fish_mind_expire),"
				"UNIX_TIMESTAMP(marriage_fast_expire),"
				"UNIX_TIMESTAMP(money_drop_rate_expire),"
				"UNIX_TIMESTAMP(create_time)"
				" FROM account WHERE login='%s'",
				pinfo->passwd, pinfo->login);
		}
	}
	break;