search this:

		if (item->GetVnum() == 90008 || item->GetVnum() == 90009) // VCARD
		{
			VCardUse(m_pkPC, ch, item);
			item = NULL;
		}
		else
		{
			char buf[512];

			if (item->GetVnum() >= 80003 && item->GetVnum() <= 80007)
			{
				snprintf(buf, sizeof(buf), "%s FROM: %u TO: %u PRICE: %llu", item->GetName(), ch->GetPlayerID(), m_pkPC->GetPlayerID(), llPrice);
				LogManager::instance().GoldBarLog(ch->GetPlayerID(), item->GetID(), SHOP_BUY, buf);
				LogManager::instance().GoldBarLog(m_pkPC->GetPlayerID(), item->GetID(), SHOP_SELL, buf);
			}

			item->RemoveFromCharacter();
			if (item->IsDragonSoul())
				item->AddToCharacter(ch, TItemPos(DRAGON_SOUL_INVENTORY, iEmptyPos));
			else
				item->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
			ITEM_MANAGER::instance().FlushDelayedSave(item);

			snprintf(buf, sizeof(buf), "%s %u(%s) %llu %u", item->GetName(), m_pkPC->GetPlayerID(), m_pkPC->GetName(), llPrice, item->GetCount());
			LogManager::instance().ItemLog(ch, item, "SHOP_BUY", buf);

			snprintf(buf, sizeof(buf), "%s %u(%s) %llu %u", item->GetName(), ch->GetPlayerID(), ch->GetName(), llPrice, item->GetCount());
			LogManager::instance().ItemLog(m_pkPC, item, "SHOP_SELL", buf);
		}
		
change to:

		char buf[512];

		if (item->GetVnum() >= 80003 && item->GetVnum() <= 80007)
		{
			snprintf(buf, sizeof(buf), "%s FROM: %u TO: %u PRICE: %llu", item->GetName(), ch->GetPlayerID(), m_pkPC->GetPlayerID(), llPrice);
			LogManager::instance().GoldBarLog(ch->GetPlayerID(), item->GetID(), SHOP_BUY, buf);
			LogManager::instance().GoldBarLog(m_pkPC->GetPlayerID(), item->GetID(), SHOP_SELL, buf);
		}

		item->RemoveFromCharacter();
		if (item->IsDragonSoul())
			item->AddToCharacter(ch, TItemPos(DRAGON_SOUL_INVENTORY, iEmptyPos));
		else
			item->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
		ITEM_MANAGER::instance().FlushDelayedSave(item);

		snprintf(buf, sizeof(buf), "%s %u(%s) %llu %u", item->GetName(), m_pkPC->GetPlayerID(), m_pkPC->GetName(), llPrice, item->GetCount());
		LogManager::instance().ItemLog(ch, item, "SHOP_BUY", buf);

		snprintf(buf, sizeof(buf), "%s %u(%s) %llu %u", item->GetName(), ch->GetPlayerID(), ch->GetName(), llPrice, item->GetCount());
		LogManager::instance().ItemLog(m_pkPC, item, "SHOP_SELL", buf);