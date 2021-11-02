search and delete this:

	HEADER_CG_PASSPOD_ANSWER = 202,

and this:

	HEADER_GC_REQUEST_PASSPOD = 202,
	HEADER_GC_REQUEST_PASSPOD_FAILED = 203,

and this:

	PHASE_PASSPOD,

and this:

typedef struct packet_passpod
{
	BYTE bHeader;
	char szAnswer[8 + 1];
} TPacketCGPasspod;

typedef struct packet_passpod_failed
{
	BYTE bHeader;
	char szMessage[128];
} TPacketCGPasspodFailed;