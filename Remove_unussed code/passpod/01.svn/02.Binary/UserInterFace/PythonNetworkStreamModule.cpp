search and delete this:

PyObject* netSendNEWCIBNPasspodAnswerPacket(PyObject* poSelf, PyObject* poArgs)
{
	char* szMatrixCardString;
	if (!PyTuple_GetString(poArgs, 0, &szMatrixCardString))
		return Py_BuildException();

	CAccountConnector& rkAccountConnector = CAccountConnector::Instance();
	rkAccountConnector.SendNEWCIBNPasspodAnswerPacket(szMatrixCardString);
	return Py_BuildNone();
}

+ this:

		{ "SendNEWCIBNPasspodAnswerPacket",		netSendNEWCIBNPasspodAnswerPacket,		METH_VARARGS },
