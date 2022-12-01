#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<climits>
#include<set>
#include<iterator>
#include<functional>
#include"utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> delimiters = {};
    std::vector<std::string> input = read_input("input", delimiters);

    int tally{0};

    // sorted calorie totals
    std::multiset<int, std::greater<int>> calorie_totals;

    // loop through input and tally up each elfs calories
    for (const auto& cal : input){

        // on empty line, reset tally for next elf
        if (cal.empty()){
            calorie_totals.insert(tally);
            tally   = 0;
            continue;
        }

        // add next item to calories tally
        tally += std::stoi(cal);
    }

    std::cout << "Answer (part 1): " << *calorie_totals.begin() << std::endl;
    std::cout << "Answer (part 2): " << *calorie_totals.begin() + *std::next(calorie_totals.begin()) + *std::next(calorie_totals.begin(),2) << std::endl;

    return 0;
}
