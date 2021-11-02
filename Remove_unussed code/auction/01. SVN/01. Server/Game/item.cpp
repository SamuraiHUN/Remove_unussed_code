Search and delete:

#ifdef __AUCTION__

// °ć¸ĹŔĺ
// window¸¦ °ć¸ĹŔĺŔ¸·Î ÇŃ´Ů.

bool CItem::MoveToAuction()
{
	LPCHARACTER owner = GetOwner();
	if (owner == NULL)
	{
		sys_err ("Item those owner is not exist cannot regist in auction");
		return false;
	}

	if (GetWindow() == AUCTION)
	{
		sys_err ("Item is already in auction.");
	}

	SetWindow(AUCTION);
	owner->SetItem(m_bCell, NULL);
	Save();
	ITEM_MANAGER::instance().FlushDelayedSave(this);

	return true;
}

void CItem::CopyToRawData (TPlayerItem* new_item)
{
	if (new_item != NULL)
		return;

	new_item->id = m_dwID;
	new_item->window = m_bWindow;
	new_item->pos = m_bCell;
	new_item->count = m_dwCount;

	new_item->vnum = GetVnum();
	thecore_memcpy (new_item->alSockets, m_alSockets, sizeof (m_alSockets));
	thecore_memcpy (new_item->aAttr, m_aAttr, sizeof (m_aAttr));

	new_item->owner = m_pOwner->GetPlayerID();
}
#endif