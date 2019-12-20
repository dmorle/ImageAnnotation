#ifndef BUFFER_H
#define BUFFER_H

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <Windows.h>
#include <list>
#include <vector>
#include <iterator>
#include <string>
#include <thread>
#include <experimental/filesystem>

namespace WCMP {

	namespace fs = std::experimental::filesystem::v1;

	template <typename T>
	class Buffer {
	public:
		Buffer(std::string target, std::string suffix, USHORT bufferSize, T* (*loadElem)(std::wstring*))
		{
			this->target = target;
			this->suffix = suffix;
			this->bufferSize = bufferSize;
			this->loadElem = loadElem;

			loadFileNames();
			loadNewBuffer();

			loadingThread = NULL;
			threadReturn = S_OK;
		}

		virtual ~Buffer()
		{
			clearDiskItems();
			emptyBuffer();
		}

		// changes internal state to the next element in the buffer and shifts accordingly
		HRESULT next()
		{
			if (absIndex == diskItems.size() - 1)
				return E_ABORT;

			releaseThread();

			if (FAILED(threadReturn))
				return threadReturn;

			absIndex++;
			std::advance(*active, 1);

			loadingThread = new std::thread(&Buffer<T>::m_next, this);
			return S_OK;
		}

		// changes internal state to the previous element in the buffer and shifts accordingly
		HRESULT prev()
		{
			if (absIndex == 0)
				return E_ABORT;

			releaseThread();

			if (FAILED(threadReturn))
				return threadReturn;

			absIndex--;
			std::advance(*active, -1);

			loadingThread = new std::thread(&Buffer<T>::m_prev, this);
			return S_OK;
		}

		/*
			Sets the crrent index to any element in the target
			TODO: entire imlementation
		*/
		HRESULT setActive(UINT nI)
		{
			if (nI >= absIndex)
				return E_ABORT;
		}

	protected:
		// path the current target
		std::string target;
		// filter target for files ending in 'suffix'
		std::string suffix;
		// paths to all files in target
		std::vector<std::wstring*> diskItems;
		// current index of the buffer in target
		UINT absIndex;

		// the number of elements to store in RAM at a time
		USHORT bufferSize;
		// the current element
		typename std::list<T*>::iterator* active;
		// the buffer of items surrounding active
		std::list<T*> buffer;

		// loads the element at the given path
		T* (*loadElem)(std::wstring*);

	private:
		std::thread* loadingThread;
		HRESULT threadReturn;

		// empties diskItems and resets absIndex
		void clearDiskItems()
		{
			// clearing the loaded file paths
			if (diskItems.size()) {
				for (auto& e : diskItems)
					delete e;
				diskItems.clear();

				absIndex = 0;
			}
		}

		// empties buffer and resets active
		void emptyBuffer()
		{
			if (active) {
				releaseThread();

				// reseting the active element
				delete active;
				active = NULL;

				// deleting the elements in the buffer
				for (auto& e : buffer)
					delete e;

				// clearing the buffer
				buffer.clear();
			}
		}

		// initializes diskItems and absIndex
		void loadFileNames()
		{
			auto dir = fs::directory_iterator(target);
			for (auto& entry : dir) {
				std::wstring* pStr = new std::wstring(entry.path());
				// TODO: check if pStr ends in suffix
				diskItems.push_back(pStr);
			}

			absIndex = 0;
		}

		// initializes buffer and active
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

				active = new typename std::list<T*>::iterator(buffer.begin());
				return S_OK;
			}

			// standard buffer load
			for (int i = 0; i <= bufferSize * 2; i++) {
				T* nE = loadElem(diskItems[i]);
				if (!nE)
					return E_FAIL;

				buffer.push_back(nE);
			}

			active = new typename std::list<T*>::iterator(buffer.begin());
			return S_OK;
		}

		// loads the next element from target
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
					delete buffer.front();
					buffer.pop_front();
					buffer.push_back(nE);
					threadReturn = S_OK;
				}
			}
		}

		// loads the previous element from target
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
					delete buffer.back();
					buffer.pop_back();
					buffer.push_front(nE);
					threadReturn = S_OK;
				}
			}
		}

		// waits for any active threads to finish
		void releaseThread() {
			if (loadingThread) {
				loadingThread->join();
				loadingThread = NULL;
			}
		}
	};

}

#endif