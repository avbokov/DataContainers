//DataContainers\ForwardList
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
class ForwardList;
class Element
{
	int Data;		// значение элемента
	Element* pNext;	// адрес следующего элемента
	static int count; // статическая переменная, которая будет считать количество элементов
public:
	Element(int Data, Element* pNext = nullptr):Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}

	friend class ForwardList;
	friend class Iterator;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);

};

int Element::count = 0; // инициализация СТАТИЧЕСКОЙ ПЕРЕМЕННОЙ

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator& operator++()	//Prefix increment
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int)	//Suffix increment
	{
		Iterator old = *this;	//сохраняем старое значение, чтобы вернуть его на место вызова
		Temp = Temp->pNext;
		return old;
	}

	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	operator bool()const
	{
		return Temp;
	}

	const int& operator*()const
	{
		return Temp->Data;
	}
	int& operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
	Element* Head;
	unsigned int size;
public:

	Element* get_Head()const
	{
		return Head;
	}

	Iterator begin()const
	{
		return Head;
	}

	Iterator end()const
	{
		return nullptr;
	}

	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	//						такой синтаксис у шаблонного класса//
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		//begin() - возвращает итератор на начало контейнера
		//end() - возвращает итератор на конец контейнера
		cout << typeid(il.begin()).name() << endl;
		//int const* - указатель на константу
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}

	ForwardList(const ForwardList& other) :ForwardList()
	{
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		//*this = other; // вызываем оператор = (это если у нас есть оператор =)
		cout << "CopyConstructor:\t" << this << endl;
	}

	~ForwardList()
	{

		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//				Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	//ForwardList& operator+(const ForwardList& other)
	//{
	//	/*Element* Temp = Head;
	//	while (Temp->pNext)
	//	{
	//		Temp = Temp->pNext;
	//	}
	//	Temp->pNext = other.Head;
	//	return *this;*/

	//	/*ForwardList* Result = new ForwardList;
	//	Element* Temp = Head;
	//	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	//	{
	//		push_front(Temp->Data);
	//	}
	//	Result->Head = other.Head;
	//	return *Result;*/
	//		
	//}

	//				Adding Elements:

	void push_front(int Data)
	{
		/*// 1) в первую очередь мы создаём новый элемент
		Element* New = new Element(Data);
		// 2) "привязываем элемент к началу списка"
		New->pNext = Head;
		// 3) делаем новый элемент началом списка
		Head = New;*/
		
		//  оптимизация
		Head = new Element(Data, Head);
		
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		// 1) в первую очередь мы создаём новый элемент
		//Element* New = new Element(Data);
		// 2) доходим до конца списка:
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		// 3) добавляем созданный элемент в конец списка:
		//Temp->pNext = New;
		Temp->pNext = new Element(Data);
		size++;
	}

	void insert(int Data, int Index)
	{
		if (Index == 0) return push_front(Data);
		if (Index > size)
		{
			cout << "Error: Выход за пределы списка" << endl;
			return;
		}
		// общий случай: 
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		//-------------------------------------------------
		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	//				Removing Elements:

	void pop_front()
	{
		Element* Temp = Head;
		Head = Head->pNext;
		delete Temp;
		size--;
	}

	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();

		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp ->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	void erase(int Index)
	{
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		Temp->pNext = Erased->pNext;
		delete Erased;
		size--;
	}

		
	//				Methods:

	void print()const
	{
		/*Element* Temp = Head;	// Temp - это Итератор.
		// Итератор - это указатель, при помощи которого можно получить доступ
		// к элементам структуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; // переходим на следующий элемент
		}*/
		for(Element* Temp = Head; Temp; Temp=Temp->pNext)
		//for(Element* Temp = Head; Temp; Temp++)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left; //CopyConstructor
	/*for (Element* Temp = right.get_Head(); Temp; Temp = Temp->pNext)
	{
		cat.push_back(Temp->Data);
	}*/
	for (Iterator Temp = right.get_Head(); Temp; ++Temp)
	{
		cat.push_back(*Temp);
	}
	return cat;
}

//#define BASE_CHECK
//#define COUNT_CHECK
//#define PERFORMANCE_CHECK
//#define OPERATOR_PLUS__CHECK
//#define RANGE_BASED_FOR_ARRAY

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер спика: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}

	list.push_back(123);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	/*list.insert(147, 2);
	list.print();*/
	int value;
	int index;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	/*list.erase(2);
	list.print();*/
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();
#endif // COUNT_CHECK

#ifdef PERFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand());
	}
	cout << "List filled" << endl;
#endif // PERFORMANCE_CHECK

#ifdef OPERATOR_PLUS__CHECK
	//int arr[] = { 3,5,8,13,21 };
	ForwardList list1 = { 3,5,8,13,21 };
	list1 = list1;
	list1.print();
	//ForwardList list2 = list; // вызывается CopyConstructor
	ForwardList list2 = { 34, 55, 89 };
	//list2 = list;				// вызывается CopyAssignment
	//list2 = list;				// вызывается CopyAssignment
	list2.print();
	cout << "\n------------------------------\n";
	ForwardList list3 = list1 + list2;
	cout << "\n------------------------------\n";
	list3.print();
#endif // OPERATOR_PLUS__CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	for (int i : arr) // range-based for (for для контейнеров)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

	ForwardList list = { 3,5,8,13,21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
}
