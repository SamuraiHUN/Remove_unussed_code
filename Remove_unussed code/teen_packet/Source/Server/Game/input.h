Search this and delete:

	INPROC_TEEN,

and delete this class:

class CInputTeen : public CInputProcessor
{
public:
	virtual BYTE GetType() { return INPROC_TEEN; }

	void SetStep(int step);

protected:
	virtual bool Process(LPDESC lpDesc, const void* c_pvOrig, int iBytes, int& r_iBytesProceed);
	virtual int Analyze(LPDESC d, BYTE bHeader, const char* c_pData) { return 0; };

private:
	int m_step;

	bool ProcessHandshake(LPDESC lpDesc, const void* c_pvOrig, size_t uiBytes, int& r_iBytesProceed);
	bool ProcessMain(LPDESC lpDesc, const void* c_pvOrig, size_t uiBytes, int& r_iBytesProceed);
};