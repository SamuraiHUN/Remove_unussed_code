search this and delete:

bool CAccountConnector::SendRunupMatrixCardPacket(const char* c_szMatrixCardString)
{
	TPacketCGRunupMatrixAnswer answerPacket;
	answerPacket.bHeader = HEADER_CG_RUNUP_MATRIX_ANSWER;
	strncpy(answerPacket.szAnswer, c_szMatrixCardString, RUNUP_MATRIX_ANSWER_MAX_LEN);
	answerPacket.szAnswer[RUNUP_MATRIX_ANSWER_MAX_LEN] = '\0';
	if (!Send(sizeof(answerPacket), &answerPacket))
	{
		TraceError("SendRunupMatrixCardPacketError");
		return false;
	}
	return SendSequence();
}

bool CAccountConnector::SendChinaMatrixCardPacket(const char* c_szMatrixCardString)
{
	TPacketCGChinaMatrixCard MatrixCardPacket;
	MatrixCardPacket.bHeader = HEADER_CG_CHINA_MATRIX_CARD;
	strncpy(MatrixCardPacket.szAnswer, c_szMatrixCardString, CHINA_MATRIX_ANSWER_MAX_LEN);
	MatrixCardPacket.szAnswer[CHINA_MATRIX_ANSWER_MAX_LEN] = '\0';

	if (!Send(sizeof(MatrixCardPacket), &MatrixCardPacket))
	{
		Tracen("SendLogin Error");
		return false;
	}

	CPythonNetworkStream::Instance().SetWaitFlag();
	m_isWaitKey = TRUE;

	return SendSequence();
}

Search this and delete:

	if (!__AnalyzePacket(HEADER_GC_CHINA_MATRIX_CARD, sizeof(TPacketGCChinaMatrixCard), &CAccountConnector::__AuthState_RecvChinaMatrixCard))
		return true;

	if (!__AnalyzePacket(HEADER_GC_RUNUP_MATRIX_QUIZ, sizeof(TPacketGCRunupMatrixQuiz), &CAccountConnector::__AuthState_RecvRunupMatrixQuiz))
		return true;

search this and delete:

bool CAccountConnector::__AuthState_RecvRunupMatrixQuiz()
{
	TPacketGCRunupMatrixQuiz kMatrixQuizPacket;
	if (!Recv(sizeof(TPacketGCRunupMatrixQuiz), &kMatrixQuizPacket))
		return false;

	PyCallClassMemberFunc(m_poHandler, "BINARY_OnRunupMatrixQuiz", Py_BuildValue("(s)", kMatrixQuizPacket.szQuiz));
	return true;
}

#define ROW(rows, i) ((rows >> ((4 - i - 1) * 8)) & 0x000000FF)
#define COL(cols, i) ((cols >> ((4 - i - 1) * 8)) & 0x000000FF)

bool CAccountConnector::__AuthState_RecvChinaMatrixCard()
{
	TPacketGCChinaMatrixCard kMatrixCardPacket;
	if (!Recv(sizeof(TPacketGCChinaMatrixCard), &kMatrixCardPacket))
		return false;

	if (m_poHandler)
	{
		PyObject* pyValue = Py_BuildValue("(iiiiiiii)", ROW(kMatrixCardPacket.dwRows, 0),
			ROW(kMatrixCardPacket.dwRows, 1),
			ROW(kMatrixCardPacket.dwRows, 2),
			ROW(kMatrixCardPacket.dwRows, 3),
			COL(kMatrixCardPacket.dwCols, 0),
			COL(kMatrixCardPacket.dwCols, 1),
			COL(kMatrixCardPacket.dwCols, 2),
			COL(kMatrixCardPacket.dwCols, 3));
		PyCallClassMemberFunc(m_poHandler, "OnMatrixCard", pyValue);
	}

	return true;
}
