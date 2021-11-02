Search and delete this.

#ifdef USE_OPENID
extern int openid_test;
#endif

and this:

#ifdef USE_OPENID
// 2012.07.16 ±čżëżí
// ŔĎş» OpenID Áöżř. ŔÎÁőĹ° ŔÎŔÚ Ăß°ˇ
bool __IsOpenIDAuthKeyOption(LPSTR lpCmdLine)
{
	return (strcmp(lpCmdLine, "--openid-authkey") == 0);
}

bool __IsOpenIDTestOption(LPSTR lpCmdLine) // Ĺ¬¶óŔĚľđĆ®żˇĽ­ ·Î±×ŔÎŔĚ °ˇ´ÉÇĎ´Ů.
{
	return (strcmp(lpCmdLine, "--openid-test") == 0);
}
#endif /* USE_OPENID */

and this:

#ifdef USE_OPENID
		else if (__IsOpenIDAuthKeyOption(szArgv[i])) //2012.07.16 OpenID : ±čżëżí
		{
			// ŔÎÁőĹ° ĽłÁ¤żŁ ŔÎŔÚ°ˇ ÇŃ °ł ´ő ÇĘżäÇÔ (ŔÎÁőĹ°)
			if (nArgc <= i + 1)
			{
				MessageBox(NULL, "Invalid arguments", ApplicationStringTable_GetStringz(IDS_APP_NAME, "APP_NAME"), MB_ICONSTOP);
				goto Clean;
			}

			const char* authKey = szArgv[++i];

			// ongoing (2012.07.16)
			// ŔÎÁőĹ° ŔúŔĺÇĎ´Â şÎşĐ
			LocaleService_SetOpenIDAuthKey(authKey);

			bAuthKeyChecked = true;
		}
		else if (__IsOpenIDTestOption(szArgv[i]))
		{
			openid_test = 1;
		}
#endif /* USE_OPENID */

and delete this too:

#ifdef USE_OPENID
	// OpenID
	// OpenID Ĺ¬¶óŔĚľđĆ®ŔÇ °ćżěŔÎÁőĹ°¸¦ ąŢľĆżŔÁö ľĘŔ» °ćżě (ŔĄŔ» Á¦żÜÇĎ°í ˝ÇÇŕ ˝Ă) Ĺ¬¶óŔĚľđĆ® Áľ·á.

	if (false == bAuthKeyChecked && !openid_test)
	{
		MessageBox(NULL, "Invalid execution", ApplicationStringTable_GetStringz(IDS_APP_NAME, "APP_NAME"), MB_ICONSTOP);
		goto Clean;
	}
#endif /* USE_OPENID */