Search and delete:

bool CPythonNetworkStream::SendMobileMessagePacket(const char* name, const char* c_szChat)
{
	int iTextLen = strlen(c_szChat) + 1;
	TPacketCGSMS SMSPacket;
	SMSPacket.bHeader = HEADER_CG_SMS;
	SMSPacket.wSize = sizeof(SMSPacket) + iTextLen;

	strncpy(SMSPacket.szNameTo, name, sizeof(SMSPacket.szNameTo) - 1);

	if (!Send(sizeof(SMSPacket), &SMSPacket))
		return false;

	if (!Send(iTextLen, c_szChat))
		return false;

	return SendSequence();
}

search and delete:

			if (on.connected & MESSENGER_CONNECTED_STATE_MOBILE)
				CPythonMessenger::Instance().SetMobile(char_name, TRUE);

search and delete:

	case MESSENGER_SUBHEADER_GC_MOBILE:
	{
		BYTE byState; // ¸đąŮŔĎ ąřČŁ°ˇ ľřľîÁł´ÂÁö ÇĂ·ˇ±×
		BYTE byLength;
		if (!Recv(sizeof(byState), &byState))
			return false;
		if (!Recv(sizeof(byLength), &byLength))
			return false;
		if (!Recv(byLength, char_name))
			return false;
		char_name[byLength] = 0;
		CPythonMessenger::Instance().SetMobile(char_name, byState);
		break;
	}