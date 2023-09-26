#include "DayFive.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;



DayFive::DayFive()
{
    //ctor
}



DayFive::DayFive(string file) {
    file_name = file;
    stacks = vector<stack<char>> {9};
    //for (int i = 0; i < 9; i++) {
        //stacks.push_back(stack<char>());
    //}

}

void DayFive::solve() {


    string instruction = "";
    int quantity = 0;
    int from_vector = 0;
    int to_vector = 0;

    ifstream ist(file_name);

    cout << "number of stacks in stacks: " << stacks.size() << endl;
    build_stacks(ist);


    cout << "Starting Stack Position" << endl;
    show_stacks();


    while (getline(ist, instruction)) {


        parse_instruction(instruction, quantity, from_vector, to_vector);
        //cout << "instruction: " << instruction << endl;

        //this for loop will move the crates such that the top crate in
        // the from_stack becomes the bottom crate of the to_stack.
        //this is the method for solving part 1
        for (int i = 0; i < quantity; i++) {

            stacks.at(to_vector).push(stacks.at(from_vector).top());
            stacks.at(from_vector).pop();

            //show_stacks();
        }
    }

    cout << endl;
    cout << "Ending Stack Position" << endl;
    show_stacks();





    //part two, the crate mover moves the same number of crates
    //but preserves their positions
    // so the top crate in the from_stack also becomes the top
    // crate in the to_stack
    //we can do this with an intermediate step or having an intermediate stack.
    //we just use the first solution to the first part but move them to an intermediate stack first
    // alternatively, we could look at the STL and find a way to copy a portion of a stack on to another stack
    // if we were not using stacks, that would probably work


    cout << endl;
    cout << endl;
    cout << "START OF PART TWO" << endl;
    ist.clear(); //clear file position flag, otherwise we cannot seek back to the beginning
    ist.seekg(0);

    clear_stacks();
    cout << "stacks cleared" << endl;

    //show_stacks();
    //cout << "snth" << endl;
    cout << endl;


    build_stacks(ist);

    cout << "Starting Position" << endl;
    show_stacks();

    stack<char> mid_stack;

    while(getline(ist, instruction)) {
        parse_instruction(instruction, quantity, from_vector, to_vector);

        //cout << "instruction: " << instruction << endl;

        for (int i = 0; i < quantity; i++) {
            mid_stack.push(stacks.at(from_vector).top());
            stacks.at(from_vector).pop();

        }

        //cout << "breakages? " << endl;

        while (!mid_stack.empty()) {
            //cout << mid_stack.top() << "....";
            stacks.at(to_vector).push(mid_stack.top());
            mid_stack.pop();
        }
        //cout << endl;
    }


    cout << "Ending Position" << endl;
    show_stacks();
    cout << "END PART TWO" << endl;





    cout << endl;
    cout << "boink" << endl;

    return;


}


void DayFive::parse(string instruction) {

    int quantity = 0;
    int from_vector = 0;
    int to_vector = 0;
    parse_instruction(instruction, quantity, from_vector, to_vector);
}


void DayFive::parse_instruction(string inst, int& q, int& fv, int& tv) {

    //move 5 from 4 to 5
    //quantity is the first number.
    //from_vector is second number
    //to_vector is third number

    int q_start = 0;
    int q_end = 0;
    int fv_start = 0;
    int fv_end = 0;
    int tv_start = 0;
    int tv_end = inst.length();

    int quantity = 0;
    int from_vector = 0;
    int to_vector = 0;

    q_start = inst.find("move ", 0)+5;
    q_end = inst.find("from", 0)-1;
    fv_start = inst.find("from", 0)+5;
    fv_end = inst.find("to", 0)-1;
    tv_start = fv_end+3;
    tv_end = inst.length();


    q = stoi(inst.substr(q_start, q_end), nullptr);
    fv = stoi(inst.substr(fv_start, fv_end), nullptr)-1; //stacks numbers start at 1
    tv = stoi(inst.substr(tv_start, tv_end), nullptr)-1;

    //cout << "quantity: " << q << ". from vector: " << fv << ". to vector: " << tv << endl;

    return;

}


//sets ist to the first position of instructions in the file
//this is probably not the best
void DayFive::build_stacks(ifstream& ist) {

    int end_of_stacks = 0;
    int start_of_instructions = 0;
    int line_length = 0;
    int stack_num = 0;
    string instruction = "";


    getline(ist, instruction);
    line_length = instruction.size();
    //cout << "line length: " << line_length << endl;


    while (getline(ist, instruction)) {

        if (instruction == "") {

            //cout << ist.tellg() << endl;
            //put the position of the stream at the beginning of the last line of the stacks
            end_of_stacks = ist.tellg()-((line_length+1) * 2)-1;
            start_of_instructions = ist.tellg(); //add three to account for newline chars


            break;
        }
    }

    //cout << "end of stacks position: " << end_of_stacks << endl;
    //cout << "start of instructions position: " << start_of_instructions << endl;

    ist.seekg(end_of_stacks);
    //loop over the stacks in reverse order
    for (int i = end_of_stacks; i >= 0; i-=(line_length+1)) {
        //cout << "seeking" << endl;
        ist.seekg(i);
        //cout << "line starting position: " << ist.tellg() << endl;


        stack_num = 0;
        getline(ist, instruction);
        //cout << "line: " << instruction << endl;
        for (int j = 1; j < line_length; j+=4) {

            char crate = instruction.at(j);
            //cout << "stack num: " << stack_num << ". crate val: " << crate << endl;

            if (crate != ' ') {

                stacks.at(stack_num).push(crate);

            }
            //cout << "incrementing stack number" << endl;
            stack_num++;
        }
        //cout << "i value: " << i << endl;

    }

    //put the cursor at the start of the instructions
    ist.seekg(start_of_instructions);

}


void DayFive::show_stacks() {

    //cout << "showing stacks" << endl;

    int i = 1;
    //cout << "stacks size" << stacks.size() << endl;
    //cout << stacks[0].size() << endl;
    //cout << stacks[1].size() << endl;

    for (int i = 0; i < stacks.size(); i++) {
        stack<char>& s = stacks.at(i);
        cout << "stack num: " << i+1 << ". ";
        cout << "address: " << &s << ". ";
        cout << "size: " << s.size() << ". top crate: ";
        if (s.size() == 0) {
            cout << " " << endl;
        }
        else {
            cout << s.top() << endl;
        }
    }


    //for (stack s : stacks) {
        //cout << "stack num: " << i << ". ";
        //cout << "address: " << &s << ". ";
        //cout << "size: " << s.size() << ". top crate: ";
        //if (s.size() == 0) {
            //cout << " " << endl;
        //}
        //else {
            //cout << s.top() << endl;
        //}

        //i++;
    //}


}


void DayFive::clear_stacks() {

    for (int i = 0; i < stacks.size(); i++) {
        stack<char>& s = stacks.at(i);
        //cout << "address of s: " << &s << ". address of stack pos " << i << ": " << &(stacks.at(i)) << endl;
        while (!s.empty()) {
            //cout << "clearing " << s.top() << " from stack num " << i+1 << ". address: " << &s;

            s.pop();
            //cout << ". new stack size: " << s.size() << endl;
        }
    }


    //if we loop this way, s is appears to be a copy of each stack in stacks.
    // if we loop the above way, with references, stacks is actually affected
    //int i = 1;
    //for (stack s : stacks) {
        //while (!s.empty()) {
            //cout << "clearing " << s.top() << " from stack num " << i << ". address: " << &s;
            //s.pop();
            //cout << ". new stack size: " << s.size() << endl;
        //}
        //i++;
    //}

}
