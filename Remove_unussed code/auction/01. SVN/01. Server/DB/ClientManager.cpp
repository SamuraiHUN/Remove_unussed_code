Search and delete:

#ifdef __AUCTION__
#include "AuctionManager.h"
#endif

Search and delete:

#ifdef __AUCTION__
		sizeof(WORD) + sizeof(WORD) + sizeof(TPlayerItem) * AuctionManager::instance().GetAuctionItemSize() +
		sizeof(WORD) + sizeof(WORD) + sizeof(TAuctionItemInfo) * AuctionManager::instance().GetAuctionSize() +
		sizeof(WORD) + sizeof(WORD) + sizeof(TSaleItemInfo) * AuctionManager::instance().GetSaleSize() +
		sizeof(WORD) + sizeof(WORD) + sizeof(TWishItemInfo) * AuctionManager::instance().GetWishSize() +
		sizeof(WORD) + sizeof(WORD) + (sizeof(DWORD) + sizeof(DWORD) + sizeof(int)) * AuctionManager::instance().GetMyBidSize() +
#endif

Search and delete:

	// Auction Boot
#ifdef __AUCTION__
	AuctionManager::instance().Boot (peer);
#endif

Search and delete:

#ifdef __AUCTION__
	else if (p->window == AUCTION)
	{
		sys_err("invalid window. how can you enter this route?");
		return ;
	}
#endif

Search and delete:

#ifdef __AUCTION__
			case HEADER_GD_COMMAND_AUCTION:
			{
				TPacketGDCommnadAuction* auction_data = (TPacketGDCommnadAuction*)data;

				switch (auction_data->get_cmd())
				{
				case AUCTION_ENR_AUC:
					EnrollInAuction (peer, dwHandle, (AuctionEnrollProductInfo*)data);
					break;
				case AUCTION_ENR_SALE:
					EnrollInSale (peer, dwHandle, (AuctionEnrollSaleInfo*)data);
					break;
				case AUCTION_ENR_WISH:
					EnrollInWish (peer, dwHandle, (AuctionEnrollWishInfo*)data);
					break;
				case AUCTION_BID:
					AuctionBid (peer, dwHandle, (AuctionBidInfo*)data);
					break;
				case AUCTION_IMME_PUR:
					AuctionImpur (peer, dwHandle, (AuctionImpurInfo*)data);
					break;
				case AUCTION_GET_AUC:
					AuctionGetAuctionedItem (peer, dwHandle, auction_data->get_item());
					break;
				case AUCTION_BUY_SOLD:
					AuctionBuySoldItem (peer, dwHandle, auction_data->get_item());
					break;
				case AUCTION_CANCEL_AUC:
					AuctionCancelAuction (peer, dwHandle, auction_data->get_item());
					break;
				case AUCTION_CANCEL_WISH:
					AuctionCancelWish (peer, dwHandle, auction_data->get_item());
					break;
				case AUCTION_CANCEL_SALE:
					AuctionCancelSale (peer, dwHandle, auction_data->get_item());
					break;
				case AUCTION_DELETE_AUCTION_ITEM:
					AuctionDeleteAuctionItem (peer, dwHandle, auction_data->get_item());
					break;
				case AUCTION_DELETE_SALE_ITEM:
					AuctionDeleteSaleItem (peer, dwHandle, auction_data->get_item());
					break;
				case AUCTION_REBID:
					AuctionReBid (peer, dwHandle, (AuctionBidInfo*)data);
					break;
//				case AUCTION_BID_CANCEL:
//					AuctionBidCancel (peer, dwHandle, data->get_item());
				default :
					break;
				}
			}
			break;
#endif

Search and delete:

