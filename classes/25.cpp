// Neighbor.cpp : Defines the entry point for the console application.
//
//25.	������ ������� ������� ��Ѳ��, �������� ��� ��� �����, ���� ����� a � b ����� ������� ������,
//� ������� � � ������������ �������. ������� ��������� ������ �����, �� �� �������� 
//������� ����� ����� ���������� ����.//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
using namespace std;
typedef unsigned short int ui;
const ui N=6;   // ������� ����
///////////////////////////////////////////////////////////////////
class CountryNeigh{
	bool **has;					//��� ������ �������
	ui size;
	char **c;					//��� ���� ����
public:
	CountryNeigh( );			//����������� ��� ���������
	CountryNeigh::CountryNeigh( ui n );		//����������� � �����������
	CountryNeigh( const CountryNeigh & c );			//����������� ���������
	~CountryNeigh( );
	void Create( ui n );			//�������� ����� �� ����
	void Clear();					//��������� ������� �����
	ui GetSize( ) const;			//������� �����(������� ����)
	void Set( );					//��� ���������� ��� �������� ����� � ����� � ����
	void Put( ) const;					//����			
	void FindCountry() const;			//������� ����� ����� � ���� �-��� �����
	char* PutCountries( ui i );			//�� ������ �� ����
};
////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
	ui num, len;
	cout<<"Enter a number of countries: ";
	cin>>num;
	CountryNeigh cn(num);
	len=cn.GetSize();			//� len - ������� ����
	cout<<"Enter countries: ";
	for(ui i=0; i<len; i++){
		cout<<i+1<<". ";
		cin>>cn.PutCountries(i);		//��� ���� ��� ������
	}
	cout<<"\t";
	for(ui i=0; i<len; i++ )
		cout<<cn.PutCountries(i)<<" ";		//���� ���� ����
	cout<<endl;
	cn.Set();							//��� ���������� ��� �������� ����� ��� ����� � ����
	cn.FindCountry();					//����� ����� � ��������� ������� �����
	cout<<endl;
	system("pause");		
	return 0;
}
///////////////////////////////////////////////////////////////
CountryNeigh::CountryNeigh( ){		//����������� ��� ���������
	Create( N );
}

///////////////////////////////////////////////////////////////
CountryNeigh::CountryNeigh( ui n ){		
	Create( n );
}
/////////////////////////////////////////////////////
void CountryNeigh::Create( ui n ){
	size=n;
	has=new bool*[size];					//������ ���� �� ������ ������� � ��� ��� �-��� �����
	if(has==NULL) {							//������� �������� �����
		cout<<"Error!Cant allocate memory"; 
		exit(1);
	}
	for( ui i=0; i<size; i++ )	{		
		has[i]=new bool[size];			
		if(has[i]==NULL) { 
			cout<<"Error!Cant allocate memory";  exit(1); }
	}

	c=new char*[size];					//�������� ����� �� ����� � ������� ����
	if(c==NULL) {						//������� �������� �����
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
CountryNeigh::CountryNeigh( const CountryNeigh & c ){		//���������� ���������
	Create(c.size);
	for( ui i=0; i<size; i++ )	     
		for( ui j=0; j<size; j++ )	
			has[i][j]=c.has[i][j];		// ����� �������� ��������
}
//////////////////////////////////////////////////////////////////
void CountryNeigh::Clear(){
	for( ui i=0; i<size; i++ )			//������� �������
		delete[] has[i];				//�� ������� 
	delete []has;						//������
	
	for( ui i=0; i<size; i++ )			//������� �������
		delete[] c[i];				//�� ����� � ������� ����
	delete []c;						//������
	size=0;
	has=NULL;
	c=NULL;
}
//////////////////////////////////////////////////////
CountryNeigh::~CountryNeigh( ){			//����������
	Clear( );
}
////////////////////////////////////////////////////////////////////
void CountryNeigh::FindCountry( ) const{    //����� ����� � ��������� �-��� �����
	ui sum[N], imax=0;
	for(ui i=0; i<size; i++){       //���� ������� ����� ��� ����� ����� � �������� � ������� ������
		ui s=0;
		for(ui j=0; j<size; j++){
			if(has[i][j]==true)
				s++;
		}
		sum[i]=s;
	}
	for(ui i=0; i<size; i++)           //��������� ����������� ����� ��������
		if(sum[i]>sum[imax]) 
			imax=i;
	cout<<"\n Country with max number of neighbors: ";
	cout<<c[imax];						//���� �����
}

/////////////////////////////////////////////////////////////////////////
ui CountryNeigh::GetSize( ) const{			//������� ������� ����
	return size;
}
////////////////////////////////////////////////////////////////////////
char* CountryNeigh::PutCountries( ui i){		//��� ������� �� ����(���/����)
	if ( i>=0 || i<size ) return *(c+i);
	else return 0;
}
/////////////////////////////////////////////////////////////////////////
 void CountryNeigh::Set( ) {				//��� ������ �������
	for(ui i=0; i<size; i++){
		cout<<PutCountries( i )<<"      ";		//���� ���� ����
		for(ui j=0; j< size; j++){
			cin>>has[i][j];
		}
	}
}
 ///////////////////////////////////////////////////////////////////////
 void CountryNeigh::Put() const{			//���� ������ ������� 
	 for(ui i=0; i<size; i++){
		for(ui j=0; j< size; j++)
			cout<<has[i][j]<<"    ";
		cout<<endl;
	}
 }