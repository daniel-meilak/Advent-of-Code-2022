#include<iostream>
#include<vector>
#include<string>
#include<iterator>
#include<deque>
#include<algorithm>
#include<cstdlib>
#include<cctype>
#include"utils.h"

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {"move ", " from ", " to "};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    // get number of stacks
    int n = 1 + (static_cast<int>(input[0][0].size()) - 3)/4;

    std::vector<std::deque<char>> stacks(n);


    size_t line{0};

    // read initial crate state
    while (!std::isdigit(input[line][0][1])){
        
        // read from n stacks
        for (int i=0; i<n; i++){

            char crate = input[line][0][4*i + 1];

            // if space not empty, assign to a stack
            if (crate != ' '){ stacks[i].push_front(crate); }
        }

        // move to next tier
        line++;
    }

    // save state for part 2
    std::vector<std::deque<char>> copy = stacks;
    
    // perform movements (part 1)
    int moves, from, to;
    for  (size_t i=line+2; i<input.size(); i++){

        moves = std::stoi(input[i][0]);
        from  = std::stoi(input[i][1])-1;
        to    = std::stoi(input[i][2])-1;

        // move the correct number of crates
        for (int j=0; j<moves; j++){
            
            // crate being moved
            char crate = stacks[from].back();

            // removed from first stack
            stacks[from].pop_back();

            // place on second stack
            stacks[to].push_back(crate);
        }
    }

    // get top of each stack (part 1)
    std::string part1;
    for (int i=0; i<n; i++){ part1.push_back(stacks[i].back()); }


    // recover initial state
    stacks = copy;

    // perform movements (part 2)   
    for  (size_t i=line+2; i<input.size(); i++){

        from  = std::stoi(input[i][1])-1;
        to    = std::stoi(input[i][2])-1;
        auto it = std::prev(stacks[from].end(), std::stoi(input[i][0]));

        // crates picked up
        std::deque<char> carry{it, stacks[from].end()};

        // remove from first stack
        stacks[from].erase(it, stacks[from].end());

        // add to second stack
        stacks[to].insert(stacks[to].end(), carry.begin(), carry.end());
    }

    // get top of each stack (part 2)
    std::string part2;
    for (int i=0; i<n; i++){ part2.push_back(stacks[i].back()); }

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}
