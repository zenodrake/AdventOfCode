#include "DayFive.h"
#include <stack>
#include <iostream>

int main() {

    string instruction_file = "/home/wrowsers/CppStuff/AdventOfCode/2022/Inputs/day_05";

    DayFive day(instruction_file);

    day.solve();
    //day.parse(instruction_file);

    //stack<int> thingus;

    //std::cout << "thingus initialized. current size: " << thingus.size() << std::endl;

    //thingus.push(1);
    //std::cout << "one number added. current size: " << thingus.size() << std::endl;

    //thingus.push(2);
    //thingus.push(8);

    //std::cout << "two numbers added. current size: " << thingus.size() << std::endl;

    //thingus.pop();
    //thingus.pop();

    //std::cout << "two numbers removed. current size: " << thingus.size() << std::endl;


    return 0;
}
