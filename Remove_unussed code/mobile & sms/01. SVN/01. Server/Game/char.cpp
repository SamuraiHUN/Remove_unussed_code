Search and delete this:

	m_szMobileAuth[0] = '\0';

Search and delete this:

	if (m_stMobile.length() && !*m_szMobileAuth)
		strlcpy(tab.szMobile, m_stMobile.c_str(), sizeof(tab.szMobile));

Search and delete this:

		//if (m_stMobile.length())
		//		ChatPacket(CHAT_TYPE_COMMAND, "sms");

Search and delete this:

		if (m_stMobile.length())
			ChatPacket(CHAT_TYPE_COMMAND, "sms");

Search and delete this:

	m_stMobile = t->szMobile;