#include "DataManager.h"



DataManager::DataManager()
{
}

DataManager::~DataManager()
{
	for (auto& e : elements)
		if (e)
			delete e;
}

DAS_RESULT DataManager::get(DataElement** ppDE) const
{
	DAS_RESULT dr = elements[idx]->loadData();
	if (DAS_RSUCCEEDED(dr))
		*ppDE = elements[idx];
	return dr;
}

DAS_RESULT DataManager::stepForward()
{
	if (idx < elements.size())
	{
		DAS_RESULT dr;

		idx++;
		if (idx - loadRgn >= 0)
			dr = elements[idx - loadRgn]->offloadData();
		if (DAS_RSUCCEEDED(dr))
			if (idx + loadRgn < elements.size())
				dr = elements[idx + loadRgn]->loadData();

		return dr;
	}

	// TODO: attempt get more data from the server
	return DAS_RERROR | DAS_RNIMP;
}

DAS_RESULT DataManager::stepBackward()
{
	if (idx > 0)
	{
		DAS_RESULT dr;

		if (idx - loadRgn >= 0)
			dr = elements[idx - loadRgn]->loadData();
		if (DAS_RSUCCEEDED(dr))
			if (idx + loadRgn < elements.size())
				dr = elements[idx + loadRgn]->offloadData();
		idx--;

		return dr;
	}
}
