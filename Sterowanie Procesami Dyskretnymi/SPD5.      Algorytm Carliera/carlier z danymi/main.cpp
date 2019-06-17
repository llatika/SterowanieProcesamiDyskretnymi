#include <iostream>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <iomanip>

using namespace std;

static int numer=1; // potrzebne do liczenia numeru zadania

class zadanie {
	public:
		int r,p,q, numer_zadania;
		int zapamietywane_p; //potrzebne do schrage z podzialem, ktory zmienia wartosc p
		zadanie* nastepny;
		zadanie();
};

zadanie::zadanie() {
	nastepny=0;
	zapamietywane_p=0;
}


class lista {
	public:
		zadanie* pierwszy;

		void push_r(int r, int p, int q);
		void push_q(int r, int p, int q, int numer);
		void push_q(int r, int p, int q, int numer, int zapamietywane_p);
		void push(int r, int p, int q, int numer);
		void show_sam_numer_zadania();
		zadanie* poll();
        int qZadania(int numerZadania);
        int cZadania(int numerZadania);
        int pZadania(int numerZadania);
        int rZadania(int numerZadania);
        int nrZadania(int numerZadania);
        void wyzeruj();
		lista();
		boolean isempty();
};

lista::lista() {
	pierwszy=0;
}

void lista::wyzeruj()
{
    zadanie *next = pierwszy;
    while(next)
    {
        zadanie *tmp = next->nastepny;
        delete(next);
        next=tmp;
    }
    pierwszy = NULL;
}

int lista::qZadania(int numerZadania)
{
    zadanie* tmp = pierwszy;
    for(int i = 0; i < numerZadania; i++)
    {
        tmp = tmp->nastepny;
    }
    return tmp->q;
}

int lista::cZadania(int numerZadania)
{
    zadanie* tmp = pierwszy;
    int c = 0;
    int t = 0;
    for(int i = 0; i < numerZadania + 1; i++)
    {
        t = max(t, tmp->r) + tmp->p;
        c = max(c, t + tmp->q);
        tmp = tmp->nastepny;
    }
    return t;
}

int lista::pZadania(int numerZadania)
{
    zadanie* tmp = pierwszy;
    for(int i = 0; i < numerZadania; i++)
    {
        tmp = tmp->nastepny;
    }
    return tmp->p;
}

int lista::rZadania(int numerZadania)
{
    zadanie* tmp = pierwszy;
    for(int i = 0; i < numerZadania; i++)
    {
        tmp = tmp->nastepny;
    }
    return tmp->r;
}

int lista::nrZadania(int numerZadania)
{
    zadanie* tmp = pierwszy;
    for(int i = 0; i < numerZadania; i++)
    {
        tmp = tmp->nastepny;
    }
    return tmp->numer_zadania;
}


void lista::push_q(int r, int p, int q, int numer) {
	zadanie *nowy = new zadanie;

	nowy->r=r;
	nowy->p=p;
	nowy->q=q;
	nowy->numer_zadania=numer;
    nowy->nastepny=0;

	if(pierwszy == 0) {
        pierwszy = nowy;
    }
    else {
      zadanie *wsk = pierwszy;
        if(pierwszy->q < nowy->q) {
            nowy->nastepny = pierwszy;
            pierwszy = nowy;
        }

        else {

            while((wsk->nastepny) && (wsk->nastepny->q >= nowy->q)) {
                wsk= wsk->nastepny;
            }
                nowy->nastepny = wsk->nastepny;
                wsk->nastepny = nowy;
        }
	}
}

void lista::push_q(int r, int p, int q, int numer, int zapamietywane_p) {
	zadanie *nowy = new zadanie;

	nowy->r=r;
	nowy->p=p;
	nowy->q=q;
	nowy->numer_zadania=numer;
	nowy->zapamietywane_p=zapamietywane_p;
    nowy->nastepny=0;

	if(pierwszy == 0) {
        pierwszy = nowy;
    }
    else {
      zadanie *wsk = pierwszy;
        if(pierwszy->q < nowy->q) {
            nowy->nastepny = pierwszy;
            pierwszy = nowy;
        }

        else {

            while((wsk->nastepny) && (wsk->nastepny->q >= nowy->q)) {
                wsk= wsk->nastepny;
            }
                nowy->nastepny = wsk->nastepny;
                wsk->nastepny = nowy;
        }
	}
}



void lista::push_r(int r, int p, int q) {
	zadanie *nowy = new zadanie;

	nowy->r=r;
	nowy->p=p;
	nowy->q=q;
    nowy->nastepny=0;
    nowy->numer_zadania=numer;
    numer++;

	if(pierwszy == 0) {
        pierwszy = nowy;
    }

    else {
      zadanie *wsk = pierwszy;
        if(pierwszy->r > nowy->r) {
            nowy->nastepny = pierwszy;
            pierwszy = nowy;
        }

        else {

            while((wsk->nastepny) && (wsk->nastepny->r <= nowy->r)) {
                wsk= wsk->nastepny;
            }
                nowy->nastepny = wsk->nastepny;
                wsk->nastepny = nowy;
        }
	}
}