#ifdef __AUCTION__
void CClientManager::EnrollInAuction (CPeer * peer, DWORD owner_id, AuctionEnrollProductInfo* data)
{
	TPlayerTableCacheMap::iterator it = m_map_playerCache.find (owner_id);

	if (it == m_map_playerCache.end())
	{
		sys_err ("Invalid Player id %d. how can you get it?", owner_id);
		return;
	}
	CItemCache* c = GetItemCache (data->get_item_id());

	if (c == NULL)
	{
		sys_err ("Item %d doesn't exist in db cache.", data->get_item_id());
		return;
	}
	TPlayerItem* item = c->Get(false);

	if (item->owner != owner_id)
	{
		sys_err ("Player id %d doesn't have item %d.", owner_id, data->get_item_id());
		return;
	}
	// ÇöŔç ˝Ă°˘ + 24˝Ă°Ł ČÄ.
	time_t expired_time = time(0) + 24 * 60 * 60;
	TAuctionItemInfo auctioned_item_info (item->vnum, data->get_bid_price(),
		data->get_impur_price(), owner_id, "", expired_time, data->get_item_id(), 0, data->get_empire());

	AuctionResult result = AuctionManager::instance().EnrollInAuction( c, auctioned_item_info );

	if (result <= AUCTION_FAIL)
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_ENR_AUC;
		enroll_result.target = data->get_item_id();
		enroll_result.result = result;
		peer->EncodeHeader(HEADER_DG_AUCTION_RESULT, owner_id, sizeof(TPacketDGResultAuction) + sizeof(TPlayerItem));
		peer->Encode(&enroll_result, sizeof(TPacketDGResultAuction));
		peer->Encode(c->Get(false), sizeof(TPlayerItem));
	}
	else
	{
		// ľĆŔĚĹŰ ÄÉ˝Ă¸¦ Auctionżˇ µî·Ď ÇßŔ¸´Ď ClientManagerżˇĽ­´Â »«´Ů.
		TItemCacheSetPtrMap::iterator it = m_map_pkItemCacheSetPtr.find(item->owner);

		if (it != m_map_pkItemCacheSetPtr.end())
		{
			it->second->erase(c);
		}
		m_map_itemCache.erase(item->id);
		sys_log(0, "Enroll In Auction Success. owner_id item_id %d %d", owner_id, item->id);

		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_ENR_AUC;
		enroll_result.target = data->get_item_id();
		enroll_result.result = result;
		for (TPeerList::iterator it = m_peerList.begin(); it != m_peerList.end(); it++)
		{
			(*it)->EncodeHeader(HEADER_DG_AUCTION_RESULT, owner_id, sizeof(TPacketDGResultAuction) + sizeof(TPlayerItem) + sizeof(TAuctionItemInfo));
			(*it)->Encode(&enroll_result, sizeof(TPacketDGResultAuction));
			(*it)->Encode(c->Get(false), sizeof(TPlayerItem));
			(*it)->Encode(&auctioned_item_info, sizeof(TAuctionItemInfo));
		}
	}

	return;
}

