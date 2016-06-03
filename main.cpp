#include <iostream>
#include <string>
#include "runner.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cstdlib>
#include <unistd.h>
#include <math.h>
#include <iomanip>

using namespace std;

void randperson(int *helpArray);
int RandomValue(int n1, int n2);
void results(double t_t[6], int index[6]);
void symulation(Runner T[6][4], int k, double t_t[6], double distance, int exceed[6]);
void random_country(Runner T[6][4], string &con);
void showplayers(Runner T[6][4] ,string &country, int distance);

int main(int argc, char** argv)
{
	srand(time(NULL));
	string country;
	int distance=atoi(argv[1]);
	int choice;
	Runner T[6][4] = {};
	Runner runners[24];
	double team_time[6] = {};
	int exceed[6] = { -1,-1,-1,-1,-1,-1 };
	int helpArray[24];
	randperson(helpArray);
	for (int i = 0, k=0, o=0; o < 24; k++,o++)
	{
		T[i][k] = runners[helpArray[o]];
		if (k == 3)
		{
			k = -1;
			i++;
		}
	}
	do
	{
		system("clear");
		cout << "Wybierz pozycje:" << endl;
		cout << "1. Wyswietl zawodnikow." << endl;
		cout << "2. Rozpocznij symulacje." << endl;
		cout << "3. Przeprowadz program od poczatku do konca." << endl;
		cout << "4. EXIT." << endl;
		do
		{
		cin >> choice;
		if((choice<1 || choice >4))
			cout<<"Zle wpisana wartosc!!"<<endl;
	}while(choice<1 && choice>4);
		switch (choice)
		{
		case 1:
			system("clear");
			showplayers(T, country, distance);
			getchar();
			getchar();
			break;
		case 2:
			system("clear");
			for (int k = 0; k < 4; k++)
			{
				symulation(T, k, team_time, distance, exceed);
			}
			getchar();
			getchar();
			break;
		case 3:
			system("clear");
			showplayers(T, country, distance);
			for (int k = 0; k < 4; k++)
			{
				symulation(T, k, team_time, distance, exceed);
			}
			getchar();
			getchar();
			break;
		case 4:
			exit(0);
			break;
		}
	} while (choice != 4);
}

void randperson(int *helpArray)
{
	int number;
	for (int i = 0; i < 24; i++)
	{
		number = (rand() % 24) + 0;
		helpArray[i] = number;
		for (int j=i-1; j >= 0; j--)
		{
			if (helpArray[i] == helpArray[j]) {
				i--; break;
			}
		}
	}
}

int RandomValue(int n1, int n2)
{
	return (rand() % n2) + n1;
}

