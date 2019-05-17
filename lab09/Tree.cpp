#include "Tree.h"
#include <iostream>
using namespace std;

Tree::~Tree()
{
	//TreeElement *tmp = nullptr;

	//while (root != nullptr)
	//{
	//	tmp = lastLeaf->parent;
	//	delete lastLeaf;
	//	lastLeaf = tmp;
	//}
}

void Tree::push(int profit, int weight, int bound, bool isPromisingFlag)
{
	if (root == nullptr)
	{
		TreeElement *nElem = new TreeElement;
		nElem->profit = profit;
		nElem->weight = weight;
		nElem->bound = bound;

		nElem->leftChild = nullptr;
		nElem->rightChild = nullptr;
		nElem->isPromisingFlag = isPromisingFlag;
		nElem->isRightChild = false;

		nElem->parent = nullptr;
		root = nElem;
		lastLeaf = root;

		//levelOfRoot++;
	}
	else
	{
		if (root != lastLeaf)
		{
			if (lastLeaf->leftChild == nullptr)
			{
				//pop();
				pushLeft(profit, weight, bound, isPromisingFlag);
			}
			else
			{
				//pop();
				pushRight(profit, weight, bound, isPromisingFlag);
			}
		}
		else
		{
			if (lastLeaf->leftChild == nullptr)
				pushLeft(profit, weight, bound, isPromisingFlag);
			else
				pushRight(profit, weight, bound, isPromisingFlag);
		}

	}
}

void Tree::pushLeft(int profit, int weight, int bound, bool isPromisingFlag)
{
	TreeElement *nElem = new TreeElement;
	nElem->profit = profit;
	nElem->weight = weight;
	nElem->bound = bound;
	nElem->isPromisingFlag = isPromisingFlag;

	nElem->leftChild = nullptr;
	nElem->rightChild = nullptr;
	nElem->isRightChild = false;

	nElem->parent = lastLeaf;
	lastLeaf->leftChild = nElem;

	lastLeaf = nElem;
	levelOfRoot++;
}

void Tree::pushRight(int profit, int weight, int bound, bool isPromisingFlag)
{
	TreeElement *nElem = new TreeElement;
	nElem->profit = profit;
	nElem->weight = weight;
	nElem->bound = bound;
	nElem->isPromisingFlag = isPromisingFlag;

	nElem->leftChild = nullptr;
	nElem->rightChild = nullptr;
	nElem->isRightChild = true;

	nElem->parent = lastLeaf;
	lastLeaf->rightChild = nElem;

	lastLeaf = nElem;
	levelOfRoot++;
}

void Tree::pop()
{
	if (root != nullptr)
	{
		TreeElement *tmp = lastLeaf;
		lastLeaf = tmp->parent;
		//delete tmp;
		levelOfRoot--;
	}
	else
	{
		cout << "Drzewo jest pusta!" << endl;
	}
}

void Tree::showWholeTree()
{
	TreeInorder(root, levelOfRoot);
	//TreeElement *tmpL = root;
	//TreeElement *tmpR = root;
	//int i{}, j{};
	//while (tmpL != nullptr)
	//{
	//	if (i == this->size())
	//	{
	//		break;
	//	}

	//	cout << i << " LEWY p = " << tmpL->profit << ", w = " << tmpL->weight << ", b = " << tmpL->bound << endl;

	//	if (tmpL->leftChild != nullptr) 
	//	{
	//		tmpL = tmpL->leftChild;
	//	}

	//	if(tmpR->rightChild == nullptr)
	//		tmpR = tmpL;
	//	else if (tmpR->rightChild != nullptr)
	//	{
	//		tmpR = tmpR->rightChild;
	//		cout << i+1 << " PRAWY p = " << tmpR->profit << ", w = " << tmpR->weight << ", b = " << tmpR->bound << endl;
	//	}
	//	
	//	if (tmpL->leftChild == nullptr)
	//		tmpL = tmpR;

	//	i++;
	//	j++;
	//}
	//cout << endl;
}

void Tree::TreeInorder(TreeElement * rt, int spaceBeetweenNodes, int lvlOfRoot)
{
	if (rt)
	{

		for (int j = 0; j <= spaceBeetweenNodes; j++)
		{
			cout << "\t";
		}

		cout << lvlOfRoot << " p = " << rt->profit << endl;

		for (int j = 0; j <= spaceBeetweenNodes; j++)
		{
			cout << "\t";
		}

		cout << lvlOfRoot << " w = " << rt->weight << endl;

		for (int j = 0; j <= spaceBeetweenNodes; j++)
		{
			cout << "\t";
		}

		cout << lvlOfRoot << " b = " << rt->bound << endl<<endl;

		spaceBeetweenNodes--;

		//cout << lvlOfRoot << " p = " << rt->profit << ", w = " << rt->weight << ", b = " << rt->bound << endl;

		TreeInorder(rt->leftChild, spaceBeetweenNodes, lvlOfRoot + 1);

		TreeInorder(rt->rightChild, spaceBeetweenNodes, lvlOfRoot + 1);

	}
}

TreeElement * Tree::getLastLeaf()
{
	return lastLeaf;
}

bool Tree::isRightChild()
{
	if (lastLeaf->isRightChild)
		return true;
	else
		return false;
}

int Tree::size()
{
	return levelOfRoot;
}

bool Tree::haveParentTwoChildren()
{
	if (lastLeaf->parent->leftChild != nullptr && lastLeaf->parent->rightChild != nullptr)
		return true;
	else
		return false;
}

bool Tree::isPromisingNode()
{
	return lastLeaf->isPromisingFlag;
}

int Tree::getProfit()
{
	return lastLeaf->profit;
}

int Tree::getWeight()
{
	return lastLeaf->weight;
}


