#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;



struct Rucksack {

    string pouch;
    string pouch1;
    string pouch2;

    void set_pouch(string s) {
        pouch = s;
    };

    void set_pouches(string p) {
        set_pouch(p);
        int len = p.length();
        int half = len/2;
        for (int i = 0; i < half; i++) {
            pouch1 += p[i];
            pouch2 += p[half+i];
        }
    };

    vector<string> common_items() {
        vector<string> rtn = {};

        int half = pouch1.length();
        string s, t = "";

        for (int i = 0; i < half; i++) {
            for (int j = 0; j < half; j++) {
                s = pouch1[i];
                t = pouch2[j];
                if (s == t) {
                    rtn.push_back(s);
                    break;
                }
            }
            if (s == t) {
                break;
            }
        }
        return rtn;
    };

    int get_priority(string s) {
        char c = s[0];

        if (c <= 97) {
            
            return ((c - 65) + 27);
        }
        else {
            return (c-96);
        }
        
    };


    int summed_priorities() {
        int total = 0;
        for (string s : common_items()) {
            //cout << s << endl;
            total += get_priority(s);
        }

        return total;
    };
    
};


class ElfGroup {

    public:
        char badge;
        int badge_val;
        void set_members(string e1, string e2, string e3) {
            _elf1 = e1;
            _elf2 = e2;
            _elf3 = e3;
            
            _find_triple_common();
        };

        ElfGroup() {};
    
        ElfGroup(string e1, string e2, string e3) {

            _elf1 = e1;
            _elf2 = e2;
            _elf3 = e3;
            
            _find_triple_common();
        }


        ElfGroup(Rucksack r1, Rucksack r2, Rucksack r3) {


            //_find_triple_common();
        }


        istream& operator>>(ElfGroup&);
        ostream& operator<<(ElfGroup&);

    private:
        string _elf1, _elf2, _elf3;


        int _get_priority(char& c) {

            if (c <= 97) {
                
                return ((c - 65) + 27);
            }
            else {
                return (c-96);
            }
            
        };


        //how would we do this but for a type of Rucksack?
        //we make sure that Rucksack can be referenced in the same was
        // as an array and has the find function
        //and I think if we make Rucsack a template class, we could do that
        void _find_triple_common() {
            vector<char> common_items;
            vector<char> triple_common;

            for (auto i = 0; i < _elf2.size(); i++) {
                char c =_elf2[i];
                int p = _elf1.find(c);
                if (p >= 0) { //match can be at 0th position too. garg
                    common_items.push_back(c);
                }
            }

            //cout << "number of shared elements: " << common_items.size() << endl;
            //for (auto i : common_items) { cout << i << " "; }
            //cout << endl;

            //cout << "first string: " << _elf1 << endl;
            //cout << "second string: " << _elf2 << endl;
            //cout << "third string: " << _elf3 << endl;

            //find only the common items in the third elf
            for (char c : common_items) {
                int p = _elf3.find(c);
                if (p >= 0) {
                    triple_common.push_back(c);
                }
            }


            //we know that elves will have at most one item in common, so
            // we don't need a loop to iterate them. we can simply refer to the
            // first item
            //cout << "items shared by all elves: " << triple_common[0] << endl;
            //cout << "number of shared elements: " << triple_common.size() << endl;
            badge = triple_common[0];
            badge_val = _get_priority(badge);
            
        };
    
};

istream& operator>>(istream& is, ElfGroup& eg) {

    //string a,b,c;
    //is >> a >> b >> c;

    //eg = ElfGroup(a,b,c);


    return is;    
}


ostream& operator<<(ostream& os, ElfGroup eg) {
    return os << "Badge: " << eg.badge << ". Value: " << eg.badge_val;
}


