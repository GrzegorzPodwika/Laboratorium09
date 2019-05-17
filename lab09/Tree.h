#ifndef TREE_H
#define TREE_H

struct TreeElement
{
	TreeElement *parent;
	TreeElement *leftChild;
	TreeElement *rightChild;

	int profit, weight, bound;
	bool isPromisingFlag, isRightChild;
};


class Tree 
{
	TreeElement *root;
	TreeElement *lastLeaf;
	unsigned levelOfRoot;

public:

	//konstruktor
	Tree() : root{ nullptr }, lastLeaf{nullptr}, levelOfRoot{}
	{}
	
	//destruktor
	~Tree();

	//metody publiczne
	void push(int profit, int weight, int bound, bool isPromisingFlag = true);
	void pushLeft(int profit, int weight, int bound, bool isPromisingFlag = true);
	void pushRight(int profit, int weight, int bound, bool isPromisingFlag = false);

	void pop();
	void showWholeTree();
	int size();
	bool haveParentTwoChildren();
	bool isPromisingNode();
	int getProfit();
	int getWeight();

	void TreeInorder(TreeElement *rt, int spaceBeetweenNodes, int lvlOfRoot = 0);
	TreeElement* getLastLeaf();
	bool isRightChild();
	void setPromisingFlag(bool promFlag);
};











#endif // !TREE_H
