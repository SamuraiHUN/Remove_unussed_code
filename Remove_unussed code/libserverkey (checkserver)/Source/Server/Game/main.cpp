Search and delete this:

#include "check_server.h"

and delete this:

    CCheckServer checkServer;

search and delete this:

Metin2Server_IsInvalid
static bool g_isInvalidServer = false;

search and delete this:

	bool Metin2Server_IsInvalid()
	{
		return g_isInvalidServer;
	}

search and delete this:

void Metin2Server_Check()
{
#ifdef _USE_SERVER_KEY_
	if (false == CheckServer::CheckIp(g_szPublicIP))
	{
#ifdef _WIN32
		fprintf(stderr, "check ip failed\n");
#endif
		g_isInvalidServer = true;
	}
	return;
#endif

	if (LC_IsEurope() || test_server)
		return;


	// şę¶óÁú ip
	if (strncmp(g_szPublicIP, "189.112.1", 9) == 0)
	{
		return;
	}

	// ÄłłŞ´Ů ip
	if (strncmp(g_szPublicIP, "74.200.6", 8) == 0)
	{
		return;
	}

	return;

	static const size_t CheckServerListSize = 1;
	static const char* CheckServerList[] = { "202.31.178.251" };
	static const int CheckServerPort = 7120;

	socket_t sockConnector = INVALID_SOCKET;

	for (size_t i = 0; i < CheckServerListSize; i++)
	{
		sockConnector = socket_connect(CheckServerList[i], CheckServerPort);

		if (0 < sockConnector)
			break;
	}

	if (0 > sockConnector)
	{
		if (true != LC_IsEurope()) // ŔŻ·´Ŕş Á˘ĽÓŔ» ÇĎÁö ¸řÇĎ¸é ŔÎÁőµČ °ÍŔ¸·Î °ŁÁÖ
			g_isInvalidServer = true;

		return;
	}

	char buf[256] = { 0, };

	socket_read(sockConnector, buf, sizeof(buf) - 1);

	sys_log(0, "recv[%s]", buf);

	if (strncmp(buf, "OK", 2) == 0)
		g_isInvalidServer = false;
	else if (strncmp(buf, "CK", 2) == 0)
		g_isInvalidServer = true;

	socket_close(sockConnector);
}

search and delete this:

Metin2Server_Check();
