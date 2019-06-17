#include <iostream>
#include <fstream>
#include <algorithm>
#include <curses.h>
#include <iomanip>
using namespace std;


int stworz_macierz(int liczba_zadan, int liczba_maszyn, int z_ilu_zadan, int z_ilu_maszyn, int** skad_brac, int** do_operacji)
{


    int **wynikowa = new int *[z_ilu_zadan + 1];             // ALOKACJA TABLICY
    for(int i = 0; i < z_ilu_zadan + 1; i++)
        wynikowa[i] = new int [z_ilu_maszyn + 2]; // tworzenie nowej tablicy wynikowa[z_ilu_zadan+1][z ilu maszyn +2]
    for(int i = 0; i < z_ilu_zadan + 1; i++){
        for(int j = 0; j < z_ilu_maszyn + 2; j++)
            wynikowa[i][j] = 99999;                 //wpisanie wartosci 99999 do calej tablicy
    }

    int **tablica = new int *[z_ilu_zadan + 1];             // ALOKACJA TABLICY
    for(int i = 0; i < z_ilu_zadan + 1; i++)
        tablica[i] = new int [z_ilu_maszyn + 2];
    for(int j = 0; j < z_ilu_maszyn + 2; j++){              // zapelnianie zerami calej tablicy - pierwsza kolumna i drugi wiersz takie zostana
        for(int i = 0; i < z_ilu_zadan + 1; i++)
            tablica[i][j] = 0;
    }

    for(int k = 1; k < z_ilu_zadan + 1; k++){                  // tworzenie (wszystkich kombinacji np. 4123, 1423, 1243, 1234) do tego jest petla for k

        for(int i = 1; i < z_ilu_zadan + 1; i++){       
            for(int j = 0; j < z_ilu_maszyn + 2; j++){          
                if(i < k){                                   
                    if(j == 0)
                        tablica[i][j] = do_operacji[i-1][z_ilu_maszyn + 1];                                                     
                    else if(j == 1)                                                                                            
                        tablica[i][j] = 0;                                                                                      
                    else                                                                                                       
                        tablica[i][j] = max(tablica[i-1][j], tablica[i][j-1]) + do_operacji[i-1][j-2];                          
                }                                                                                                               
                if(i == k){                                                                                                     
                    if(j == 0)                                                                                                  
                        tablica[i][j] = do_operacji[z_ilu_zadan - 1][z_ilu_maszyn + 1];                                         
                    else if(j == 1)
                        tablica[i][j] = 0;
                    else
                        tablica[i][j] = max(tablica[i-1][j], tablica[i][j-1]) + do_operacji[z_ilu_zadan - 1][j-2];
                }
                if(i > k){
                    if(j == 0)
                        tablica[i][j] = do_operacji[i-2][z_ilu_maszyn + 1];
                    else if(j == 1)
                        tablica[i][j] = 0;
                    else
                        tablica[i][j] = max(tablica[i-1][j], tablica[i][j-1]) + do_operacji[i-2][j-2];
                }
            }
        }
        if(tablica[z_ilu_zadan][z_ilu_maszyn + 1] < wynikowa[z_ilu_zadan][z_ilu_maszyn + 1]){           // nadpisywanie wynikowej
            for(int i = 0; i < z_ilu_zadan + 1; i++){
                for(int j = 0; j < z_ilu_maszyn + 2; j++){
                    wynikowa[i][j] = tablica[i][j];
                }
            }
        }

    }

    c = wynikowa[z_ilu_zadan][z_ilu_maszyn + 1];// nasze cmax
    for(int i = 1; i < z_ilu_zadan + 1; i++){
        for(int j = 0; j < z_ilu_maszyn + 2; j++){
            do_operacji[i - 1][j] = skad_brac[wynikowa[i][0] - 1][j];
        }

    }

    return c;
}

int main() {
    int liczba_maszyn, liczba_zadan, tmp, cmax = -1;
    fstream plik;
    int **wejsciowe;
    int **do_operacji;
    plik.open( "ta071.txt", std::ios::in | std::ios::out );


        if( plik.good() == true ) {

        plik >> liczba_zadan;                        // wczytywanie pierwszych 2 danych
        plik >> liczba_maszyn;
        }
        wejsciowe = new int *[liczba_zadan];
        for(int i = 0; i < liczba_zadan; i++)
            wejsciowe[i] = new int [liczba_maszyn + 2];   // tworzenie 2 wymiarowej tablicy
        for(int i = 0; i < liczba_zadan; i++){
            for(int j = 0; j < liczba_maszyn; j++){

                plik >> wejsciowe[i][j];              //wpisanie danych z pliku do tablicy 2 wymiarowej
            }
        }
        for(int i = 0; i < liczba_zadan; i++){                           //  tutaj jest tworzona podwojna tablica; wejsciowe[liczba zadan][liczba maszyn+2]
            wejsciowe[i][liczba_maszyn] = 0;                             // Kolumn jest o 2 wiecej, poniewaz majac 4 maszyny zadeklarowane mamy tablice indeksowana od 0 do 3( gdzie sa wartosci z pliku)
            wejsciowe[i][liczba_maszyn + 1] = i + 1;                    // w tablicy indeksowanej[i][liczbamaszyn](czyli indeks 4) mamy wpisane wszedzie 0, a 2 linijki nizej mamy tam sumy poszczegolnych zadan.
            for(int j = 0; j < liczba_maszyn; j++)                      // w indeksie wejsciowe[i][liczba maszyn+1] mamy po prostu wpisane wartosci od 1 do [liczby zadan] i jest to numeracja zadan potrzebna do wyswietlania kolejnosci
                wejsciowe[i][liczba_maszyn] += wejsciowe[i][j];             // tworzenie wiersza sumy -
        }

        do_operacji = new int *[liczba_zadan];        // TABLICA DO OPERACJI
        for(int i = 0; i < liczba_zadan; i++){
            do_operacji[i] = new int [liczba_maszyn + 2]; //tworzenie podwojnej tablicy(macierz)
            for(int j = 0; j < liczba_maszyn + 2; j++)
                do_operacji[i][j] = wejsciowe[i][j];  //do operacji == wejsciowe
        }
        for( int i = 0; i < liczba_zadan; i++ ){            // sortowanie od najwiekszych sum
            for( int j = 0; j < liczba_zadan - 1; j++ ){
                if(do_operacji[j][liczba_maszyn] < do_operacji[j + 1][liczba_maszyn]){  //jak if znajdzie sume>poprzedniej to zamienia miejscami( sortowanie babelkowe)
                    for(int k = 0; k < liczba_maszyn + 2; k++){
                        tmp = do_operacji[j][k];
                        do_operacji[j][k] = do_operacji[j + 1][k];
                        do_operacji[j + 1][k] = tmp;
                    }
                }
            }
        }

        for(int i = 2; i < liczba_zadan + 1; i++)   
            cmax = stworz_macierz(liczba_zadan, liczba_maszyn, i, liczba_maszyn, wejsciowe, do_operacji);

        cout << endl << "Kolejnosc zestawu to: ";
        for(int i = 0; i < liczba_zadan; i++){

            cout << do_operacji[i][liczba_maszyn + 1] << " ";  // indeks  do_operacji[i][liczba_maszyn + 1] oznacza kolumne w kt�rej jest numer zadania.
        }
        cout << endl << "Cmax zestawu: " << cmax;


    plik.close();



}
