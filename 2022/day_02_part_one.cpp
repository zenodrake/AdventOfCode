
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;



enum Choice {Rock=1, Paper, Scissor};
enum Result {loss=0, draw=3, win=6};

//
class Round {

public:

	Round() {};
	
	Round(string opponent, string self) {
		num = 0;
		_opp = opponent;
		_you = self;
		
		Round::_set_choice();
		Round::_score();
	}

	Round(int number, string opponent, string self) {
		num = number;
		Round::_set_choice();
		Round::_score();
	}

	Choice opp;
	Choice you;
	int num;

	Result result;
	int score;


	ostream& operator<<(const Round&);
	istream& operator>>(const Round&);


private:

	string _opp;
	string _you;

	void _set_choice() {
		
		if (_opp == "A") { opp = Rock; }
		if (_opp == "B") { opp = Paper; }
		if (_opp == "C") { opp = Scissor; }

		if (_you == "X") { you = Rock; }
		if (_you == "Y") { you = Paper; }
		if (_you == "Z") { you = Scissor; }
		
	}

	void _score() {
		switch(opp) {
			
			case Rock:
				switch(you) {
					case Rock:
						result = draw;
						break;

					case Paper:
						result = win;
						break;

					case Scissor:
						result = loss;
						break;
				}
				
				score = result + you;
				break;

			case Paper:
				switch(you) {
					case Rock:
						result = loss;
						break;

					case Paper:
						result = draw;
						break;

					case Scissor:
						result = win;
						break;
				}

				score = result + you;
				break;

			case Scissor:
				switch(you) {
					case Rock:
						result = win;
						break;

					case Paper:
						result = loss;
						break;

					case Scissor:
						result = draw;
						break;
				}

				score = result + you;
				break;
		}
	};
	
	
};


ostream& operator<<(ostream& os,  Round& r) {
	string out = "Round num: " + to_string(r.num);
	out += ". Opponent's play: ";
	switch (r.opp) {
		case Rock:
			out += "Rock";
			break;
		case Paper:
			out += "Paper";
			break;
		case Scissor:
			out += "Scissor";
			break;
	}


	out += ". Your play: ";
	switch (r.you) {
		case Rock:
			out += "Rock";
			break;
		case Paper:
			out += "Paper";
			break;
		case Scissor:
			out += "Scissor";
			break;
		default:
			out += "thingus";
			break;
	}

	out += ". Result: ";
	switch (r.result) {
		case win:
			out += "win";
			break;
		case loss:
			out += "loss";
			break;
		case draw:
			out += "draw";
			break;
	}

	out += ". Score: " + to_string(r.score);
	
	return os << out << endl;
}


istream& operator>>(istream& is, Round& r) {

	string opp = "";
	string you = "";

	is >> opp >> you;
	r = Round(opp, you);	

	return is;
}

//template<class T>
class StrategyGuide {

public:

	StrategyGuide();
	StrategyGuide(string);

	void fill();
	void fill(string);

	int total_score();

	Round get_round(int round_num) { return _rounds[round_num]; };
	vector<Round> rounds() { return _rounds; };
	

private:

	int _num_rounds;
	vector<Round> _rounds;
	
};



StrategyGuide::StrategyGuide (string file) {

	//could check if file exists
	cout << file << endl;
	

	//get the directory of the current file and derive the name of the input file from it
	//ifstream ist("/home/wrowsers/CppStuff/AdventOfCode/2022/Inputs/" & file);
	ifstream ist{file};

	Round r;
	
	int i = 0;
	while (ist >> r) {
		r.num = i++;
		_rounds.push_back(r);
		//cout << r << endl;
	}
}

int StrategyGuide::total_score() {

	//want to use accumulate for the summing, but I haven't been focused enough to figure it out
	//return accumulate(_rounds.begin(), _rounds.end(), 0);

	int score = 0;
	for (Round r : _rounds) {
		score += r.score;
	}
	

	return score;
}

int main() {
	StrategyGuide s{"/home/wrowsers/CppStuff/AdventOfCode/2022/Inputs/day_02"};

	cout << s.total_score() << endl;
}
