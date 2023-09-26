#ifndef DAYSIX_H
#define DAYSIX_H


#include <iostream>
#include <string>



class DaySix
{
    public:


        void solve();
        void solve_part_one();
        void solve_part_two();

        DaySix();
        DaySix(std::string);

    protected:

    private:
        std::string file_name;

        int number_of_shifts(std::string, int);

        struct Group {
            std::string value;
            bool has_repeats();
            
            Group(std::string);

            
        };;
};

#endif // DAYSIX_H
