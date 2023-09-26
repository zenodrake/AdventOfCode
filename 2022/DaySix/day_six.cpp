#include "day_six.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;




DaySix::DaySix()
{
    //ctor
    
}


DaySix::DaySix(string file) {

    file_name = file;

}

DaySix::Group::Group(string v) : value(v) {}


bool DaySix::Group::has_repeats() {
    int last_pos = value.size();

    //start at the second position and compare at each letter in turn
    for (int i = 1; i < last_pos; i++) {
        //cout << "i:" << i  << endl;
        for (int j = i; j < last_pos; j++) {
            //this is where a debug statement might go          
            //cout << "j:" << j  << endl;
            //cout << "pos " << i-1 << " val: " << value[i-1] << endl;
            //cout << "pos " << j << " val: " << value[j] << endl;

            if (value[i-1] == value[j])
        
            return true;
        }
        
        
    }

    return false;
};


int DaySix::number_of_shifts(string buffer, int group_len) {

        
    int first_pos = 0;
    //int last_pos = 4;
    //int group_len = 4;
    //int group_len = 14;
    int num_shifts = first_pos + group_len; //number of shifts always counts the first four caharacters
    //cout << "buffer size: " << buffer.size() << endl;
    //cout << buffer.substr(first_pos, group_len);
    while (num_shifts < buffer.size()) {

        Group group {buffer.substr(first_pos, group_len)};
        //cout << "current group: " << group.value << endl;
        if (!group.has_repeats()) {
            break;
        }

        first_pos++;
        num_shifts++;

    }

    //cout << "number of shifts" << num_shifts << endl;


    //an alternative way? wouldn't be the best if we couldn't guarantee non repeats
    //while (group.has_repeats()) {

        //buffer.seekg(first_pos);
        //buffer.read(group, group_size);
        //first_pos++;
        
    //}

    return num_shifts;
}


void DaySix::solve_part_one() {

    //iterate over all lines
    cout << "file name: " << file_name << endl;

    cout << "--Start of Part One--" << endl;
    ifstream ist(file_name);
    string buffer = "";
    size_t group_len = 4;
    while (getline(ist, buffer)) {

        int line_shifts = number_of_shifts(buffer, group_len);
        cout << "number of shifts: " << line_shifts << endl;

    }

    ist.close();

    cout << "--End of Part One--\n\n" << endl;
    
}


void DaySix::solve_part_two() {

    //iterate over all lines
    cout << "file name: " << file_name << endl;

    cout << "--Start of Part Two--" << endl;
    ifstream ist(file_name);
    string buffer = "";
    size_t group_len = 14;
    while (getline(ist, buffer)) {

        int line_shifts = number_of_shifts(buffer, group_len);
        cout << "number of shifts: " << line_shifts << endl;

    }

    ist.close();

    cout << "--End of Part Two--\n\n" << endl;
    
}


void DaySix::solve() {
    solve_part_one();
    solve_part_two();

/* instructions
    //we are given a long string of characters
    //starting at the left, look at the first 4 characters.
    //then shift over one to the right and look at those characters
    //the task is to determine how many characters have been read
    // once there are no repeats

    //example. string = bvwbjplbgvbhsrlpgdmjqwftvncz
    //first 4 characters = bvwb. the 'b' repeats
    //shift one to right
    //new group of 4 = vwbj
    // there are no repeats. so we stop and count the number of characters read
    // here, it is 5. 4, for the first group, then 1 additional character


    //another example. string = zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw
    //first group = zcfz
    //shift. second group = cfzf
    //third group = fzfw
    //fourth group = zfwz
    //fifth group = fwzz
    //sixth group = wzzq
    //seventh group = zzqf
    //eigth group = zqfr. stop as group has no repeats
    //characters read = 11. 4 + 7 (because there were 7 shifts)

    //istringstream total_f {file_name};

    //istringstream total_buffer {"zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"};

    //char buff[4];
    //int group_size = 4;
    //int first_pos = 0;
    //int last_pos = 4;
    //total_buffer.seekg(first_pos);
    //total_buffer.read(buff, group_size);

    //cout << buff << endl;


    //string buffer = "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw";
    //Group group {buffer.substr(first_pos, last_pos)};
    //cout << "group: " << group.value << endl;
    //if (group.has_repeats())
        //cout << "p'twang!" << endl;

*/
    



/* test case blurb
this is where we'd write a test case. but as I've learned, just because you write
* a test doesn't mean it's testing waht you think it's testings.
* ensure one's tests are testing what one want.
*
* but i don't want to make a test right now


*/

    Group test_group {"whtt"};
    cout << "sloink " << test_group.has_repeats() << endl;
    
    



    
    

    

    
    

}
