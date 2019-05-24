#ifndef KNAPSACKPROBLEMBYBACKTRACKING_H
#define KNAPSACKPROBLEMBYBACKTRACKING_H
#include <iostream>
#include <fstream>
#include <vector>
#include "Tree.h"
#include "libFiles.h"
#include "libExceptions.h"

/*
Funkcja wypelniajaca przyslane wektory wagami i cenami poszczegolnych rzeczy z pliku
@param inFile wejsciowy plik z ktorego czytamy wartosci
@param priceOfItems vector do ktorego dopisujemy ceny poszczegolnych rzeczy
@param massOfItems vector do ktorego dopisujemy wagi poszczegolnych rzeczy
*/
void fillVectorsWithDataFromFile(std::fstream & inFile, std::vector<int>& priceOfItems, std::vector<int>& weightOfItems);

/*
Funkcja glowna zajmujaca sie obliczaniem algorytmu z nawrotami dla problemu plecakowego 0-1
@param tree drzewo do wyszukiwan algorytmem z nawrotami
@param priceOfItems vector cen poszczegolnych rzeczy
@param massOfItems vector wag poszczegolnych rzeczy
@param maxMass masa plecaka, ktorej nie mozna przekroczyc
*/
void backtrackingAlgorithm(Tree &tree, std::vector<int>& priceOfItems, std::vector<int>& weightOfItems, int maxMass);

/*
Funkcja zwracajaca poziom przekroczenia sum wag (k)
@param massOfItems vector wag poszczegolnych rzeczy
@param maxMass masa plecaka, ktorej nie mozna przekroczyc
@param drzewo do wyszukiwan algorytmem z nawrotami
@return k - poziom po ktorym nastepuje przekroczenie sumy wag
*/
int getLevelOfExceedingSumOfWeight(std::vector<int>& weightOfItems, int maxMass, Tree &root);

#endif // !KNAPSACKPROBLEMBYBACKTRACKING_H

