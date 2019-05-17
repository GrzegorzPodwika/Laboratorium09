#ifndef KNAPSACKPROBLEMBYBACKTRACKING_H
#define KNAPSACKPROBLEMBYBACKTRACKING_H
#include <iostream>
#include <fstream>
#include <vector>
#include "Tree.h"
#include "libFiles.h"
#include "libExceptions.h"

void menu();

void fillVectorsWithDataFromFile(std::fstream & inFile, std::vector<int>& priceOfItems, std::vector<int>& massOfItems);

void backtrackingAlgorithm(Tree &root, std::vector<int>& priceOfItems, std::vector<int>& massOfItems, int maxMass);

int getLevelOfExceedingSumOfWeight(std::vector<int>& massOfItems, int maxMass, Tree &root);

#endif // !KNAPSACKPROBLEMBYBACKTRACKING_H

