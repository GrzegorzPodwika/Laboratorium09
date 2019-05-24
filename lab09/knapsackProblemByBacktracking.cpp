#include "Tree.h"
#include "knapsackProblemByBacktracking.h"
using namespace std;


void fillVectorsWithDataFromFile(fstream & inFile, vector<int>& priceOfItems, vector<int>& weightOfItems)
{
	//pomocnicze zmienne do wczytywania z pliku
	int tmpMass{}, tmpPrice{};

	while (!inFile.eof())
	{
		inFile >> tmpPrice >> tmpMass;

		priceOfItems.push_back(tmpPrice);
		weightOfItems.push_back(tmpMass);
	}
}

void backtrackingAlgorithm(Tree &tree, std::vector<int>& priceOfItems, std::vector<int>& weightOfItems, int maxMass)
{
	//utworzenie pliku do zapisu oraz zmiennych pomocniczych
	fstream outFile = createOutputFile();
	int tmpPrice{}, tmpMass{}, totWeight{}, bound{}, k{};
	int weightCounter{}, profitCounter{};
	int iter = 1;

	for (int i = 0; i < priceOfItems.size(); i++, weightCounter = 0, profitCounter = 0)
	{
		//jesli w algorytmie powrocilismy do i = 0 i ostatni lisc nie rowna sie nullptr, konczymy petle
		//odpowiada to gdy wrocilismy do korzenia wyjsciowego po dzialaniu algorytmu
		if (i == 0 && tree.getLastLeaf() != nullptr)
		{
			break;
		}

		//obliczenie k i wpisanie iterator oraz k do pliku w celu rozpoznawczym
		k = getLevelOfExceedingSumOfWeight(weightOfItems, maxMass, tree);
		outFile << iter << " iteracja, i = " << i << ", k = " << k << endl;

		//pierwsza iteracja, tworzenie korzenia drzewa
		if (i == 0)
		{
			tmpPrice = priceOfItems[i];
			tmpMass = weightOfItems[i];

			//obliczenia do algorytmu profit, weight, bound
			for (int j = i + 1; j <= k - 1; j++)
			{
				weightCounter += weightOfItems[j];
			}
			totWeight = tmpMass + weightCounter;

			for (int j = i + 1; j <= k - 1; j++)
			{
				profitCounter += priceOfItems[j];
			}

			if (k == weightOfItems.size() || k == 1)
				bound = tmpPrice + profitCounter;
			else
				bound = (tmpPrice + profitCounter) + (maxMass - totWeight)*priceOfItems[k] / weightOfItems[k];

			//jesli warunek sie zgadza tworzymy korzen i przechodzimy dalej
			//w przeciwnym wypadku tworzymy korzen, zapisujemy dane i ionczymy petle, bo nic sie nie zmiesci do plecaka
			if (bound > tree.getMaxProfit())
			{
				tree.push(tmpPrice, tmpMass, bound);
			}
			else
			{
				tree.push(tmpPrice, tmpMass, bound, false);
				tree.saveDataToFile(outFile);
				break;
			}

			tmpPrice = 0;
			tmpMass = 0;

		}
		else
		{
			/*
			Jesli ostatni lisc drzewa jest obiecujacy to wykonuje sie pierwszy blok, w przeciwnym wypadku drugi
			*/
			if (tree.isPromisingNode())
			{
				tmpPrice += priceOfItems[i];
				tmpMass += weightOfItems[i];

				for (int j = i + 1; j <= k - 1; j++)
				{
					weightCounter += weightOfItems[j];
				}
				totWeight = tmpMass + weightCounter;

				for (int j = i + 1; j <= k - 1; j++)
				{
					profitCounter += priceOfItems[j];
				}

				if (k == weightOfItems.size())
					bound = tmpPrice + profitCounter;
				else
					bound = (tmpPrice + profitCounter) + (maxMass - totWeight)*priceOfItems[k] / weightOfItems[k];
			}
			else
			{
				//jesli nie jest obiecujacy to wracamy do rodzica
				tree.pop();

				tmpPrice = tree.getProfit();
				tmpMass = tree.getWeight();

				for (int j = i + 1; j <= k - 1; j++)
				{
					weightCounter += weightOfItems[j];
				}
				totWeight = tmpMass + weightCounter;

				for (int j = i + 1; j <= k - 1; j++)
				{
					profitCounter += priceOfItems[j];
				}

				if (k == weightOfItems.size())
					bound = tmpPrice + profitCounter;
				else
					bound = (tmpPrice + profitCounter) + (maxMass - totWeight)*priceOfItems[k] / weightOfItems[k];
			}


			//jesli zachodza te warunki to ustawiamy nowy maxProfit i dolaczamy lisc z flaga obiecujacy = true
			if (tmpMass < maxMass && bound > tree.getMaxProfit() && bound > tmpPrice)
			{
				tree.setMaxProfit(tmpPrice);
				tree.push(tmpPrice, tmpMass, bound, true);
			}
			else
			{
				//jesli nie zachodza te warunki to dolaczamy lisc z flaga obiecujacy = false
				tree.push(tmpPrice, tmpMass, bound, false);

				while (tree.haveParentTwoChildren())
				{
					tree.pop();
					i--;
				}

				outFile << "POWROT Z NIEOBIECUJACEGO WEZLA/WEZLOW " << endl;
				tree.setPromisingFlag(false);
				i--;
			}
		}

		//zapis stanu drzewa do pliku
		tree.saveDataToFile(outFile);
		iter++;
	}
	outFile.close();
}


int getLevelOfExceedingSumOfWeight(std::vector<int>& weightOfItems, int maxMass, Tree &root)
{
	Tree tmp = root;
	int *tabOfIncides = new int[weightOfItems.size()]{};
	int counter{}, searchLevel{};

	/*
	Jesli lisc jest prawym dzieckiem to eliminujemy go z pozniejszych obliczen,
	jesli lisc jest lewym dzieckiem, ale nieobiecujacym to rowniez eliminujemy
	*/
	for (int i = tmp.size(); i > 0; i--)
	{
		if (tmp.isRightChild())
		{
			tabOfIncides[i]++;
			tmp.pop();
		}
		else
		{
			if (!tmp.isPromisingNode())
			{
				tabOfIncides[i]++;
				tmp.pop();
			}
			else
				tmp.pop();
		}
	}

	for (int i = 0; i < weightOfItems.size(); i++)
	{
		if (tabOfIncides[i] == 0)
		{
			counter += weightOfItems[i];
			if (counter > maxMass)
				return i;
		}
	}

	delete[] tabOfIncides;
	return weightOfItems.size();
}
