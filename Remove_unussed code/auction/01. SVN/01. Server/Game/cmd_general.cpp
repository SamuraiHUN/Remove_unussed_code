Search and delete:

#ifdef __AUCTION__
#include "auction_manager.h"
#endif

Search and delete:

#ifdef __AUCTION__
// temp_auction
ACMD(do_get_item_id_list)
{
	for (int i = 0; i < INVENTORY_MAX_NUM; i++)
	{
		LPITEM item = ch->GetInventoryItem(i);
		if (item != NULL)
			ch->ChatPacket(CHAT_TYPE_INFO, "nume : %s id : %d", item->GetProto()->szName, item->GetID());
	}
}

// temp_auction

ACMD(do_enroll_auction)
{
	char arg1[256];
	char arg2[256];
	char arg3[256];
	char arg4[256];
	two_arguments (two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2)), arg3, sizeof(arg3), arg4, sizeof(arg4));

	DWORD item_id = strtoul(arg1, NULL, 10);
	BYTE empire = strtoul(arg2, NULL, 10);
	int bidPrice = strtol(arg3, NULL, 10);
	int immidiatePurchasePrice = strtol(arg4, NULL, 10);

	LPITEM item = ITEM_MANAGER::instance().Find(item_id);
	if (item == NULL)
		return;

	AuctionManager::instance().enroll_auction(ch, item, empire, bidPrice, immidiatePurchasePrice);
}

ACMD(do_enroll_wish)
{
	char arg1[256];
	char arg2[256];
	char arg3[256];
	one_argument (two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2)), arg3, sizeof(arg3));

	DWORD item_num = strtoul(arg1, NULL, 10);
	BYTE empire = strtoul(arg2, NULL, 10);
	int wishPrice = strtol(arg3, NULL, 10);

	AuctionManager::instance().enroll_wish(ch, item_num, empire, wishPrice);
}

ACMD(do_enroll_sale)
{
	char arg1[256];
	char arg2[256];
	char arg3[256];
	one_argument (two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2)), arg3, sizeof(arg3));

	DWORD item_id = strtoul(arg1, NULL, 10);
	DWORD wisher_id = strtoul(arg2, NULL, 10);
	int salePrice = strtol(arg3, NULL, 10);

	LPITEM item = ITEM_MANAGER::instance().Find(item_id);
	if (item == NULL)
		return;

	AuctionManager::instance().enroll_sale(ch, item, wisher_id, salePrice);
}

// temp_auction
// packetŔ¸·Î Ĺë˝ĹÇĎ°Ô ÇĎ°í, ŔĚ°Ç »čÁ¦ÇŘľßÇŃ´Ů.
ACMD(do_get_auction_list)
{
	char arg1[256];
	char arg2[256];
	char arg3[256];
	two_arguments (one_argument (argument, arg1, sizeof(arg1)), arg2, sizeof(arg2), arg3, sizeof(arg3));

	AuctionManager::instance().get_auction_list (ch, strtoul(arg1, NULL, 10), strtoul(arg2, NULL, 10), strtoul(arg3, NULL, 10));
}
//
//ACMD(do_get_wish_list)
//{
//	char arg1[256];
//	char arg2[256];
//	char arg3[256];
//	two_arguments (one_argument (argument, arg1, sizeof(arg1)), arg2, sizeof(arg2), arg3, sizeof(arg3));
//
//	AuctionManager::instance().get_wish_list (ch, strtoul(arg1, NULL, 10), strtoul(arg2, NULL, 10), strtoul(arg3, NULL, 10));
//}
ACMD (do_get_my_auction_list)
{
	char arg1[256];
	char arg2[256];
	two_arguments (argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	AuctionManager::instance().get_my_auction_list (ch, strtoul(arg1, NULL, 10), strtoul(arg2, NULL, 10));
}

ACMD (do_get_my_purchase_list)
{
	char arg1[256];
	char arg2[256];
	two_arguments (argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	AuctionManager::instance().get_my_purchase_list (ch, strtoul(arg1, NULL, 10), strtoul(arg2, NULL, 10));
}

ACMD (do_auction_bid)
{
	char arg1[256];
	char arg2[256];
	two_arguments (argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	AuctionManager::instance().bid (ch, strtoul(arg1, NULL, 10), strtoul(arg2, NULL, 10));
}

ACMD (do_auction_impur)
{
	char arg1[256];
	one_argument (argument, arg1, sizeof(arg1));

	AuctionManager::instance().immediate_purchase (ch, strtoul(arg1, NULL, 10));
}

ACMD (do_get_auctioned_item)
{
	char arg1[256];
	char arg2[256];
	two_arguments (argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	AuctionManager::instance().get_auctioned_item (ch, strtoul(arg1, NULL, 10), strtoul(arg2, NULL, 10));
}

ACMD (do_buy_sold_item)
{
	char arg1[256];
	char arg2[256];
	one_argument (argument, arg1, sizeof(arg1));

	AuctionManager::instance().get_auctioned_item (ch, strtoul(arg1, NULL, 10), strtoul(arg2, NULL, 10));
}

ACMD (do_cancel_auction)
{
	char arg1[256];
	one_argument (argument, arg1, sizeof(arg1));

	AuctionManager::instance().cancel_auction (ch, strtoul(arg1, NULL, 10));
}

ACMD (do_cancel_wish)
{
	char arg1[256];
	one_argument (argument, arg1, sizeof(arg1));

	AuctionManager::instance().cancel_wish (ch, strtoul(arg1, NULL, 10));
}

ACMD (do_cancel_sale)
{
	char arg1[256];
	one_argument (argument, arg1, sizeof(arg1));

	AuctionManager::instance().cancel_sale (ch, strtoul(arg1, NULL, 10));
}

ACMD (do_rebid)
{
	char arg1[256];
	char arg2[256];
	two_arguments (argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	AuctionManager::instance().rebid (ch, strtoul(arg1, NULL, 10), strtoul(arg2, NULL, 10));
}

ACMD (do_bid_cancel)
{
	char arg1[256];
	char arg2[256];
	two_arguments (argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	AuctionManager::instance().bid_cancel (ch, strtoul(arg1, NULL, 10));
}
#endif