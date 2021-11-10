Search and delete:

	case HEADER_GC_CHINA_MATRIX_CARD:
		if (__RecvChinaMatrixCardPacket())
			return;
		break;

	case HEADER_GC_RUNUP_MATRIX_QUIZ:
		if (__RecvRunupMatrixQuizPacket())
			return;
		break;

Search and delete:

bool CPythonNetworkStream::__RecvRunupMatrixQuizPacket()
{
	TPacketGCRunupMatrixQuiz kMatrixQuizPacket;
	if (!Recv(sizeof(TPacketGCRunupMatrixQuiz), &kMatrixQuizPacket))
		return false;

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_LOGIN], "BINARY_OnRunupMatrixQuiz", Py_BuildValue("(s)", kMatrixQuizPacket.szQuiz));
	return true;
}

bool CPythonNetworkStream::SendRunupMatrixAnswerPacket(const char* c_szMatrixCardString)
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

search and delete:

bool CPythonNetworkStream::SendChinaMatrixCardPacket(const char* c_szMatrixCardString)
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

	m_isWaitLoginKey = TRUE;

	return SendSequence();
}

#define ROW(rows, i) ((rows >> ((4 - i - 1) * 8)) & 0x000000FF)
#define COL(cols, i) ((cols >> ((4 - i - 1) * 8)) & 0x000000FF)

bool CPythonNetworkStream::__RecvChinaMatrixCardPacket()
{
	TPacketGCChinaMatrixCard kMatrixCardPacket;
	if (!Recv(sizeof(TPacketGCChinaMatrixCard), &kMatrixCardPacket))
		return false;

	PyObject* pyValue = Py_BuildValue("(iiiiiiii)", ROW(kMatrixCardPacket.dwRows, 0),
		ROW(kMatrixCardPacket.dwRows, 1),
		ROW(kMatrixCardPacket.dwRows, 2),
		ROW(kMatrixCardPacket.dwRows, 3),
		COL(kMatrixCardPacket.dwCols, 0),
		COL(kMatrixCardPacket.dwCols, 1),
		COL(kMatrixCardPacket.dwCols, 2),
		COL(kMatrixCardPacket.dwCols, 3));
	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_LOGIN], "OnMatrixCard", pyValue);
	return true;
}