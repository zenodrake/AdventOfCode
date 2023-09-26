
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;



class Choice {
public:
	string name;	
	int value;

	Choice to_beat() {
		Choice c;
		if (name == "Rock") { c = Choice("B"); }

		if (name == "Paper") { c = Choice("C"); }

		if (name == "Scissor") { c = Choice("A"); }

		return c;
	}

	Choice to_lose() {

		Choice c;
		if (name == "Rock") { c = Choice("C"); }

		if (name == "Paper") { c = Choice("A"); }

		if (name == "Scissor") { c = Choice("B"); }

		return c;
		
	}

	Choice to_draw() {

		Choice c;
		if (name == "Rock") { c = Choice("A"); }

		if (name == "Paper") { c = Choice("B"); }

		if (name == "Scissor") { c = Choice("C"); }

		return c;
	}

	Choice() {};
	
	Choice(string c) {
		if (c == "A") {
			name = "Rock";
			value = 1;
		}

		if (c == "B") {
			name = "Paper";
			value = 2;
		}

		if (c == "C") {
			name = "Scissor";
			value = 3;
		}

	}

	bool operator==(Choice& a) { return name == a.name; }

	bool operator==(string a) { return name == a; }

	bool operator<(Choice& a) { return value < a.value; }

	bool operator>(Choice& a) { return value > a.value; }

	ostream& operator<<(Choice& a);

	
};


ostream& operator<<(ostream& os, Choice& a) {
	return os << "Choice: " << a.name << ". Value: " << to_string(a.value);
}


class Result {
public:
	string name;
	int value;

	Result() : name("result"), value(-1) {};

	Result(string code) {
		if (code == "X") {
			name = "loss";
			value = 0;
		}

		if (code == "Y") {
			name = "draw";
			value = 3;
		}

		if (code == "Z") {
			name = "win";
			value = 6;
		}
	};

	Result(Choice c1, Choice c2) {
		if (c1 > c2) {
			name = "loss";
			value = 0;
		}

		if (c1 == c2) {
			name = "draw";
			value = 3;
		}

		if (c1 < c2) {
			name = "win";
			value = 6;
		}

		
	}

	bool operator==(string a) { return name == a; }

	bool operator==(Result a) { return name == a.name; }

	ostream& operator<<(Result& r);

};

ostream& operator<<(ostream& os, Result& r) {
	return os << "Result: " << r.name << ". Value: " << to_string(r.value);
}




//
class Round {

public:
	Choice opp;
	Choice you;
	int num;
	Result result;
	int score;

	Round() {};

	Round(int number, Choice c, Result r) {
		num = number;
		opp = c;
		result = r;
		_score();
	}

	Round(Choice c, Result r) {
		opp = c;
		result = r;
		_score();
	}


	Round(Choice c1, Choice c2) {
		opp = c1;
		you = c2;
		
		//result = Result(opp, you);
		_score();
	}

	ostream& operator<<(Round& r);

private:

	string _opp;
	string _you;
	

	void _score() {

		cout << "calling _score" << endl;

		string loss = "loss";
		string draw = "draw";
		string win = "win";
		string rock = "Rock";
		string paper = "Paper";
		string scissor = "Scissor";
		

		
		if (result == win) {
			cout << "win" << endl;	
			you = opp.to_beat();
		}

		if (result == loss) {
			cout << "loss" << endl;
			you = opp.to_lose();
		}

		if (result == draw) {
			cout << "draw" << endl;
			you = opp.to_draw();
		}

		cout << "The Result: ";
		cout << result << endl;
		

		score = you.value + result.value;
		
		cout << "opponent: " << opp << endl;
		cout << "your play: " << you << endl;
		
		cout << "the score is: " << score << endl;

	};
	
};


ostream& operator<<(ostream& os, Round& r) {
	string rtn = "Round: " + to_string(r.num) + ". Opponent Play: " + r.opp.name + ". Result: " + r.result.name;
	rtn += ". Score: " + to_string(r.score);
	return os << rtn;
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

	string opponent_choice = "";
	string result = "";

	Round r;

	
	int i = 0;
	while (ist >> opponent_choice >> result) {
		r.num = i++;
		Choice c(opponent_choice);
		Result res(result);

		r = Round(c, res);
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

	string rock = "A";
	string draw = "Y";

	string paper = "B";
	string loss = "X";

	string scissors = "C";
	string win = "Z";

	
	Choice a(scissors);
	Result x(win);

	Choice b = a.to_beat();
	Choice c = a.to_draw();
	Choice d = a.to_lose();

	cout << "original: " << a << endl;
	//cout << "to_beat: " << b << endl;
	//cout << "to_draw: " << c << endl;
	//cout << "to_lose: " << d << endl;

	Round r(0, a, x);

	cout << r << endl;


	

	//cout << x << endl;


	//for(string s : {"X", "Y", "Z"}) {
		//Result x(s);
		//cout << x << endl;
	//}


	//Round r(a, x);
	//cout << r << endl;
	
	//StrategyGuide s{"/home/wrowsers/CppStuff/AdventOfCode/2022/Inputs/day_02"};	
	//cout << s.total_score() << endl;
}
