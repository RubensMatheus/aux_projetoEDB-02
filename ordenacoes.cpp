#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>
#include <string>
#include <cstdarg>
#include "funcao.h"

using Compare = bool (*)(const int &, const int &);

bool compare(const int &a, const int &b) { return (a < b); }


struct ordenacoes
{
    std::vector<void (*)(int *, int *, Compare)> function_pointers = {sa::insertion, sa::selection, sa::bubble, 
    sa::shell, sa::quick, sa::mergeSort, sa::radix};
    
    std::vector<std::string> nomes = {"insertion", "selection", "bubble", "shell", "quick", 
    "merge", "radix"};

    std::vector<string> selecionaSorting;

    std::vector<void (*)(int *, int *, Compare)> newfunction_pointers;
    
    std::vector<std::string> newNomes;

    void teste(){
        for (auto x : selecionaSorting){
            for(int i = 0; i < 7; i++ ){
                if (x == nomes[i])
                {
                    newfunction_pointers.push_back(function_pointers[i]);
                    newNomes.push_back(nomes[i]);
                    break;
                }
            }  
        }   
    }
    
};



//=== CONSTANT DEFINITIONS.
const string insertion = "insertion";
const string selection = "selection";
const string bubble = "bubble";
const string shell = "shell";
const string quick = "quick";
const string merge = "merge";
const string radix = "radix";
//===============================

int main()
{
    int aux = 0;

    ordenacoes ordem;

    ordem.selecionaSorting = {insertion, selection, bubble, shell, quick, radix};

    ordem.teste();

    for(auto x : ordem.selecionaSorting){
        std::cout << x << " -- " ;
    }

    std::cout << "\n";

    std::vector<int> vetor = {3, 1, 4, 259, 122, 250, 98, 0, 66, 5};

    for (auto it : ordem.newfunction_pointers){

        std::vector<int> newVector(vetor.size());
        std::copy(vetor.begin(), vetor.end(), newVector.begin());

        std::cout << ordem.newNomes[aux] << std::endl;
        for (auto i : newVector){
            std::cout << i << " - ";
        }
        std::cout << "\n\n";

        it(newVector.data(), std::addressof(*newVector.end()), compare);

        for (auto i : newVector){
            std::cout << i << " - ";
        }
        std::cout << "\n\n";
        aux++;
    }

    return 0;
}