void lista::push(int r, int p, int q, int numer) {
	zadanie *nowy = new zadanie;

	nowy->r=r;
	nowy->p=p;
	nowy->q=q;
	nowy->numer_zadania=numer;

	if(pierwszy==0) {
		pierwszy=nowy;
	}
	else {
		zadanie* tmp = pierwszy;

		while (tmp->nastepny){
			tmp=tmp->nastepny;
		}
		tmp->nastepny = nowy;
		nowy->nastepny=0;
	}

}

void lista::show_sam_numer_zadania() {
	zadanie* tmp = pierwszy;
	while(tmp){
		cout << setw(5) << tmp->numer_zadania;
		tmp=tmp->nastepny;
	}
}




zadanie* lista::poll() {
    zadanie *tmp = pierwszy;
    pierwszy = tmp->nastepny;
   	 return tmp;
    	delete tmp;
}


boolean lista::isempty(){
	if(pierwszy)
		return false;
	else
		return true;
}



int schrage(lista *permutacje1, int liczba_zadan, int liczba_kolumn) {

	int t=0,k=0,cmax=0;
	int r, p,q;


	lista *N = new lista;
	lista *G = new lista;
	lista *permutacje = new lista;
	zadanie* tmp = N->pierwszy;
	zadanie* e = new zadanie;


	int **tmptab = new int *[liczba_zadan];             // ALOKACJA TABLICY
    for(int i = 0; i < liczba_zadan; i++)
        tmptab[i] = new int [liczba_kolumn + 1];
    for(int i = 0; i < liczba_zadan; i++)
    {
        tmptab[i][0] = i;
        tmptab[i][1] = permutacje1->rZadania(i);
        tmptab[i][2] = permutacje1->pZadania(i);
        tmptab[i][3] = permutacje1->qZadania(i);
    }
    permutacje1->wyzeruj();
    for(int i=0;i<liczba_zadan;i++){
		//plik >> r >> p >> q;
		r = tmptab[i][1];
		p = tmptab[i][2];
		q = tmptab[i][3];
		N->push_r(r,p,q);
	}



	while(!N->isempty() || !G->isempty()) {
		while(!N->isempty() && (N->pierwszy->r <= t)){
			e=N->poll();
			G->push_q(e->r, e->p, e->q, e->numer_zadania);
		}

		if(G->isempty()){
			tmp = N->pierwszy;
			t=tmp->r;
		}

		else {
			e=G->poll();
			t=t+e->p;
			permutacje1->push(e->r, e->p, e->q, e->numer_zadania);

			cmax=max(cmax, t+e->q);
		}

	}

	return cmax;
}

int schrage_przerwania(lista *permutacje1, int liczba_zadan, int liczba_kolumn) {
	int t=0,k=0,q0=99999999,cmax=0;
	int r,p,q;
	numer = 1;
	lista *permutacje2 = new(lista);

	lista *N = new lista;
	lista *G = new lista;
	zadanie* tmp = N->pierwszy;
	zadanie* e = new zadanie;
	zadanie* l = new zadanie;
	numer=1;

	int **tmptab = new int *[liczba_zadan];             // ALOKACJA TABLICY
    for(int i = 0; i < liczba_zadan; i++)
        tmptab[i] = new int [liczba_kolumn + 1];
    for(int i = 0; i < liczba_zadan; i++)
    {
        tmptab[i][0] = i;
        tmptab[i][1] = permutacje1->rZadania(i);
        tmptab[i][2] = permutacje1->pZadania(i);
        tmptab[i][3] = permutacje1->qZadania(i);
    }

    for(int i=0;i<liczba_zadan;i++){

		r = tmptab[i][1];
		p = tmptab[i][2];
		q = tmptab[i][3];
		N->push_r(r,p,q);
	}

	while(!N->isempty() || !G->isempty()) {
		while(!N->isempty() && (N->pierwszy->r <= t)){
			e=N->poll();
			G->push_q(e->r, e->p, e->q, e->numer_zadania);
				if(e->q > l->q){
					l->zapamietywane_p=l->p;
					l->p=t-e->r;
					t=e->r;

					if(l->p > 0) {
						G->push_q(l->r, l->p, l->q, l->numer_zadania, l->zapamietywane_p);
					}
				}
		}

		if(G->isempty()){
			tmp = N->pierwszy;
			t=tmp->r;
		}

		else {
			e=G->poll();
			l=e;
			t=t+e->p;
			if(e->zapamietywane_p!=0){

			permutacje2->push(e->r, e->zapamietywane_p, e->q, e->numer_zadania);
		}
			else{
			permutacje2->push(e->r, e->p, e->q, e->numer_zadania);
		}

			cmax=max(cmax, t+e->q);

		}

	}
    return cmax;
}

