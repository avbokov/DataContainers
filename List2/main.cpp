//DataContainers\List2(ClassWork)
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, * Tail; // сразу же после описания класса Element объявляем два указателя на Element
	size_t size;    // объявляем размер списка
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
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
	//List(const std::initializer_list<int>& il) :List()
	//{
	//	//begin() - возвращает итератор на начало контейнера
	//	//end() - возвращает итератор на конец контейнера
	//	cout << typeid(il.end()).name() << endl;
	//	//int const* - указатель на константу
	//	for (int const* it = il.end()-1; it != il.begin()-1; it--)
	//	{
	//		push_front(*it);
	//	}
	//}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//					Adding Elements:

	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			// добавление элемента в пустой список:
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		// общий случай:
		Element* New = new Element(Data); //1)
		New->pNext = Head; //2)
		Head->pPrev = New; //3)
		Head = New; //4)
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		Element* New = new Element(Data); //1)
		New->pPrev = Tail; //2)
		Tail->pNext = New; //3)
		Tail = New; //4)
		size++;
	}

	void insert(int Data, int Index)
	{
		if (Index > size)	return;
		if (Index == 0)		return push_front(Data);
		if (Index == size)	return push_back(Data);

		Element* Temp; // создаём Итератор, но мы пока не знаем,
		//с какой стороны списка лучше зайти, с начала или с конца
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}

		// Не важно, с какой стороны мы добрались до нужно позиции
		// вставка элемента будет осуществляться по одному и тому же алгоритму:
		Element* New = new Element(Data); //1)
		New->pNext = Temp; //2)
		New->pPrev = Temp->pPrev; //3)
		Temp->pPrev->pNext = New; //4)
		Temp->pPrev = New;
		size++;

	}

	//					Removing Elements:

	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr) return;
		if (Head == Tail)
		{
			// удаление единственного элемента из списка
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}

	void pop_back()
	{
		if (Head == Tail) return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}

	void erase(int Index)
	{
		if (Index >= size)	return;
		if (Index == 0)		return pop_front();
		if (Index == size-1)	return pop_back();

		Element* Temp; // создаём Итератор, но мы пока не знаем,
		//с какой стороны списка лучше зайти, с начала или с конца
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		// исключаем элемент из списка:
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;

		// удаляем элемент из памяти:
		delete Temp;
		size--;
	}

	//					Methods:

	void print()const
	{
		for(Element* Temp=Head; Temp; Temp=Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
	}

};

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

	List list = { 3,5,8,13,21 };

	
	list.print(); 
	//list.reverse_print();
}