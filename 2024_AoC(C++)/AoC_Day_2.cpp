#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

std::pair<bool, std::pair<int, int>> checkAscending(std::vector<int>& v){
    for(int i = 0; i < v.size() - 1; ++i){
        if((v[i + 1] < v[i] ) || (v[i + 1] - v[i] == 0)){
            return {false, {i, i + 1}};
        }
    }
    return {true, {0, 0}};
}

std::pair<bool, std::pair<int, int>> checkDescending(std::vector<int>& v){
    for(int i = 0; i < v.size() - 1; ++i){
        if((v[i + 1] > v[i] ) || (v[i + 1] - v[i] == 0)){
            return {false, {i, i + 1}};
        }
    }
    return {true, {0, 0}};
}

std::pair<bool, std::pair<int, int>> checkDifference(std::vector<int>& v){
    for(int i = 0; i < v.size() - 1; ++i){
        if(std::abs(v[i] - v[i + 1]) < 1 || std::abs(v[i] - v[i + 1]) > 3){
            return {false, {i, i + 1}};
        }
    }
    return {true, {0, 0}};
}

void firstQuestion(){
    // Open file
    std::ifstream inputFile("Day_2_input.txt");
    
    if (!inputFile) {
        std::cerr << "Unable to open the file.\n";
        return;
    }

    std::vector<std::vector<int>> list_1;
    std::string line;

    int totalSafe = 0;
    while (std::getline(inputFile, line)){
        std::vector<int> row;
        std::istringstream stream(line);
        int number;

        // Read each number in the line
        while (stream >> number) {
            row.push_back(number);
        }

        bool isSafe = false;
        bool isAscending = checkAscending(row).first;
        bool isDescending = checkDescending(row).first;
        bool isValidDifference = checkDifference(row).first;

        if ((isAscending && isValidDifference) || (isDescending && isValidDifference)){
            isSafe = true;
        }

        if(isSafe){
            ++totalSafe;
        }
    }

    inputFile.close();
    std::cout << "Total safe: " << totalSafe << std::endl;
}

std::pair<bool, std::pair<int, int>> checkAscendingAfterRemove(std::vector<int>& v, int firstIndexToRemove, int secondIndexToRemove){
    std::vector<int> tempVecOne = v;
    std::vector<int> tempVecTwo = v;

    tempVecOne.erase(tempVecOne.begin() + firstIndexToRemove);
    bool isValidDifference_1 = checkDifference(tempVecOne).first;

    tempVecTwo.erase(tempVecTwo.begin() + secondIndexToRemove);
    bool isValidDifference_2 = checkDifference(tempVecTwo).first;

    auto firstResult = checkAscending(tempVecOne);
    auto secondResult = checkAscending(tempVecTwo);

    if(firstResult.first  && isValidDifference_1){
        v.erase(v.begin() + firstIndexToRemove);
        return firstResult;
    }
    else if(secondResult.first  && isValidDifference_2){
        v.erase(v.begin() + secondIndexToRemove);
        return secondResult;
    }
    else{
        return {false, {0, 0}};
    }
}

std::pair<bool, std::pair<int, int>> checkDescendingAfterRemove(std::vector<int>& v, int firstIndexToRemove, int secondIndexToRemove){
    std::vector<int> tempVecOne = v;
    std::vector<int> tempVecTwo = v;

    tempVecOne.erase(tempVecOne.begin() + firstIndexToRemove);
    bool isValidDifference_1 = checkDifference(tempVecOne).first;

    tempVecTwo.erase(tempVecTwo.begin() + secondIndexToRemove);
    bool isValidDifference_2 = checkDifference(tempVecTwo).first;

    auto firstResult = checkDescending(tempVecOne);
    auto secondResult = checkDescending(tempVecTwo);

    if(firstResult.first && isValidDifference_1){
        v.erase(v.begin() + firstIndexToRemove);
        return firstResult;
    }
    else if(secondResult.first && isValidDifference_2){
        v.erase(v.begin() + secondIndexToRemove);
        return secondResult;
    }
    else{
        return {false, {0, 0}};
    }
}

