Search and delete:

#ifdef __AUCTION__
int			auction_server = 0;
#endif

Search too and delete:

#ifdef __AUCTION__
		TOKEN("auction_server")
		{
			printf("-----------------------------------------------\n");
			printf("AUCTION_SERVER\n");
			printf("-----------------------------------------------\n");
			str_to_number(auction_server, value_string);
			continue;
		}
#endif