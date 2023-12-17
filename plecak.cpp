#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "json.hpp"
#include <fstream>
#include "Knapsack.h"
using namespace std;
using json = nlohmann::json;

using namespace std::chrono;

int main() {
    srand(time(0));
    int ilosc;
    cout<<"Podaj Ilosc przedmiotow"<<endl;
    cin>>ilosc;
    while(ilosc<1)
    {
        cout<<"Podaj naturalna ilosc przedmiotow"<<endl;
        cin>>ilosc;
    }
    float inflacja;
    cout<<"Podaj inflacje (wartosc bedzie w procentach czyli na przyklad 10 to 10%)"<<endl;
    cin>>inflacja;
    while(inflacja<0)
    {
        cout<<"Podaj dodatnia ilosc przedmiotow"<<endl;
        cin>>inflacja;
    }
    int capacity;
    cout<<"Podaj pojemnosc plecaka"<<endl;
    cin>>capacity;
    while(capacity<0)
    {
        cout<<"Podaj pojemnosc plecaka (minimum 10)"<<endl;
        cin>>capacity;
    }
    string czyBruteForceSTR;
    bool warunek=false;
    bool czyBF;
    while(warunek==false)
    {
        cout<<"Czy chcesz BruteForce (Y/N)"<<endl;
        cin>>czyBruteForceSTR;
        if(czyBruteForceSTR=="Y" || czyBruteForceSTR=="y")
        {
            warunek=true;
            czyBF=true;
        }
        else if(czyBruteForceSTR=="N" || czyBruteForceSTR=="n")
        {
            warunek=true;
            czyBF=false;
        }
    }

    generator(ilosc);
    json READ;
    std::ifstream fileR("data.json");
        if (fileR.is_open()) {
            fileR >> READ;
            fileR.close();
        }
        std::vector<Item> Plecak;
        if (READ.contains("items")) {
        for (const auto &item : READ["items"]) {
        Item newItem;
        newItem.weight = item["weight"];
        newItem.value = item["value"];
        newItem.JakiPrzedmiot = item["Item"];
        Plecak.push_back(newItem);
        }
        } 
        else 
        {
        std::cout << "Brak danych o przedmiotach w pliku JSON." << std::endl;
        }
    std::vector<Item> TempPlecak;
    ofstream outputGreedy("Greedy.txt");
    ofstream outputGreedyOrder("GreedyOrder.txt");
    ofstream outputBruteForce("BruteForce.txt");
    float maxValueGreedy;
    float maxValueGreedyOrder;
    float maxValueBruteForce;
    for(int i=3;i<=ilosc;i++)
    {
        TempPlecak.insert(TempPlecak.end(), Plecak.begin(), Plecak.begin()+i);
        auto startGreedy = high_resolution_clock::now();
        maxValueGreedy = knapsackGreedy(capacity, TempPlecak, inflacja);
        auto endGreedy = high_resolution_clock::now();
        auto durationGreedy = duration_cast<nanoseconds>(endGreedy-startGreedy);
        outputGreedy<<durationGreedy.count()<<endl;

        //TempPlecak.insert(TempPlecak.end(), Plecak.begin(), Plecak.end());
        auto startGO = high_resolution_clock::now();
        maxValueGreedyOrder = knapsackGreedyKolejnosc(capacity, TempPlecak, inflacja);
        auto endGO = high_resolution_clock::now();
        auto durationGreedyOrder = duration_cast<nanoseconds>(endGO-startGO);
        outputGreedyOrder<<durationGreedyOrder.count()<<endl;

        if(czyBF==true)
        {
        //TempPlecak.insert(TempPlecak.end(), Plecak.begin(), Plecak.end());
        auto startBF = high_resolution_clock::now();
        maxValueBruteForce = knapsackBruteForce(capacity, TempPlecak, inflacja);
        auto endBF = high_resolution_clock::now();
        auto durationBruteForce = duration_cast<nanoseconds>(endBF-startBF);
        outputBruteForce<<durationBruteForce.count()<<endl;
        }
        TempPlecak.clear();
    }
    outputGreedy.close();
    outputGreedyOrder.close();
    outputBruteForce.close();
    cout<<"Kuniec"<<endl;



    return 0;
}
