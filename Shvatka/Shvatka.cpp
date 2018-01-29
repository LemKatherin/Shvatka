/* ��������� ��� ���� �������
   [���������� � ���� ����� ����. 
   ������� ��������� ������� � �����-���� ����������� ����������, 
   �� ������������ ���������� ��������� ����� � ���������� ��������� - ������, 
   ������ ������� �������� ���� ������� (����� ������� �������),
   �� ������ ������ ������� ��������� ������� �� �����-���� �����, ������� �����������,
   ��� �� ����� ���� �������� ��� �������� �����, � ����������� �� ����, ��� ������� ��������� �������,
   �� ����������� ������� ������ ������� �������� ���, ������� ������� ����� ��������� �����,
   �� �����, ����� ����������� ������ ������� ������ ��������, ����������� ����� ����������� ������� � ������ ������� � �������,
   ���������� ������� � ����������� ��������]
   ������ ��������� ���������: 
      �������� ��� �������(��������, ���������� ����������, �������) � ��� ������(��������, �������, ��� � �����),
	  ������� ��� �������� �������
	  �������� ����� ����������� ������ ������� ������� ������ (+ ������, ������)
	  ���������� �������� ����� ����������� ������ ������� ������ ��������
	  ������� ����������
	�� ����� ������ ��������� ��� ���������� ������������ � ��������� ���� ��� ��������
*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <list>
#include <fstream>
#include <windows.h>
using namespace std;

                    // �������� ������
class Pick
{
	string name;
	string challenge;
	string code;
	string number;
public:
	Pick()
	{
		name = "";
		challenge = "";
		code = "";
		number = "";
	}
	~Pick() {}
	void create(int i)
	{
		cout << " �������� ������: ";
		getline(cin, name);
		name.append(" � ");
		number = ('0' + i);
		name.append(number);
		cout << " ������� �������: ";
		getline(cin, challenge);
		cout << " ��� �� ����������� : ";
		getline(cin, code);
		cout << endl;
	}
	void output(ofstream &outfile)
	{
		cout << " �������� ������: " << name << endl;
		cout << " ������� �������: " << challenge << endl;
		cout << " ��� �� �����������: " << code << endl;
		cout << endl;
		outfile << " �������� ������: " << name << endl;
		outfile << " ������� �������: " << challenge << endl;
		outfile << " ��� �� �����������: " << code << endl;
		outfile << endl;
	}
	void output_n(ofstream &outfile)
	{
		cout << name << endl;
		outfile << name << endl;
	}
};
                        // ���� ����
class Game
{
protected:
	static int n_picks;
	static int n_teams;
public:
	Game() {}
	Game(int b)
	{
		n_picks = b;
	}
	~Game() {}
	void picks(Pick *mas[])                                   // ���������� ������� ��� ����
	{
		for (int i = 1; i <= n_picks; i++)
		{
			Pick *p = new Pick;
			p->create(i);
			mas[i - 1] = p;
		}
	}
	void output_p(Pick *mas[], ofstream &outfile)
	{
		for (int i = 0; i < n_picks; i++)
		{
			mas[i]->output(outfile);
		}
	}
};

                                  // �������
class Team : public Game
{
	int n_mem;
protected:
	string name;
	list<int> way;
public:
	Team()
	{
		name = "";
		n_mem = 0;
	}
	~Team() {}
	void create(ofstream &outfile)
	{

		cout << " �������� �������: ";
		getline(cin, name);
		outfile << " �������� �������: " << name << endl;
		cout << " ���������� ����������: ";
		cin >> n_mem;
		outfile << " ���������� ����������: " << n_mem << endl;
		cout << " �������: " << endl;
		outfile << " �������: " << endl;
		for (int i = 0; i < n_picks; i++)
		{
			int n;
			cout << " ";
			cin >> n;
			cin.get();
			outfile << " " << n << endl;
			way.push_back(n);
		}
		cout << endl;
		outfile << endl;
		n_teams++;
	}
	void copy(Team &p)
	{
		name = p.name;
		n_mem = p.n_mem;
		way = p.way;
	}
};

                  // ����� ��� �������� �������
class Time
{
	int hour;
	int min;
	int sec;
public:
	Time()
	{
		hour = 0;
		min = 0;
		sec = 0;
	}
	~Time() {}
	friend void operator >> (istream&, Time& p)
	{
		cout << "  ������: ";
		cin >> p.min;
		cout << "  �������: ";
		cin >> p.sec;
	}
	friend ostream& operator << (ostream& a, const Time& p)
	{
		a << "  ����: " << p.hour << endl << " ������: " << p.min << endl << " �������: " << p.sec << endl;
		return a;
	}
	Time& operator = (const int &a)
	{
		hour = a;
		min = a;
		sec = a;
		return *this;
	}
	Time operator + (const Time &p)
	{
		Time result;
		result.hour = hour + p.hour;
		result.min = min + p.min;
		result.sec = sec + p.sec;
		if (result.sec >= 60)
		{
			result.sec -= 60;
			result.min++;
		}
		if (result.min >= 60)
		{
			result.min -= 60;
			result.hour++;
		}
		return result;
	}
	Time& operator += (const Time &p)
	{
		hour += p.hour;
		min += p.min;
		sec += p.sec;
		if (sec >= 60)
		{
			sec -= 60;
			min++;
		}
		if (min >= 60)
		{
			min -= 60;
			hour++;
		}
		return *this;
	}
	Time& operator -= (const Time &p)
	{
		hour -= p.hour;
		min -= p.min;
		sec -= p.sec;
		if (sec < 0)
		{
			min--;
			sec = 60 + sec;
		}
		if (min < 0)
		{
			hour--;
			min = 60 + min;
		}
		if (hour < 0)
		{
			hour = 0;
			min = 0;
			sec = 0;
		}
		return *this;
	}
	bool operator > (const Time &p)
	{
		if (hour == p.hour && min == p.min && sec > p.sec)
			return 1;
		else if (hour == p.hour && min == p.min && sec < p.sec)
			return 0;
		else if (hour == p.hour && min > p.min)
			return 1;
		else if (hour == p.hour && min < p.min)
			return 1;
		else if (hour > p.hour)
			return 1;
		else
			return 0;
	}
	bool operator == (const Time &p)
	{
		if (hour == p.hour && min == p.min && sec == p.sec)
			return 1;
		else return 0;
	}
};

                        // ���������� �� �������
class Results : public Team
{
	Time time;
	Time plus_time;
	Time all;
	Time bonus;
public:
	Results()
	{
		time = 0;
		plus_time = 0;
		all = 0;
		bonus = 0;
	}
	~Results() {}
	void output(Pick *mas[], Team &x, ofstream &outfile)
	{
		copy(x);
		cout << " �������� �������: " << name << endl << endl;
		outfile << " �������� �������: " << name << endl;
		list<int>::iterator p = way.begin();
		while (p != way.end())    // �������� ����� ������
		{
			cout << " �����: ";
			outfile << endl << " �����: ";
			mas[*p - 1]->output_n(outfile);
			cout << endl << " ����� �����������: " << endl << endl;
			cin >> time;
			outfile << endl << " ����� �����������: " << endl << endl << time;
			cout << endl << " �������� �����: " << endl << endl;
			cin >> plus_time;
			outfile << endl << " �������� �����: " << endl << endl << plus_time;
			cout << endl << " ����� ����� ������: " << endl << endl << time + plus_time;
			outfile << endl << " ����� ����� ������: " << endl << endl << time + plus_time;
			cout << endl;
			all += (time + plus_time);
			p++;
		}
		cout << endl << " �����: " << endl << endl;
		cin >> bonus;
		outfile << endl << " �����: " << endl << endl << bonus;
		all -= bonus;
		cout << endl << " �������� �����: " << endl << endl << all;
		outfile << endl << " �������� �����: " << endl << endl << all;
		cout << endl;
		outfile << endl;
	}
	Results& operator =(const Results &p)
	{
		name = p.name;
		way = p.way;
		time = p.time;
		plus_time = p.plus_time;
		bonus = p.bonus;
		all = p.all;
		return *this;
	}
	friend void victory(Results *mas_r[], int h, ofstream &outfile);
};

                                           // ������� ����������� ����������
void victory(Results *mas_r[], int h, ofstream &outfile)               
{
	Results winner;
	winner = *mas_r[0];
	int d = 0;
	for (int i = 1; i < h; i++)
	{
		Results a = *mas_r[i];
		if (a.all > winner.all)
		{
			winner = a;
			d = i;
		}
	}
	cout << " ����������" << endl << endl << " ������� " << winner.name << endl;
	outfile << endl << " ����������" << endl << endl << " ������� " << winner.name << endl;
	for (int i = 0; i < h; i++)
	{
		Results a = *mas_r[i];
		if (a.all == winner.all && i != d)
		{
			cout << " ������� " << a.name << endl;
			outfile << " ������� " << a.name << endl;
		}
	}
}

int Game::n_teams = 0;
int Game::n_picks = 0;

void add_del(int &h, Team *mas_t[], ofstream &outfile)                       // ���������� ��� �������� �������
{
	while (true)
	{
		cout << " �������� �� ������� �������� ��� ������� �������?" << endl << endl;
		int a;
		cout << "  0 - ������ " << endl << "  1 - �������� ������� " << endl << "  2 - ������� ������� " << endl << endl;
		cin >> a;
		cin.get();
		cout << endl;
		switch (a)
		{
		case 0:
			cout << " �� � ���������" << endl << endl;
			return;
			break;
		case 1:
			int q;
			cout << " ������� ������ �� ������� ��������? ";
			cin >> q;
			cin.get();
			cout << endl;
			h += q;
			for (int i = h - q; i < h; i++)
			{
				Team *p = new Team;
				p->create(outfile);
				mas_t[i] = p;
			}
			break;
		case 2:
			cout << " ������� ����� �������, ������� ������� �������: ";
			cin >> q;
			cin.get();
			cout << endl;
			if (q >= h)
			{
				cout << endl << " ������. ������� � ����� ������� ���" << endl << endl;
				return;
			}
			Team *p = mas_t[q - 1];
			for (int i = q - 1; i < h; i++)
			{
				if (i == h - 1)
					mas_t[i] = NULL;
				mas_t[i] = mas_t[i + 1];
			}
			h--;
			delete p;
			cout << " ������� � " << q << " �������" << endl << endl;
			outfile << " ������� � " << q << " �������" << endl << endl;
			break;
		}
	}
}

int main()
{
	//	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ofstream outfile("Game.txt");
	int h;
	cout << endl << " ������� ���������� ������: ";
	cin >> h;
	cin.get();
	int n;
	cout << endl << " ������� ���������� �������: ";
	cin >> n;
	cin.get();
	cout << endl;
	Pick **mas = new Pick*[n];
	Game first(n);
	first.picks(mas);
	system("cls");
	outfile << " ������ " << endl << endl;
	cout << " ������ " << endl << endl;
	outfile << " ���������� �������: " << n << endl << endl;
	cout << " ���������� �������: " << n << endl << endl;
	first.output_p(mas, outfile);
	Team **mas_t = new Team*[h];
	outfile << " ������� " << endl << endl;
	cout << " ������� " << endl << endl;
	for (int i = 0; i < h; i++)
	{
		Team *p = new Team;
		p->create(outfile);
		mas_t[i] = p;
	}
	add_del(h, mas_t, outfile);
	cout << " ���������� " << endl << endl;
	outfile << " ���������� " << endl << endl;
	Results **mas_r = new Results*[h];
	for (int i = 0; i < h; i++)
	{
		Results *p = new Results;
		mas_r[i] = p;
		mas_r[i]->output(mas, *mas_t[i], outfile);
	}
	victory(mas_r, h, outfile);
	outfile.close();
	return 0;
}