void CClientManager::EnrollInSale (CPeer * peer, DWORD owner_id, AuctionEnrollSaleInfo* data)
{
	TPlayerTableCacheMap::iterator it = m_map_playerCache.find (owner_id);

	if (it == m_map_playerCache.end())
	{
		sys_err ("Invalid Player id %d. how can you get it?", owner_id);
		return;
	}

	CPlayerTableCache* player_cache = it->second;
	TPlayerTable* player = player_cache->Get(false);

	CItemCache* c = GetItemCache (data->get_item_id());

	if (c == NULL)
	{
		sys_err ("Item %d doesn't exist in db cache.", data->get_item_id());
		return;
	}
	TPlayerItem* item = c->Get(false);

	if (item->owner != owner_id)
	{
		sys_err ("Player id %d doesn't have item %d.", owner_id, data->get_item_id());
		return;
	}
	// ÇöŔç ˝Ă°˘ + 24˝Ă°Ł ČÄ.
	time_t expired_time = time(0) + 24 * 60 * 60;
	TSaleItemInfo sold_item_info (item->vnum, data->get_sale_price(),
		owner_id, player->name, data->get_item_id(), data->get_wisher_id());

	AuctionResult result = AuctionManager::instance().EnrollInSale( c, sold_item_info );

	if (result <= AUCTION_FAIL)
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_ENR_SALE;
		enroll_result.target = data->get_item_id();
		enroll_result.result = result;
		peer->EncodeHeader(HEADER_DG_AUCTION_RESULT, owner_id, sizeof(TPacketDGResultAuction) + sizeof(TPlayerItem));
		peer->Encode(&enroll_result, sizeof(TPacketDGResultAuction));
		peer->Encode(c->Get(false), sizeof(TPlayerItem));
	}
	else
	{
		// ľĆŔĚĹŰ ÄÉ˝Ă¸¦ Auctionżˇ µî·Ď ÇßŔ¸´Ď ClientManagerżˇĽ­´Â »«´Ů.
		TItemCacheSetPtrMap::iterator it = m_map_pkItemCacheSetPtr.find(item->owner);

		if (it != m_map_pkItemCacheSetPtr.end())
		{
			it->second->erase(c);
		}
		m_map_itemCache.erase(item->id);
		sys_log(0, "Enroll In Sale Success. owner_id item_id %d %d", owner_id, item->id);

		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_ENR_SALE;
		enroll_result.target = data->get_item_id();
		enroll_result.result = result;

		for (TPeerList::iterator it = m_peerList.begin(); it != m_peerList.end(); it++)
		{
			(*it)->EncodeHeader(HEADER_DG_AUCTION_RESULT, owner_id, sizeof(TPacketDGResultAuction) + sizeof(TPlayerItem) + sizeof(TSaleItemInfo));
			(*it)->Encode(&enroll_result, sizeof(TPacketDGResultAuction));
			(*it)->Encode(c->Get(false), sizeof(TPlayerItem));
			(*it)->Encode(&sold_item_info, sizeof(TSaleItemInfo));
		}
	}

	return;
}

void CClientManager::EnrollInWish (CPeer * peer, DWORD wisher_id, AuctionEnrollWishInfo* data)
{
	TPlayerTableCacheMap::iterator it = m_map_playerCache.find (wisher_id);

	if (it == m_map_playerCache.end())
	{
		sys_err ("Invalid Player id %d. how can you get it?", wisher_id);
		return;
	}

	CPlayerTableCache* player_cache = it->second;
	TPlayerTable* player = player_cache->Get(false);

	// ÇöŔç ˝Ă°˘ + 24˝Ă°Ł ČÄ.
	time_t expired_time = time(0) + 24 * 60 * 60;
	TWishItemInfo wished_item_info (data->get_item_num(), data->get_wish_price(), wisher_id, player->name, expired_time, data->get_empire());

	AuctionResult result = AuctionManager::instance().EnrollInWish ( wished_item_info );

	if (result <= AUCTION_FAIL)
	{
		sys_log(0, "Enroll In Wish Success. wisher_id item_num %d %d", wisher_id, data->get_item_num());

		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_ENR_WISH;
		enroll_result.target = data->get_item_num();
		enroll_result.result = result;
		peer->EncodeHeader(HEADER_DG_AUCTION_RESULT, wisher_id, sizeof(TPacketDGResultAuction));
		peer->Encode(&enroll_result, sizeof(TPacketDGResultAuction));
	}
	else
	{
		sys_log(0, "Enroll In Wish Fail. wisher_id item_num %d %d", wisher_id, data->get_item_num());

		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_ENR_WISH;
		enroll_result.target = data->get_item_num();
		enroll_result.result = result;

		for (TPeerList::iterator it = m_peerList.begin(); it != m_peerList.end(); it++)
		{
			(*it)->EncodeHeader(HEADER_DG_AUCTION_RESULT, wisher_id, sizeof(TPacketDGResultAuction) + sizeof(TWishItemInfo));
			(*it)->Encode(&enroll_result, sizeof(TPacketDGResultAuction));
			(*it)->Encode(&wished_item_info, sizeof(TWishItemInfo));
		}
	}

	return;
}

