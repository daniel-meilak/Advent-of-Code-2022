#include<array>
#include<cmath>
#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include"utils.h"

long long SNAFUtoDecimal(const std::string& SNAFU);
std::string DecimalToSNAFU(long long decimal);

static constexpr std::array<const char *,5> D = {{"=","-","0","1","2"}};

int main(){

    // read input into vector of strings.
    std::vector<std::string> delimiters = {};
    std::vector<std::string> input = read_input("input", delimiters);

    long long part1{0};
    // add up numbers
    for (const auto& line : input){ part1 += SNAFUtoDecimal(line); }

    std::cout << "Answer (part 1): " << DecimalToSNAFU(part1) << std::endl;
    std::cout << "Answer (part 2): " << "Done" << std::endl;

    return 0;
}

long long SNAFUtoDecimal(const std::string& SNAFU){
    long long answer{0};

    for (std::size_t i=0; i<SNAFU.size(); i++){
        switch (SNAFU[i]){
            case '2': answer +=  2*static_cast<long long>(std::pow(5,SNAFU.size()-i-1)); break;
            case '1': answer +=  1*static_cast<long long>(std::pow(5,SNAFU.size()-i-1)); break;
            case '0': break;
            case '-': answer += -1*static_cast<long long>(std::pow(5,SNAFU.size()-i-1)); break;
            case '=': answer += -2*static_cast<long long>(std::pow(5,SNAFU.size()-i-1)); break;
        }
    }

    return answer;
}

std::string DecimalToSNAFU(long long decimal){
    std::string answer;

    if (decimal != 0){
        long long quotient  = (decimal+2)/5;
        long long remainder = (decimal+2)%5;

        return DecimalToSNAFU(quotient).append(D[remainder]);
    }
    else { return "" ; }
}