#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>

void firstQuestion(){

    std::ifstream file("Day_3_input.txt");

    if (!file) {
        std::cerr << "Error: Unable to open file " << std::endl;
        return;
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file.close();

    std::regex pattern(R"(mul\((\d+),(\d+)\))");
    std::sregex_iterator begin(content.begin(), content.end(), pattern);
    std::sregex_iterator end;

    long int result = 0;

    for (auto it = begin; it != end; ++it) {
        result += std::stol((*it)[1]) * std::stol((*it)[2]); 
    }

    std::cout << "Result " << result << std::endl;
}

void secondQuestion(){
    std::ifstream file("Day_3_input.txt");

    if (!file) {
        std::cerr << "Error: Unable to open file " << std::endl;
        return;
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file.close();

    // Regex to capture do(), don't(), and mul(num1,num2)
    std::regex pattern(R"((do\(\))|(don't\(\))|mul\((\d+),(\d+)\))");

    std::sregex_iterator begin(content.begin(), content.end(), pattern);
    std::sregex_iterator end;

    long int result = 0;
    bool enabled = true;

    for (auto it = begin; it != end; ++it) {
        if ((*it)[1].matched) {
            enabled = true; // do()
        } else if ((*it)[2].matched) {
            enabled = false; // don't()
        } else if ((*it)[3].matched && (*it)[4].matched && enabled) {
            result += std::stol((*it)[3]) * std::stol((*it)[4]); 
        }
    }
    std::cout << "Result " << result << std::endl;
}

int main(){
    firstQuestion();
    secondQuestion();
}