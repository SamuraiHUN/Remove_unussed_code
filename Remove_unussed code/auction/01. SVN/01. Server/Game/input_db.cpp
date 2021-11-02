search and delete:

#ifdef __AUCTION__
#include "auction_manager.h"
#endif

search and delete:

#ifdef __AUCTION__
	// Auction
	AuctionManager::instance().Boot(data);
#endif

search and delete:

#ifdef __AUCTION__
	case HEADER_DG_AUCTION_RESULT:
		if (auction_server)
			AuctionManager::instance().recv_result_auction(m_dwHandle, (TPacketDGResultAuction*)c_pData);
		break;
#endif