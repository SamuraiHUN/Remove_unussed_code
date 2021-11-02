Search and delete:

#include "../../common/auction_table.h"

Search and delete:

#ifdef __AUCTION__
	void EnrollInAuction (CPeer * peer, DWORD owner_id, AuctionEnrollProductInfo* data);
	void EnrollInSale (CPeer * peer, DWORD owner_id, AuctionEnrollSaleInfo* data);
	void EnrollInWish (CPeer * peer, DWORD wisher_id, AuctionEnrollWishInfo* data);
	void AuctionBid (CPeer * peer, DWORD bidder_id, AuctionBidInfo* data);
	void AuctionImpur (CPeer * peer, DWORD purchaser_id, AuctionImpurInfo* data);
	void AuctionGetAuctionedItem (CPeer * peer, DWORD actor_id, DWORD item_id);
	void AuctionBuySoldItem (CPeer * peer, DWORD actor_id, DWORD item_id);
	void AuctionCancelAuction (CPeer * peer, DWORD actor_id, DWORD item_id);
	void AuctionCancelWish (CPeer * peer, DWORD actor_id, DWORD item_num);
	void AuctionCancelSale (CPeer * peer, DWORD actor_id, DWORD item_id);
	void AuctionDeleteAuctionItem (CPeer * peer, DWORD actor_id, DWORD item_id);
	void AuctionDeleteSaleItem (CPeer * peer, DWORD actor_id, DWORD item_id);
	void AuctionReBid (CPeer * peer, DWORD bidder_id, AuctionBidInfo* data);
	void AuctionBidCancel (CPeer * peer, DWORD bidder_id, DWORD item_id);
#endif