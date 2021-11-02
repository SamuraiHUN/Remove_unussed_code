search and delete this:

extern bool g_bNoPasspod;

and  this:

		else if (!stBuf.compare("IS_PASSPOD_UP"))
		{
			if (g_bNoPasspod)
				stResult = "NO";
			else
				stResult = "YES";
		}

and this:

				else if (!stBuf.compare("CLOSE_PASSPOD"))
				{
					g_bNoPasspod = true;
					stResult += "CLOSE_PASSPOD";
				}
				else if (!stBuf.compare("OPEN_PASSPOD"))
				{
					g_bNoPasspod = false;
					stResult += "OPEN_PASSPOD";
				}