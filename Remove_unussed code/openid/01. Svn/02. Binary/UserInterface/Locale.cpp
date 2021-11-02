Search and delete this:

#ifdef USE_OPENID

std::string __OPENID_AUTH_KEY_STRING__;
int openid_test = 0;

void LocaleService_SetOpenIDAuthKey(const char* authKey)
{
	__OPENID_AUTH_KEY_STRING__ = authKey;

	return;
}

const char* LocaleService_GetOpenIDAuthKey()
{
	return __OPENID_AUTH_KEY_STRING__.c_str();
}

#endif /* USE_OPENID */