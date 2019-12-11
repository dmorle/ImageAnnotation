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
	Buffer(std::string target, std::string suffix)
	{
		this->target = target;
		absIndex = 0;

		loadFileNames();
		loadNewBuffer();
	}

	virtual ~Buffer()
	{
		clearDiskItems();
		emptyBuffer();
	}

	HRESULT next()
	{
		if (absIndex == diskItems.size() - 1)
			return E_ABORT;

		releaseThread();

		if (FAILED(threadReturn))
			return threadReturn;

		absIndex++;
		std::advance(active, 1);

		loadingThread = new std::thread(m_next);
		return S_OK;
	}

	HRESULT prev()
	{
		if (absIndex == 0)
			return E_ABORT;

		releaseThread();

		if (FAILED(threadReturn))
			return threadReturn;

		absIndex--;
		std::advance(active, -1);

		std::thread newThread(m_prev);

		loadingThread = new std::thread(m_next);
		return S_OK;
	}

	HRESULT setActive(UINT nI)
	{
		if (nI >= absIndex)
			return E_ABORT;
	}

protected:
	std::string target;
	std::vector<std::string*> diskItems;
	UINT absIndex;

	USHORT bufferSize;
	std::list<T*>::iterator active;
	std::list<T*> buffer;

	// loades the element at absIndex
	virtual T* loadElem(std::string*) = 0;

	USHORT activeIndex()
	{
		USHORT index;
		for (auto it : elements) {
			if (it == active)
				return index;
		}
		return -1;
	}

private:
	std::thread* loadingThread;
	HRESULT threadReturn;

	void clearDiskItems()
	{
		// clearing the loaded file paths
		if (!diskItems.size()) {
			for (auto& e : diskItems)
				delete e;
			diskItems.clear();

			activeIndex = 0;
		}
	}

	void emptyBuffer()
	{
		if (active) {
			releaseThread();

			// reseting the active element
			active = NULL;

			// deleting the elements in the buffer
			for (auto& e : buffer)
				delete e;

			// clearing the buffer
			buffer.clear();
		}
	}

	void loadFileNames()
	{
		auto dir = std::filesystem::directory_iterator(target);
		for (auto& entry : dir) {
			std::string* pStr = new entry.path();
			// TODO: check if pStr ends in suffix
			buffer.push_back(pStr);
		}

		activeIndex = 0;
	}
	
	HRESULT loadNewBuffer()
	{
		// check if buffer size is too large
		if (diskItems.size() < bufferSize * 2) {
			// Load all disk items
			for (auto& e : diskItems) {
				T* nE = loadElem(e);
				if (!nE)
					return E_FAIL;

				buffer.push_back(nE);
			}
			return S_OK;
		}

		// standard buffer load
		for (int i = 0; i < bufferSize * 2; i++) {
			T* nE = loadElem(diskItems[i]);
			if (!nE)
				return E_FAIL;

			buffer.push_back(nE);
		}
		return S_OK;
	}

	void m_next()
	{
		if (absIndex <= bufferSize)
			// at the start of target => buffer ready
			threadReturn = S_OK;

		else if (absIndex + bufferSize >= diskItems.size())
			// at the end of target => buffer ready
			threadReturn = S_OK;

		else {
			// normal response
			T* nE = loadElem(diskItems[absIndex + bufferSize]);
			if (!nE)
				threadReturn = E_FAIL;

			else {
				delete buffer.front;
				buffer.pop_front();
				buffer.push_back(nE);
				threadReturn = S_OK;
			}
		}
	}

	void m_prev()
	{
		if (absIndex <= bufferSize)
			// at the start of target => buffer ready
			threadReturn = S_OK;

		else if (absIndex + bufferSize >= diskItems.size())
			// at the end of target => buffer ready
			threadReturn = S_OK;

		else {
			// normal response
			T* nE = loadElem(diskItems[absIndex - bufferSize]);
			if (!nE)
				threadReturn = E_FAIL;

			else {
				delete buffer.back;
				buffer.pop_back();
				buffer.push_front(nE);
				threadReturn = S_OK;
			}
		}
	}

	void releaseThread() {
		if (loadingThread) {
			loadingThread->join();
			delete loadingThread;
		}
	}
};

#endif