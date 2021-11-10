Search and delete:

PyObject* netSendMobileMessagePacket(PyObject* poSelf, PyObject* poArgs)
{
	char* szName;
	char* szLine;
	if (!PyTuple_GetString(poArgs, 0, &szName))
		return Py_BuildException();

	if (!PyTuple_GetString(poArgs, 1, &szLine))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendMobileMessagePacket(szName, szLine);
	return Py_BuildNone();
}

Search and delete:

		{ "SendMobileMessagePacket",			netSendMobileMessagePacket,				METH_VARARGS },