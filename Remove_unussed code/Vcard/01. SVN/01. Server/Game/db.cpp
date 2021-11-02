search and delete this:

void VCardUse(LPCHARACTER CardOwner, LPCHARACTER CardTaker, LPITEM item)
{
	TPacketGDVCard p;

	p.dwID = item->GetSocket(0);
	strlcpy(p.szSellCharacter, CardOwner->GetName(), sizeof(p.szSellCharacter));
	strlcpy(p.szSellAccount, CardOwner->GetDesc()->GetAccountTable().login, sizeof(p.szSellAccount));
	strlcpy(p.szBuyCharacter, CardTaker->GetName(), sizeof(p.szBuyCharacter));
	strlcpy(p.szBuyAccount, CardTaker->GetDesc()->GetAccountTable().login, sizeof(p.szBuyAccount));

	db_clientdesc->DBPacket(HEADER_GD_VCARD, 0, &p, sizeof(TPacketGDVCard));

	CardTaker->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("%dşĐŔÇ °áÁ¦˝Ă°ŁŔĚ Ăß°ˇ µÇľú˝Ŕ´Ď´Ů. (°áÁ¦ąřČŁ %d)"), item->GetSocket(1) / 60, item->GetSocket(0));

	LogManager::instance().VCardLog(p.dwID, CardTaker->GetX(), CardTaker->GetY(), g_stHostname.c_str(),
		CardOwner->GetName(), CardOwner->GetDesc()->GetHostName(),
		CardTaker->GetName(), CardTaker->GetDesc()->GetHostName());

	ITEM_MANAGER::instance().RemoveItem(item);

	sys_log(0, "VCARD_TAKE: %u %s -> %s", p.dwID, CardOwner->GetName(), CardTaker->GetName());
}