void CClientManager::AuctionBid (CPeer * peer, DWORD bidder_id, AuctionBidInfo* data)
{
	TPlayerTableCacheMap::iterator it = m_map_playerCache.find (bidder_id);

	if (it == m_map_playerCache.end())
	{
		sys_err ("Invalid Player id %d. how can you get it?", bidder_id);
		return;
	}

	CPlayerTableCache* player_cache = it->second;
	TPlayerTable* player = player_cache->Get(false);

	AuctionResult result = AuctionManager::instance().Bid(bidder_id, player->name, data->get_item_id(), data->get_bid_price());

	if (result == AUCTION_FAIL)
	{
		sys_log(0, "Bid Fail. bidder_id item_id %d %d", bidder_id, data->get_item_id());
	}
	else
	{
		sys_log(0, "Bid Success. bidder_id item_id %d %d", bidder_id, data->get_item_id());
	}

	if (result <= AUCTION_FAIL)
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_BID;
		enroll_result.target = data->get_bid_price();
		enroll_result.result = result;

		peer->EncodeHeader(HEADER_DG_AUCTION_RESULT, bidder_id, sizeof(TPacketDGResultAuction) + sizeof(AuctionBidInfo));
		peer->Encode(&enroll_result, sizeof(TPacketDGResultAuction));
	}
	else
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_BID;
		enroll_result.target = data->get_item_id();
		enroll_result.result = result;

		TAuctionItemInfo* auctioned_item_info = AuctionManager::instance().GetAuctionItemInfoCache(data->get_item_id())->Get(false);

		for (TPeerList::iterator it = m_peerList.begin(); it != m_peerList.end(); it++)
		{
			(*it)->EncodeHeader(HEADER_DG_AUCTION_RESULT, bidder_id, sizeof(TPacketDGResultAuction) + sizeof(TAuctionItemInfo));
			(*it)->Encode(&enroll_result, sizeof(TPacketDGResultAuction));
			(*it)->Encode(auctioned_item_info, sizeof(TAuctionItemInfo));
		}

	}
	return;
}

void CClientManager::AuctionImpur (CPeer * peer, DWORD purchaser_id, AuctionImpurInfo* data)
{
	TPlayerTableCacheMap::iterator it = m_map_playerCache.find (purchaser_id);

	if (it == m_map_playerCache.end())
	{
		sys_err ("Invalid Player id %d. how can you get it?", purchaser_id);
		return;
	}

	CPlayerTableCache* player_cache = it->second;
	TPlayerTable* player = player_cache->Get(false);

	AuctionResult result = AuctionManager::instance().Impur(purchaser_id, player->name, data->get_item_id());

	if (result == AUCTION_FAIL)
	{
		sys_log(0, "Impur Fail. purchaser_id item_id %d %d", purchaser_id, data->get_item_id());
	}
	else
	{
		sys_log(0, "Impur Success. purchaser_id item_id %d %d", purchaser_id, data->get_item_id());
	}

	if (result <= AUCTION_FAIL)
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_IMME_PUR;
		enroll_result.target = data->get_item_id();
		enroll_result.result = result;

		peer->EncodeHeader(HEADER_DG_AUCTION_RESULT, purchaser_id, sizeof(TPacketDGResultAuction));
		peer->Encode(&enroll_result, sizeof(TPacketDGResultAuction));
	}
	else
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_IMME_PUR;
		enroll_result.target = data->get_item_id();
		enroll_result.result = result;

		TAuctionItemInfo* auctioned_item_info = AuctionManager::instance().GetAuctionItemInfoCache(data->get_item_id())->Get(false);
		for (TPeerList::iterator it = m_peerList.begin(); it != m_peerList.end(); it++)
		{
			(*it)->EncodeHeader(HEADER_DG_AUCTION_RESULT, purchaser_id, sizeof(TPacketDGResultAuction) + sizeof(TAuctionItemInfo));
			(*it)->Encode(&enroll_result, sizeof(TPacketDGResultAuction));
			(*it)->Encode(auctioned_item_info, sizeof(TAuctionItemInfo));
		}
	}
	return;
}

