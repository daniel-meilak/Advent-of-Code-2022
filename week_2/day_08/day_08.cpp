#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include"utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> delimiters = {};
    std::vector<std::string> input = read_input("input", delimiters);

    int width = static_cast<int>(input[0].size());
    int height = static_cast<int>(input.size());

    // number of visible trees 
    std::size_t part1{0}, part2{0};

    for (int i=1; i<width-1; i++){
        for (int j=1; j<height-1; j++){

            int tree_height = input[j][i], k;
            std::size_t scenic_score{1};
            bool visible{false};

            // look north
            k = j;
            while (--k > -1){
                if (input[k][i] >= tree_height){
                    scenic_score *= j-k;
                    break;
                }
            }
            if (k == -1){
                visible = true;
                scenic_score *= j;
            }

            // look south
            k = j;
            while (++k < height){
                if (input[k][i] >= tree_height){
                    scenic_score *= k-j;
                    break;
                }
            }
            if (k == height){
                visible = true;
                scenic_score *= input.size()-j-1;
            }

            // look west
            k = i;
            while (--k > -1){
                if (input[j][k] >= tree_height){
                    scenic_score *= i-k;
                    break;
                }
            }
            if (k == -1){
                visible = true;
                scenic_score *= i;
            }

            // look east
            k = i;
            while (++k < width){
                if (input[j][k] >= tree_height){
                    scenic_score *= k-i;
                    break;
                }
            }
            if (k == width){
                visible = true;
                scenic_score *= input[0].size()-i-1;
            }

            part1 += visible;
            if (scenic_score > part2){ part2 = scenic_score; }
        }
    }

    // add border trees 
    part1 += 2*input.size() + 2*(input[0].size()-2);

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}