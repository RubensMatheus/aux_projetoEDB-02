/*!
 * Several types of sorting algorithms that work on a data range.
 * @author Somebody
 * @date May 1st, 2023.
 * @file sorting.h
 */

#ifndef FUNCAO_H
#define FUNCAO_H

#include <sstream>
using std::ostringstream;
#include <iterator>
using std::next;
using std::ostream_iterator;
#include <functional>
using std::function;
using std::less;
#include <vector>
using std::vector;
#include <array>
using std::array;
#include <algorithm>
using std::copy;
using std::for_each;
using std::max_element;
#include <cmath>
using std::pow;
#include <string>
using std::string;
using std::to_string;

namespace sa { // sa = sorting algorithms
/// Prints out the range to a string and returns it to the client.
template <typename FwrdIt> std::string to_string(FwrdIt first, FwrdIt last) {
  std::ostringstream oss;
  oss << "[ ";
  while (first != last) {
    oss << *first++ << " ";
  }
  oss << "]";
  return oss.str();
}

//{{{ RADIX SORT
/*!
 * This function implements the Radix Sorting Algorithm based on the **less
 * significant digit** (LSD).
 *
 * @note There is no need for a comparison function to be passed as argument.
 *
 * @param first Pointer/iterator to the beginning of the range we wish to sort.
 * @param last Pointer/iterator to the location just past the last valid value
 * of the range we wish to sort.
 * @tparam FwrdIt A forward iterator to the range we need to sort.
 * @tparam Comparator A Comparator type function tha returns true if first
 * argument is less than the second argument.
 */
template <typename DataType, typename Comparator>
void radix(DataType *first, DataType *last, Comparator /*unused*/) {
  const DataType radix = 10;
    std::vector<std::vector<int>> buckets(radix);
    DataType exp = 1;
    // Encontra o maior valor no vetor
    // int *maxVal = std::max_element(first, last);
    DataType maxVal = *std::max_element(first, last);

    // Ordena os elementos em cada dígito
    while (maxVal / exp > 0){
        // Separa os elementos em baldes de acordo com o dígito atual
        for (DataType *p = first; p < last; ++p){
            DataType digit = (*p / exp) % radix;
            buckets[digit].push_back(*p);
        }

        // Copia os elementos dos baldes de volta para o vetor
        int *p = first;
        for (auto &bucket : buckets){
            for (DataType val : bucket){
                *p++ = val;
            }
            bucket.clear();
        }

        // Multiplica o exp por 10 para processar o próximo dígito
        exp *= radix;
    }
}
//}}} RADIX SORT

//{{{ INSERTION SORT
/// Implementation of the Insertion Sort algorithm.
template <typename DataType, typename Compare>
void insertion(DataType *first, DataType *last, Compare cmp) {
  DataType key;
    DataType *runner = std::next(first);
    while (runner != last){
        key = *runner;
        DataType *j = runner - 1;
        while (j >= first && cmp(key, *j)){
            *(j + 1) = *j;
            j--;
        }
        *(j + 1) = key;
        runner++;
    }
}
//}}} INSERTION SORT

//{{{ SELECTION SORT
template <typename DataType, typename Compare>
void selection(DataType *first, DataType *last, Compare cmp) {
  bool swaped = true;

    while (swaped){
        DataType *fast = first;
        swaped = false;
        while (fast != last - 1){
            if (cmp(*(fast + 1), *fast)){
                std::iter_swap(fast, (fast + 1));
                swaped = true;
            }
            fast++;
        }
    }
}
//}}} SELECTION SORT

//{{{ BUBBLE SORT
template <typename DataType, typename Compare>
void bubble(DataType *first, DataType *last, Compare cmp) {
  DataType *runner = first; 
    DataType *min;            
    while (runner != last - 1){
        DataType menor = INT_MAX; 
        DataType *j = runner;     
        while (j != last){
            if (cmp(*j, menor)){
                menor = *j;
                min = j;
            }
            j++;
        }
        std::iter_swap(runner, min);
        runner++;
    }
}
//}}} BUBBLE SORT

//{{{ SHELL SORT
template <typename DataType, typename Compare>
void shell(DataType *first, DataType *last, Compare cmp) {
  DataType len = last - first;

  for(DataType gap = len/2; gap > 0; gap/=2){
    for(DataType i = gap; i < len; i++){
      DataType temp = *(first+i);
      DataType j;
      for(j = i; j >= gap && *(first+(j-gap)) > temp; j -=gap){
        *(first+j) = *(first+(j-gap));
      }
      *(first+j) = temp;
    }
  }
}
//}}} SHELL SORT

//{{{ MERGE SORT
template <typename DataType, typename Compare>
void merge(DataType *first, DataType *mid, DataType *last, Compare cmp){
    DataType leftSize = mid - first ;
    DataType rightSize = last - mid;

    std::vector<DataType> vetleft;
    std::vector<DataType> vetright;

    for (auto i = 0; i < leftSize; i++){
        vetleft.push_back(*(first+i));
    }

    for (auto i = 0; i < rightSize; i++){
        vetright.push_back(*(mid+i));
    }

    DataType index1 = 0;
    DataType index2 = 0;
    DataType index = 0;

    while (index1 < leftSize && index2 < rightSize){
        if (cmp(vetleft[index1], vetright[index2])){
            *(first + index) = vetleft[index1];
            index1++;
        }else{
            *(first + index) = vetright[index2];
            index2++;
        }
        index++;
    }
    
    while (index1 < leftSize) {
        *(first + index) = vetleft[index1];
        index1++;
        index++;
    }

    while (index2 < rightSize) {
        *(first + index) = vetright[index2];
        index2++;
        index++;
    }
}

template <typename DataType, typename Compare>
void mergeSort(DataType *first, DataType *last, Compare cmp) {
  size_t len = std::distance(first, last);
    if (len > 1){
        DataType *mid = first+len/ 2;
        mergeSort(first, mid, cmp);
        mergeSort(mid, last, cmp);
        merge(first, mid, last, cmp);
    }
}
//}}} MERGE SORT

//{{{ QUICK SORT

template <typename DataType, typename Compare>
DataType* mediana(DataType* first, DataType* last, Compare cmp){
  DataType* A = first;
  DataType* B = first + (last - first) / 2;
  DataType* C = last;
  DataType* mediana = 0;

  if((*A < *B && *B < *C) || (*C < *B && *B <= *A)){
    mediana = B;
  } else if((*C <= *A && *A < *B) || (*B <= *A && *A<= *C)){
    mediana = A;
  } else{
    mediana = C;
  }
  return mediana;
}

template <typename DataType, typename Compare>
DataType* partition(DataType *first, DataType *last, Compare cmp){

  DataType* median = mediana(first, last - 1,cmp);
  
  std::swap(*median, *(last-1));
  
  DataType* pivot = last-1;
  DataType* i = first-1;

  for(DataType* j = first; j <= last-2; j++){
    if(cmp(*j, *pivot)){
      i++;
      std::swap(*i,*j);
    }
  }
  std::swap(*(i+1),*(last-1));
  return (i+1);
}


/// Quick sort implementation.
template <typename DataType, typename Compare>
void quick(DataType *first, DataType *last, Compare cmp) {
  if(std::distance(first,last) >= 2){
    DataType* pi = partition(first,last,cmp);
    quick(first,pi, cmp);
    quick(pi+1,last, cmp);
  }
}
//}}} QUICK SORT
};     // namespace sa
#endif // FUNCAO_H