void CClientManager::AuctionGetAuctionedItem (CPeer * peer, DWORD actor_id, DWORD item_id)
{
	TPlayerTableCacheMap::iterator it = m_map_playerCache.find (actor_id);
	AuctionResult result = AUCTION_FAIL;
	if (it == m_map_playerCache.end())
	{
		sys_err ("Invalid Player id %d. how can you get it?", actor_id);
		return;
	}

	TPlayerItem item;
	result = AuctionManager::instance().GetAuctionedItem(actor_id, item_id, item);

	if (result <= AUCTION_FAIL)
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_GET_AUC;
		enroll_result.target = item_id;
		enroll_result.result = result;

		peer->EncodeHeader (HEADER_DG_AUCTION_RESULT, actor_id, sizeof(TPacketDGResultAuction));
		peer->Encode (&enroll_result, sizeof(TPacketDGResultAuction));
	}
	else
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_GET_AUC;
		enroll_result.target = item_id;
		enroll_result.result = result;

		for (TPeerList::iterator it = m_peerList.begin(); it != m_peerList.end(); it++)
		{
			(*it)->EncodeHeader (HEADER_DG_AUCTION_RESULT, actor_id, sizeof(TPacketDGResultAuction) + sizeof(TPlayerItem));
			(*it)->Encode (&enroll_result, sizeof(TPacketDGResultAuction));
			(*it)->Encode (&item, sizeof(TPlayerItem));
		}
	}
	return;
}

void CClientManager::AuctionBuySoldItem (CPeer * peer, DWORD actor_id, DWORD item_id)
{
	TPlayerTableCacheMap::iterator it = m_map_playerCache.find (actor_id);
	AuctionResult result = AUCTION_FAIL;
	if (it == m_map_playerCache.end())
	{
		sys_err ("Invalid Player id %d. how can you get it?", actor_id);
		return;
	}

	TPlayerItem item;
	result = AuctionManager::instance().BuySoldItem(actor_id, item_id, item);

	if (result <= AUCTION_FAIL)
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_BUY_SOLD;
		enroll_result.target = item_id;
		enroll_result.result = result;

		peer->EncodeHeader (HEADER_DG_AUCTION_RESULT, actor_id, sizeof(TPacketDGResultAuction));
		peer->Encode (&enroll_result, sizeof(TPacketDGResultAuction));
	}
	else
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_BUY_SOLD;
		enroll_result.target = item_id;
		enroll_result.result = result;

		for (TPeerList::iterator it = m_peerList.begin(); it != m_peerList.end(); it++)
		{
			(*it)->EncodeHeader (HEADER_DG_AUCTION_RESULT, actor_id, sizeof(TPacketDGResultAuction) + sizeof(TPlayerItem));
			(*it)->Encode (&enroll_result, sizeof(TPacketDGResultAuction));
			(*it)->Encode (&item, sizeof(TPlayerItem));
		}
	}
	return;
}

void CClientManager::AuctionCancelAuction (CPeer * peer, DWORD actor_id, DWORD item_id)
{
	TPlayerTableCacheMap::iterator it = m_map_playerCache.find (actor_id);
	AuctionResult result = AUCTION_FAIL;
	if (it == m_map_playerCache.end())
	{
		sys_err ("Invalid Player id %d. how can you get it?", actor_id);
		return;
	}

	TPlayerItem item;
	result = AuctionManager::instance().CancelAuction(actor_id, item_id, item);

	if (result <= AUCTION_FAIL)
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_CANCEL_AUC;
		enroll_result.target = item_id;
		enroll_result.result = result;

		peer->EncodeHeader (HEADER_DG_AUCTION_RESULT, actor_id, sizeof(TPacketDGResultAuction));
		peer->Encode (&enroll_result, sizeof(TPacketDGResultAuction));
	}
	else
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_CANCEL_AUC;
		enroll_result.target = item_id;
		enroll_result.result = result;

		for (TPeerList::iterator it = m_peerList.begin(); it != m_peerList.end(); it++)
		{
			(*it)->EncodeHeader (HEADER_DG_AUCTION_RESULT, actor_id, sizeof(TPacketDGResultAuction) + sizeof(TPlayerItem));
			(*it)->Encode (&enroll_result, sizeof(TPacketDGResultAuction));
			(*it)->Encode (&item, sizeof(TPlayerItem));
		}
	}
	return;
}

