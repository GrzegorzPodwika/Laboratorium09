#include "Tree.h"
#include "knapsackProblemByBacktracking.h"
using namespace std;

void menu()
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
	vector <int> massOfItems(1);

	//wypelnianie vectorow pomocniczych wartosciami z pliku
	fillVectorsWithDataFromFile(inFile, priceOfItems, massOfItems);

	Tree root;

	backtrackingAlgorithm(root, priceOfItems, massOfItems, maxMass);
	//root.showWholeTree();

}

void fillVectorsWithDataFromFile(fstream & inFile, vector<int>& priceOfItems, vector<int>& massOfItems)
{
	//pomocnicze zmienne do wczytywania z pliku
	int tmpMass{}, tmpPrice{};

	while (!inFile.eof())
	{
		inFile >> tmpPrice >> tmpMass;

		priceOfItems.push_back(tmpPrice);
		massOfItems.push_back(tmpMass);
	}
}

void backtrackingAlgorithm(Tree &root, std::vector<int>& priceOfItems, std::vector<int>& massOfItems, int maxMass)
{
	int tmpPrice{}, tmpMass{}, totWeight{}, bound{}, k{};
	int weightCounter{}, profitCounter{}, lackOfItemX{};
	int iter = 1;

	for (int i = 0; i < priceOfItems.size(); i++, weightCounter = 0, profitCounter = 0)
	{
		k = getLevelOfExceedingSumOfWeight(massOfItems, maxMass, root);
		cout << iter << " iteracja, i = " << i << ", k = " << k << endl;

		if (i == 0)
		{
			tmpPrice = priceOfItems[i];
			tmpMass = massOfItems[i];

			for (int j = i + 1; j <= k - 1; j++)
			{
				weightCounter += massOfItems[j];
			}
			totWeight = tmpMass + weightCounter;

			for (int j = i + 1; j <= k - 1; j++)
			{
				profitCounter += priceOfItems[j];
			}

			if (k == massOfItems.size())
				bound = tmpPrice + profitCounter;
			else
				bound = (tmpPrice + profitCounter) + (maxMass - totWeight)*priceOfItems[k] / massOfItems[k];

			root.push(tmpPrice, tmpMass, bound);

			tmpPrice = 0;
			tmpMass = 0;
		}
		else
		{
			if (root.isPromisingNode())
			{
				tmpPrice += priceOfItems[i];
				tmpMass += massOfItems[i];

				for (int j = i + 1; j <= k - 1; j++)
				{
					weightCounter += massOfItems[j];
				}
				totWeight = tmpMass + weightCounter;

				for (int j = i + 1; j <= k - 1; j++)
				{
					profitCounter += priceOfItems[j];
				}

				if (k == massOfItems.size())
					bound = tmpPrice + profitCounter;
				else
					bound = (tmpPrice + profitCounter) + (maxMass - totWeight)*priceOfItems[k] / massOfItems[k];
			}
			else
			{
				root.pop();

				tmpPrice = root.getProfit();
				tmpMass = root.getWeight();

				for (int j = i + 1; j <= k - 1; j++)
				{
					weightCounter += massOfItems[j];
				}
				totWeight = tmpMass + weightCounter;

				for (int j = i + 1; j <= k - 1; j++)
				{
					profitCounter += priceOfItems[j];
				}

				if (k == massOfItems.size())
					bound = tmpPrice + profitCounter;
				else
					bound = (tmpPrice + profitCounter) + (maxMass - totWeight)*priceOfItems[k] / massOfItems[k];
			}



			if (tmpMass < maxMass && bound > tmpPrice)
			{
				root.push(tmpPrice, tmpMass, bound, true);
			}
			else
			{
				root.push(tmpPrice, tmpMass, bound, false);

				while (root.haveParentTwoChildren())
				{
					root.pop();
					i--;
				}
				//lackOfItemX = i;
				root.setPromisingFlag(false);
				i--;
			}
		}

		root.showWholeTree();
		iter++;
	}

}


int getLevelOfExceedingSumOfWeight(std::vector<int>& massOfItems, int maxMass, Tree &root)
{
	Tree tmp = root;
	int *tabOfIncides = new int[massOfItems.size()]{};
	int counter{}, searchLevel{};

	for (int i = tmp.size(); i > 0; i--)
	{
		if (tmp.isRightChild())
		{
			tabOfIncides[i]++;
			tmp.pop();
		}
		else
		{
			tmp.pop();
		}
	}

	for (int i = 0; i < massOfItems.size(); i++)
	{
		if (tabOfIncides[i] == 0)
		{

			counter += massOfItems[i];
			if (counter > maxMass)
				return i;
		}
	}
	
	delete[] tabOfIncides;
	return massOfItems.size();
}
