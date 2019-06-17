#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <string>
//#include <conio.h>

using namespace std;

class Element
{
public:
	int r,p,q;     //Inicjalizacja zmiennych r,p,q,czyli terminu dostepnosci zadania,czas wykonania zadania i czas dostarczenia zadania
	
	Element()
    {
		r = p = q = 0;   //Konstruktor: stan poczatkowy wsyztskie wartosci zerowe
	}
	
	void czytaj(fstream &file)  //Funckja wczytujaca dane z pliku
    {
		file >> r >> p >> q;
	}
};

class Sortowanie_q    //Sortowanie zadan wzgledem dlugosci czasu dostarczenia q i-tego zadania raz zwrocenie zadania o najmniejszym q
{
public:
	inline bool operator()
    
    (const Element& el1, const Element& el2)
    {
		return el1.q < el2.q;
	}
};

class Sortowanie_r //Sortowanie zadan wzgledem dlugosci czasu inicjalizacji r i-tego zadania raz zwrocenie zadania o najwiekszym r
{

public:
	inline bool operator().
    (const Element& el1, const Element& el2)
    {
		return el1.r > el2.r;
	}
};

int main(int argc, char *argv[])
{
	char * filename= new char[32];
  fstream plik;
  if(argc > 1)
  {
    plik.open(argv[1], ios::in);
  }
  else
  {
    cout<<"Input path: ";
    cin >> filename;
    plik.open(filename, ios::in);
  }

 	priority_queue <Element, vector<Element>, Sortowanie_q> Kolejka_q;    //Inicjalizacja kolejki priorytetetowej uwzgledniajacej wartosci q
 	priority_queue <Element, vector<Element>, Sortowanie_r> Kolejka_r;    //Inicjalizacja kolejki priorytetetowej uwzgledniajacej wartosci r
 	Element test;
    

 	int n;
	plik >> n;
	for (int j=0;j<n;j++)
    {
	 	test.czytaj(plik);
	 	Kolejka_r.push(test);                                             //Dodanie nowego zadania na koniec kolejki
	}

	int t = 0; //chwila czasowa w ktorej pojawia sie element
	int Cmax = 0;
	Element e;
	while (!Kolejka_q.empty() || !Kolejka_r.empty())
    {
	 	while(!Kolejka_r.empty() && Kolejka_r.top().r <= t){
		 	e = Kolejka_r.top();

		 	Kolejka_q.push(e);
		 	Kolejka_r.pop(); //dodanie najmniejszego r do kolejki q
	 	}
	 	if (Kolejka_q.empty()){ // sprawdzenie czy kolejka q nie jest 0
	 		t = Kolejka_r.top().r; //przekakujemy do nastepnej chwili (nastepne zad. z kolejki r)
	 	}
		else 
        {
		 	e = Kolejka_q.top();//pobieramy kolejna z gory
		 	Kolejka_q.pop();//
		 	t += e.p;
		 	Cmax = max(Cmax, t + e.q);//suma czasu potrzebnego na wykonanie wszystkich zadan
	 	}
	}
 	cout << "Cmax="<<Cmax<<endl;
 	return 0;
}