void CClientManager::AuctionCancelWish (CPeer * peer, DWORD actor_id, DWORD item_num)
{
	TPlayerTableCacheMap::iterator it = m_map_playerCache.find (actor_id);
	AuctionResult result = AUCTION_FAIL;
	if (it == m_map_playerCache.end())
	{
		sys_err ("Invalid Player id %d. how can you get it?", actor_id);
		return;
	}

	TPlayerItem item;
	result = AuctionManager::instance().CancelWish(actor_id, item_num);

	if (result <= AUCTION_FAIL)
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_CANCEL_WISH;
		enroll_result.target = item_num;
		enroll_result.result = result;

		peer->EncodeHeader (HEADER_DG_AUCTION_RESULT, actor_id, sizeof(TPacketDGResultAuction));
		peer->Encode (&enroll_result, sizeof(TPacketDGResultAuction));
	}
	else
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_CANCEL_WISH;
		enroll_result.target = item_num;
		enroll_result.result = result;

		for (TPeerList::iterator it = m_peerList.begin(); it != m_peerList.end(); it++)
		{
			(*it)->EncodeHeader (HEADER_DG_AUCTION_RESULT, actor_id, sizeof(TPacketDGResultAuction));
			(*it)->Encode (&enroll_result, sizeof(TPacketDGResultAuction));
		}
	}
	return;
}

void CClientManager::AuctionCancelSale (CPeer * peer, DWORD actor_id, DWORD item_id)
{
	TPlayerTableCacheMap::iterator it = m_map_playerCache.find (actor_id);
	AuctionResult result = AUCTION_FAIL;
	if (it == m_map_playerCache.end())
	{
		sys_err ("Invalid Player id %d. how can you get it?", actor_id);
		return;
	}

	TPlayerItem item;
	result = AuctionManager::instance().CancelSale(actor_id, item_id, item);

	if (result <= AUCTION_FAIL)
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_CANCEL_SALE;
		enroll_result.target = item_id;
		enroll_result.result = result;

		peer->EncodeHeader (HEADER_DG_AUCTION_RESULT, actor_id, sizeof(TPacketDGResultAuction));
		peer->Encode (&enroll_result, sizeof(TPacketDGResultAuction));
	}
	else
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_CANCEL_SALE;
		enroll_result.target = item_id;
		enroll_result.result = result;

		for (TPeerList::iterator it = m_peerList.begin(); it != m_peerList.end(); it++)
		{
			(*it)->EncodeHeader (HEADER_DG_AUCTION_RESULT, actor_id, sizeof(TPacketDGResultAuction) + sizeof(TPlayerItem));
			(*it)->Encode (&enroll_result, sizeof(TPacketDGResultAuction));
			(*it)->Encode (&item, sizeof(TPlayerItem));
		}
	}
	return;
}

void CClientManager::AuctionDeleteAuctionItem (CPeer * peer, DWORD actor_id, DWORD item_id)
{
	TPlayerTableCacheMap::iterator it = m_map_playerCache.find (actor_id);
	AuctionResult result = AUCTION_FAIL;
	if (it == m_map_playerCache.end())
	{
		sys_err ("Invalid Player id %d. how can you get it?", actor_id);
		return;
	}

	AuctionManager::instance().DeleteAuctionItem (actor_id, item_id);
}
void CClientManager::AuctionDeleteSaleItem (CPeer * peer, DWORD actor_id, DWORD item_id)
{
	TPlayerTableCacheMap::iterator it = m_map_playerCache.find (actor_id);
	AuctionResult result = AUCTION_FAIL;
	if (it == m_map_playerCache.end())
	{
		sys_err ("Invalid Player id %d. how can you get it?", actor_id);
		return;
	}

	AuctionManager::instance().DeleteSaleItem (actor_id, item_id);
}

