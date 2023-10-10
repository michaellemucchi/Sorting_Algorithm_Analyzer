// Merge Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "mergesort.h"

void MergeSort(std::vector<int>* numbers, int& comparisons, int& memory_access) {
   MergeSortRecurse(numbers, 0, numbers->size() - 1, comparisons, memory_access);
}


void MergeSortRecurse(std::vector<int>* numbers, int i, int k, int& comparisons, int& memory_access) {
   int j = 0;
   
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSortRecurse(numbers, i, j, comparisons, memory_access);
      MergeSortRecurse(numbers, j + 1, k, comparisons, memory_access);
      
      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k, comparisons, memory_access);
   }
}

void Merge(std::vector<int>* numbers, int i, int j, int k, int& comparisons, int& memory_access) {
   int mergedSize = k - i + 1;                // Size of merged partition
   int mergePos = 0;                          // Position to insert merged number
   int leftPos = 0;                           // Position of elements in left partition
   int rightPos = 0;                          // Position of elements in right partition
   std::vector<int> mergedNumbers;
   mergedNumbers.resize(mergedSize);          // Dynamically allocates temporary array
                                              // for merged numbers
   
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if ((*numbers)[leftPos] < (*numbers)[rightPos]) {
         mergedNumbers[mergePos] = (*numbers)[leftPos];
         ++leftPos;
         comparisons++; // account for 1 comparison
         memory_access+=4; // add 4 memaccesses from if statement and in namespace
      }
      else {
         mergedNumbers[mergePos] = (*numbers)[rightPos];
         ++rightPos;
         comparisons++; // account for 1 comparison, if if statement doesn't run
         memory_access+=4; // add 4 memaccesses from if statement and in namespace
      }
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers[mergePos] = (*numbers)[leftPos];
      ++leftPos;
      ++mergePos;
      memory_access+=2; // account for 2 memaccesses
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers[mergePos] = (*numbers)[rightPos];
      ++rightPos;
      ++mergePos;
      memory_access+=2; // account for 2 memaccesses
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      (*numbers)[i + mergePos] = mergedNumbers[mergePos];
      memory_access+=2; // account for 2 memaccesses
   }
}