#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <set>

void firstQuestion(){
    // Open file
    std::ifstream inputFile("input.txt");
    
    if (!inputFile) {
        std::cerr << "Unable to open the file.\n";
        return;
    }

    // Create 2 vectors to store the inputs
    std::vector<int> list_1, list_2;
    

    // Read each row 
    int num1, num2;
    while (inputFile >> num1 >> num2) {
        list_1.push_back(num1);
        list_2.push_back(num1);
    }

    inputFile.close();

    // Sort vectors
    std::sort(list_1.begin(), list_1.end());
    std::sort(list_2.begin(), list_2.end());

    int total = 0;

    for(int i = 0; i < list_1.size(); ++i){
        total += std::abs(list_1[i] - list_2[i]);
    }

    std::cout << "Total: " << total << std::endl;
}

void secondQuestion(){
    // Open file
    std::ifstream inputFile("input.txt");
    
    if (!inputFile) {
        std::cerr << "Unable to open the file.\n";
        return;
    }

    // Create vectors
    std::vector<int> list_1, list_2;

    // Read each row 
    int num1, num2;
    while (inputFile >> num1 >> num2) {
        list_1.push_back(num1);
        list_2.push_back(num2);
    }

    inputFile.close();

    // Sort vectors
    std::sort(list_1.begin(), list_1.end());
    std::sort(list_2.begin(), list_2.end());

    int result = 0;

    for(int i = 0; i < list_1.size(); ++i){
        int count = 0;
        for(int j = 0; j < list_2.size(); ++j){
            if(list_2[j] == list_1[i]){
                ++count;
            }
            else{
                result += (list_1[i] * count);
                count = 0;
            }
        }
    }

    std::cout << "Result: " << result << std::endl;
}


int main(){
    firstQuestion();
    secondQuestion();
}