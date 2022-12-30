#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<iterator>
#include<list>
#include<numeric>
#include<string>
#include<vector>
#include"utils.h"

static constexpr long decryptionKey{811589153};

long mix(std::list<long> positions, std::vector<long>& input, bool part1);

int main(){

    // read input into vector of strings.
    std::vector<std::string> delimiters = {};
    std::vector<long> input = input_to_int<long>(read_input("input", delimiters));

    // list of original positions
    std::list<long> positions(input.size());
    std::iota(positions.begin(), positions.end(), 0);

    std::cout << "Answer (part 1): " << mix(positions, input, true ) << std::endl;
    std::cout << "Answer (part 2): " << mix(positions, input, false) << std::endl;

    return 0;
}

// (note using part2 permanently changes input)
long mix(std::list<long> positions, std::vector<long>& input, bool part1){

    if (!part1){ std::ranges::transform(input, input.begin(), [](auto i){ return i*= decryptionKey; }); }

    for (int i=0; i<(part1? 1 : 10); i++){

        for (long j=0; j<static_cast<long>(input.size()); j++){
            
            auto it = std::ranges::find(positions, j);
            std::size_t new_index = mod(static_cast<long>(std::distance(positions.begin(), it)) + input[j], static_cast<long>(input.size()-1));

            positions.erase(it);
            positions.insert(std::next(positions.begin(), new_index), j);
        }
    }

    // get the index of 0 in input, then find the index of [index of zero] in positions
    std::size_t zero_pos = std::distance(positions.begin(), std::ranges::find(positions ,std::distance(input.begin(), std::ranges::find(input, 0))));
    
    return input[*std::next(positions.begin(), mod(zero_pos+1000,input.size()))] + 
           input[*std::next(positions.begin(), mod(zero_pos+2000,input.size()))] +
           input[*std::next(positions.begin(), mod(zero_pos+3000,input.size()))];
}