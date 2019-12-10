#ifndef BUFFER_H
#define BUFFER_H

#include <Windows.h>
#include <list>
#include <vector>
#include <string>
#include <thread>
#include <filesystem>

template <typename T>
class Buffer {
public:
	Buffer(std::string target, std::string suffix) {
		this->target = target;
		absIndex = 0;

		loadFileNames();
		loadNewBuffer();
	}

	void next()
	{
		if (SUCCEEDED(m_next()))
			absIndex++;
	}

	void prev()
	{
		if (SUCCEEDED(m_prev()))
			absIndex--;
	}

protected:
	std::string target;
	USHORT bufferSize;
	UINT absIndex;

	std::vector<std::string*> elemVec;
	std::list<T>::iterator active;
	std::list<T> elemLoaded;

	virtual T* loadElem(PSTR file) = 0;

	USHORT activeIndex() {
		USHORT index;
		for (auto it : elements) {
			if (it == active)
				return index;
		}
		return -1;
	}

private:
	void loadFileNames() {
		auto dir = std::filesystem::directory_iterator(target);
		for (auto& entry : dir) {
			std::string* pStr = new entry.path();
			// TODO: check if pStr ends in suffix
			elemLoaded.push_back(pStr);
		}
	}

	void loadNewBuffer() {
		// throws away the current buffer and creates a new one
		// new buffer is created on another thread from object state
	}

	HRESULT m_next()
	{
		if (activeIndex() < bufferSize) {
			// at the start of target
		}
		else if (activeIndex() > bufferSize) {
			// at the end of target
		}
		else {
			// normal response
		}
	}

	HRESULT m_prev* ()
	{

	}
};

#endif