// ReBid´Â ŔĚŔü ŔÔÂű±Ýľ×żˇ ´őÇŘĽ­ ŔÔÂűÇŃ´Ů.
// ReBidżˇĽ± data->bid_price°ˇ ŔĚŔü ŔÔÂű°ˇżˇ ´őÇŘÁ®Ľ­
// ±× ±Ýľ×Ŕ¸·Î rebidÇĎ´Â °Í.
// ŔĚ·¸°Ô ÇŃ ŔĚŔŻ´Â rebidżˇ ˝ÇĆĐ ÇßŔ» ¶§,
// ŔŻŔúŔÇ ČŁÁÖ¸Ó´ĎżˇĽ­ »« µ·Ŕ» µą·ÁÁÖ±â ĆíÇĎ°Ô ÇĎ±â Ŕ§ÇÔŔĚ´Ů.

void CClientManager::AuctionReBid (CPeer * peer, DWORD bidder_id, AuctionBidInfo* data)
{
	TPlayerTableCacheMap::iterator it = m_map_playerCache.find (bidder_id);

	if (it == m_map_playerCache.end())
	{
		sys_err ("Invalid Player id %d. how can you get it?", bidder_id);
		return;
	}

	CPlayerTableCache* player_cache = it->second;
	TPlayerTable* player = player_cache->Get(false);

	AuctionResult result = AuctionManager::instance().ReBid(bidder_id, player->name, data->get_item_id(), data->get_bid_price());

	if (result == AUCTION_FAIL)
	{
		sys_log(0, "ReBid Fail. bidder_id item_id %d %d", bidder_id, data->get_item_id());
	}
	else
	{
		sys_log(0, "ReBid Success. bidder_id item_id %d %d", bidder_id, data->get_item_id());
	}
	// ŔĚ°Ç FAILŔĚ ¶°Ľ­´Â ľČµĹ.
	// FAILŔĚ ¶ă Ľö°ˇ ľř´Â°Ô, MyBidżˇ ŔÖ´Â bidder_idżˇ ´ëÇŃ ÄÁĹŮĂ÷´Â bidder_id¸¸ŔĚ Á˘±Ů ÇŇ Ľö ŔÖ°Ĺµç?
	// ±×·ŻąÇ·Î ´Ů¸Ą °ÍŔĚ ´Ů Á¤»óŔűŔ¸·Î ŔŰµżÇŃ´Ů°í °ˇÁ¤ ÇŃ´Ů¸é
	// ÇŃ °ÔŔÓ Ľ­ąö ł»żˇĽ­ bidder_id·Î MyBid¸¦ ĽöÁ¤ÇŃ´Ů ÇŇ Áö¶óµµ, ±×°Ç µż±âČ­ ą®Á¦°ˇ ľřľî.
	// ´Ů¸Ą °ÔŔÓ Ľ­ąöżˇ ¶Č°°Ŕş bidder_id¸¦ °ˇÁř łđŔĚ ŔÖŔ» Ľö°ˇ ľřŔ¸´Ď±î.
	// ±×·ŻąÇ·Î ±× °ÔŔÓ Ľ­ąöżˇĽ­ BidCancel ¸í·ÉŔ» dbżˇ łŻ·Č´Ů´Â °ÍŔş,
	// ŔĚąĚ ±× şÎşĐżˇ ´ëÇŘĽ­´Â °Ë»ç°ˇ żĎş®ÇĎ´Ů´Â °ÍŔĚľß.
	// ±×·ˇµµ Č¤˝ĂłŞ ˝ÍľîĽ­, µđąö±ëŔ» Ŕ§ÇŘ fail ÄÚµĺ¸¦ ł˛°ÜµĐ´Ů.
	if (result <= AUCTION_FAIL)
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_REBID;
		enroll_result.target = data->get_item_id();
		enroll_result.result = result;

		peer->EncodeHeader(HEADER_DG_AUCTION_RESULT, bidder_id, sizeof(TPacketDGResultAuction) + sizeof(int));
		peer->Encode(&enroll_result, sizeof(TPacketDGResultAuction));
		peer->EncodeDWORD(data->get_bid_price());
	}
	else
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_REBID;
		enroll_result.target = data->get_item_id();
		enroll_result.result = result;

		TAuctionItemInfo* auctioned_item_info = AuctionManager::instance().GetAuctionItemInfoCache(data->get_item_id())->Get(false);

		for (TPeerList::iterator it = m_peerList.begin(); it != m_peerList.end(); it++)
		{
			(*it)->EncodeHeader(HEADER_DG_AUCTION_RESULT, bidder_id, sizeof(TPacketDGResultAuction) + sizeof(TAuctionItemInfo));
			(*it)->Encode(&enroll_result, sizeof(TPacketDGResultAuction));
			(*it)->Encode(auctioned_item_info, sizeof(TAuctionItemInfo));
		}
	}
	return;
}

