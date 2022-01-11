﻿//DataContainers\List2(ClassWork)
#include<iostream>
#include<string>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List<T>;
	}*Head, *Tail; // сразу же после описания класса Element объявляем два указателя на Element
	size_t size;    // объявляем размер списка

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp);
		~ConstBaseIterator();

		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;

		const T& operator*()const;
		
	};

public:
	class ConstIterator:public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
	//					Operators:

		ConstIterator& operator++();
		ConstIterator& operator++(int);
		ConstIterator& operator--();
		ConstIterator& operator--(int);
				
	};

	class ConstReverseIterator:public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();

		//					Operators:

		ConstReverseIterator& operator++();
		ConstReverseIterator& operator--();
		ConstReverseIterator& operator++(int);
		ConstReverseIterator& operator--(int);
			
	};

	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp=nullptr) :ConstIterator(Temp) {}

		T& operator*();
	};

	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp=nullptr) : ConstReverseIterator(Temp) {}

		T& operator*();
	};

	Iterator begin();
	Iterator end();
	ConstIterator cbegin()const;
	ConstIterator cend()const;

	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;

	//					Constructors:

	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	List(List<T>&& other);
	~List();

	//					Operators:

	List<T>& operator=(const List<T>& other);
	List<T>& operator=(List<T>&& other);

	//					Adding Elements:

	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	//					Removing Elements:
	void pop_front();
	void pop_back();
	void erase(int Index);

	//					Methods:

	void print()const;
	void reverse_print()const;
};

template<typename T>
List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) :Temp(Temp)
{
#ifdef DEBUG
	cout << "BaseItConstructor:/t" << this << endl;
#endif // DEBUG
}
template<typename T>
List<T>::ConstBaseIterator::~ConstBaseIterator()
{
#ifdef DEBUG
	cout << "BaseItDestructor:/t" << this << endl;
#endif // DEBUG
}

template<typename T>
bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>
bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T>
const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}

template<typename T>
List<T>::ConstIterator::ConstIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>
List<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
}
//					Operators:

template<typename T>
typename List<T>::ConstIterator::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>
typename List<T>::ConstIterator::ConstIterator& List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T>
typename List<T>::ConstIterator::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>
typename List<T>::ConstIterator::ConstIterator& List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}

template<typename T>
List<T>::Element::Element(T Data, Element* pNext, Element* pPrev )
	:Data(Data), pNext(pNext), pPrev(pPrev)
{
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T>
List<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

}

template<typename T>List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
	cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG
}

//					Operators:

template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

template<typename T>
T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

template<typename T>
T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

template<typename T>
typename List<T>::Iterator List<T>::begin()
{
	return Head;
}

template<typename T>
typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>
typename List<T>::ConstIterator List<T>::cbegin()const
{
	return Head;
}
template<typename T>
typename List<T>::ConstIterator List<T>::cend()const
{
	return nullptr;
}

template<typename T>
typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}

template<typename T>
typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

template<typename T>
typename List<T>::ConstReverseIterator List<T>::crbegin()const
{
	return Tail;
}

template<typename T>
typename List<T>::ConstReverseIterator List<T>::crend()const
{
	return nullptr;
}

//					Constructors:
template<typename T>
List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
#ifdef DEBUG
	cout << "LConstructor:\t" << this << endl;
#endif // DEBUG

}

template<typename T>
List<T>::List(const std::initializer_list<T>& il) :List()
{
	//begin() - возвращает итератор на начало контейнера
	//end() - возвращает итератор на конец контейнера
	//cout << typeid(il.begin()).name() << endl;
	//int const* - указатель на константу
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
	//for (T i : il) push_back(i);
}

template<typename T>
List<T>::List(const List<T>& other) :List()
{
	*this = other;
#ifdef DEBUG
	cout << "CopyConstructor;\t" << this << endl;
#endif // DEBUG

}

template<typename T>
List<T>::List(List<T>&& other)
{
	*this = std::move(other);
#ifdef DEBUG
	cout << "MoveConstructor:\t" << this << endl;
#endif // DEBUG

}

template<typename T>
List<T>::~List()
{
	//while (Head)pop_front();
	while (Tail)pop_back();
#ifdef DEBUG
	cout << "LDestructor:\t" << this << endl;
#endif // DEBUG

}

//					Operators:
template<typename T>
List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	//Deep copy (глубокое копирование) - побитовое копирование:
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
#ifdef DEBUG
	cout << "CopyAssignment;\t" << this << endl;
#endif // DEBUG

	return *this;
}

template<typename T>
List<T>& List<T>::operator=(List<T>&& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	//Shallow copy - поверхностное копирование
	this->Head = other.Head;
	this->Tail = other.Tail;
	this->size = other.size;
	// обнуление other:
	other.Head = nullptr;
	other.Tail = nullptr;
	other.size = 0;
#ifdef DEBUG
	cout << "MoveAssignment:\t;" << this << endl;
#endif // DEBUG

}

//					Adding Elements:
template<typename T>
void List<T>::push_front(T Data)
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

template<typename T>
void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)return push_front(Data);
	Element* New = new Element(Data); //1)
	New->pPrev = Tail; //2)
	Tail->pNext = New; //3)
	Tail = New; //4)
	size++;
}

template<typename T>
void List<T>::insert(T Data, int Index)
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

template<typename T>
void List<T>::pop_front()
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

template<typename T>
void List<T>::pop_back()
{
	if (Head == Tail) return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}

template<typename T>
void List<T>::erase(int Index)
{
	if (Index >= size)	return;
	if (Index == 0)		return pop_front();
	if (Index == size - 1)	return pop_back();

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

template<typename T>
void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Количество элементов списка: " << size << endl;
}

template<typename T>
void List<T>::reverse_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Количество элементов списка: " << size << endl;
}

template<typename T>
void print_list(const List<T>& list)
{
	for (typename List<T>::ConstIterator it = list.cbegin(); it != list.cend(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
}

template<typename T>
void reverse_print_list(const List<T>& list)
{
	for (typename List<T>::ConstReverseIterator rit = list.crbegin(); rit != list.crend(); rit++)
	{
		cout << *rit << tab;
	}
	cout << endl;
}


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