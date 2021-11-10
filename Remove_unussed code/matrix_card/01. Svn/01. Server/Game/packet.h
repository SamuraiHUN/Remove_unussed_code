search and delete this:

	HEADER_CG_CHINA_MATRIX_CARD = 108,

search and delete this:

	HEADER_GC_MATRIX_CARD = 116,

and this:

	HEADER_GC_RUNUP_MATRIX_QUIZ = 201,

search and delete this:

typedef struct command_matrix_card
{
	BYTE bHeader;
	char szAnswer[MATRIX_ANSWER_MAX_LEN + 1];
} TPacketCGMatrixCard;

typedef struct packet_matrix_card
{
	BYTE bHeader;
	DWORD dwRows;
	DWORD dwCols;
} TPacketGCMatrixCard;

and this:

enum
{
	RUNUP_MATRIX_ANSWER_MAX_LEN = 4,
	RUNUP_MATRIX_QUIZ_MAX_LEN = 8,
};

typedef struct packet_runup_matrix_quiz
{
	BYTE bHeader;
	char szQuiz[RUNUP_MATRIX_QUIZ_MAX_LEN + 1];
} TPacketGCRunupMatrixQuiz;

typedef struct command_runup_matrix_answer
{
	BYTE bHeader;
	char szAnswer[RUNUP_MATRIX_ANSWER_MAX_LEN + 1];
} TPacketCGRunupMatrixAnswer;