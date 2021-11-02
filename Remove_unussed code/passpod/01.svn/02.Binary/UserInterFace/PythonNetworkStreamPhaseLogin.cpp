search and delete this:

	case HEADER_GC_NEWCIBN_PASSPOD_REQUEST:
		if (__RecvNEWCIBNPasspodRequestPacket())
			return;
		break;
	case HEADER_GC_NEWCIBN_PASSPOD_FAILURE:
		if (__RecvNEWCIBNPasspodFailurePacket())
			return;
		break;

and this:

bool CPythonNetworkStream::__RecvNEWCIBNPasspodRequestPacket()
{
	TPacketGCNEWCIBNPasspodRequest kRequestPacket;
	if (!Recv(sizeof(kRequestPacket), &kRequestPacket))
		return false;

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_LOGIN], "BINARY_OnNEWCIBNPasspodRequest", Py_BuildValue("()"));
	return true;
}

bool CPythonNetworkStream::__RecvNEWCIBNPasspodFailurePacket()
{
	TPacketGCNEWCIBNPasspodFailure kFailurePacket;
	if (!Recv(sizeof(kFailurePacket), &kFailurePacket))
		return false;

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_LOGIN], "BINARY_OnNEWCIBNPasspodFailure", Py_BuildValue("()"));
	return true;
}


bool CPythonNetworkStream::SendNEWCIBNPasspodAnswerPacket(const char* answer)
{
	TPacketCGNEWCIBNPasspodAnswer answerPacket;
	answerPacket.bHeader = HEADER_CG_NEWCIBN_PASSPOD_ANSWER;
	strncpy(answerPacket.szAnswer, answer, NEWCIBN_PASSPOD_ANSWER_MAX_LEN);
	answerPacket.szAnswer[NEWCIBN_PASSPOD_ANSWER_MAX_LEN] = '\0';
	if (!Send(sizeof(answerPacket), &answerPacket))
	{
		TraceError("SendNEWCIBNPasspodAnswerPacket");
		return false;
	}
	return SendSequence();
}
