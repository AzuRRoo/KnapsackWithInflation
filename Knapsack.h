#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "json.hpp"
#include "generator.h"
#include <fstream>

using namespace std;
using json = nlohmann::json;


bool compare(Item a, Item b) {
    double ratioA = (double)a.value / a.weight;
    double ratioB = (double)b.value / b.weight;
    return ratioA > ratioB;
}
bool compareByValue(const Item &a, const Item &b) {
    return a.value < b.value;
}

void displayItemsInKnapsack(const vector<Item>& items, const vector<Item>& knapsack) {
    cout << "Przedmioty w plecaku: " << endl;
    for (const auto& item : knapsack) {
        cout << "Przedmiot: " << item.JakiPrzedmiot << " Waga: " << item.weight << " Wartosc: " << item.value << endl;
    }
}

float knapsackGreedy(float capacity, vector<Item>& items, float inflacja) {
    sort(items.begin(), items.end(), compare);

    float totalValue = 0;
    float currentWeight = 0;
    vector<Item> includedItemsGreedy;

    for (int i = 0; i < items.size(); i++) {
        if (currentWeight + items[i].weight <= capacity && totalValue*(100-inflacja)/100 + items[i].value >= totalValue) {
            currentWeight += items[i].weight;
            totalValue = (totalValue*(100-inflacja)/100) + items[i].value;
            
            includedItemsGreedy.push_back(items[i]);
        }
    }
    // 
    //cout<<"WAGA GREEDY "<<currentWeight<<endl;
    //displayItemsInKnapsack(items, includedItemsGreedy);
    return totalValue;
}

float knapsackGreedyKolejnosc(float capacity, vector<Item>& items, float inflacja) {
    sort(items.begin(), items.end(), compare);

    float totalValue = 0;
    float currentWeight = 0;
    vector<Item> includedItemsGreedy;

    for (int i = 0; i < items.size(); i++) {
        if (currentWeight + items[i].weight <= capacity) {
            currentWeight += items[i].weight;
            totalValue = totalValue + items[i].value;
            includedItemsGreedy.push_back(items[i]);
        }
    }
    sort(includedItemsGreedy.begin(), includedItemsGreedy.end(), compareByValue);
    vector<Item> NewGreedy;
    totalValue=0;
    for(int i=0;i<includedItemsGreedy.size();i++)
    {
       if(totalValue < totalValue*(100-inflacja)/100 + includedItemsGreedy[i].value)
       {
        totalValue= (totalValue*(100-inflacja)/100) + includedItemsGreedy[i].value;
        NewGreedy.push_back(includedItemsGreedy[i]);
       } 
    }


    //displayItemsInKnapsack(items, NewGreedy);
    //displayItemsInKnapsack(items, includedItemsGreedy);
    return totalValue;
}
float knapsackBruteForce(float capacity, vector<Item>& items, float inflacja) {
    int n = items.size();
    

    float maxValue = 0;
    vector<Item> bestCombination;

    for (int i = 0; i < (1<<n); ++i) {
        
        float currentWeight = 0;
        float currentValue = 0;
        vector<Item> currentCombination;

        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                    currentWeight += items[j].weight;
                    currentValue += items[j].value;
                    currentCombination.push_back(items[j]);
                
            }
        }

        if (currentValue > maxValue && currentWeight<=capacity) {
            maxValue = currentValue;
            bestCombination = currentCombination;
        }
    }
    std::sort(bestCombination.begin(), bestCombination.end(), compareByValue);

    vector<Item> bestCombinationNew;
    float currentValueINF=0;
    int waga=0;
    for(int i=0;i<bestCombination.size();i++)
    {
       if(currentValueINF < currentValueINF*(100-inflacja)/100 + bestCombination[i].value)
       {
        bestCombinationNew.push_back(bestCombination[i]);
        currentValueINF= (currentValueINF*(100-inflacja)/100) + bestCombination[i].value;
        waga+=bestCombination[i].weight;
       } 
    }

    //cout<<"WAGA Z BRUTEFORCE "<<waga<<endl;
    //displayItemsInKnapsack(items, bestCombinationNew);
    return currentValueINF;
}