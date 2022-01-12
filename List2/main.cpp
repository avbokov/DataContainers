﻿//DataContainers\List2(ClassWork)
//#define DEBUG

#include"List.h"
#include"List.cpp"

#define tab "\t"

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();

	list.erase(2);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

	List<int> list = { 3,5,8,13,21 };
	list.print(); 
	list.reverse_print();

	List<int> list2 = list;
	/*list2.print();
	list2.reverse_print();*/
	for (int i : list2) cout << i << tab; cout << endl;

	for (List<int>::ReverseIterator rit = list2.rbegin(); rit != list2.rend(); rit++)
	{
		cout << *rit << tab;
	}
	cout << endl;

	print_list(list);
	reverse_print_list(list);

	List<double> d_list = { 2.5, 3.14, 5.2, 8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;

	List<std::string> s_list = { "Happy", "New", "Year" };
	for (std::string i : s_list)cout << i << tab; cout << endl;

	for (List<double>::ReverseIterator it = d_list.rbegin(); it != d_list.rend(); it++)
		cout << *it << tab;
	cout << endl;
	
	for (List<string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); it++)
		cout << *it << tab;
	cout << endl;

	cout << "\n-------------------------------------------\n" << endl;
	List<List<int>> list2d =
	{
		{3,5,8,13,21},
		{34,55,89},
		{144,233,377,610}
	};
	for (List<List<int>>::Iterator i = list2d.begin(); i != list2d.end(); i++)
	{
		for (List<int>::Iterator j = (*i).begin(); j != (*i).end(); j++)
		{
			cout << *j << tab;
		}
		cout << endl;
	}
	cout << "\n-------------------------------------------\n" << endl;
	for (List<int> i : list2d)
	{
		for (int j : i)
		{
			cout << j << tab;
		}
		cout << endl;
	}
}