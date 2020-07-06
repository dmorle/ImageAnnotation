#ifndef DATA_ELEMENT_H
#define DATA_ELEMENT_H

#include <windows.h>

class DataElement
{
	friend class DataManager;

public:
	DataElement()
	{
		id = ID++;
	}

	virtual ~DataElement()
	{
		if (pData)
			free(pData);
	}

protected:
	// raw data for the image or video
	BYTE* pData;

	// serializes pData to disk (annotations don't use much memory)
	virtual DAS_RESULT offloadData() = 0;

	// loads pData from disk
	virtual DAS_RESULT loadData() = 0;

private:
	size_t id;
	static size_t ID;
};

#endif