void results(double t_t[6], int index[6])
{
	int o = 0;
	for (int i = 0; i < 6; i++)
		for (int j = 1; j < 6 - i; j++)
			if (t_t[j - 1]>t_t[j])
			{
				swap(t_t[j - 1], t_t[j]);
				swap(index[j - 1], index[j]);
			}
	while (t_t[0] == 0 && o != 5)
	{
		for (int i = 0, j = 1; i < 6, j < 6; i++, j++)
		{
			if (t_t[i] == 0)
			{
				swap(t_t[i], t_t[j]);
				swap(index[i], index[j]);
			}
		}
		o++;
	}
}
void symulation(Runner T[6][4], int k, double t_t[6], double distance, int exceed[6])
{
	int index[6] = { 1,2,3,4,5,6 };
	string comment[6][4];
	string time[6];
	int clearRun = 0, stick = 0;
	if (k == 0)
	{
		cout << "Rozpocznijmy turniej!" << endl;
		usleep(1500000);
		system("clear");
		cout << "Bieg rozpoczynaja nastepujacy zawodnicy:" << endl;
		usleep(2000000);
		system("clear");
		cout << setw(10) << left << "TEAM:" << setw(12) << "TEAM 1" << setw(12) << "TEAM 2";
		cout << setw(12) << "TEAM 3" << setw(12) << "TEAM 4";
		cout << setw(12) << "TEAM 5" << setw(12) << "TEAM 6" << endl;
	}
	cout << setw(10) << left << "Zawodnik:";
	usleep(1500000);
	for (int i = 0; i < 6; i++)
	{
		cout << setw(12) << left << T[i][k].name();
		if (k == 0) usleep(100000);
		T[i][k].weight();
	}
	cout << endl;
	usleep(2000000);
	if (k == 0)
	{
		cout << setw(10) << left << "START!" << endl;
		usleep(2000000);
	}
	for (int i = 0; i < 6; i++)
	{
		if (T[i][k].chancesOfstart() == true) comment[i][0] = " rozpoczal bardzo slabo!";
		while (T[i][k].road() <= distance)
		{
			T[i][k].speedv0();
			T[i][k].add_road();
			if (((fmod(T[i][k].time(), 5.0)) >= 0.0) && ((fmod(T[i][k].time(), 5.0)) < 0.01))
			{
				if ((T[i][k].chancesOfexceed() == true) && (exceed[i] == -1))
				{
					exceed[i] = i;
				}
			}
			if (((fmod(T[i][k].time(), 2.0)) >= 0.0) && ((fmod(T[i][k].time(), 2.0)) < 0.01))
			{
				T[i][k].tiredness();
				if (T[i][k].chancesOfdown() == true)
				{
					comment[i][1] = " niespodziewanie upada!!";
				}
			}
			if ((T[i][k].road() > (distance - 4.f)) && (T[i][k].chancesOfdrop() == true))
			{
				stick++;
				if ((k < 3) && (stick == 1))
				{
					comment[i][3] = " zle podaje paleczke!";
					T[i][(k + 1)].afterdrop();
				}
			}
		}
		stick = 0;
	}
	cout << setw(10) << left << "Komentarze: " << endl;
	usleep(2000000);
	for (int i = 0; i < 6; i++)
	{
		if (exceed[i] != -1)
		{
			if (t_t[exceed[i]] != 0 || k==0)
			{
				cout << "Zawodnik " << T[i][k].name() << " wybiegl poza tor! Mamy dyskwalifikacje!!" << endl;
				usleep(2000000);
			}
			clearRun++;
			T[exceed[i]][k].time_0();
			t_t[exceed[i]] = 0;
			for (int j = 0; j < 4; j++)
			{
				comment[exceed[i]][j] = "";
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (comment[j][i].length() >1)
			{
				cout << "Zawodnik " << T[j][k].name() << comment[j][i] << endl;
				usleep(2000000);
				clearRun++;
			}
		}
	}
	if (clearRun == 0)
	{
		cout << "Piekny bieg!" << endl;
		usleep(2000000);
		clearRun = 0;
	}
	cout << endl;
	for (int i = 0; i < 6; i++)
	{
		if (i == 0) cout << setw(10) << left << "TIME[s]:";
		t_t[i] += (T[i][k].time() + T[i][k].penalty_time()) / 60.f;
		cout << setw(12) << left << setprecision(4) << (T[i][k].time() + T[i][k].penalty_time());
	}
	usleep(1500000);
	cout << endl;
	if (k > 0)
	{
		cout << setw(10) << left << "SUMA[m]:";
		for (int i = 0; i < 6; i++)
		{
			cout << setw(12) << left << setprecision(3) << t_t[i];
		}
		cout<<endl;
	}
	cout << endl;
	if (k == 3)
	{
		cout << endl;
		cout << setw(15) << left << "Oto wyniki naszej rozgrywki:" << endl;
		results(t_t, index);
		for (int i = 0; i < 6; i++)
		{
			cout << (i + 1) << setw(10) << left << ".miejsce:" << setprecision(3) << setw(5) << left << t_t[i];
			cout << " - TEAM " << index[i] << endl;
		}
	}
}

void random_country(Runner T[6][4], string &con)
{
	int x, y;
	for (int i = 0; i < 15; i++)
	{
		x = RandomValue(0, 6);
		y = RandomValue(0, 4);
		cout << "Zawody odbeda sie w ...   ";
		cout << T[x][y].country() << endl;
		usleep((i + 1) * 70000);
		if (i == 14) break;
		system("clear");
	}
	con = T[x][y].country();
}
void showplayers(Runner T[6][4] ,string &country, int distance)
{
	cout << "Witamy na zawodach w biegu sztafetowym na dystansie " << distance << " metrow."<< endl;
	usleep(2500000);
	system("clear");
	random_country(T,country);
	cout << "Przedstawiamy naszych dzisiejszych bohaterow!!" << endl;
	usleep(2500000);
	for (int i = 0; i < 6; i++)
	{
	cout << "W druzynie " << (i + 1) << " wystapia: " << endl;
	cout << " ------------------------------------------"<<endl;
	cout << "Team " << (i+1) << endl;
	usleep(1500000);
	for (int j = 0; j < 4; j++)
	{
	if (T[i][j].country() == country)
	{
	T[i][j].change_morale();
	}
	cout << T[i][j].description() << endl << endl;
	usleep(1500000);
	}
	usleep(2000000);
	}
}