void CClientManager::AuctionBidCancel (CPeer * peer, DWORD bidder_id, DWORD item_id)
{
	AuctionResult result = AuctionManager::instance().BidCancel (bidder_id, item_id);

	// ŔĚ°Ç FAILŔĚ ¶°Ľ­´Â ľČµĹ.
	// FAILŔĚ ¶ă Ľö°ˇ ľř´Â°Ô, MyBidżˇ ŔÖ´Â bidder_idżˇ ´ëÇŃ ÄÁĹŮĂ÷´Â bidder_id¸¸ŔĚ Á˘±Ů ÇŇ Ľö ŔÖ°Ĺµç?
	// ±×·ŻąÇ·Î ´Ů¸Ą °ÍŔĚ ´Ů Á¤»óŔűŔ¸·Î ŔŰµżÇŃ´Ů°í °ˇÁ¤ ÇŃ´Ů¸é
	// ÇŃ °ÔŔÓ Ľ­ąö ł»żˇĽ­ bidder_id·Î MyBid¸¦ ĽöÁ¤ÇŃ´Ů ÇŇ Áö¶óµµ, ±×°Ç µż±âČ­ ą®Á¦°ˇ ľřľî.
	// ´Ů¸Ą °ÔŔÓ Ľ­ąöżˇ ¶Č°°Ŕş bidder_id¸¦ °ˇÁř łđŔĚ ŔÖŔ» Ľö°ˇ ľřŔ¸´Ď±î.
	// ±×·ŻąÇ·Î ±× °ÔŔÓ Ľ­ąöżˇĽ­ BidCancel ¸í·ÉŔ» dbżˇ łŻ·Č´Ů´Â °ÍŔş,
	// ŔĚąĚ ±× şÎşĐżˇ ´ëÇŘĽ­´Â °Ë»ç°ˇ żĎş®ÇĎ´Ů´Â °ÍŔĚľß.
	// ±×·ˇµµ Č¤˝ĂłŞ ˝ÍľîĽ­, µđąö±ëŔ» Ŕ§ÇŘ fail ÄÚµĺ¸¦ ł˛°ÜµĐ´Ů.
	if (result <= AUCTION_FAIL)
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_BID_CANCEL;
		enroll_result.target = item_id;
		enroll_result.result = result;

		peer->EncodeHeader(HEADER_DG_AUCTION_RESULT, bidder_id, sizeof(TPacketDGResultAuction));
		peer->Encode(&enroll_result, sizeof(TPacketDGResultAuction));
	}
	else
	{
		TPacketDGResultAuction enroll_result;
		enroll_result.cmd = AUCTION_BID_CANCEL;
		enroll_result.target = item_id;
		enroll_result.result = result;

		peer->EncodeHeader(HEADER_DG_AUCTION_RESULT, bidder_id, sizeof(TPacketDGResultAuction));
		peer->Encode(&enroll_result, sizeof(TPacketDGResultAuction));
	}
}
#endif
