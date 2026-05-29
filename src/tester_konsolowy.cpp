#include "tester_konsolowy.h"
#include "plansza.h"
#include "algorytm.h"
#include <iostream>

using namespace std;

void TesterKonsolowy::uruchomTest() {
    cout << "=============================================================" << endl;
    cout << "  TEST LOGIKI BIZNESOWEJ I INTERFEJSU TEKSTOWEGO (ASCII)" << endl;
    cout << "=============================================================" << endl;

    // 1. Tworzymy planszę testową 12 wierszy na 12 kolumn
    Plansza plansza(12, 12);
    
    // Ustawiamy punkty startu i celu
    plansza.ustawStart(Punkt(1, 1));
    plansza.ustawCel(Punkt(10, 10));

    // 2. Budujemy przeszkody ze ścian blokujące prostą ścieżkę
    plansza.ustawTypKomorki(3, 2, TypKomorki::Sciana);
    plansza.ustawTypKomorki(3, 3, TypKomorki::Sciana);
    plansza.ustawTypKomorki(3, 4, TypKomorki::Sciana);
    plansza.ustawTypKomorki(3, 5, TypKomorki::Sciana);
    plansza.ustawTypKomorki(3, 6, TypKomorki::Sciana);
    plansza.ustawTypKomorki(3, 7, TypKomorki::Sciana);
    plansza.ustawTypKomorki(4, 7, TypKomorki::Sciana);
    plansza.ustawTypKomorki(5, 7, TypKomorki::Sciana);

    cout << "Stan planszy poczatkowej (S - start, C - cel, # - sciana, . - wolne):" << endl;
    cout << "----------------------------------------" << endl;
    for (int w = 0; w < plansza.pobierzWiersze(); w++) {
        cout << "  ";
        for (int k = 0; k < plansza.pobierzKolumny(); k++) {
            Punkt p(w, k);
            if (p == plansza.pobierzStart()) {
                cout << "S ";
            } else if (p == plansza.pobierzCel()) {
                cout << "C ";
            } else if (plansza.pobierzTypKomorki(p) == TypKomorki::Sciana) {
                cout << "# ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << "----------------------------------------" << endl;

    // 3. Uruchamiamy algorytm Dijkstry w celach testowych
    AlgorytmDijkstry alg;
    WynikWyszukiwania wynik = alg.szukaj(plansza, plansza.pobierzStart(), plansza.pobierzCel());

    cout << "Status szukania drogi: " << (wynik.znaleziono ? "SUKCES!" : "PORAZKA (droga zablokowana)") << endl;
    
    if (wynik.znaleziono) {
        cout << "Dlugosc wyznaczonej trasy: " << wynik.najkrotszaSciezka.size() << " pol." << endl;
        cout << "Liczba zbadanych (odwiedzonych) komorek: " << wynik.kolejnoscOdwiedzania.size() << endl;
        
        // Zapisujemy wyznaczoną ścieżkę na planszy testowej
        // Pomijamy pierwszy i ostatni element, aby nie nadpisać ikon startu/celu
        for (size_t i = 1; i < wynik.najkrotszaSciezka.size() - 1; i++) {
            plansza.ustawTypKomorki(wynik.najkrotszaSciezka[i], TypKomorki::Sciezka);
        }

        cout << "\nStan planszy końcowej z wyznaczona sciezka (x):" << endl;
        cout << "----------------------------------------" << endl;
        for (int w = 0; w < plansza.pobierzWiersze(); w++) {
            cout << "  ";
            for (int k = 0; k < plansza.pobierzKolumny(); k++) {
                Punkt p(w, k);
                if (p == plansza.pobierzStart()) {
                    cout << "S ";
                } else if (p == plansza.pobierzCel()) {
                    cout << "C ";
                } else if (plansza.pobierzTypKomorki(p) == TypKomorki::Sciana) {
                    cout << "# ";
                } else if (plansza.pobierzTypKomorki(p) == TypKomorki::Sciezka) {
                    cout << "x ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
        cout << "----------------------------------------" << endl;
    }
    
    cout << "=============================================================" << endl;
}