int main() {


    //a rucksack is a string of length 2n
    //the first items are rucksack[:2n/2]. second items are rucksack[2n/2+1:]

    //the items have at least one item in common
    //each item has priority. a=1, b=2, z=26. A=27, B=28, Z=52

    //find the item in common for each rucksack, then sum those items priorities

    string file = "/home/wrowsers/CppStuff/AdventOfCode/2022/Inputs/day_03";

    ifstream ist{file};


    vector<Rucksack> sacks;
    vector<ElfGroup> groups;
    string rucksack = "";     

    int i = 0;
    while(getline(ist, rucksack)) {
        Rucksack ruck;
        ruck.set_pouches(rucksack);
        sacks.push_back(ruck);
        //cout << rucksack << endl;
        //cout << sacks.size() << endl;

        //we could easily paramaterize the modulus, but we don't need to
        i = sacks.size();
        if (i % 3 == 0){
            
            //cout << "thingus: " << i << ". remainder: " << i % 3 << endl;
            string a,b,c = "";
            a = sacks[i-3].pouch;
            //cout << "first group: " << a << endl;

            b = sacks[i-2].pouch;
            //cout << "second group: " << b << endl;

            c = sacks[i-1].pouch;
            //cout << "third group: " << c << endl;
            
            ElfGroup e(a,b,c);
            //e.set_members(a,b,c);

            //cout << "is it getting here" << endl;
            //could do it this way but we don't need to have a variable group size
            //vector<Rucksack> 
            //for (int j = 0; j < i; j++) {
                
                //groups.push_back(sacks[j]);
            //}

            groups.push_back(e);
        }
    }

    cout << "number of groups: " << groups.size() << endl;


    int priorities = 0;
    int g_priorities = 0;

    for (Rucksack r : sacks) { priorities += r.summed_priorities(); }

    for (auto group : groups) {
        g_priorities += group.badge_val;
    }


    

    cout << "priorities for part 01: " << priorities << endl;
    cout << "priorities for part 02: " << g_priorities << endl;




    //for part two, we need to look at three lines at a time
    //line 1 = elf 01
    //line 2 = elf 02
    //line 3 = elf 03

    //find the common item in each group of three
    //then find the priority of that item
    //then sum the priorities across all groups

    //each elf can be carrying a different number of items, which makes things interesting

    //we can loop over the first two elves and find their common items
    //then we can loop over the last elf, but only compare its items to the common items

    //do this stuff with sets instead of vectors. it will make finding common items easier


    //string elfa = "vJrwpWtwJgWrhcsFMMfFFhFp";
    //string elfb = "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL";
    //string elfc = "PmmdzqPrVvPwwTWBwg";
    //ElfGroup eg1(elfa, elfb, elfc);

    //cout << "items shared by all elves: " << eg1.badge << endl;
    //cout << "priority: " << eg1.badge_val << endl;

    //cout << eg1 << endl;
    
    //string elf1 = "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn";
    //string elf2 = "ttgJtRGJQctTZtZT";
    //string elf3 = "CrZsJsPPZsGzwwsLwLmpwMDw";
    

    //ElfGroup eg(elf1, elf2, elf3);

    //we know that elves will have at most one item in common, so
    // we don't need a loop to iterate them. we can simply refer to the
    // first item
    //cout << "items shared by all elves: " << eg.badge << endl;
    //cout << "priority: " << eg.badge_val << endl;
    

    //cout << "position of stream cursor: " << ist.tellg() << endl;


    
    ////seek to the beginning of the file to read it again
    //ist.seekg(0, ist.beg);
    //cout << "sought" << endl;
    //cout << "new position: " << ist.tellg() << endl;

    
    //int c = ist.peek();

    //if (c != EOF) {
        //cout << "stuff to read" << endl;
        //cout << ist.peek() << endl;
    //}


    //ist.seekg(10);
    //c = ist.peek();
    //cout << c << endl;

    
    //vector<ElfGroup> groups;
    //ElfGroup group;

    //int i = 0;
    //string s;
    //while (ist >> s) {
        //cout << s << endl;
        ////if (i % 3 == 0) {
            
        ////}
    //}


    //for (ElfGroup eg : groups) {
        //cout << eg << endl;
    //}

    return 0;
}

