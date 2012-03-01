// Neighbor.cpp : Defines the entry point for the console application.
//
//25.	Задана бульова матриця СУСІДИ, елементи якої рівні істині, якщо країни a і b мають спільний кордон,
//і хибності — в протилежному випадку. Скласти процедуру пошуку країни, що має найбільшу 
//кількість сусідів серед перелічених країн.//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
using namespace std;
typedef unsigned short int ui;
const ui N=6;   // кількість країн
///////////////////////////////////////////////////////////////////
class CountryNeigh{
	bool **has;					//для булевої матриці
	ui size;
	char **c;					//для назв країн
public:
	CountryNeigh( );			//конструктор без параметрів
	CountryNeigh::CountryNeigh( ui n );		//конструктор з параметрами
	CountryNeigh( const CountryNeigh & c );			//конструктор копіювання
	~CountryNeigh( );
	void Create( ui n );			//виділення памяті під обєкт
	void Clear();					//звільнення виділеної памяті
	ui GetSize( ) const;			//повертає розмір(кількість країн)
	void Set( );					//ввід інформації про наявність сусідів у кожної з країн
	void Put( ) const;					//вивід			
	void FindCountry() const;			//здійснює пошук країни з макс к-стю сусідів
	char* PutCountries( ui i );			//дає доступ до країн
};
////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
	ui num, len;
	cout<<"Enter a number of countries: ";
	cin>>num;
	CountryNeigh cn(num);
	len=cn.GetSize();			//в len - кількість країн
	cout<<"Enter countries: ";
	for(ui i=0; i<len; i++){
		cout<<i+1<<". ";
		cin>>cn.PutCountries(i);		//ввід країн для аналізу
	}
	cout<<"\t";
	for(ui i=0; i<len; i++ )
		cout<<cn.PutCountries(i)<<" ";		//вивід назв країн
	cout<<endl;
	cn.Set();							//ввід інформації про наявність сусідів для кожної з країн
	cn.FindCountry();					//пошук країни з найбільшою кількістю сусідів
	cout<<endl;
	system("pause");		
	return 0;
}
///////////////////////////////////////////////////////////////
CountryNeigh::CountryNeigh( ){		//конструктор без параметрів
	Create( N );
}

///////////////////////////////////////////////////////////////
CountryNeigh::CountryNeigh( ui n ){		
	Create( n );
}
/////////////////////////////////////////////////////
void CountryNeigh::Create( ui n ){
	size=n;
	has=new bool*[size];					//виділяє місце під булеву матрицю з інф про к-сть сусідів
	if(has==NULL) {							//помилка виділення памяті
		cout<<"Error!Cant allocate memory"; 
		exit(1);
	}
	for( ui i=0; i<size; i++ )	{		
		has[i]=new bool[size];			
		if(has[i]==NULL) { 
			cout<<"Error!Cant allocate memory";  exit(1); }
	}

	c=new char*[size];					//виділення памяті під масив з назвами країн
	if(c==NULL) {						//помилка виділення памяті
		cout<<"Error!Cant allocate memory"; 
		exit(1);
	}
	for( ui i=0; i<size; i++ )	{		
		c[i]=new char[20];			
		if(c[i]==NULL) { 
			cout<<"Error!Cant allocate memory";  exit(1); }
	}
}
///////////////////////////////////////////////////////////////
CountryNeigh::CountryNeigh( const CountryNeigh & c ){		//коструктор копіювання
	Create(c.size);
	for( ui i=0; i<size; i++ )	     
		for( ui j=0; j<size; j++ )	
			has[i][j]=c.has[i][j];		// копіює значення елементів
}
//////////////////////////////////////////////////////////////////
void CountryNeigh::Clear(){
	for( ui i=0; i<size; i++ )			//звільняє виділену
		delete[] has[i];				//під матрицю 
	delete []has;						//память
	
	for( ui i=0; i<size; i++ )			//звільняє виділену
		delete[] c[i];				//під масив з назвами країн
	delete []c;						//память
	size=0;
	has=NULL;
	c=NULL;
}
//////////////////////////////////////////////////////
CountryNeigh::~CountryNeigh( ){			//деструктор
	Clear( );
}
////////////////////////////////////////////////////////////////////
void CountryNeigh::FindCountry( ) const{    //пошук країни з найбільшою к-стю сусідів
	ui sum[N], imax=0;
	for(ui i=0; i<size; i++){       //рахує кількість сусідів для кожної країни і заносить у окремий вектор
		ui s=0;
		for(ui j=0; j<size; j++){
			if(has[i][j]==true)
				s++;
		}
		sum[i]=s;
	}
	for(ui i=0; i<size; i++)           //знаходить максимальне число входжень
		if(sum[i]>sum[imax]) 
			imax=i;
	cout<<"\n Country with max number of neighbors: ";
	cout<<c[imax];						//вивід країни
}

/////////////////////////////////////////////////////////////////////////
ui CountryNeigh::GetSize( ) const{			//повертає кількість країн
	return size;
}
////////////////////////////////////////////////////////////////////////
char* CountryNeigh::PutCountries( ui i){		//для доступу до країн(ввід/вивід)
	if ( i>=0 || i<size ) return *(c+i);
	else return 0;
}
/////////////////////////////////////////////////////////////////////////
 void CountryNeigh::Set( ) {				//ввід булевої матриці
	for(ui i=0; i<size; i++){
		cout<<PutCountries( i )<<"      ";		//вивід назв країн
		for(ui j=0; j< size; j++){
			cin>>has[i][j];
		}
	}
}
 ///////////////////////////////////////////////////////////////////////
 void CountryNeigh::Put() const{			//вивід булевої матриці 
	 for(ui i=0; i<size; i++){
		for(ui j=0; j< size; j++)
			cout<<has[i][j]<<"    ";
		cout<<endl;
	}
 }