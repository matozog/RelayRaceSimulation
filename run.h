#pragma once
#include <vector>
#include <string.h>

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
	float _time_base, _time;
	accidents _chances;
	static void init();
	static void init1();
public:
	Runner();
	string name() { return _name; }
	string country() { return _country; }
	void random_country();
	int morale() { return _morale; }
	int condition() { return _condition; }
	int tiredness();
	int stamina() { return _stamina; }
	int weight();
	int aglity();
	int change_morale();
	int inteligence() { return _inteligence; }
	double max_speed() { return _max_speed; }
	double base_acc() { return _base_acc; }
	double acc();
	double road();
	double time();
	double speedv0();
	void chancesOfdown();
	void chancesOfdrop();
	void chancesOfexceed();
	void chancesOfstart();
	//double time_base() { return _time_base; }

	string description();
	//~Runner();
};