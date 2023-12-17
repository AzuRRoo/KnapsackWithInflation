#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "json.hpp"
#include <fstream>
using namespace std;
using json = nlohmann::json;



struct Item {
    int weight;
    int value;
    string JakiPrzedmiot;
};

string generateItemType()
{
    vector<string> itemType = {"Pierscionek","Lancuszek","Kolczyk","Naszyjnik","Wisiorek","Zegarek","brelok"};
    vector<string> itemMaterial = {"Srebrny","Zloty","Platynowy","Diamentowy","Bursztynowy","Szmaragdowy","Onyksowy","Rubinowy","Szafirowy","Jadeitowy"};
    int randomItemType = rand() % itemType.size();
    int randomItemMaterial = rand() % itemMaterial.size();
    string combinedItem = itemMaterial[randomItemMaterial] + " " + itemType[randomItemType];
    return combinedItem;

}
void generator(int ilosc)
{
vector<Item> items;
for (int i = 0; i < ilosc; ++i) {
        Item newItem;
        newItem.weight = rand() % 20 + 1;
        newItem.value = rand() % 20 + 1;
        newItem.JakiPrzedmiot = generateItemType();
        items.push_back(newItem);
    }
json data;
    for (const auto &item : items) {
        json itemData = {
            {"weight", item.weight},
            {"value", item.value},
            {"Item", item.JakiPrzedmiot}
        };
        data["items"].push_back(itemData);
    }
    std::ofstream file("data.json");
    if(file.is_open())
    {
        file<<std::setw(4)<<data<<std::endl;
        file.close();
        std::cout<<"Zapisano dane"<<std::endl;
    }
    else
    {
        std::cout<<"Nie można otworzyć pliku do zapisu"<<std::endl;
    }
}
