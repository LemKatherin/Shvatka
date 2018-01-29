/* Программа для игры Схватка
   [Популярная в наше время игра. 
   Участие принимает команды с каким-либо количеством участников, 
   на определенной территории создаются точки с различными заданиями - пикеты, 
   каждая команда получает свой маршрут (набор номеров пикетов),
   на каждом пикете команда выполняет задание за какое-либо время, которое фиксируется,
   так же может быть штрафное или бонусное время, в зависимости от того, как команда выполнила задание,
   за прохождение каждого пикета команда получает код, который поможет найти следующий пикет,
   по итогу, после прохождения каждой команды своего маршрута, суммируется время прохождения пикетов с учетом штрафов и бонусов,
   выигрывает команда с минимальным временем]
   Данная программа позволяет: 
      записать все команды(название, количество участников, маршрут) и все пикеты(название, задание, код и номер),
	  удалить или добавить команду
	  записать время прохождения каждой команды каждого пикета (+ штрафы, бонусы)
	  подсчитать итоговое время прохождения каждой команды своего маршрута
	  выявить победителя
	Во время работы программы вся информация записывается в текстовый файл для удобства
*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <list>
#include <fstream>
#include <windows.h>
using namespace std;

                    // описание пикета
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
		cout << " Название пикета: ";
		getline(cin, name);
		name.append(" № ");
		number = ('0' + i);
		name.append(number);
		cout << " Условие задания: ";
		getline(cin, challenge);
		cout << " Код за прохождение : ";
		getline(cin, code);
		cout << endl;
	}
	void output(ofstream &outfile)
	{
		cout << " Название пикета: " << name << endl;
		cout << " Условие задания: " << challenge << endl;
		cout << " Код за прохождение: " << code << endl;
		cout << endl;
		outfile << " Название пикета: " << name << endl;
		outfile << " Условие задания: " << challenge << endl;
		outfile << " Код за прохождение: " << code << endl;
		outfile << endl;
	}
	void output_n(ofstream &outfile)
	{
		cout << name << endl;
		outfile << name << endl;
	}
};
                        // сама игра
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
	void picks(Pick *mas[])                                   // заполнение пикетов для игры
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

                                  // команды
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

		cout << " Название команды: ";
		getline(cin, name);
		outfile << " Название команды: " << name << endl;
		cout << " Количество участников: ";
		cin >> n_mem;
		outfile << " Количество участников: " << n_mem << endl;
		cout << " Маршрут: " << endl;
		outfile << " Маршрут: " << endl;
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

                  // класс для подсчета времени
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
		cout << "  минуты: ";
		cin >> p.min;
		cout << "  секунды: ";
		cin >> p.sec;
	}
	friend ostream& operator << (ostream& a, const Time& p)
	{
		a << "  часы: " << p.hour << endl << " минуты: " << p.min << endl << " секунды: " << p.sec << endl;
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

                        // результаты по времени
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
		cout << " Название команды: " << name << endl << endl;
		outfile << " Название команды: " << name << endl;
		list<int>::iterator p = way.begin();
		while (p != way.end())    // итератор конца списка
		{
			cout << " Пикет: ";
			outfile << endl << " Пикет: ";
			mas[*p - 1]->output_n(outfile);
			cout << endl << " время прохождения: " << endl << endl;
			cin >> time;
			outfile << endl << " время прохождения: " << endl << endl << time;
			cout << endl << " штрафное время: " << endl << endl;
			cin >> plus_time;
			outfile << endl << " штрафное время: " << endl << endl << plus_time;
			cout << endl << " общее время пикета: " << endl << endl << time + plus_time;
			outfile << endl << " общее время пикета: " << endl << endl << time + plus_time;
			cout << endl;
			all += (time + plus_time);
			p++;
		}
		cout << endl << " бонус: " << endl << endl;
		cin >> bonus;
		outfile << endl << " бонус: " << endl << endl << bonus;
		all -= bonus;
		cout << endl << " итоговое время: " << endl << endl << all;
		outfile << endl << " итоговое время: " << endl << endl << all;
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

                                           // функция определения победителя
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
	cout << " ПОБЕДИТЕЛИ" << endl << endl << " Команда " << winner.name << endl;
	outfile << endl << " ПОБЕДИТЕЛИ" << endl << endl << " Команда " << winner.name << endl;
	for (int i = 0; i < h; i++)
	{
		Results a = *mas_r[i];
		if (a.all == winner.all && i != d)
		{
			cout << " Команда " << a.name << endl;
			outfile << " Команда " << a.name << endl;
		}
	}
}

int Game::n_teams = 0;
int Game::n_picks = 0;

void add_del(int &h, Team *mas_t[], ofstream &outfile)                       // добавление или удаление команды
{
	while (true)
	{
		cout << " Возможно вы желаете добавить или удалить команду?" << endl << endl;
		int a;
		cout << "  0 - ничего " << endl << "  1 - добавить команду " << endl << "  2 - удалить команду " << endl << endl;
		cin >> a;
		cin.get();
		cout << endl;
		switch (a)
		{
		case 0:
			cout << " Ну и ладненько" << endl << endl;
			return;
			break;
		case 1:
			int q;
			cout << " Сколько команд вы желаете добавить? ";
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
			cout << " Введите номер команды, которую желаете удалить: ";
			cin >> q;
			cin.get();
			cout << endl;
			if (q >= h)
			{
				cout << endl << " Ошибка. Команды с таким номером нет" << endl << endl;
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
			cout << " Команда № " << q << " удалена" << endl << endl;
			outfile << " Команда № " << q << " удалена" << endl << endl;
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
	cout << endl << " Введите количество команд: ";
	cin >> h;
	cin.get();
	int n;
	cout << endl << " Введите количество пикетов: ";
	cin >> n;
	cin.get();
	cout << endl;
	Pick **mas = new Pick*[n];
	Game first(n);
	first.picks(mas);
	system("cls");
	outfile << " ПИКЕТЫ " << endl << endl;
	cout << " ПИКЕТЫ " << endl << endl;
	outfile << " Количество пикетов: " << n << endl << endl;
	cout << " Количество пикетов: " << n << endl << endl;
	first.output_p(mas, outfile);
	Team **mas_t = new Team*[h];
	outfile << " КОМАНДЫ " << endl << endl;
	cout << " КОМАНДЫ " << endl << endl;
	for (int i = 0; i < h; i++)
	{
		Team *p = new Team;
		p->create(outfile);
		mas_t[i] = p;
	}
	add_del(h, mas_t, outfile);
	cout << " РЕЗУЛЬТАТЫ " << endl << endl;
	outfile << " РЕЗУЛЬТАТЫ " << endl << endl;
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