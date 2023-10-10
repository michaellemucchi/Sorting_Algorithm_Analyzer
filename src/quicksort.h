// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector>

void QuickSort(std::vector<int>* numbers, int& comparisons, int& memory_access);
void QuickSortRecurse(std::vector<int>* numbers, int i, int k, int& comparisons, int& memory_access);
int Partition(std::vector<int>* numbers, int i, int k, int& comparisons, int& memory_access);