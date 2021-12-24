//DataContainers\ForwardList
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
template<typename T> class ForwardList; // Объявляем ForwardList как шаблонный класс
template<typename T> class Iterator;
//Class - обычный класс
//Class<T> - шаблонный класс

template<typename T>class Element
{
	T Data;		// значение элемента
	Element<T>* pNext;	// адрес следующего элемента
	static int count; // статическая переменная, которая будет считать количество элементов
public:
	Element(T Data, Element<T>* pNext = nullptr):Data(Data), pNext(pNext)
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

	friend class ForwardList<T>;
	friend class Iterator<T>;
	friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);

};

template<typename T>int Element<T>::count = 0; // инициализация СТАТИЧЕСКОЙ ПЕРЕМЕННОЙ

template<typename T>class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator<T>& operator++()	//Prefix increment
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator<T> operator++(int)	//Suffix increment
	{
		Iterator<T> old = *this;	//сохраняем старое значение, чтобы вернуть его на место вызова
		Temp = Temp->pNext;
		return old;
	}

	bool operator==(const Iterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}
	operator bool()const
	{
		return Temp;
	}

	const T& operator*()const
	{
		return Temp->Data;
	}
	T& operator*()
	{
		return Temp->Data;
	}
};

template<typename T>class ForwardList
{
	Element<T>* Head;
	unsigned int size;
public:

	Element<T>* get_Head()const
	{
		return Head;
	}

	Iterator<T> begin()const
	{
		return Head;
	}

	Iterator<T> end()const
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
	ForwardList(const std::initializer_list<T>& il) :ForwardList()
	{
		//begin() - возвращает итератор на начало контейнера
		//end() - возвращает итератор на конец контейнера
		cout << typeid(il.begin()).name() << endl;
		//int const* - указатель на константу
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}

	ForwardList(const ForwardList<T>& other) :ForwardList()
	{
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
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
	ForwardList<T>& operator=(const ForwardList<T>& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
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

	void push_front(T Data)
	{
		/*// 1) в первую очередь мы создаём новый элемент
		Element* New = new Element(Data);
		// 2) "привязываем элемент к началу списка"
		New->pNext = Head;
		// 3) делаем новый элемент началом списка
		Head = New;*/
		
		//  оптимизация
		Head = new Element<T>(Data, Head);
		
		size++;
	}

	void push_back(T Data)
	{
		if (Head == nullptr)return push_front(Data);
		// 1) в первую очередь мы создаём новый элемент
		//Element* New = new Element(Data);
		// 2) доходим до конца списка:
		Element<T>* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		// 3) добавляем созданный элемент в конец списка:
		//Temp->pNext = New;
		Temp->pNext = new Element<T>(Data);
		size++;
	}

	void insert(T Data, int Index)
	{
		if (Index == 0) return push_front(Data);
		if (Index > size)
		{
			cout << "Error: Выход за пределы списка" << endl;
			return;
		}
		// общий случай: 
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		//-------------------------------------------------
		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element<T>(Data, Temp->pNext);
		size++;
	}

	//				Removing Elements:

	void pop_front()
	{
		Element<T>* Temp = Head;
		Head = Head->pNext;
		delete Temp;
		size--;
	}

	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();

		Element<T>* Temp = Head;
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
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		Element<T>* Erased = Temp->pNext;
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
		for(Element<T>* Temp = Head; Temp; Temp=Temp->pNext)
		//for(Element* Temp = Head; Temp; Temp++)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element<T>::count << endl;
	}
};

template<typename T>
ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> cat = left; //CopyConstructor
	/*for (Element* Temp = right.get_Head(); Temp; Temp = Temp->pNext)
	{
		cat.push_back(Temp->Data);
	}*/
	for (Iterator<T> Temp = right.get_Head(); Temp; ++Temp)
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

	ForwardList<int> list = { 3,5,8,13,21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	ForwardList<double> d_list = { 2.5,3.14,5.2,8.3 };
	for (double i : d_list) cout << i << tab; cout << endl;

	ForwardList<std::string> s_list = {"Happy", "New", "Year"};
	for(std::string i : s_list) cout << i << tab; cout << endl;
}
