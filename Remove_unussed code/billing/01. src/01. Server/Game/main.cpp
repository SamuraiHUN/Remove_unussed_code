search this:

		else
		{
			DESC_MANAGER::instance().ProcessExpiredLoginKey();
			DBManager::instance().FlushBilling();
			/*
			if (!(pulse % (ht->passes_per_sec * 600)))
				DBManager::instance().CheckBilling();
			*/
		}

modify to:

		else
		{
			DESC_MANAGER::instance().ProcessExpiredLoginKey();
		}

search this and remove:

		DBManager::instance().FlushBilling(true);
