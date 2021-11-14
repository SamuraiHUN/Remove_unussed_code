Search and delete this:

#include "check_server.h"

and this:

    if (!CCheckServer::Instance().IsValid())
    {
        ClearAdminPages();
        return;
    }

Search and delet this:

	extern bool Metin2Server_IsInvalid();

and this:

	if (Metin2Server_IsInvalid())
	{
		extern bool g_bShutdown;
		g_bShutdown = true;
		ClearAdminPages();
	}