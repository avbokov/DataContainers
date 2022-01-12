#include<List.h>

#pragma comment(lib, "List2.lib")

void main()
{
	setlocale(LC_ALL, "");
	List<int> list1 = {3,5,8,13,21};
	list1.print();
	list1.reverse_print();
}