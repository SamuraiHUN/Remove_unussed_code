Search and delete this:

#include "check_server.h"

and this:

    if (!CCheckServer::Instance().IsValid())
    {
        extern void ClearAdminPages();
        ClearAdminPages();
        exit(1);
        return;
    }

search this and delete:

	Metin2Server_IsInvalid();
	extern bool Metin2Server_IsInvalid();

and this:

	if (Metin2Server_IsInvalid())
	{
		extern void ClearAdminPages();
		ClearAdminPages();
		exit(1);
		return;
	}

######################## If u don't deleted OpenID

search this and delete:

	Metin2Server_IsInvalid();
	extern bool Metin2Server_IsInvalid();

and this:

	if (Metin2Server_IsInvalid())
	{
		extern void ClearAdminPages();
		ClearAdminPages();
		exit(1);
		return;
	}