#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <vector>

#include <core/IManager.h>
#include <core/Data/DataElement.h>
#include <WDASAPI/WDASAPI.h>

class DataManager :
    public IManager
{
public:
    DataManager();
    ~DataManager();

    DAS_RESULT get(DataElement** ppDE) const;

    DAS_RESULT stepForward();
    DAS_RESULT stepBackward();

private:
    std::vector<DataElement*> elements;

    size_t idx;

    const static size_t loadRgn = 5;
};

#endif
