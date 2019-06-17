#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>

#define size_tab 5 //ilosc zadan
using namespace std;
void wyswietl_perm(int *tab1,int *tab2, int *kolej) //wyswietlanie tab1 i tab2
{
    for(int i=0;i<size_tab;i++)
        {
    int c=kolej[i];
     cout<<"["<<tab1[c]<<","<<tab2[c]<<"]"<<",";
        }
}








int main()
{
    int a = 0; //potrzebne do petli while
    int j = 0;
    int f = 1;
int najmniejsza=999; // potrzebna do porownania najmniejszej wartosci w tabeli 1
int najmniejsza2=999; // potrzebna do porownania najmniejszej wartosci w tabeli 2
int tab1[size_tab]; //maszyna 1
int tab2[size_tab]; //maszyna 2

int bufor1[size_tab]; //potrzebne do wyswietlania, bo pozniej zmieniamy tab1 i tab2
int bufor2[size_tab];
int kolej2=99; //ustalanie kolejnosci tabeli 2
int kolej1=99; //ustalanie kolejnosci tabeli 1
int kolejnosc[size_tab];
cout<<"      M1   M2"<<endl;
srand( time( NULL ) );
for(int i=0;i<size_tab;i++)
    {
    tab1[i]=rand() % 50 + 1; // generuj numer od 1 do 50, czas wykonania zadan maszyny 1
    tab2[i]=rand() % 50 + 1; // generuj numer od 1 do 50, czas wykonania zadan maszyny 2
    cout<<"zad"<<i+1<<"  "<< tab1[i]<<"  "<<tab2[i]<<endl; //wypisz zadania i ich czas;
    bufor1[i]=tab1[i];
    bufor2[i]=tab2[i];

    }

//jhonson

while(a<size_tab)
{
for(int i=0;i<size_tab;i++)
{
   if(tab1[i]<najmniejsza)
   {
       najmniejsza=tab1[i];
       kolej1=i;
   }
    else if(tab1[i]==najmniejsza && najmniejsza!=999) // jesli 2 czasy na maszynie 1 sa takie same to wybrac pierwszy ten z dluzszym czasem na maszynie 2.
    {
       if(tab2[i]>tab2[kolej1])
       {
          najmniejsza=tab1[i];
          kolej1=i;
       }

    }

   if(tab2[i]<najmniejsza2)
   {
       najmniejsza2=tab2[i];
       kolej2=i;
   }
    else if(tab2[i]==najmniejsza2 && najmniejsza2!=999) // jesli 2 czasy na maszynie 2 sa takie same to wybrac pierwszy ten z dluzszym czasem na maszynie 1.
    {
       if(tab1[i]>tab1[kolej2])
       {
          najmniejsza2=tab2[i];
          kolej2=i;
       }

    }
}

if(najmniejsza2>=najmniejsza)
{
    kolejnosc[0+j]=kolej1;
    j +=1;
    tab1[kolej1]=1000;
    tab2[kolej1]=1000;
    najmniejsza=999;gimnazjalna 
    najmniejsza2=999;
}
else
    {
        kolejnosc[size_tab-f]=kolej2;
    f +=1;
    tab2[kolej2]=1000;
    tab1[kolej2]=1000;
    najmniejsza2=999;
    najmniejsza=999;
    }


a +=1;
}
wyswietl_perm(bufor1,bufor2,kolejnosc);
}
