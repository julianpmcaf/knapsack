#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <algorithm>
using namespace std;

void readInput(int& maxWeight, string& filename, vector<int>& itemWeight, vector<int>& itemValue){
    ifstream file;
    int x;
    int y;
    
    file.open(filename);

    if (!file.is_open()){
        throw runtime_error("Could not open file " );

    }
    file >> maxWeight;
    while (file >> x >> y){
        itemWeight.push_back(x);
        itemValue.push_back(y);

    }
    
    file.close();
    
}

int KnapSack(int maxWeight, vector<int>& itemWeight, vector<int>& itemValue, const int i, vector<bool>& finalKnapsack, int totalKnapsackValue){
  
    if (itemValue.size() == i || maxWeight == 0){
        //cout << "yes4" << endl;
        return totalKnapsackValue;
    
    }
    else if (itemWeight.at(i) > maxWeight){
        finalKnapsack.at(i) = false;
        return KnapSack(maxWeight, itemWeight, itemValue, i + 1 , finalKnapsack, totalKnapsackValue);

    }

    else {

        int knapsackValueWithoutItem = KnapSack(maxWeight, itemWeight,itemValue,i+1, finalKnapsack, totalKnapsackValue);
        int knapsackValueWithItem = KnapSack(maxWeight - itemWeight.at(i), itemWeight, itemValue, i + 1, finalKnapsack, totalKnapsackValue + itemValue.at(i));
    

        if (knapsackValueWithItem > knapsackValueWithoutItem){
            finalKnapsack.at(i) = true;

            return KnapSack(maxWeight - itemWeight.at(i), itemWeight,itemValue,i+1, finalKnapsack, totalKnapsackValue + itemValue.at(i));

        }
        else{
            finalKnapsack.at(i) = false;
            return KnapSack(maxWeight, itemWeight, itemValue, i + 1, finalKnapsack, totalKnapsackValue);

        }
    }
    
}



int main(int argc, char* argv[]){
    try{
        if (argc < 2){
            cout << "No input filename given" << endl;
            return 0;

        }
        vector<int> itemWeight;
        vector<int> itemValue;
        
        int i = 0;
        int maxWeight;
        int totalValue = 0;
        int totalKnapsackValue = 0;
        string filename = argv[1];

        readInput(maxWeight,filename, itemWeight, itemValue);
        vector<bool> finalKnapsack(itemWeight.size());
        totalValue = KnapSack (maxWeight,itemWeight,itemValue, i, finalKnapsack, totalKnapsackValue);

        int totalWeight = 0;

        for (i = 0; i < itemWeight.size(); ++i)
        {
            if (finalKnapsack.at(i) == true){
                totalWeight += itemWeight.at(i);
                
            }
        }    
        
        cout << "With a capacity of "<< maxWeight << " kg, the total value is " << totalValue << " Eur, leading to a total weight of " << totalWeight << " kg" << endl << "The following items are included:";

        for (i = 0; i < itemWeight.size(); ++i)
        {
            if (finalKnapsack.at(i) == true){
                cout << " [" << itemWeight.at(i) << "," << itemValue.at(i) << "]" ;

            }
        } 
    }   
    
    catch(const std::exception& e)
    {
        std::cerr << e.what() << argv[1] <<'\n';

    }
    
}   