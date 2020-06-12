#ifndef IAP_TREE_H
#define IAP_TREE_H

#include <list>
#include <string>
#include <stdlib.h>

/*
 * Template argument must have the == operator overloaded
 * Additionally, this class is not to be used polymorphically,
 * inherited classes must be expicitly typed at runtime
 */
template <typename T>
class Tree
{
private:
	struct Node
	{
		T* pVal;
		Node* pParent;
		std::list<Node*> children;
	};

public:
	Tree();

	~Tree();

	// returns a reference to the root node of the tree
	const Node* getRoot();
	// returns the node reference by the list of values
	const Node* findNode(std::list<T*> path);

	const Node* getChild(const Node* pn, const T* pChildVal);

	void addChild(Node* pParent, Node* npNode);

	Node* createNode(T* pVal);

private:
	// the root node of the tree
	Node* pRoot;

	void releaseNode(Node* pND);
};

// public interface

template <typename T>
inline Tree<T>::Tree()
{
	pRoot = NULL;
}

template <typename T>
inline Tree<T>::~Tree()
{
	this->releaseNode(pRoot);
}

template <typename T>
inline const typename Tree<T>::Node*
Tree<T>::getRoot()
{
	return pRoot;
}

template <typename T>
inline const typename Tree<T>::Node*
Tree<T>::findNode(std::list<T*> path)
{
	Node* pActive = pRoot;
	for (T* t : path) {
		if (!pActive->children.size())
			return NULL;

		for (int i = 0; i < pActive->children.size(); i++) {
			if (i == pActive->children.size())
				return NULL;
			if (*(pActive->children[i]->pVal) == *t) {
				pActive = t;
				break;
			}
		}
	}

	return pActive;
}

template <typename T>
inline const typename Tree<T>::Node*
Tree<T>::getChild(const Node* pND, const T* pChildVal)
{
	if (!pChildVal)
		return pND->pParent;

	for (Node* e : pND->children)
		if (*(e->pVal) == *pChildVal)
			return e;

	return NULL;
}

template <typename T>
inline void
Tree<T>::addChild(Node* pParent, Node* npNode)
{
	pParent->children.push_back(npNode);
}

template <typename T>
inline typename Tree<T>::Node* Tree<T>::createNode(T* pVal)
{
	Node* npNode = (Node *)malloc(sizeof(Node));
	npNode->pVal = pVal;
	npNode->pParent = NULL;
}

// private interface

template <typename T>
inline void 
Tree<T>::releaseNode(Node* pND)
{
	for (Node* e : pND->children)
		releaseNode(e);

	free(pND);
}

#endif
