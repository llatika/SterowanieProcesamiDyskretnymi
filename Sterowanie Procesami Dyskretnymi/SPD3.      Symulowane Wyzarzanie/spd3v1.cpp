#include <iostream>
#include <fstream>
#include <conio.h>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;
 void reset(int liczba_zadan,int liczba_maszyn, int** wejsciowe, int** do_operacji)
 {
    for(int i = 0; i < liczba_zadan; i++)
    {
            for(int j = 0; j < liczba_maszyn+1; j++)
        {
                do_operacji[i][j]=wejsciowe[i][j];
        }
    }
 }
 void zamien(int liczba_zadan,int liczba_maszyn, int** wejsciowe, int** do_operacji)
 {

     int v1 = rand() % liczba_zadan;
     int v2 = rand() % liczba_zadan;
    for(int i =0;i<=liczba_maszyn+1;i++)
    {
        do_operacji[v1][i]=wejsciowe[v2][i];
        do_operacji[v2][i]=wejsciowe[v1][i];


    }

 }
 int liczcmax(int liczba_zadan,int liczba_maszyn, int** wejsciowe)
 {
     int tablica[liczba_zadan+1][liczba_maszyn+1];

    for(int i=0;i<liczba_zadan+1;i++)
    {
        for(int j = 0;j<liczba_maszyn+1;j++)
        {

           if( i==0 || j==0)
           {
               tablica[i][j]=0;
           }
           else
           {
               tablica[i][j]=wejsciowe[i-1][j-1]+max(tablica[i][j-1],tablica[i-1][j]);
           }
        }

    }
int a=tablica[liczba_zadan][liczba_maszyn];
return a;
 }

 bool czyprzejdzie(int a,int b,float temp)
 {
     double p;
     if(a<b) p=1;
     else
     {
         p=(exp((b-a)/temp));
     }

      double r = ((double) rand() / (RAND_MAX));
      if(p>=r)
      {
          return true;
      }
      else
      {
          return false;
      }


 }
int main() {
    srand (time(NULL));
    int liczba_maszyn, liczba_zadan,tmp=0,c=0,b=0;
    fstream plik;
    int **wejsciowe, **do_operacji;
    float wspl=0.99,temp=30;
    plik.open( "ta071.txt", std::ios::in | std::ios::out );


        if( plik.good() == true ) {

        plik >> liczba_zadan;                        // wczytywanie pierwszych 2 danych
        plik >> liczba_maszyn;
        }
        wejsciowe = new int *[liczba_zadan];
        do_operacji = new int *[liczba_zadan];
        for(int i = 0; i < liczba_zadan; i++)
        {
            wejsciowe[i] = new int [liczba_maszyn+1];   // tworzenie 2 wymiarowej tablicy
            do_operacji[i] = new int [liczba_maszyn+1];
        }

        for(int i = 0; i < liczba_zadan; i++){
            for(int j = 0; j < liczba_maszyn; j++){

                plik >> wejsciowe[i][j];
                do_operacji[i][j]=wejsciowe[i][j];

            }

        }

while(tmp<1000)
{
    reset(liczba_zadan,liczba_maszyn,wejsciowe,do_operacji);
    zamien(liczba_zadan,liczba_maszyn,wejsciowe,do_operacji);
     c=liczcmax(liczba_zadan,liczba_maszyn,wejsciowe);
     b=liczcmax(liczba_zadan,liczba_maszyn,do_operacji);
    if(czyprzejdzie(b,c,temp))
    {
        temp = temp * wspl;
        for(int i=0;i<liczba_zadan;i++)
        {
            for(int j=0;j<liczba_maszyn;j++)
            {
                wejsciowe[i][j]=do_operacji[i][j];

            }

        }
        for(int x=0;x<liczba_zadan;x++)
        {
            wejsciowe[x][liczba_maszyn+1]=do_operacji[x][liczba_maszyn+1];
        }
    }
    else
    {
        temp = temp * wspl;
    }


tmp++;
}
cout<<"Temperatura wynosi  " <<temp<<endl;
cout<<"cmax wynosi   "<<c<<endl;
 plik.close();
}
