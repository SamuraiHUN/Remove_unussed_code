search and delete this:

bool CAccountConnector::SendNEWCIBNPasspodAnswerPacket(const char* answer)
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

and this:

	if (!__AnalyzePacket(HEADER_GC_NEWCIBN_PASSPOD_REQUEST, sizeof(TPacketGCNEWCIBNPasspodRequest), &CAccountConnector::__AuthState_RecvNEWCIBNPasspodRequest))
		return true;

aaand this:

bool CAccountConnector::__AuthState_RecvNEWCIBNPasspodRequest()
{
	TPacketGCNEWCIBNPasspodRequest kRequestPacket;
	if (!Recv(sizeof(kRequestPacket), &kRequestPacket))
		return false;

	PyCallClassMemberFunc(m_poHandler, "BINARY_OnNEWCIBNPasspodRequest", Py_BuildValue("()"));
	return true;
}