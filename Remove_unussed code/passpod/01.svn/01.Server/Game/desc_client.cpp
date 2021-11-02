search and delete this:

LPCLIENT_DESC g_PasspodDesc = NULL;

+ delete this:

	else if (desc == g_PasspodDesc)
	{
		return "g_PasspodDesc";
	}