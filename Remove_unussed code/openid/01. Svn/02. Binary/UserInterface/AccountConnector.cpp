search this and delete:

#ifdef USE_OPENID
extern int openid_test;
#endif

and this:

#ifdef USE_OPENID
	if (!__AnalyzePacket(HEADER_GC_AUTH_SUCCESS_OPENID, sizeof(TPacketGCAuthSuccess), &CAccountConnector::__AuthState_RecvAuthSuccess_OpenID))
		return true;
#endif /* USE_OPENID */

and this change:

#ifdef USE_OPENID
		if (!openid_test)
		{
			//2012.07.19 OpenID : ±čżëżí 
			//Ongoing : żŔÇÂ ľĆŔĚµđ °ćżě-> TPacketCGLogin5
			//Ĺ¬¶ó°ˇ °ˇÁö°í ŔÖ´Â ŔÎÁőĹ°¸¸Ŕ» Ľ­ąöżˇ ş¸ł»µµ·Ď.

			//const char* tempAuthKey = "d4025bc1f752b64fe5d51ae575ec4730"; //ÇĎµĺÄÚµů ±ćŔĚ 32
			TPacketCGLogin5 LoginPacket;
			LoginPacket.header = HEADER_CG_LOGIN5_OPENID;

			strncpy(LoginPacket.authKey, LocaleService_GetOpenIDAuthKey(), OPENID_AUTHKEY_LEN);
			LoginPacket.authKey[OPENID_AUTHKEY_LEN] = '\0';

			for (DWORD i = 0; i < 4; ++i)
				LoginPacket.adwClientKey[i] = g_adwEncryptKey[i];

			if (!Send(sizeof(LoginPacket), &LoginPacket))
			{
				Tracen(" CAccountConnector::__AuthState_RecvPhase - SendLogin5 Error");
				return false;
			}

			if (!SendSequence())
			{
				return false;
			}
		}
		else
		{
			TPacketCGLogin3 LoginPacket;
			LoginPacket.header = HEADER_CG_LOGIN3;

			strncpy(LoginPacket.name, m_strID.c_str(), ID_MAX_NUM);
			strncpy(LoginPacket.pwd, m_strPassword.c_str(), PASS_MAX_NUM);
			LoginPacket.name[ID_MAX_NUM] = '\0';
			LoginPacket.pwd[PASS_MAX_NUM] = '\0';

			// şńąĐąřČŁ¸¦ ¸Ţ¸đ¸®żˇ °čĽÓ °®°í ŔÖ´Â ą®Á¦°ˇ ŔÖľîĽ­, »çżë Áď˝Ă łŻ¸®´Â °ÍŔ¸·Î şŻ°ć
			ClearLoginInfo();
			CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
			rkNetStream.ClearLoginInfo();

			m_strPassword = "";

			for (DWORD i = 0; i < 4; ++i)
				LoginPacket.adwClientKey[i] = g_adwEncryptKey[i];

			if (!Send(sizeof(LoginPacket), &LoginPacket))
			{
				Tracen(" CAccountConnector::__AuthState_RecvPhase - SendLogin3 Error");
				return false;
			}

			if (!SendSequence())
			{
				return false;
			}
		}
#else /* USE_OPENID */

		TPacketCGLogin3 LoginPacket;
		LoginPacket.header = HEADER_CG_LOGIN3;

		strncpy(LoginPacket.name, m_strID.c_str(), ID_MAX_NUM);
		strncpy(LoginPacket.pwd, m_strPassword.c_str(), PASS_MAX_NUM);
		LoginPacket.name[ID_MAX_NUM] = '\0';
		LoginPacket.pwd[PASS_MAX_NUM] = '\0';

		// şńąĐąřČŁ¸¦ ¸Ţ¸đ¸®żˇ °čĽÓ °®°í ŔÖ´Â ą®Á¦°ˇ ŔÖľîĽ­, »çżë Áď˝Ă łŻ¸®´Â °ÍŔ¸·Î şŻ°ć
		ClearLoginInfo();
		CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
		rkNetStream.ClearLoginInfo();

		m_strPassword = "";

		for (DWORD i = 0; i < 4; ++i)
			LoginPacket.adwClientKey[i] = g_adwEncryptKey[i];

		if (!Send(sizeof(LoginPacket), &LoginPacket))
		{
			Tracen(" CAccountConnector::__AuthState_RecvPhase - SendLogin3 Error");
			return false;
		}

		if (!SendSequence())
		{
			return false;
		}
#endif /* USE_OPENID */

to:

		TPacketCGLogin3 LoginPacket;
		LoginPacket.header = HEADER_CG_LOGIN3;

		strncpy(LoginPacket.name, m_strID.c_str(), ID_MAX_NUM);
		strncpy(LoginPacket.pwd, m_strPassword.c_str(), PASS_MAX_NUM);
		LoginPacket.name[ID_MAX_NUM] = '\0';
		LoginPacket.pwd[PASS_MAX_NUM] = '\0';

		// şńąĐąřČŁ¸¦ ¸Ţ¸đ¸®żˇ °čĽÓ °®°í ŔÖ´Â ą®Á¦°ˇ ŔÖľîĽ­, »çżë Áď˝Ă łŻ¸®´Â °ÍŔ¸·Î şŻ°ć
		ClearLoginInfo();
		CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
		rkNetStream.ClearLoginInfo();

		m_strPassword = "";

		for (DWORD i = 0; i < 4; ++i)
			LoginPacket.adwClientKey[i] = g_adwEncryptKey[i];

		if (!Send(sizeof(LoginPacket), &LoginPacket))
		{
			Tracen(" CAccountConnector::__AuthState_RecvPhase - SendLogin3 Error");
			return false;
		}

		if (!SendSequence())
		{
			return false;
		}


and delete this:

#ifdef USE_OPENID
bool CAccountConnector::__AuthState_RecvAuthSuccess_OpenID()
{
	TPacketGCAuthSuccessOpenID kAuthSuccessOpenIDPacket;
	if (!Recv(sizeof(kAuthSuccessOpenIDPacket), &kAuthSuccessOpenIDPacket))
		return false;

	if (!kAuthSuccessOpenIDPacket.bResult)
	{
		if (m_poHandler)
			PyCallClassMemberFunc(m_poHandler, "OnLoginFailure", Py_BuildValue("(s)", "BESAMEKEY"));
	}
	else
	{
		DWORD dwPanamaKey = kAuthSuccessOpenIDPacket.dwLoginKey ^ g_adwEncryptKey[0] ^ g_adwEncryptKey[1] ^ g_adwEncryptKey[2] ^ g_adwEncryptKey[3];
		CEterPackManager::instance().DecryptPackIV(dwPanamaKey);

		CPythonNetworkStream& rkNet = CPythonNetworkStream::Instance();
		rkNet.SetLoginInfo(kAuthSuccessOpenIDPacket.login, "0000");		//OpenID ŔÎÁő °úÁ¤żˇĽ­ şńąĐąřČŁ´Â »çżëµÇÁö ľĘ´Â´Ů.
		rkNet.SetLoginKey(kAuthSuccessOpenIDPacket.dwLoginKey);
		rkNet.Connect(m_strAddr.c_str(), m_iPort);
	}

	Disconnect();
	__OfflineState_Set();

	return true;
}
#endif /* USE_OPENID */

