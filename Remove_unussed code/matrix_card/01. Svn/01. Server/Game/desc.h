search and delete this:

	void SetMatrixCode(const char* c_psz) { m_stMatrixCode = c_psz; }
	const char* GetMatrixCode() { return m_stMatrixCode.c_str(); }

	void SetMatrixCardRowsAndColumns(unsigned long rows, unsigned long cols);
	unsigned long GetMatrixRows();
	unsigned long GetMatrixCols();
	bool CheckMatrixTryCount();

search and delete this:

	DWORD m_dwMatrixRows;
	DWORD m_dwMatrixCols;
	BYTE m_bMatrixTryCount;

and this:

	std::string m_stMatrixCode;

search and delete this:

protected:
	std::string m_stMatrixCardID;
	std::string m_stMatrixQuiz;

search and delete this:

	void SetMatrixCardID(const char* szCardID) { m_stMatrixCardID = szCardID; }
	const char* GetMatrixCardID() { return m_stMatrixCardID.c_str(); }
	void SetMatrixQuiz(const char* szCode) { m_stMatrixCode = szCode; }
	const char* GetMatrixQuiz() { return m_stMatrixCode.c_str(); }
