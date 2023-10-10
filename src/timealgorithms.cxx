#include <algorithm>
#include <iostream>
#include <functional>
#include <fstream>
#include <vector>
#include <string>
#include "json.hpp"
#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"
#include <chrono>

class Clock {  // create a clock class to check runtime
  public:
    Clock() : result_time(0) {};  // constructor for the object

    void start_time() {  // start running the time
      start = std::chrono::high_resolution_clock::now();
    }

    void end_time() {  // end the time
      end = std::chrono::high_resolution_clock::now();
    }

    void calculate_time() {  // calculate the time used and store it in microseconds
      result_time = std::chrono::duration<double, std::micro>(end-start).count();
    }

    double get_time() {  // read out the time elapsed
      return result_time;
    }


  private:
    std::chrono::time_point <std::chrono::high_resolution_clock> start;  // time when clock starts
    std::chrono::time_point <std::chrono::high_resolution_clock> end;  // time when clock ends
    double result_time;  // total time elapsed

};


int main(int argc, char** argv) {

    std::ifstream file;  // create file object to read in data
    file.open(argv[1]);  // open our sample json file
    nlohmann::json MainObject;  // create object to store data in 
    if (file.is_open()) {  // if the file is open, do this
        file >> MainObject;   // transfer data into an object
    }  
    file.close();   // close the file to prevent memory leaks


    
    int num_samples = MainObject["metadata"]["numSamples"];   // create integer value for the length of the arrays to traverse
    int arraylength = MainObject["metadata"]["arraySize"];  // create integer value for number of samples to check
    std::string samplenum;  // create a string for sample number 

    // print out the title of each data point in below line
    std::cout << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTime,QuickSortCompares,QuickSortMemaccess" << std::endl;    
    for (int i = 1; i < num_samples + 1; i++) {  // iterate through all the samples 

        std::vector<int> insertion_sample;  // create vector to run insertion sort
        std::vector<int> merge_sample;  // create vector to run merge sort
        std::vector<int> quicksort_sample;  // create vector to run quicksort
        int insertion_comparison = 0;  // count the number of comparisons made in insertion sort
        int insertion_memory_access = 0; // count the number of memory accesses made in insertion sort
        Clock insertion_clock; // count the runtinme for insertion sort 
        int merge_comparison = 0;  // count the number of comparisons made in merge sort
        int merge_memory_access = 0;  // count the number of memory accesses made in merge sort
        Clock merge_clock;  // count the runtinme for merge sort 
        int quicksort_comparison = 0;  // count the number of comparisons made in quicksort
        int quicksort_memory_access = 0;  // count the number of memory accesses made in quicksort
        Clock quicksort_clock;  // count the runtinme for quicksort

        if (i >= 10) {  // formatting the sample part of the output object
                samplenum = "Sample";  // if the sample number is >= 10 then label it like so
            } else {
                samplenum = "Sample0";  // if the sample number is < 10 then label it like so
            }
        samplenum += std::to_string(i);  // add on the current sample number

        for (int j = 0; j < arraylength; j++) {  // iterate through the entire array fill in vectors to run sorting algorithms
            insertion_sample.push_back(MainObject[samplenum][j]);  // fill in insertion sort vector
            merge_sample.push_back(MainObject[samplenum][j]);  // fill in mergesort vector
            quicksort_sample.push_back(MainObject[samplenum][j]);  // fill in quicksort vector
        }

        insertion_clock.start_time();  // start insertion sort clock
        InsertionSort(&insertion_sample, insertion_comparison, insertion_memory_access);  // run insertion sort with comparisons and memory access parameter references
        insertion_clock.end_time();  // end insertion sort clock
        insertion_clock.calculate_time();  // calculate runtime of insertion sort
        double insertion_time = insertion_clock.get_time();  // store insertion sort runtime into a double in microseconds

        merge_clock.start_time();  // start merge sort clock
        MergeSort(&merge_sample, merge_comparison, merge_memory_access);  // run merge sort with comparisons and memory access parameter references
        merge_clock.end_time();  // end merge sort clock
        merge_clock.calculate_time();  // calculate runtime of merge sort
        double merge_time = merge_clock.get_time();  // store merge sort runtime into a double in microseconds

        quicksort_clock.start_time();  // start quick sort clock
        QuickSort(&quicksort_sample, quicksort_comparison, quicksort_memory_access);   // run quicksort with comparisons and memory access parameter references
        quicksort_clock.end_time();  // end quick sort clock
        quicksort_clock.calculate_time();  // calculate runtime of quicksort
        double quicksort_time = quicksort_clock.get_time();  // store quick sort runtime into a double in microseconds

        // print out required topics in CSV (comma seperated values) format
        std::cout << samplenum << "," << insertion_time << "," << insertion_comparison << "," <<  
                     insertion_memory_access << "," << merge_time << "," << merge_comparison << "," <<
                     merge_memory_access << "," << quicksort_time << "," <<  quicksort_comparison << "," <<
                     quicksort_memory_access << std::endl; 

    }

    return 0;
}