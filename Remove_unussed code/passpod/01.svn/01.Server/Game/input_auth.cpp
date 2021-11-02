delete this:

#include "passpod.h"

and this:

	case HEADER_CG_PASSPOD_ANSWER:
		PasspodAnswer(d, c_pData);
		break;

and this:

void CInputAuth::PasspodAnswer(LPDESC d, const char* c_pData)
{
	if (!g_bAuthServer)
	{
		sys_err("CInputAuth class is not for game server. IP %s might be a hacker.",
			inet_ntoa(d->GetAddr().sin_addr));
		d->DelayedDisconnect(5);
		return;
	}

	TPacketCGPasspod* packet = (TPacketCGPasspod*)c_pData;

	RequestConfirmPasspod Confirm;

	memcpy(Confirm.passpod, packet->szAnswer, MAX_PASSPOD + 1);
	memcpy(Confirm.login, d->GetAccountTable().login, LOGIN_MAX_LEN + 1);

	if (!d->GetAccountTable().id)
	{
		sys_err("HEADER_CG_PASSPOD_ANSWER received to desc with no account table binded");
		return;
	}

	int ret_code = 1;
	sys_log(0, "Passpod start %s %s", d->GetAccountTable().login, packet->szAnswer);
	ret_code = CPasspod::instance().ConfirmPasspod(d->GetAccountTable().login, packet->szAnswer);

	if (ret_code != 0)
	{
		sys_log(0, "PASSPOD: wrong answer: %s ret_code %d", d->GetAccountTable().login, ret_code);

		LoginFailure(d, ERR_MESSAGE[ret_code]);

		if (!d->CheckMatrixTryCount())
		{
			LoginFailure(d, "QUIT");
			d->SetPhase(PHASE_CLOSE);
		}
	}
	else
	{
		sys_log(0, "PASSPOD: success: %s", d->GetAccountTable().login);
		DBManager::instance().SendAuthLogin(d);
	}
	//g_PasspodDesc->DBPacket(HEADER_GP_CONFIRM_PASSPOD,  0, &Confirm, sizeof(Confirm));

	//sys_log(0, "PASSPOD %s %d", Confirm.login, Confirm.passpod);
}
