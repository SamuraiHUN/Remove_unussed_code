Search and delete:

PyObject* playerHasMobilePhoneNumber(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonPlayer::Instance().HasMobilePhoneNumber());
}

Search and delete:

		// Mobile
		{ "HasMobilePhoneNumber", playerHasMobilePhoneNumber, METH_VARARGS },