Search and delete this:

	HEADER_CG_CHINA_MATRIX_CARD = 108,

Search and delete this:

	HEADER_CG_RUNUP_MATRIX_ANSWER = 201,

Search and delete this:

	HEADER_GC_CHINA_MATRIX_CARD = 116,

Search and delete this:

	HEADER_GC_RUNUP_MATRIX_QUIZ = 201,

Search and delete this:

	CHINA_MATRIX_ANSWER_MAX_LEN = 8,

	RUNUP_MATRIX_QUIZ_MAX_LEN = 8,
	RUNUP_MATRIX_ANSWER_MAX_LEN = 4,

Search and delete this:

typedef struct command_china_matrix_card
{
	BYTE	bHeader;
	char	szAnswer[CHINA_MATRIX_ANSWER_MAX_LEN + 1];
} TPacketCGChinaMatrixCard;

typedef struct command_runup_matrix_answer
{
	BYTE	bHeader;
	char	szAnswer[RUNUP_MATRIX_ANSWER_MAX_LEN + 1];
} TPacketCGRunupMatrixAnswer;

search and delete:

typedef struct packet_china_matrixd_card
{
	BYTE	bHeader;
	DWORD	dwRows;
	DWORD	dwCols;
} TPacketGCChinaMatrixCard;

typedef struct packet_runup_matrixd_quiz
{
	BYTE	bHeader;
	char	szQuiz[RUNUP_MATRIX_QUIZ_MAX_LEN + 1];
} TPacketGCRunupMatrixQuiz;

search and delete:

