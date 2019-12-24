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

#define bufferItem BufferElement::_bufferItem<T>

namespace WCMP {

	namespace BufferElement{

		template <typename T>
		struct _bufferItem {
			T* item;                    // contains the item loaded by the thread
			std::thread* loadingThread; // will be NULL once the thread has finished
			HRESULT threadReturn;       // contains the thread status once loadingThread is NULL

			// constructor for creating a new bufferItem from disk
			_bufferItem()
			{
				item = NULL;
				loadingThread = NULL;
				threadReturn = S_OK;
			}

			// constructor used for copying a buffer
			_bufferItem(T* item, HRESULT threadReturn)
			{
				this->item = item;
				this->loadingThread = NULL;
				this->threadReturn = threadReturn;
			}
		};
	}

	namespace fs = std::experimental::filesystem::v1;

	/*
		Creates a buffer of object for quick usage through multithreading

		'bufferSize' objects are loaded previous to and preceeding the active element
		TODO: Create a buffer for cloud resources
	*/
	template <typename T>
	class Buffer {
	public:
		Buffer(std::string target, std::string suffix, USHORT bufferSize, T* (*loadItem)(std::wstring*), void(*destructItem)(T*) = NULL)
		{
			this->target = target;
			this->suffix = suffix;
			this->bufferSize = bufferSize;
			this->loadItem = loadItem;
			this->destructItem = destructItem;

			loadFileNames();
			loadNewBuffer();
		}

		virtual ~Buffer()
		{
			clearDiskItems();
			emptyBuffer();
		}

		// changes internal state to the next element in the buffer and shifts accordingly
		void next()
		{
			// checking to ensure request is valid
			if (absIndex >= diskItems.size() - 1)
				return;

			// moving the active buffer element
			std::advance(active, 1);
			absIndex++;

			// deleting and loading the edge elements
			if (!smallTarget) {
				// loading new
				if (absIndex + bufferSize < diskItems.size())
					buffer.push_back(loadBufferItem(diskItems[absIndex + bufferSize]));

				// deleting old
				if (absIndex > bufferSize) {
					releaseBufferItem(buffer.front());
					buffer.pop_front();
				}
			}
		}

		// changes internal state to the previous element in the buffer and shifts accordingly
		void prev()
		{
			// checking to ensure request is valid
			if (absIndex <= 0)
				return;

			// moving the active buffer element
			std::advance(*active, -1);
			absIndex--;

			// deleting and loading the edge elements
			if (!smallTarget) {
				// loading new
				if (absIndex + bufferSize < diskItems.size()) {
					buffer.push_front(loadBufferItem(diskItems[absIndex - bufferSize]));
				}

				// deleting old
				if (absIndex < diskItems.size() - bufferSize) {
					releaseBufferItem(buffer.back());
					buffer.pop_back();
				}
			}
		}

		/*
			Sets the crrent index to any element in the target
			TODO: entire imlementation
		*/
		void setActive(UINT nI) {}

		T* getActiveItem()
		{
			readyBufferItem(*active);
			return (*active)->item;
		}

	protected:
		Buffer(Buffer<T> *pB)
		{
			this->target = pB->target;
			this->suffix = pB->suffix;
			this->bufferSize = pB->bufferSize;
			this->loadItem = pB->loadItem;
			this->destructItem = pB->destructItem;
			for (auto e : pB->diskItems)
				this->diskItems.push_back(new std::wstring(*e));

			loadNewBuffer();
		}

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
		typename std::list<bufferItem*>::iterator active;
		// the buffer of items surrounding active
		std::list<bufferItem*> buffer;

		// loads the element at the given path
		T* (*loadItem)(std::wstring*);

	private:
		void (*destructItem)(T*);
		BOOL smallTarget;

		// empties diskItems and resets absIndex
		void clearDiskItems()
		{
			// clearing the loaded file paths
			for (auto& e : diskItems)
				delete e;

			diskItems.clear();
			absIndex = 0;
		}

		// empties buffer and resets active
		void emptyBuffer()
		{
			for (auto& e : buffer)
				releaseBufferItem(e);

			buffer.clear();
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
		void loadNewBuffer()
		{
			// check if buffer size is too large
			if (diskItems.size() < bufferSize * 2) {
				// Load all disk items
				smallTarget = TRUE;
				for (auto& e : diskItems)
					buffer.push_back(loadBufferItem(e));
			}
			else {
				// standard buffer load
				smallTarget = FALSE;
				int i = 0;
				for (auto& e : diskItems) {
					buffer.push_back(loadBufferItem(e));
					if (bufferSize < ++i)
						break;
				}
			}
			active = buffer.begin();
		}

		// loads an item from target into the buffer, runs on a different thread
		void loadDiskItem(bufferItem* npItem, std::wstring* path)
		{
			// loading the item from disk
			T* nE = loadItem(path);

			// putting the result into the buffer
			npItem->item = nE;
			if (!nE)
				npItem->threadReturn = E_FAIL;
		}

	protected:
		// waits for all active threads to finish
		void releaseThreads()
		{
			for (auto& e : buffer)
				readyBufferItem(e);
		}

		// creates a new bufferItem from path and returns it
		bufferItem* loadBufferItem(std::wstring* path)
		{
			auto npItem = new bufferItem();
			npItem->loadingThread = new std::thread(&Buffer<T>::loadDiskItem, this, npItem, path);
			return npItem;
		}

		// ensures pItem is ready for use
		void readyBufferItem(bufferItem* pItem)
		{
			if (pItem->loadingThread) {
				pItem->loadingThread->join();
				delete pItem->loadingThread;
				pItem->loadingThread = NULL;
			}
		}

		// deletes pItem, a bufferItem object
		void releaseBufferItem(bufferItem*& pItem)
		{
			// ensuring that the item can be deleted
			readyBufferItem(pItem);

			// deleting the contained item
			if (pItem->threadReturn == S_OK) {
				if (destructItem)
					destructItem(pItem->item);
				else
					delete pItem->item;
			}

			// deleting the bufferItem itself
			delete pItem;
			pItem = NULL;

		}

		// copies pb
		Buffer(const Buffer* pb)
		{
			target = pb->target;
			suffix = pb->suffix;
			bufferSize = pb->bufferSize;
			loadItem = pb->loadItem;
			destructItem = pb->destructItem;
			smallTarget = pb->smallTarget;

			loadFileNames();

			for (int i = max(0, (int)pb->absIndex - bufferSize); i < min(diskItems.size(), absIndex + bufferSize + 1); i++)
				buffer.push_back(loadBufferItem(diskItems[i]));

			// getting active properly initialized
			active = buffer.begin();
			if (smallTarget)
				std::advance(active, min(absIndex, bufferSize));
			else
				std::advance(active, absIndex);
		}
	};

}

#endif