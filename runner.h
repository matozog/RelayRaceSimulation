#pragma once
#include <vector>
#include <string>

using namespace std;


struct accidents
{
	int chanceOffalldown, chanceOfdrop, chanceOfexceedline,
		chanceOfslowstart;
};

class Runner
{
	static vector <string> names;
	static vector <string> countries;
	string _name,_country;
	int _morale, _condition, _stamina, _inteligence;
	int _weight, _aglity, _tiredness;
	double _max_speed, _acc, _road, _base_acc, _speedv0;
	double _time_base, _time, _penalty_time;
	accidents _chances;
	static void init();
	static void init1();
public:
	Runner();
	string name() { return _name; }
	string country() { return _country; }
	int morale() { return _morale; }
	int condition() { return _condition; }
	int tiredness() { return _tiredness; }
	int stamina() { return _stamina; }
	int aglity() { return _aglity; }
	int inteligence() { return _inteligence; }
	double max_speed() { return _max_speed; }
	double base_acc() { return _base_acc; }
	double acc() { return _acc; }
	double time() { return _time; }
	double speedv0() { return _speedv0; }
	double penalty_time() { return _penalty_time; }
	int weight();
	double road();
	void afterdrop();
	void change_morale();
	void change_tiredness();
	bool chancesOfdown();
	bool chancesOfdrop();
	bool chancesOfexceed();
	bool chancesOfstart();
	void add_road();
	void time_0();


	string description();
	//~Runner();
};