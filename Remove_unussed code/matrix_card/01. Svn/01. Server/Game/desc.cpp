search and delete this:

	m_dwMatrixRows = m_dwMatrixCols = 0;
	m_bMatrixTryCount = 0;

search and delete this:

void DESC::SetMatrixCardRowsAndColumns(unsigned long rows, unsigned long cols)
{
	m_dwMatrixRows = rows;
	m_dwMatrixCols = cols;
}

unsigned long DESC::GetMatrixRows()
{
	return m_dwMatrixRows;
}

unsigned long DESC::GetMatrixCols()
{
	return m_dwMatrixCols;
}

bool DESC::CheckMatrixTryCount()
{
	if (++m_bMatrixTryCount >= 3)
		return false;

	return true;
}