#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include"utils.h"

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {",", "-"};
    std::vector<std::vector<int>> input = input_to_int_2D(read_input_2D("input", delimiters));

    // part1: contained in each other & part2: any overlap
    int part1{0}, part2{0};

    // work through all pairs
    for (const auto& line : input){
        if ((line[0] >= line[2] && line[1] <= line[3]) || (line[2] >= line[0] && line[3] <= line[1])){ part1++; }
        if ((line[0] <= line[2] && line[1] >= line[2]) || (line[2] <= line[0] && line[3] >= line[0])){ part2++; }
    }

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}
