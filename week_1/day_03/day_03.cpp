#include<algorithm>
#include<cctype>
#include<cstdlib>
#include<iostream>
#include<string>
#include<unordered_set>
#include<vector>
#include"utils.h"

// forward declaration
template <typename It, typename OutputIt>
void intersection(It first1, It last1, It first2, It last2, OutputIt d_first);

int main(){

    // read input into vector of strings.
    std::vector<std::string> delimiters = {};
    std::vector<std::string> input = read_input("input", delimiters);

    // tally of priorities
    int part1{0}, part2{0};

    // string of all duplicate items
    std::string duplicates;

    // find all duplicates
    for (auto& rucksack : input){

        // get iterator to midpoint
        auto midpoint = rucksack.begin() + rucksack.size()/2;

        // sort the first and second half
        std::sort(rucksack.begin(), midpoint);
        std::sort(midpoint, rucksack.end());

        // get intersection of first and second half
        intersection(rucksack.begin(), midpoint, midpoint, rucksack.end(), std::back_inserter(duplicates));

    }

    // calculate priority of duplicates
    for (const char& c : duplicates){ part1 += std::isupper(c) ? c - '&' : c - '`'; }

    std::cout << "Answer (part 1): " << part1 << std::endl;

    // string of each groups badge
    std::string badges, temp;

    // find the group badges
    for (std::size_t i=0; i<input.size(); i+= 3){

        // sort each members sack
        std::sort(input[i+0].begin(), input[i+0].end());
        std::sort(input[i+1].begin(), input[i+1].end());
        std::sort(input[i+2].begin(), input[i+2].end());

        // calculate intersections of member 1 & 2
        std::set_intersection(input[i].begin(), input[i].end(), input[i+1].begin(), input[i+1].end(), std::back_inserter(temp));

        // then find intersection with member 3
        intersection(temp.begin(), temp.end(), input[i+2].begin(), input[i+2].end(), std::back_inserter(badges));
    
        // clear temp for next group
        temp.clear();
    }

    // calculate priority of badges
    for (const char& c : badges){ part2 += std::isupper(c) ? c - '&' : c - '`'; }


    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}

// implementation of std::set_intersection which returns after
// the first intersection is found (since we know there is only one)
// (edited from cppreference possible implementation 1)
template <typename It, typename OutputIt>
void intersection(It first1, It last1, It first2, It last2, OutputIt d_first){

    while (first1 != last1 && first2 != last2){
        if (*first1 < *first2){ ++first1; }
        else {
            if (!(*first2 < *first1)){
                *d_first = *first1;
                return;
            }
            ++first2;
        }
    }
}
