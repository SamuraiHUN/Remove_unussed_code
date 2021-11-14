Search this and delete:

#include "../../common/teen_packet.h"

Search this and delete:

	if (g_TeenDesc)
	{
		int offset = 0;
		char buf[245] = { 0 };

		buf[0] = HEADER_GT_LOGOUT;
		offset += 1;

		memset(buf + offset, 0x00, 2);
		offset += 2;

		TAccountTable& acc_table = GetDesc()->GetAccountTable();
		memcpy(buf + offset, &acc_table.id, 4);
		offset += 4;

		g_TeenDesc->Packet(buf, offset);
	}