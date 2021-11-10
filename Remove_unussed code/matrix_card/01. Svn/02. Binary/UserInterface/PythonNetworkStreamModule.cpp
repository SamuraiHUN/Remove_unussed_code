Search and delete:

PyObject* netSendChinaMatrixCardPacket(PyObject* poSelf, PyObject* poArgs)
{
	char* szMatrixCardString;
	if (!PyTuple_GetString(poArgs, 0, &szMatrixCardString))
		return Py_BuildException();

	CAccountConnector& rkAccountConnector = CAccountConnector::Instance();
	rkAccountConnector.SendChinaMatrixCardPacket(szMatrixCardString);
	return Py_BuildNone();
}

PyObject* netSendRunupMatrixCardPacket(PyObject* poSelf, PyObject* poArgs)
{
	char* szMatrixCardString;
	if (!PyTuple_GetString(poArgs, 0, &szMatrixCardString))
		return Py_BuildException();

	CAccountConnector& rkAccountConnector = CAccountConnector::Instance();
	rkAccountConnector.SendRunupMatrixCardPacket(szMatrixCardString);
	return Py_BuildNone();
}

search and delete:

		{ "SendChinaMatrixCardPacket",			netSendChinaMatrixCardPacket,			METH_VARARGS },
		{ "SendRunupMatrixCardPacket",			netSendRunupMatrixCardPacket,			METH_VARARGS },