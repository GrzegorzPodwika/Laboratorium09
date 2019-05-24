#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <fstream>

//Struktura imituj¹ca pojedynczy element drzewa
struct TreeElement
{
	TreeElement *parent;
	TreeElement *leftChild;
	TreeElement *rightChild;

	int profit, weight, bound;
	bool isPromisingFlag, isRightChild;
};

//klasa imitujaca drzewo skladajaca sie z pojedynczych obiektow struktury TreeElement
class Tree 
{
	TreeElement *root;			//wskaznik na korzen
	TreeElement *lastLeaf;		//wskaznik na ostatni lisc
	unsigned levelOfRoot;		//poziom drzewa liczony od góry
	int maxProfit;

public:

	//konstruktor
	Tree() : root{ nullptr }, lastLeaf{nullptr}, levelOfRoot{}, maxProfit{}
	{}
	
	//destruktor
	~Tree();

	//metody publiczne
	//metody dolaczajace do danego drzewa nastepny lisc
	void push(int profit, int weight, int bound, bool isPromisingFlag = true);
	void pushLeft(int profit, int weight, int bound, bool isPromisingFlag = true);
	void pushRight(int profit, int weight, int bound, bool isPromisingFlag = false);

	void pop();																			//metoda wracajaca sie do rodzica ostatniego liscia
	void showWholeTree();																//metoda pomocnicza pokazujaca stanm drzewa w danej chwilii
	int size();																			//metoda zwracajaca rozmiar drzewa liczony od gory
	bool haveParentTwoChildren();														//metoda zwracajaca true jesli rodzic ostatniego liscia ma dwoje dzieci, false w przeciwnym wypadkuj
	bool isPromisingNode();																//metoda zwracajaca true jesli dany wezel jest obiecujacy, false w przeciwnym wypadku
	int getProfit();																	//metoda zwracajaca profit w danym wezle
	int getWeight();																	//metoda zwracajaca weight w danym wezle
	void TreeInorder(TreeElement *rt, int spaceBeetweenNodes, int lvlOfRoot = 0);		//metoda rekurencyjna pomocnicza do pokazywania drzewa na ekran
	TreeElement* getLastLeaf();															//metoda zwracajaca ostatni lisc
	bool isRightChild();																//metoda zwracajaca true jesli wezel jest prawym dzieckiem, false w przeciwnym wypadku
	void setPromisingFlag(bool promFlag);												//funkcja ustawiajaca flage czy jest obiecujacy wezel na true lub false
	void saveDataToFile(std::fstream &outFile);											//metoda zapisujaca drzewo do pliku
	void TreeInOrderToFile(std::fstream &outFile, TreeElement *rt, int lvlOfRoot = 0);	//metoda rekurencyjna pomocnicza do zapisywania stanu drzewa do pliku
	int getMaxProfit();																	//metoda zwracajaca dotychczasowy maxProfit
	void setMaxProfit(int maxProf);														//metoda ustawiajaca nowy, wiekszy maxProfit
};











#endif // !TREE_H
