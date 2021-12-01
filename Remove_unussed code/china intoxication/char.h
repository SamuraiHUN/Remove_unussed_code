Search and delete this:

#define SET_OVER_TIME(ch, time) (ch)->SetOverTime(time)

Search and delete this:

enum e_overtime
{
	OT_NONE,
	OT_3HOUR,
	OT_5HOUR,
};

Search and delete this:

private:
	e_overtime m_eOverTime;

public:
	bool IsOverTime(e_overtime e) const { return (e == m_eOverTime); }
	void SetOverTime(e_overtime e) { m_eOverTime = e; }