Search and delete:

	else if (!strcmpi(szCmd, "sms"))
	{
		IAbstractPlayer& rPlayer=IAbstractPlayer::GetSingleton();
		rPlayer.SetMobileFlag(TRUE);
	}
	else if (!strcmpi(szCmd, "nosms"))
	{
		IAbstractPlayer& rPlayer=IAbstractPlayer::GetSingleton();
		rPlayer.SetMobileFlag(FALSE);
	}
	else if (!strcmpi(szCmd, "mobile_auth"))
	{
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnMobileAuthority", Py_BuildValue("()"));
	}