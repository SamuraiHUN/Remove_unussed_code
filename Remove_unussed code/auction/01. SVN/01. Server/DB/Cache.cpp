Search and delete:

#ifdef __AUCTION__
#include "AuctionManager.h"
#endif

search and delete:

const int auctionMinFlushSec = 1800;

Search and delete:

#ifdef __AUCTION__
CAuctionItemInfoCache::CAuctionItemInfoCache()
{
	m_expireTime = MIN (auctionMinFlushSec, g_iItemCacheFlushSeconds);
}

CAuctionItemInfoCache::~CAuctionItemInfoCache()
{

}

void CAuctionItemInfoCache::Delete()
{
	if (m_data.item_num == 0)
		return;

	if (g_test_server)
		sys_log(0, "CAuctionItemInfoCache::Delete : DELETE %u", m_data.item_id);

	m_data.item_num = 0;
	m_bNeedQuery = true;
	m_lastUpdateTime = time(0);
	OnFlush();
	delete this;
}

void CAuctionItemInfoCache::OnFlush()
{
	char szQuery[QUERY_MAX_LEN];

	if (m_data.item_num == 0)
	{
		snprintf(szQuery, sizeof(szQuery), "DELETE FROM auction where item_id = %d", m_data.item_id);
		CDBManager::instance().AsyncQuery(szQuery);
	}
	else
	{
		snprintf(szQuery, sizeof(szQuery), "REPLACE INTO auction VALUES (%u, %d, %d, %u, \"%s\", %u, %u, %u, %u)",
			m_data.item_num, m_data.offer_price, m_data.price, m_data.offer_id, m_data.shown_name, (DWORD)m_data.empire, (DWORD)m_data.expired_time,
			m_data.item_id, m_data.bidder_id);

		CDBManager::instance().AsyncQuery(szQuery);
	}
}

CSaleItemInfoCache::CSaleItemInfoCache()
{
	m_expireTime = MIN (auctionMinFlushSec, g_iItemCacheFlushSeconds);
}

CSaleItemInfoCache::~CSaleItemInfoCache()
{
}

void CSaleItemInfoCache::Delete()
{
}

void CSaleItemInfoCache::OnFlush()
{
	char szQuery[QUERY_MAX_LEN];

	snprintf(szQuery, sizeof(szQuery), "REPLACE INTO sale VALUES (%u, %d, %d, %u, \"%s\", %u, %u, %u, %u)",
		m_data.item_num, m_data.offer_price, m_data.price, m_data.offer_id, m_data.shown_name, (DWORD)m_data.empire, (DWORD)m_data.expired_time,
		m_data.item_id, m_data.wisher_id);

	CDBManager::instance().AsyncQuery(szQuery);
}

CWishItemInfoCache::CWishItemInfoCache()
{
	m_expireTime = MIN (auctionMinFlushSec, g_iItemCacheFlushSeconds);
}

CWishItemInfoCache::~CWishItemInfoCache()
{
}

void CWishItemInfoCache::Delete()
{
}

void CWishItemInfoCache::OnFlush()
{
	char szQuery[QUERY_MAX_LEN];

	snprintf(szQuery, sizeof(szQuery), "REPLACE INTO wish VALUES (%u, %d, %d, %u, \"%s\", %u, %d)",
		m_data.item_num, m_data.offer_price, m_data.price, m_data.offer_id, m_data.shown_name, (DWORD)m_data.empire, (DWORD)m_data.expired_time);

	CDBManager::instance().AsyncQuery(szQuery);
}
#endif