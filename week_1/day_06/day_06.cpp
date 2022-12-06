#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<unordered_map>
#include"utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> delimiters = {};
    std::string input = read_line("input", delimiters);

    // set to check 4 consecutive letters
    std::unordered_map<char,int> letters1, letters2;
    for (int i=0; i<4 ; i++){ letters1[input[i]]++; }
    for (int i=0; i<14; i++){ letters2[input[i]]++; }

    // marker for first 4 & 14 unique characters
    std::size_t part1{0}, part2{0};

    // work through input
    std::size_t i{0};
    while (!(part1 && part2)){

        // add the next letter
        letters1[input[i+4 ]]++;
        letters2[input[i+14]]++;

        // remove the oldest
        auto it1 = letters1.find(input[i]);
        auto it2 = letters2.find(input[i]);

        it1->second--;
        it2->second--;

        if (it1->second == 0){ letters1.erase(it1); }
        if (it2->second == 0){ letters2.erase(it2); }

        // if letters contains 4 elements, they are all different
        if (!part1 && letters1.size() == 4 ){ part1 = i+5 ; }
        if (!part2 && letters2.size() == 14){ part2 = i+15; }

        i++;
    }

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}
