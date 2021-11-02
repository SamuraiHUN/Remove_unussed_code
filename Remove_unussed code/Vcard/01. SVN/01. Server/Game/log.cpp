search and delete:

void LogManager::VCardLog(DWORD vcard_id, DWORD x, DWORD y, const char* hostname, const char* giver_name, const char* giver_ip, const char* taker_name, const char* taker_ip)
{
	Query("INSERT DELAYED INTO vcard_log (vcard_id, x, y, hostname, giver_name, giver_ip, taker_name, taker_ip) VALUES(%u, %u, %u, '%s', '%s', '%s', '%s', '%s')",
		vcard_id, x, y, hostname, giver_name, giver_ip, taker_name, taker_ip);
}
