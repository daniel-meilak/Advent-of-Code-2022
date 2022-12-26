#include<cctype>
#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include"utils.h"

// forward function declaration
bool compare(std::string s1, std::string s2);

int main(){

    // read input into vector of strings.
    std::vector<std::string> delimiters = {"\n"};
    std::vector<std::string> input = read_input("input", delimiters);

    // sum of indices of correct pairs
    std::size_t part1{0};

    // work through all pairs
    for (std::size_t i=0; i<input.size(); i+=2){
        part1 += compare(input[i], input[i+1])*(1 + static_cast<int>(i/2));
    }

    // compare divisors to rest of input find their positions
    int n1{1}, n2{2};
    for (const auto& line : input){ n1 += compare(line, "[[2]]"); }
    for (const auto& line : input){ n2 += compare(line, "[[6]]"); }

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << n1*n2 << std::endl;

    return 0;
}

bool compare(std::string s1, std::string s2){
    
    // flag for adding brackets
    bool bracket1{false}, bracket2{false};

    auto it1 = s1.begin();
    auto it2 = s2.begin();

    while (it1 != s1.end() && it2 != s2.end()){

        // if both are numbers, compare numbers
        if (std::isdigit(*it1) && std::isdigit(*it2)){

            // get to end of value
            auto it3 = it1++;
            auto it4 = it2++;
            while (std::isdigit(*it1)){ it1++; }
            while (std::isdigit(*it2)){ it2++; }

            int value1 = std::stoi(std::string(it3,it1));
            int value2 = std::stoi(std::string(it4,it2));

            // add bracket if needed
            if (bracket1){
                it1 = s1.insert(it1, ']');
                bracket1 = false;
            }
            if (bracket2){
                it2 = s2.insert(it2, ']');
                bracket1 = false;
            }

            // if equal, continue comparing items
            if (value1 == value2){ continue; }
            // if value1 < value2 they are in the right order
            if (value1 < value2){ return true; }

            break;
        }
        // if both are '[', ']' or ',' continue
        else if (*it1 == *it2){
            it1++;
            it2++;
        }
        // if item one is shorter they are in the right order
        else if (*it1 == ']' || it1 == s1.end()){ return true; }
        // if item two is shorter they are in the wrong order
        else if (*it2 == ']' || it2 == s2.end()){ break; }
        // continue reading characters at ','
        else if (*it1 == ','){ it1++; }
        else if (*it2 == ','){ it2++; }
        // on uneven open bracket continue with flag to add close bracket
        else if (*it1 == '['){ it1++; bracket2 = true; }
        else if (*it2 == '['){ it2++; bracket1 = true; }
    }

    return false;
}