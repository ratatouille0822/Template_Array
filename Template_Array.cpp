#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

struct PrintInt
{
	void operator()(int i)
	{
		cout << i << "->";
	}
};


struct PrintChar
{
	void operator()(char i)
	{
		cout << i << "->";
	}
};


class Person
{
	friend struct PrintPerson;

public:
	Person()
	{

	}
	Person(int age, string name)
	{
		this->age = age;
		this->name = name;
	}
	Person(const Person& another_person_instance)
	{
		this->age = another_person_instance.age;
		this->name = another_person_instance.name;
	}

	Person operator=(const Person& another_person_instance)
	{
		this->age = another_person_instance.age;
		this->name = another_person_instance.name;
		return *this;
	}

	~Person()
	{
		cout << "delete person" << endl;
	}
private:
	int age;
	string name;

};

struct PrintPerson
{
	void operator()(const Person& person_instance)
	{
		cout << person_instance.age << ", " << person_instance.name << endl;
	}
};

template<class T>
class MyArray
{
public:
	MyArray()
	{
		this->capa = 10;
		this->size = 0;
		this->arr = new T[10];
		cout << "MyArray()" << endl;
	}

	MyArray(int capa)
	{
		this->capa = capa;
		this->size = 0;
		this->arr = new T[capa];
		cout << "MyArray(int capa)" << endl;
	}

	MyArray(const MyArray& another_myarray_instance)
	{
		this->size = another_myarray_instance.size;
		this->capa = another_myarray_instance.capa;
		this->arr = new T[another_myarray_instance.size];
		memcpy(this->arr, another_myarray_instance.arr,sizeof(T) * another_myarray_instance.size);
	}

	~MyArray()
	{
		delete[] this->arr;
		this->arr = NULL;
		cout << "~MyArray()" << endl;
	}

	void push_back(const T& push_back_data)
	{
		if (this->size == this->capa)
		{
			T* temp = new T[capa * 2];
			memcpy(temp, this->arr, sizeof(T) * this->size);
			delete[] this->arr;
			this->arr = temp;
			//memcpy(&this->arr[this->size], &push_back_data, sizeof(T));
			this->arr[this->size] = push_back_data;
			this->size++;
			this->capa*= 2;
		}
		else
		{
			this->arr[size] = push_back_data;
			//memcpy(&this->arr[this->size], &push_back_data, sizeof(T));
			this->size++;
		}
	}

	void pop()
	{
		this->size--;
	}
	
	int get_size()
	{
		return this->size;
	}

	template<class FUN>
	void print_data(FUN func)
	{
		for (int i = 0; i < size; i++)
		{
			func(arr[i]);
		}
		cout << endl;

	}

	T& operator[](int i)
	{
		if (i >= this->size || i < 0)
		{
			cout << "Out of range" << endl;
		}
		else
		{
			return arr[i];
		}

	}

	MyArray operator=(const MyArray & another_myarray_instance)
	{
		if (!(this->arr == NULL))
			delete[] this->arr;
		this->capa = another_myarray_instance.capa;
		this->size = another_myarray_instance.size;
		this->arr = new T[another_myarray_instance.size];
		memcpy(this->arr, another_myarray_instance.arr, sizeof(T)*another_myarray_instance.size);
		return *this;
	}

private:
	int capa;
	int size;
	T * arr;

};

void test01()
{
	MyArray<int> array(5);
	array.push_back(1);
	array.push_back(2);
	array.push_back(3);
	array.push_back(4);
	array.print_data(PrintInt());
	MyArray<int> array1 = array;
	array1.print_data(PrintInt());
	MyArray<int> array2;
	array2 = array1;
	array2.print_data(PrintInt());
}

void test02()
{
	MyArray<char> char_array(5);
	char_array.push_back('a');
	char_array.push_back('b');
	char_array.push_back('c');
	char_array.push_back('d');
	char_array.push_back('e');
	char_array.print_data(PrintChar());

	cout << char_array[0] << endl;
	cout << char_array[1] << endl;
	cout << char_array[2] << endl;
	cout << char_array[3] << endl;
	cout << char_array[4] << endl;

	cout << char_array.get_size() << endl;

	for (int i = 0; i < char_array.get_size(); i++)
	{
		char_array.pop();
		char_array.print_data(PrintChar());
	}

}

void test03()
{
	MyArray<Person>* person_array = new MyArray<Person>;
	PrintPerson print_person = PrintPerson();
	person_array->push_back(Person(10, "Liu, Bei"));
	person_array->push_back(Person(20, "Guan, Yu"));
	person_array->push_back(Person(30, "Zhang, Fei"));
	person_array->get_size();

	person_array->print_data(print_person);
	person_array->pop();
	person_array->print_data(print_person);

	MyArray<Person> p1 = *person_array;
	p1.print_data(print_person);

	print_person(Person(40, "Zhao, yun"));

	const int* p = NULL;
	int* p2 = const_cast<int*>(p);


}

int main()
{
	/*test01();
	test02();*/
	test03();
    std::cout << "Hello World!\n"; 
}
