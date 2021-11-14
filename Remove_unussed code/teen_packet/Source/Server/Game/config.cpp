Search this and delete:

char teen_addr[ADDRESS_MAX_LEN + 1] = { 0 };
WORD teen_port = 0;

and delete this too:

		TOKEN("teen_addr")
		{
			strlcpy(teen_addr, value_string, sizeof(teen_addr));

			for (int n = 0; n < ADDRESS_MAX_LEN; ++n)
			{
				if (teen_addr[n] == ' ')
					teen_addr[n] = '\0';
			}

			continue;
		}

		TOKEN("teen_port")
		{
			str_to_number(teen_port, value_string);
		}
