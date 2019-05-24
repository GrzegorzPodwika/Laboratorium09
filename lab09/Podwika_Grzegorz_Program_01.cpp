#include "knapsackProblemByBacktracking.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{	
	//wczytanie pliku z dysku
	fstream inFile = createInputFile();

	//wczytanie najwiekszej masy z pliku
	int maxMass{};
	try
	{
		inFile >> maxMass;
		if (maxMass <= 0)
			throw EXCEPTION_CODE::notNaturalNumber;
	}
	catch (EXCEPTION_CODE error)
	{
		seeExceptions(error);
		exit(0);
	}


	//utworzenie pomocniczych wektorow + wstepna inicjalizacja zerowych indexow zerami
	vector <int> priceOfItems(1);
	vector <int> weightOfItems(1);

	//wypelnianie vectorow pomocniczych wartosciami z pliku
	fillVectorsWithDataFromFile(inFile, priceOfItems, weightOfItems);

	//utworzenie drzewa do problemu plecakowego 0-1 z nawrotami
	Tree tree;
	
	//wywolanie funkcji rozwiazujacej problem plecakowy 0-1 poprzez algorytm z nawrotami
	backtrackingAlgorithm(tree, priceOfItems, weightOfItems, maxMass);

	inFile.close();
	getchar();
	getchar();
}