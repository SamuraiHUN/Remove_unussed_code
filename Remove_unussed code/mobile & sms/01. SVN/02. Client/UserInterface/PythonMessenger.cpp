Search and delete:

void CPythonMessenger::SetMobile(const char * c_szKey, BYTE byState)
{
	m_FriendNameMap.insert(c_szKey);

	if (m_poMessengerHandler)
		PyCallClassMemberFunc(m_poMessengerHandler, "OnMobile", Py_BuildValue("(isi)", MESSENGER_GRUOP_INDEX_FRIEND, c_szKey, byState));
}
