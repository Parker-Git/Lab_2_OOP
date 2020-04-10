#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <set>
#include <map>
#include <iterator>

#define LENGTH 20

using namespace std;
// �� ������� �������� ������� ����������� ������� ����������

class FindMin
{
public:
	bool operator() (const pair<char, int>& p1, const pair<char, int>& p2) const
	{
		return p1.second < p2.second;
	}
};

int main()
{
	setlocale(LC_ALL, "Rus");

	int a = 0, b = 100; // �������� �����

	random_device rnd;
	mt19937 gen(rnd());
	uniform_int_distribution<> distr(a, b);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Set
	set<int, greater<int> > setInt;
	cout << "______________________________________________" << endl << "Set" << endl << "______________________________________________" << endl;

	for (int i = 0; i < LENGTH; i++)
	{
		setInt.insert(distr(gen));
	}

	ostream_iterator<int> outIter(cout, "\n");
	copy(setInt.begin(), setInt.end(), outIter);

	auto ittMin = min_element(setInt.begin(), setInt.end());
	cout << endl << "�������: " << *ittMin << endl << endl << "��������� ������:";

	set<int, greater<int> > bufSet;
	set<int> ::iterator itt = setInt.begin();
	while (itt != setInt.end())
	{
		bufSet.insert(*(itt++) - *ittMin);
	}
	bufSet.swap(setInt);

	cout << endl;
	copy(setInt.begin(), setInt.end(), outIter);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Map
	cout << "______________________________________________" << endl << "Map" << endl << "______________________________________________" << endl;

	map<char, int> mapInt;
	map<char, int> ::iterator it = mapInt.begin();

	for (int i = 0; i < LENGTH; i++)
	{
		mapInt[char('a' + rand() % ('z' - 'a'))] = distr(gen);
	}

	cout << endl;
	for (it = mapInt.begin(); it != mapInt.end(); it++)
	{
		cout << (*it).first << " : " << (*it).second << endl;
	}

	pair<char, int> min = *min_element(mapInt.begin(), mapInt.end(), FindMin());
	cout << endl << "�������: " << min.second << endl << endl << "��������� ������:" << endl;

	for (it = mapInt.begin(); it != mapInt.end(); it++)
	{
		(*it).second -= min.second;
		cout << (*it).first << " : " << (*it).second << endl;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// �������� �� ����� �� ���������� map
	bool flag = true;
	do
	{
		cout << endl << "������� ����������� �� map? (y/n)" << endl;
		char answ = 'a';
		cin >> answ;
		if (answ == 'y')
		{
			if (!mapInt.empty())
			{
				cout << endl << "������� ���� ��� ��������: ";
				char key = 'a';
				cin >> key;

				auto finder = mapInt.find(key);
				if (finder != mapInt.cend())
				{
					auto toErase = mapInt.find(key);
					mapInt.erase(toErase);
					cout << endl << "��������� ������:" << endl;
					for (it = mapInt.begin(); it != mapInt.end(); it++)
					{
						cout << (*it).first << " : " << (*it).second << endl;
					}
					flag = true;
				}
				else
				{
					cout << "����������� � ����� ������ �� ����������!" << endl;
				}
			}
			else
			{
				cout << endl << "����������� ������ ���" << endl;
				flag = false;
				break;
			}
		}
		else if (answ == 'n')
		{
			flag = false;
		}
		else
		{
			cout << endl << "����� ������������ ������!" << endl;
		}
	} while (flag);

	return 0;
}