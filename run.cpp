#include "runner.h"
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <string>
#include <time.h>
#include <iostream>
#include <unistd.h>
#include <cmath>

using namespace std;
vector <string> Runner::names;
vector <string> Runner::countries;

void Runner::init()
{
	ifstream file("names.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(names));
	file.close();
}

void Runner::init1()
{
	ifstream file("countries.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(countries));
	file.close();
}
int randomValue(int n1, int n2)
{
	return (rand() % n2) + n1;
}
Runner::Runner()
{
	static int amountOfNames = (init(), names.size());
	static int amountOfCountries = (init1(), countries.size());
	_name = names[rand() % amountOfNames];
	_country = countries[rand() % amountOfCountries];
	_max_speed = ((randomValue(800, 450))/100.f);
	_base_acc = ((randomValue(520, 400))/100.f);
	_morale = randomValue(10, 89);
	_condition = randomValue(10, 89);
	_tiredness =randomValue(1, 70);
	_stamina =  randomValue(10, 89);
	_inteligence = randomValue(30, 70);
	_weight = randomValue(50, 40);
	_aglity =  randomValue(30, 70);
	_acc = 0.001*_base_acc;
	_road = 0.00;
	_time_base = 0.01;
	_speedv0 = 0.01;
	_time=0.01;
	_penalty_time = 0.00;
	_chances = { randomValue(1,3) , randomValue(1,3),
		randomValue(1,3), randomValue(1,4) };
}
void Runner::change_morale()
{
	(_morale>85)? _morale=100:_morale += 15;
}
void Runner::change_tiredness()
{
	_tiredness += (int)(((1000000 - _morale*_condition*_stamina) / 250000.f));
	if (_tiredness > 70) _tiredness = 70;
	(_max_speed <= 5) ? _max_speed = 5:_max_speed -= _tiredness / 450.f;
	(_acc < 0.002) ? _acc = 0 : _acc -= (_tiredness / 100000.f);
	if (_tiredness ==70 )
	{
		_chances.chanceOfdrop += 1;
		_chances.chanceOfexceedline += 2;
		_chances.chanceOffalldown += 2;
	}
}
int Runner::weight()
{
	if (_weight <= 70)
	{
		_acc *= (1 + (_weight / 1000.f));
		(_morale<95)?_morale += 5:_morale=100;
	}
	else
	{
		_acc *= (1 - (_weight / 1000.f));
		(_morale>16) ? _morale -= 5 : _morale = 10;
	}
	return _weight;
}

double Runner::road()
{
	return _road;
}
void Runner::add_road()
{
	_speedv0 = _acc*_time;
	_time += _time_base;
	(_speedv0 < (_max_speed / 1000)) ?
	_road += (_speedv0 + (_acc*pow(_time_base, 2)) / 2) :
	_road += _max_speed*_time_base;
}
bool Runner::chancesOfdown()
{
	if (randomValue(1,99) <= _chances.chanceOffalldown)
	{
		_speedv0 = 0.01;
		(_morale < 20) ? _morale = 10 : _morale -= 10;
		(_tiredness >= 65) ? _tiredness = 70 : _tiredness += 5;
		(_aglity < 35) ? _aglity = 30 : _aglity -= 5;
		_penalty_time += (1000000-(_inteligence*_aglity*_stamina)) / 200000.f;
		return true;
	}
	return false;
}

bool Runner::chancesOfdrop()
{
	if (randomValue(1, 99) < _chances.chanceOfdrop)
	{
		_speedv0 = 0.01;
		(_morale < 20) ? _morale = 10 : _morale -= 10;
		_penalty_time += (1000000 - (_inteligence*_aglity*_stamina)) / 200000.f;
		return true;
	}
	return false;
}
void Runner::afterdrop()
{
	(_morale <= 25) ? _morale = 10 : _morale -= 15;
	(_aglity <= 40) ? _aglity = 30 : _aglity -= 10;
	(_inteligence <= 40)? _inteligence = 30: _inteligence -= 10;
	(_max_speed <= 5) ? _max_speed = 5 : _max_speed -= ((240-(_morale+_aglity+_inteligence)) / 450.f);
	(_acc < 0.002) ? _acc = 0 : _acc -= ((240 - (_morale + _aglity + _inteligence)) / 2500000.f);
	_chances.chanceOfdrop += 2;
	_chances.chanceOffalldown += 2;
	_chances.chanceOfslowstart += 5;
}
void Runner::time_0()
{
	_time = 0;
	_penalty_time = 0;
}
bool Runner::chancesOfexceed()
{
	if (randomValue(1, 99) < _chances.chanceOfexceedline)
	{
		return true;
	}
	return false;
}
bool Runner::chancesOfstart()
{
	if (randomValue(1, 99) < _chances.chanceOfslowstart)
	{
		(_morale <= 25) ? _morale = 10 : _morale -= 15;
		(_condition <= 20) ? _condition = 10 : _condition -= 10;
		(_stamina <= 25) ? _stamina = 10 : _stamina -= 15;
		(_inteligence <= 40) ? _inteligence = 30 : _inteligence -= 10;
		(_aglity <= 40) ? _aglity = 30 : _aglity -= 10;
		(_tiredness >= 60) ? _tiredness = 70 : _tiredness += 10;
		_acc -= ((490-(_morale+_condition+_stamina+_inteligence+_aglity))/350000.f );
		_max_speed -= ((490 - (_morale + _condition + _stamina + _inteligence + _aglity)) / 350.f);
		return true;
	}
	return false;
}
string Runner::description()
{
	return _name + "\n" + _country + "\nMax Speed [m/s]:" + to_string(_max_speed) +
		"\nBase Acceleration[m/s^2]:" + to_string(_base_acc) +
		"\nWeight:"+ to_string(_weight)+
		"\nMorale:" + to_string(_morale) +
		"\nCondition:" +to_string(_condition) +
		"\nTiredness:" + to_string(_tiredness)
		+"\nStamina:" + to_string(_stamina);
}