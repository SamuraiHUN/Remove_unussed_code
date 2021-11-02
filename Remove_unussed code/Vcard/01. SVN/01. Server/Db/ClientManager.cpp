search and delete this:

void CClientManager::VCard(TPacketGDVCard* p)
{
	sys_log(0, "VCARD: %u %s %s %s %s",
		p->dwID, p->szSellCharacter, p->szSellAccount, p->szBuyCharacter, p->szBuyAccount);

	m_queue_vcard.push(*p);
}

void CClientManager::VCardProcess()
{
	if (!m_pkAuthPeer)
		return;

	while (!m_queue_vcard.empty())
	{
		m_pkAuthPeer->EncodeHeader(HEADER_DG_VCARD, 0, sizeof(TPacketGDVCard));
		m_pkAuthPeer->Encode(&m_queue_vcard.front(), sizeof(TPacketGDVCard));

		m_queue_vcard.pop();
	}
}

search and delete:

		case HEADER_GD_VCARD:
			VCard((TPacketGDVCard*)data);
			break;

and delete too:

	VCardProcess();