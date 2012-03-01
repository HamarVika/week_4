// Matr_transp.cpp : Defines the entry point for the console application.
//Задана квадратна матриця дійсних чисел m × m. Написати програму   транспонування цiєї матрицi 
//(помiняти рядки iз стовпцями). Матрицю задати  в класі Matr. Розмірність задати в головній програмі константою. 
#include "stdafx.h"
#include<iostream>
#include<iomanip>
using namespace std;
typedef unsigned short int ui;
const ui N=4;
class Matr{			
	float **m;
	ui size;
public:
	Matr();								// конструктор без параметрів
	Matr(ui n);				//конструктор з параметрами, n-кількість елементів в матриці; виділяємо ДП
	~Matr();							// в деструкторі звільняємо ДП
	void Create(uinn);
	void Clear();
	Matr(const Matr&);						// конструктор копіювання
	ui Getsize();
	void Setel(ui i,ui j, float ch);	    	//запис елемента матриці в позицію [i][j]
	void Transp();						 //транспонування матриці
	void ShowMatr() const;				// роздрук матриці
};
/////////////////////////////////////////////////////////////
void Matr::Create(ui nn)
{
	size=nn;
	m=new float*[size];
	if (m==NULL) {						//якщо помилка виділення памяті
		cout<<" Error! Can't allocate! not enough memory. ";
		exit(1);
	}
	for(ui i=0; i<size; i++)
	{
		m[i]=new float[size];				
		if (m[i]==NULL) 				//якщо не вдалось виділити память
		{
		cout<<" Error! Can't allocate! not enough memory. ";	//то помилка
		exit(1);						//аварійний вихід
	    }
	}
}
/////////////////////////////////////////////////////////////
Matr::Matr()
{
	Create(N);
}
////////////////////////////////////////////////////////////
Matr::Matr(const Matr& a)
{
	Create(a.size);					//виділяє память під новий елемент
	for( ui i=0; i<size; i++ )      
		 for(ui j=0; j<size; j++ ) 
			m[i][j]=a.m[i][j];		 // копіює значення елементів
}
//////////////////////////////////////////////////////////////
Matr::Matr(ui n)
{
	Create(n);
}
//////////////////////////////////////////////////////////////
void Matr::Clear()					//звільнення виділеної памяті
{
	for(ui i=0; i<size; i++)
		delete[] m[i];
	delete[] m;
	m=NULL;
}
////////////////////////////////////////////////////////////////
Matr::~Matr()
{
	Clear();
}

/////////////////////////////////////////////////////////////
void Matr::Setel(ui i,ui j, float ch){
	if(i<size||i>=0||j<size||j>=0)		//якщо індекс вірний
		m[i][j]=ch;			//записуємо значення в м
	else 
		cout<<"Error!";			//інакще - помилка
}
//////////////////////////////////////////////////////////////
void Matr::Transp()			//здійснює транспонування матриці
{
	float aa;
	for(ui i=0; i<size; i++)
		for(ui j=0; j<size; j++)
			if(i<j)
			{
				aa=m[i][j];
				m[i][j]=m[j][i];
				m[j][i]=aa;
			}
}
//////////////////////////////////////////////////////////////
void Matr::ShowMatr() const			//вивід матриці на екран
{
	for(ui i=0; i<size; i++)
	{
		for(ui j=0; j<size; j++)
			cout<<setw(5)<<m[i][j];
		cout<<endl;
	}
	cout<<endl;
}
////////////////////////////////////////////////////////////////
ui Matr::Getsize()		//повертає розмір матриці
{
	return size;
}
/////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
	ui n;
	cout<<" Enter matrix size: ";
	cin>>n;
	Matr M1(n);
	ui len=M1.Getsize();
	for(ui i=0; i<len; i++)		// заповнюємо матрицю
		for(ui j=0; j<len; j++)
			M1.Setel(i,j,i+j*2);
	cout<<"\n\t Matrix:"<<endl;
	M1.ShowMatr();
	cout<<endl;
	cout<<"\tTransposed matrix: \n";
	M1.Transp();
	M1.ShowMatr();
	system("pause");
	return 0;
}

