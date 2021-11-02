Search and delete:

#ifdef __AUCTION__
// temp_auction ŔÓ˝Ă
ACMD(do_get_auction_list);
ACMD (do_get_my_auction_list);
ACMD (do_get_my_purchase_list);
ACMD(do_get_item_id_list);
ACMD(do_enroll_auction);
ACMD (do_auction_bid);
ACMD (do_auction_impur);
ACMD (do_enroll_wish);
ACMD (do_enroll_sale);

ACMD (do_get_auctioned_item);
ACMD (do_buy_sold_item);
ACMD (do_cancel_auction);
ACMD (do_cancel_wish);
ACMD (do_cancel_sale);

ACMD (do_rebid);
ACMD (do_bid_cancel);
#endif

Search too and delete:

#ifdef __AUCTION__
	// auction ŔÓ˝Ă
	{ "auction_list",	do_get_auction_list,	0,	POS_DEAD,	GM_PLAYER	},
	{ "my_auction_list", do_get_my_auction_list, 0, POS_DEAD,	GM_PLAYER	},
	{ "my_purchase_list", do_get_my_purchase_list, 0, POS_DEAD,	GM_PLAYER	},


	{ "enroll_auction",		do_enroll_auction, 		0,	POS_DEAD,	GM_PLAYER	},
	{ "bid", do_auction_bid, 	0,	POS_DEAD,	GM_PLAYER	},
	{ "impur", do_auction_impur, 	0,	POS_DEAD,	GM_PLAYER	},
	{ "enroll_wish", do_enroll_wish, 	0,	POS_DEAD,	GM_PLAYER	},
	{ "enroll_sale", do_enroll_sale, 	0,	POS_DEAD,	GM_PLAYER	},
	{ "get_auctioned_item", do_get_auctioned_item, 	0,	POS_DEAD,	GM_PLAYER	},
	{ "buy_sold_item", do_buy_sold_item, 	0,	POS_DEAD,	GM_PLAYER	},
	{ "cancel_auction", do_cancel_auction, 	0,	POS_DEAD,	GM_PLAYER	},
	{ "cancel_wish", do_cancel_wish, 	0,	POS_DEAD,	GM_PLAYER	},
	{ "cancel_sale", do_cancel_sale, 	0,	POS_DEAD,	GM_PLAYER	},
	{ "rebid", do_rebid, 	0,	POS_DEAD,	GM_PLAYER	},
	{ "bid_cancel", do_bid_cancel, 	0,	POS_DEAD,	GM_PLAYER	},

#endif