int carlier(lista *permutacje, int UB) {
    int n, U, LB;
    int r_2 = 9999999, q_2 = 9999999, p_2 = 0;
    int UB_tmp = -1;
    lista *temp = new(lista);
    lista *temp2 = new(lista);
    numer = 1;
    n = 50;
    U = schrage(permutacje, n, 3);
    if(U < UB)
    {
        UB = U;
    }
    // wyznaczanie B
    int B = 0;
    bool nie_znalazl_B = true;

    for (int i = n - 1; nie_znalazl_B && i > 0; i--)
    {
        if (U == (permutacje->qZadania(i) + permutacje->cZadania(i)))
        {
            nie_znalazl_B = false;
            B = i;

        }
    }
    // wyznaczanie A
    int A, tmp = 0;
    bool nie_znalazl_A = true;
    for (int i = 0; i < B && nie_znalazl_A; i++)
    {
        tmp = 0;
        for (int j = i; j <= B; j++)
        { //liczy ile wykonuja sie wszyskie zadania
            tmp += permutacje->pZadania(j);
        }//jezeli jest to zadanie ktore najdluzej czeka
        if (U == (tmp + permutacje->rZadania(i) + permutacje->qZadania(B)))
        {
            nie_znalazl_A = false;
            A = i;  // nr 1 zad w sciezce krytycznej

        }
    }
    //wyznaczanie C--numer zadania
    int C = -1;
    bool nie_znalazl_C = true;
    for (int i = B; nie_znalazl_C && i >= A; i--) {
        if (permutacje->qZadania(i) < permutacje->qZadania(B)) {//pierwsze zad kotergo q jest mniejsze niz zadania max
            nie_znalazl_C = false;
            C = i;
        }
    }
    if (C == -1) {//nie znalazl zadania int -> Schrage jest optymalny
        return UB;
    }

    for (int i = C + 1; i <= B; i++) // tworzymy r(k),p(k),q(k)
    {
        r_2 = min(r_2, permutacje->rZadania(i)); // min r
        p_2 += permutacje->pZadania(i); // suma p
        q_2 = min(q_2, permutacje->qZadania(i)); // min q
    }

    int r_tmp = max(permutacje->rZadania(C), r_2 + p_2);
    int r_do_wrzutki = max(r_tmp, r_2 + p_2);// rPI(c)
    temp->wyzeruj();
    for(int i = 0; i < n; i++)
    {
        temp->push(permutacje->rZadania(i), permutacje->pZadania(i), permutacje->qZadania(i), permutacje->nrZadania(i));
        //temp -> permutacja, nastepnie zerujemy permutacje i permutacja == permutacje ze zmienionym r
    }
    permutacje->wyzeruj();
    for(int i = 0; i < n; i++)
    {
        if(i == C)
            permutacje->push(r_do_wrzutki, temp->pZadania(i), temp->qZadania(i), temp->nrZadania(i));
        else
            permutacje->push(temp->rZadania(i), temp->pZadania(i), temp->qZadania(i), temp->nrZadania(i));
    }
    LB = schrage_przerwania(permutacje, n, 3);
    if(LB < UB)
    {
        UB_tmp = carlier(permutacje, UB);
        if (UB_tmp != -1 && UB_tmp < UB) // jezeli zadzialalo
            UB = UB_tmp;

    }
    permutacje->wyzeruj();
    for(int i = 0; i < n; i++) // odtwarzamy rPI(C)
    {
        if(i == C)
            permutacje->push(r_tmp, temp->pZadania(i), temp->qZadania(i), temp->nrZadania(i));
        else
            permutacje->push(temp->rZadania(i), temp->pZadania(i), temp->qZadania(i), temp->nrZadania(i));
    }


    int q_tmp = permutacje->qZadania(C);
    int q_do_wrzutki = max(q_tmp, q_2 + p_2);

    temp2->wyzeruj();
    for(int i = 0; i < n; i++)//temp2->permutacje
    {
        temp2->push(permutacje->rZadania(i), permutacje->pZadania(i), permutacje->qZadania(i), permutacje->nrZadania(i));
    }

    permutacje->wyzeruj();
    for(int i = 0; i < n; i++) //zamieniamy q dla zadania C
    {
        if(i == C)
            permutacje->push(temp2->rZadania(i), temp2->pZadania(i), q_do_wrzutki, temp2->nrZadania(i));
        else
            permutacje->push(temp2->rZadania(i), temp2->pZadania(i), temp2->qZadania(i), temp2->nrZadania(i));
    }

    LB = schrage_przerwania(permutacje, n, 3);
    if(LB < UB)
    {
        UB_tmp = carlier(permutacje, UB);
        if (UB_tmp != -1 && UB_tmp < UB) // jezeli zadzialalo
            UB = UB_tmp;
    }

    return UB;
}


int main() {
	int U, UB=99999999, LB;
	int schrage_przerwania_wynik;
	fstream plik;
	plik.open( "in8.txt", std::ios::in | std::ios::out ); // in4,in6 liczy zle,
	int liczba_zadan, liczba_kolumn, r, p, q;
	plik >> liczba_zadan;
	plik >> liczba_kolumn;

	lista *permutacje1 = new(lista);

	for(int i=0;i<liczba_zadan;i++){
		plik >> r >> p >> q;
		permutacje1->push(r,p,q, i+1);
	}

	cout << carlier(permutacje1, 9999999);
}
