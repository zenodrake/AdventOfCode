
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;


struct Elf {

	public:
		int num;

		vector<int> items;
		
		const int max_cal() { return *max_element(items.begin(), items.end()); };

		const int cals() {
			int s = 0;
			for (int i : items) {
				s += i;
			}
			return s;
		};

		bool operator< (Elf& e) {
			return cals() < e.cals();
		}

		bool operator+ (Elf& e) {
			return cals() + e.cals();
		}

		ostream& operator<<(Elf);
			
	
};

ostream& operator<<(ostream& os, Elf e) {
	return os << "Elf num: " << e.num << ". Calories: " << e.cals();
}

int main()
{

	vector<Elf> elves;

	//get the directory of the current file and derive the name of the input file from it
	ifstream calories("/home/wrowsers/CppStuff/AdventOfCode/2022/Inputs/day_01");

	string s = "";
	int cal = 0;
	int pack = 0;



	/*  part 1. find the elf carrying the most calories.
	 * elves are separated by new lines
	 * and they carry one snack per line
	 */
	//I don't like how I have to have two loops here
	while (getline(calories, s)) {
		Elf elf;
		elf.num = pack;
		while (s != "") {
				cal = stoi(s, nullptr);
				elf.items.push_back(cal);
				getline(calories, s);
		}
		elves.push_back(elf);
		pack++;
	}

	//this line uses a lambda function to specify a custom comparitor for the Elves
	Elf idk = *max_element(elves.begin(), elves.end(), [](Elf a, Elf b) { return a < b; });


	//part one solution. the Elf carrying the most calories
	cout << idk << endl;


	//part two solution is to calculate the calories carried by the top three elves.
	//we could sort the elves to do this then take the first (or last) three and sum them

	// sort the elves based on most calories
	//sort(elves.begin(), elves.end());
	sort(elves.begin(), elves.end(), [](Elf a, Elf b) { return b < a; });

	int top_three_cals = 0;

	for (int i = 0; i < 3; i++) {
		cout << elves[i].cals() << endl;
		top_three_cals += elves[i].cals();
	}

	

	cout << top_three_cals << endl;






	
	

	
	


	return 0;



}

