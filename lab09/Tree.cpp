#include "Tree.h"

using namespace std;

Tree::~Tree()
{}

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
				pushLeft(profit, weight, bound, isPromisingFlag);
			else
				pushRight(profit, weight, bound, isPromisingFlag);		
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

void Tree::setPromisingFlag(bool promFlag)
{
	lastLeaf->isPromisingFlag = promFlag;
}

void Tree::saveDataToFile(std::fstream &outFile)
{
	TreeInOrderToFile(outFile, root);
}

void Tree::TreeInOrderToFile(std::fstream & outFile, TreeElement * rt, int lvlOfRoot)
{
	if (rt)
	{
		outFile << lvlOfRoot << " p = " << rt->profit << endl;
		outFile << lvlOfRoot << " w = " << rt->weight << endl;
		outFile << lvlOfRoot << " b = " << rt->bound << endl << endl;

		TreeInOrderToFile(outFile, rt->leftChild, lvlOfRoot + 1);
		TreeInOrderToFile(outFile, rt->rightChild, lvlOfRoot + 1);
	}
}

int Tree::getMaxProfit()
{
	return maxProfit;
}

void Tree::setMaxProfit(int maxProf)
{
	maxProfit = maxProf;
}

int Tree::size()
{
	return levelOfRoot;
}

bool Tree::haveParentTwoChildren()
{
	if (root == lastLeaf)
	{
		return false;
	}
	else
	{
		if (lastLeaf->parent->leftChild != nullptr && lastLeaf->parent->rightChild != nullptr)
			return true;
		else
			return false;
	}
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


