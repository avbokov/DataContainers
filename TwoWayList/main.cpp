//DataContainers\TwoWayList
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Element
{
	int Data;		// значение элемента
	Element* pPrev;	// адрес предыдущего элемента
	Element* pNext;	// адрес следующего элемента

	static int count; // статическая переменная, которая будет считать количество элементов

public:
	Element(int Data, Element* pPrev = nullptr, Element* pNext = nullptr) :Data(Data), pPrev(pPrev), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}

	friend class TwoWayList;
};

int Element::count = 0;

class TwoWayList
{
	Element* Tail;
	Element* Head;
	unsigned int size;

public:

	Element* get_Tail()const
	{
		return Tail;
	}
	
	Element* get_Head()const
	{
		return Head;
	}

	TwoWayList() // Конструктор по умолчанию, создаёт пустой список
	{
		Tail = nullptr;
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~TwoWayList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//				Adding Elements:

	void push_front(int Data)
	{
		if (Tail == nullptr && Head == nullptr)
		{
			Element* New = new Element(Data);
			Tail = New;
			Head = New;
			size++;
			return;
		}

		Element* New = new Element(Data, nullptr, Head);
		Head->pPrev = New;
		Head = New;
		size++;
	}
		

	void push_back(int Data) 
	{
		if (Tail == nullptr && Head == nullptr)return push_front(Data);
		
		Element* New = new Element(Data, Tail, nullptr);
		Tail->pNext = New;
		Tail = New;
		size++;
	}

	//				Removing Elements:

	void pop_front()
	{
		if (Tail == nullptr && Head == nullptr) return;
		if (Tail == Head)
		{
			delete Head;
			Tail = nullptr;
			Head = nullptr;
			size--;
			return;
		}
		Element* Temp = Head;
		Head = Head->pNext;
		Head->pPrev = nullptr;
		delete Temp;
		size--;
	}

	void pop_back()
	{
		if (Tail == nullptr && Head == nullptr) return;
		if (Tail == Head) return pop_front();
		Element* Temp = Tail;
		Tail = Tail->pPrev;
		Tail->pNext = nullptr;
		delete Temp;
		size--;
	}
	
	//				Methods:

	void print()const
	{
		
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}

	void print_rev()const
	{
		for (Element* Temp = Tail; Tail; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
};


void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "Введите размер списка: "; cin >> n;
	TwoWayList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);
	}
	list.print();

	/*list.push_front(147);
	list.print();
	
	list.push_back(147);
	list.print();*/
		
	//list.pop_front();
	//list.print();
	
	list.pop_back();
	list.print();

	//list.print_rev();

		
}