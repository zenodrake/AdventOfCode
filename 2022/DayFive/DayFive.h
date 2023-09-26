#ifndef DAY_FIVE_H
#define DAY_FIVE_H
#include <stack>
#include <vector>
#include <string>


using namespace std;
class DayFive
{
    public:

        void parse(string);

        DayFive();
        DayFive(string);

        void solve();


    protected:

    private:

        vector<stack<char>> stacks;
        vector<string> crates;
        vector<string> instructions;

        string file_name;


        void parse_instruction(string, int&, int&, int&);
        void read_file(string);
        void build_stacks(ifstream&);
        void build_instructions(ifstream&);
        void show_stacks();
        void clear_stacks();

};




#endif // DAY_FIVE_H
