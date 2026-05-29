#include "tester_konsolowy.h"
#include "plansza.h"
#include "algorytm.h"
#include <iostream>

void TesterKonsolowy::uruchomTest() {
    std::cout << "=============================================================" << std::endl;
    std::cout << "  TEST LOGIKI BIZNESOWEJ I INTERFEJSU TEKSTOWEGO (ASCII)" << std::endl;
    std::cout << "=============================================================" << std::endl;

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

    std::cout << "Stan planszy poczatkowej (S - start, C - cel, # - sciana, . - wolne):" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    for (int w = 0; w < plansza.pobierzWiersze(); w++) {
        std::cout << "  ";
        for (int k = 0; k < plansza.pobierzKolumny(); k++) {
            Punkt p(w, k);
            if (p == plansza.pobierzStart()) {
                std::cout << "S ";
            } else if (p == plansza.pobierzCel()) {
                std::cout << "C ";
            } else if (plansza.pobierzTypKomorki(p) == TypKomorki::Sciana) {
                std::cout << "# ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;

    // 3. Uruchamiamy algorytm Dijkstry w celach testowych
    AlgorytmDijkstry alg;
    WynikWyszukiwania wynik = alg.szukaj(plansza, plansza.pobierzStart(), plansza.pobierzCel());

    std::cout << "Status szukania drogi: " << (wynik.znaleziono ? "SUKCES!" : "PORAZKA (droga zablokowana)") << std::endl;
    
    if (wynik.znaleziono) {
        std::cout << "Dlugosc wyznaczonej trasy: " << wynik.najkrotszaSciezka.size() << " pol." << std::endl;
        std::cout << "Liczba zbadanych (odwiedzonych) komorek: " << wynik.kolejnoscOdwiedzania.size() << std::endl;
        
        // Zapisujemy wyznaczoną ścieżkę na planszy testowej
        // Pomijamy pierwszy i ostatni element, aby nie nadpisać ikon startu/celu
        for (size_t i = 1; i < wynik.najkrotszaSciezka.size() - 1; i++) {
            plansza.ustawTypKomorki(wynik.najkrotszaSciezka[i], TypKomorki::Sciezka);
        }

        std::cout << "\nStan planszy końcowej z wyznaczona sciezka (x):" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        for (int w = 0; w < plansza.pobierzWiersze(); w++) {
            std::cout << "  ";
            for (int k = 0; k < plansza.pobierzKolumny(); k++) {
                Punkt p(w, k);
                if (p == plansza.pobierzStart()) {
                    std::cout << "S ";
                } else if (p == plansza.pobierzCel()) {
                    std::cout << "C ";
                } else if (plansza.pobierzTypKomorki(p) == TypKomorki::Sciana) {
                    std::cout << "# ";
                } else if (plansza.pobierzTypKomorki(p) == TypKomorki::Sciezka) {
                    std::cout << "x ";
                } else {
                    std::cout << ". ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "----------------------------------------" << std::endl;
    }
    
    std::cout << "=============================================================" << std::endl;
}
