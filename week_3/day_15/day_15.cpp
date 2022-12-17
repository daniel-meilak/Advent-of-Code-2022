#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<unordered_set>
#include<map>
#include"utils.h"
#include"point.h"
#include"interval_map.h"

// forward function declaration
interval_map_t<long> find_intervals(const std::vector<std::vector<int>>& input, long yLevel);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {"Sensor at x=", ", y=", ": closest beacon is at x="};
    std::vector<std::vector<int>> input = input_to_int_2D(read_input_2D("input", delimiters));

    interval_map_t<long> interval = find_intervals(input, 2'000'000);
 
    long part1 = interval.begin()->second - interval.begin()->first;

    long part2;
    for (long i=0; i<=4'000'000; i++){
        interval = find_intervals(input, i);

        if (interval.size() >= 2){
            part2 = i + (interval.begin()->second + 1)*4'000'000;
            break;
        }
    }

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}

interval_map_t<long> find_intervals(const std::vector<std::vector<int>>& input, long yLevel){

    interval_map_t<long> intervals;

    for (const auto& line : input){

        long x = line[0], y = line[1];

        // radius of source to beacon
        long radius  = manhattan(line[0],line[1],line[2], line[3]);

        // distance to y = 2'000'000
        long distance = std::abs(y - yLevel);

        long diff = distance - radius;

        if ( diff < 0){ intervals.insert(x+diff, x-diff); }
    }

    return intervals;

}