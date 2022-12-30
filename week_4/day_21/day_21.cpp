#include<complex>
#include<cstdlib>
#include<iomanip>
#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
#include"utils.h"

// forward function declaration
std::complex<double> calc(const std::string& name);

// read number with special case
auto stoc = [](const std::string& s){ return s=="-1i" ?  std::complex<double>(0,-1) : std::complex<double>(std::stoi(s),0); };

std::unordered_map<std::string, std::vector<std::string>> monkeys;

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {":", " "};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    // fill map with monkey equations
    for (const auto& line : input){ monkeys[line[0]] = std::vector<std::string>(line.begin()+1, line.end()); }

    std::complex<double> part1 = calc("root");

    // set up part 2, turn human into only imaginary component
    monkeys["root"][1] = "=";
    monkeys["humn"][0] = "-1i";

    std::complex<double> part2 = calc("root");

    std::cout << std::fixed << "Answer (part 1): " << static_cast<long long>(std::real(part1)) << std::endl;
    std::cout << std::fixed << "Answer (part 2): " << static_cast<long long>(std::real(part2)) << std::endl;

    return 0;
}

std::complex<double> calc(const std::string& name){

    const auto& equation = monkeys.at(name);

    // monkey calls out number
    if (equation.size() == 1){ return stoc(equation[0]); }
    // monkey calls out equation
    else {
        switch (equation[1][0]){
            case '+': return calc(equation[0]) + calc(equation[2]);
            case '-': return calc(equation[0]) - calc(equation[2]);
            case '*': return calc(equation[0]) * calc(equation[2]);
            case '/': return calc(equation[0]) / calc(equation[2]);
            // part 2
            default : {
                std::complex<double> left{calc(equation[0])}, right{calc(equation[2])};
                return std::real(left - right)/std::imag(left - right);
            }
        }
    }
}