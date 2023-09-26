#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>


using namespace std;



//if we do test driven development, we write a test for every function we write
//before we write the function itself

/*
 * two columns of numbers
 * first column is a range(start, end). the second column is also a range
 * in each row, the first range can contain the second range or it cannot.
 * a range contains another range if the first.start <= second.start and first.end >= second.end
 *
 * example range: 23-36,6-10
 *
 * how many rows or pairs of ranges have a range fully contained in the other
 *
 */

class Range {
    public:
        int start() { return _start; }
        int end() { return _end; }
        int distance() { return _end - _start; };

        bool contains(Range& r) {
            if (_start <= r.start() && _end >= r.end() ) { return true; }

            return false;
        };

        bool contained_in(Range& r) {
            if (r.start() <= _start && r.end() >= _end ) { return true; }

            return false;

        };

        bool overlaps(Range&r ) {

            //2-4, 6-8

            //6-8, 2-4
            if (_end >= r.start() && _start <= r.end()) { return true; }
            return false;
        };

        Range() {};


        Range(int s, int e) {
            _start = s;
            _end = e;
        }

        Range(string r) {
            //split the string on the - character
            // first to first and second to second


            int separator = 0;
            separator = r.find("-");

            //cout << "first part:" << r.substr(0,separator);
            //cout << ". second part:" << r.substr(separator+1, r.length()) << "." << endl;
            _start = stoi(r.substr(0,separator), nullptr);
            _end = stoi(r.substr(separator+1, r.size()), nullptr);

        };


        ostream& operator <<(Range& r);

    private:
        int _start = 0;
        int _end = 0;

};


ostream& operator<<(ostream& os, Range& r) {
    return os << "Start: " << r.start() << ". End: " << r.end() << ". Distance: " << r.distance();
}



class Assignment {
    public:

        Range& first() { return _first; };
        Range& second() { return _second; };

        bool fully_contained() {
            if (_first.contains(_second) || _second.contains(_first)) { return true; }

            return false;
        };

        bool overlap() {
            if (_first.overlaps(_second)) { return true; }
            return false;
        };

        Assignment() {};

        Assignment(string a) {

            int sep = 0;
            sep = a.find(",");

            _first = Range(a.substr(0, sep));
            _second = Range(a.substr(sep+1, a.length()));
        }


        istream& operator >>(Assignment&);

    private:
        Range _first;
        Range _second;
};

istream& operator >>(istream& is, Assignment& m) {
    string a;
    is >> a;
    m = Assignment(a);
    return is;
}




//not sure how to do this effectively
class RangeTest {

};

int main() {


    string file = "/home/wrowsers/CppStuff/AdventOfCode/2022/Inputs/day_04";

    ifstream ist(file);

    vector<Assignment> ments;

    string assignment = "";
    int num_fully_contained = 0;
    int num_overlaps = 0;
    while (getline(ist, assignment)) {

        Assignment a(assignment);
        num_fully_contained += a.fully_contained();
        num_overlaps += a.overlap();
        ments.push_back(a);


        //could also do this and not need the initial ctor, but with construction
        // of the Assignment first, we only need one loop
        //ments.emplace_back(Assignment(assignment));
    }


    cout << "number of assignments: " << ments.size() << endl;
    cout << "number which are fully contained: " << num_fully_contained << endl;
    cout << "number of overlaps: " << num_overlaps << endl;


    //show which ones are fully contained
    //for (auto a : ments) {
        //if (a.fully_contained()) {
            //cout << a.first() << "~~~~~" << a.second() << endl;
        //};
    //}



    return 0;
}
