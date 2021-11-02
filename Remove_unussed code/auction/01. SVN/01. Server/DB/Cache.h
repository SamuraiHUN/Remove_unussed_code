Search and delete:

#include "../../common/auction_table.h"

search and delete:

#ifdef __AUCTION__

class CAuctionItemInfoCache : public cache <TAuctionItemInfo>
{
public:
	typedef TWishItemInfo value_type;
	CAuctionItemInfoCache();
	virtual ~CAuctionItemInfoCache();

	void Delete();
	virtual void OnFlush();
};

class CSaleItemInfoCache : public cache <TSaleItemInfo>
{
public:
	typedef TWishItemInfo value_type;
	CSaleItemInfoCache();
	virtual ~CSaleItemInfoCache();

	void Delete();
	virtual void OnFlush();
};

class CWishItemInfoCache : public cache <TWishItemInfo>
{
public:
	typedef TWishItemInfo value_type;
	CWishItemInfoCache();
	virtual ~CWishItemInfoCache();

	void Delete();
	virtual void OnFlush();
};
#endif