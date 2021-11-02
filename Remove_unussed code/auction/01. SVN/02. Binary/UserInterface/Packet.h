Search and delete:

#ifdef __AUCTION__
	HEADER_CG_AUCTION_CMD							= 205,
#endif

Search and delete:

#ifdef __AUCTION__
	HEADER_GC_AUCTOIN_ITEM_LIST					= 206,
#endif

Search and delete:

#ifdef __AUCTION__
// ArgumentŔÇ żëµµ´Â cmdżˇ µű¶ó ´Ů¸Ł´Ů.
typedef struct SPacketCGAuctionCmd
{
	BYTE bHeader;
	BYTE cmd;
	int arg1;
	int arg2;
	int arg3;
	int arg4;
} TPacketCGAuctionCmd;

typedef struct SPacketGCAuctionItemListPack
{
	BYTE bHeader;
	BYTE bNumbers;
} TPacketGCAuctionItemListPack;

#endif