bool checkValidDifferenceAfterRemove(std::vector<int>& v, int firstIndexToRemove, int secondIndexToRemove){
    std::vector<int> tempVecOne = v;
    std::vector<int> tempVecTwo = v;

    tempVecOne.erase(tempVecOne.begin() + firstIndexToRemove);
    tempVecTwo.erase(tempVecTwo.begin() + secondIndexToRemove);

    auto firstResult = checkDifference(tempVecOne);
    auto secondResult = checkDifference(tempVecTwo);

    if(firstResult.first){
        v.erase(v.begin() + firstIndexToRemove);
        return firstResult.first;
    }
    else if(secondResult.first){
        v.erase(v.begin() + secondIndexToRemove);
        return secondResult.first;
    }
    else{
        return false;
    }
}

void secondQuestion(){
    // Open file
    std::ifstream inputFile("Day_2_input.txt");
    
    if (!inputFile) {
        std::cerr << "Unable to open the file.\n";
        return;
    }

    std::vector<std::vector<int>> list_1;
    std::string line;

    int totalSafe = 0;
    int debugLine = 0;
    while (std::getline(inputFile, line)){
        std::vector<int> row;
        std::istringstream stream(line);
        int number;

        // Read each number in the line
        while (stream >> number) {
            row.push_back(number);
        }

        bool isSafe = false;
        auto firstResult = checkAscending(row);
        auto secondResult = checkDescending(row);
        auto thirdResult = checkDifference(row);

        bool isAscending = firstResult.first;
        bool isDescending = secondResult.first;
        bool isValidDifference = thirdResult.first;

        if ((isAscending && isValidDifference) || (isDescending && isValidDifference)){
            isSafe = true;
        }
        else if(isAscending && !isValidDifference){
            int firstDiffIndex = thirdResult.second.first;
            int secondDiffIndex = thirdResult.second.second;
            std::vector<int> temp = row;
            bool isAscending_2 = checkAscendingAfterRemove(temp, firstDiffIndex, secondDiffIndex).first;
            bool secondValidDifferenceCheck = checkValidDifferenceAfterRemove(temp, firstDiffIndex, secondDiffIndex);
            if(isAscending_2 && secondValidDifferenceCheck){
                isSafe = true;
            }
        }
        else if(isDescending && !isValidDifference){
            int firstDiffIndex = thirdResult.second.first;
            int secondDiffIndex = thirdResult.second.second;
            std::vector<int> temp = row;
            bool isDescending_2 = checkDescendingAfterRemove(temp, firstDiffIndex, secondDiffIndex).first;
            bool secondValidDifferenceCheck = checkValidDifferenceAfterRemove(temp, firstDiffIndex, secondDiffIndex);
            if(isDescending_2 && secondValidDifferenceCheck){
                isSafe = true;
            }
        }

        if(!isAscending){
            int firsAscIndex = firstResult.second.first;
            int secondAscIndex = firstResult.second.second;

            auto secondAscendingCheck = checkAscendingAfterRemove(row, firsAscIndex, secondAscIndex);

            if((secondAscendingCheck.first && isValidDifference)){
                isSafe = true;
            }
            else if(!isValidDifference){
                auto secondValidDifferenceCheck = checkDifference(row);
                if(secondAscendingCheck.first && secondValidDifferenceCheck.first){
                    isSafe = true;
                }
            }
        }

        if(!isDescending){
            int firstDescIndex = secondResult.second.first;
            int secondDescIndex = secondResult.second.second;

            auto secondDescendingCheck = checkDescendingAfterRemove(row, firstDescIndex, secondDescIndex);

            if((secondDescendingCheck.first && isValidDifference)){
                isSafe = true;
            }
            else if(!isValidDifference){
                auto secondValidDifferenceCheck = checkDifference(row);
                if(secondDescendingCheck.first && secondValidDifferenceCheck.first){
                    isSafe = true;
                }
            }
        }

        if(isSafe){
            ++totalSafe;
            ++debugLine;
            std::cout << debugLine << " - GOOD!" << std::endl;
        }
        else{
            ++debugLine;
            std::cout << debugLine << " - BAD!" << std::endl;
        }
    }

    inputFile.close();
    std::cout << "Total safe: " << totalSafe << std::endl;
}

int main(){
    firstQuestion();
    secondQuestion();
}