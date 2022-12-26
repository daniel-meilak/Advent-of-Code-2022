#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include"utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> delimiters = {};
    std::vector<std::string> input = read_input("input", delimiters);

    // tally for match scores
    int part1{0};
    int part2{0};

    // work through each match
    for (const auto& match : input){

        // verbose branch for each case
        if (match[0]=='A'){
            if      (match[2]=='X'){ part1 += 4; part2 += 3; }
            else if (match[2]=='Y'){ part1 += 8; part2 += 4; }
            else if (match[2]=='Z'){ part1 += 3; part2 += 8; }
        }
        else if (match[0]=='B'){
            if      (match[2]=='X'){ part1 += 1; part2 += 1; }
            else if (match[2]=='Y'){ part1 += 5; part2 += 5; }
            else if (match[2]=='Z'){ part1 += 9; part2 += 9; }
        }
        else {
            if      (match[2]=='X'){ part1 += 7; part2 += 2; }
            else if (match[2]=='Y'){ part1 += 2; part2 += 6; }
            else if (match[2]=='Z'){ part1 += 6; part2 += 7; }
        }
    }

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}
