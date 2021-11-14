Search this:

	/* game server to teen server */
	else
	{
		if (teen_addr[0] && teen_port)
			g_TeenDesc = DESC_MANAGER::instance().CreateConnectionDesc(main_fdw, teen_addr, teen_port, PHASE_TEEN, true);

		extern unsigned int g_uiSpamBlockDuration;
		extern unsigned int g_uiSpamBlockScore;
		extern unsigned int g_uiSpamReloadCycle;

		sys_log(0, "SPAM_CONFIG: duration %u score %u reload cycle %u\n",
			g_uiSpamBlockDuration, g_uiSpamBlockScore, g_uiSpamReloadCycle);

		extern void LoadSpamDB();
		LoadSpamDB();
	}

modify to:

	else
	{
		extern unsigned int g_uiSpamBlockDuration;
		extern unsigned int g_uiSpamBlockScore;
		extern unsigned int g_uiSpamReloadCycle;

		sys_log(0, "SPAM_CONFIG: duration %u score %u reload cycle %u\n",
			g_uiSpamBlockDuration, g_uiSpamBlockScore, g_uiSpamReloadCycle);

		extern void LoadSpamDB();
		LoadSpamDB();
	}
	
Search this and delete:

			else if (g_TeenDesc == d)
			{
				int buf_size = buffer_size(d->GetOutputBuffer());
				int sock_buf_size = fdwatch_get_buffer_size(fdw, d->GetSocket());

				int ret = d->ProcessOutput();

				if (ret < 0)
				{
					d->SetPhase(PHASE_CLOSE);
				}

				if (buf_size)
					sys_log(0, "TEEN::Send(size %d sock_buf %d ret %d)", buf_size, sock_buf_size, ret);
			}