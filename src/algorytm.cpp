#include "algorytm.h"
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>

using namespace std;

// ==========================================
// IMPLEMENTACJA ALGORYTMU BFS (Wszerz)
// ==========================================
WynikWyszukiwania AlgorytmBFS::szukaj(const Plansza& plansza, Punkt start, Punkt cel) {
    WynikWyszukiwania wynik;
    
    int wiersze = plansza.pobierzWiersze();
    int kolumny = plansza.pobierzKolumny();
    
    // Inicjalizacja tablicy odwiedzonych elementów - początkowo wszystkie są fałszem (false)
    vector<vector<bool>> odwiedzone;
    odwiedzone.resize(wiersze);
    for (int i = 0; i < wiersze; i++) {
        odwiedzone[i].resize(kolumny, false);
    }
    
    // Tablica rodziców - pozwala odtworzyć drogę wstecz po znalezieniu celu
    vector<vector<Punkt>> rodzic;
    rodzic.resize(wiersze);
    for (int i = 0; i < wiersze; i++) {
        rodzic[i].resize(kolumny, Punkt(-1, -1));
    }
    
    // Kolejka typu FIFO (First In First Out)
    queue<Punkt> kolejka;
    
    // Zaczynamy przeszukiwanie od punktu początkowego
    kolejka.push(start);
    odwiedzone[start.wiersz][start.kolumna] = true;
    
    // Definiujemy dopuszczalne ruchy (tylko w 4 kierunkach: góra, dół, lewo, prawo)
    int ruchWiersz[] = {-1, 1, 0, 0};
    int ruchKolumna[] = {0, 0, -1, 1};
    
    bool celZnaleziony = false;
    
    // Główna pętla algorytmu BFS
    while (!kolejka.empty()) {
        // Pobieramy pierwszy element z kolejki
        Punkt biezacy = kolejka.front();
        kolejka.pop();
        
        // Zapisujemy odwiedzone punkty (oprócz startu i celu), aby móc je narysować w animacji
        if (biezacy != start && biezacy != cel) {
            wynik.kolejnoscOdwiedzania.push_back(biezacy);
        }
        
        // Sprawdzamy, czy to już cel
        if (biezacy == cel) {
            celZnaleziony = true;
            break;
        }
        
        // Sprawdzamy 4 sąsiadujące pola
        for (int i = 0; i < 4; i++) {
            int nowyWiersz = biezacy.wiersz + ruchWiersz[i];
            int nowaKolumna = biezacy.kolumna + ruchKolumna[i];
            Punkt sasiad(nowyWiersz, nowaKolumna);
            
            // Jeśli sąsiad leży na planszy
            if (plansza.czyWGranicach(sasiad)) {
                // Jeśli nie jest ścianą i nie został jeszcze odwiedzony
                if (!odwiedzone[sasiad.wiersz][sasiad.kolumna] && plansza.czyMoznaWejsc(sasiad)) {
                    odwiedzone[sasiad.wiersz][sasiad.kolumna] = true;
                    rodzic[sasiad.wiersz][sasiad.kolumna] = biezacy; // Zapisujemy skąd przyszliśmy
                    kolejka.push(sasiad);
                }
            }
        }
    }
    
    // Jeśli cel został odnaleziony, rekonstruujemy ścieżkę od końca do początku
    if (celZnaleziony) {
        wynik.znaleziono = true;
        Punkt biezacy = cel;
        
        while (biezacy != start) {
            wynik.najkrotszaSciezka.push_back(biezacy);
            biezacy = rodzic[biezacy.wiersz][biezacy.kolumna];
        }
        wynik.najkrotszaSciezka.push_back(start);
        
        // Odwracamy wektor, aby ścieżka zaczynała się od startu
        reverse(wynik.najkrotszaSciezka.begin(), wynik.najkrotszaSciezka.end());
    }
    
    return wynik;
}

// ==========================================
// IMPLEMENTACJA ALGORYTMU DFS (W głąb)
// ==========================================
WynikWyszukiwania AlgorytmDFS::szukaj(const Plansza& plansza, Punkt start, Punkt cel) {
    WynikWyszukiwania wynik;
    
    int wiersze = plansza.pobierzWiersze();
    int kolumny = plansza.pobierzKolumny();
    
    vector<vector<bool>> odwiedzone;
    odwiedzone.resize(wiersze);
    for (int i = 0; i < wiersze; i++) {
        odwiedzone[i].resize(kolumny, false);
    }
    
    vector<vector<Punkt>> rodzic;
    rodzic.resize(wiersze);
    for (int i = 0; i < wiersze; i++) {
        rodzic[i].resize(kolumny, Punkt(-1, -1));
    }
    
    // Używamy vector jako stosu LIFO (Last In First Out)
    vector<Punkt> stos;
    stos.push_back(start);
    
    int ruchWiersz[] = {-1, 1, 0, 0};
    int ruchKolumna[] = {0, 0, -1, 1};
    
    bool celZnaleziony = false;
    
    while (!stos.empty()) {
        // Pobieramy element z samej góry stosu
        Punkt biezacy = stos.back();
        stos.pop_back();
        
        // Jeśli ten węzeł był już zbadany, pomijamy go
        if (odwiedzone[biezacy.wiersz][biezacy.kolumna]) {
            continue;
        }
        odwiedzone[biezacy.wiersz][biezacy.kolumna] = true;
        
        if (biezacy != start && biezacy != cel) {
            wynik.kolejnoscOdwiedzania.push_back(biezacy);
        }
        
        if (biezacy == cel) {
            celZnaleziony = true;
            break;
        }
        
        // Dokładamy nieodwiedzonych sąsiadów na stos
        for (int i = 0; i < 4; i++) {
            int nowyWiersz = biezacy.wiersz + ruchWiersz[i];
            int nowaKolumna = biezacy.kolumna + ruchKolumna[i];
            Punkt sasiad(nowyWiersz, nowaKolumna);
            
            if (plansza.czyWGranicach(sasiad)) {
                if (!odwiedzone[sasiad.wiersz][sasiad.kolumna] && plansza.czyMoznaWejsc(sasiad)) {
                    rodzic[sasiad.wiersz][sasiad.kolumna] = biezacy;
                    stos.push_back(sasiad);
                }
            }
        }
    }
    
    if (celZnaleziony) {
        wynik.znaleziono = true;
        Punkt biezacy = cel;
        
        while (biezacy != start) {
            wynik.najkrotszaSciezka.push_back(biezacy);
            biezacy = rodzic[biezacy.wiersz][biezacy.kolumna];
        }
        wynik.najkrotszaSciezka.push_back(start);
        reverse(wynik.najkrotszaSciezka.begin(), wynik.najkrotszaSciezka.end());
    }
    
    return wynik;
}

// ==========================================
// IMPLEMENTACJA ALGORYTMU A*
// ==========================================

// Metoda prywatna obliczająca odległość miejską (Manhattan)
int AlgorytmAStar::obliczManhattan(Punkt a, Punkt b) {
    int dx = abs(a.wiersz - b.wiersz);
    int dy = abs(a.kolumna - b.kolumna);
    return dx + dy;
}

// Struktura pomocnicza reprezentująca węzeł A* w kolejce priorytetowej
struct WezelAStar {
    Punkt pozycja;
    int gScore; // Rzeczywisty koszt drogi od startu do tego węzła
    int hScore; // Szacowany koszt (odległość Manhattan) do celu
    
    // Całkowita ocena węzła: F = G + H
    int fScore() const {
        return gScore + hScore;
    }
    
    // Potrzebne do kolejki priorytetowej (zwraca true, gdy ten koszt jest WIĘKSZY od innego,
    // dzięki czemu w priority_queue na szczycie wyląduje najmniejszy element)
    bool operator>(const WezelAStar& inny) const {
        return fScore() > inny.fScore();
    }
};

WynikWyszukiwania AlgorytmAStar::szukaj(const Plansza& plansza, Punkt start, Punkt cel) {
    WynikWyszukiwania wynik;
    
    int wiersze = plansza.pobierzWiersze();
    int kolumny = plansza.pobierzKolumny();
    
    // Tablica kosztów dojścia. Domyślnie ustawiamy bardzo dużą liczbę (nieskończoność)
    vector<vector<int>> gScore;
    gScore.resize(wiersze);
    for (int i = 0; i < wiersze; i++) {
        gScore[i].resize(kolumny, 1000000);
    }
    
    // Tablica zamknięta - dla węzłów, które już zostały w pełni zbadane
    vector<vector<bool>> zamkniete;
    zamkniete.resize(wiersze);
    for (int i = 0; i < wiersze; i++) {
        zamkniete[i].resize(kolumny, false);
    }
    
    vector<vector<Punkt>> rodzic;
    rodzic.resize(wiersze);
    for (int i = 0; i < wiersze; i++) {
        rodzic[i].resize(kolumny, Punkt(-1, -1));
    }
    
    // Kolejka priorytetowa posortowana rosnąco według kosztu fScore
    priority_queue<WezelAStar, vector<WezelAStar>, greater<WezelAStar>> otwartaKolejka;
    
    // Inicjalizacja startowa
    gScore[start.wiersz][start.kolumna] = 0;
    otwartaKolejka.push({start, 0, obliczManhattan(start, cel)});
    
    int ruchWiersz[] = {-1, 1, 0, 0};
    int ruchKolumna[] = {0, 0, -1, 1};
    
    bool celZnaleziony = false;
    
    while (!otwartaKolejka.empty()) {
        // Pobieramy węzeł o najniższym koszcie szacowanym (fScore)
        WezelAStar biezacy = otwartaKolejka.top();
        otwartaKolejka.pop();
        
        Punkt p = biezacy.pozycja;
        
        // Jeśli ten węzeł był już zbadany, omijamy go
        if (zamkniete[p.wiersz][p.kolumna]) {
            continue;
        }
        zamkniete[p.wiersz][p.kolumna] = true;
        
        if (p != start && p != cel) {
            wynik.kolejnoscOdwiedzania.push_back(p);
        }
        
        if (p == cel) {
            celZnaleziony = true;
            break;
        }
        
        // Sprawdzamy sąsiadów
        for (int i = 0; i < 4; i++) {
            int nowyWiersz = p.wiersz + ruchWiersz[i];
            int nowaKolumna = p.kolumna + ruchKolumna[i];
            Punkt sasiad(nowyWiersz, nowaKolumna);
            
            if (plansza.czyWGranicach(sasiad)) {
                if (plansza.czyMoznaWejsc(sasiad)) {
                    // Obliczamy tymczasowy koszt drogi do sąsiada (droga od startu + 1 krok)
                    int tymczasoweG = gScore[p.wiersz][p.kolumna] + 1;
                    
                    // Jeśli ten koszt jest mniejszy niż poprzednio zapisany (znaleźliśmy lepszą drogę)
                    if (tymczasoweG < gScore[sasiad.wiersz][sasiad.kolumna]) {
                        gScore[sasiad.wiersz][sasiad.kolumna] = tymczasoweG;
                        rodzic[sasiad.wiersz][sasiad.kolumna] = p;
                        
                        // Dodajemy sąsiada do kolejki do dalszego rozpatrzenia
                        otwartaKolejka.push({sasiad, tymczasoweG, obliczManhattan(sasiad, cel)});
                    }
                }
            }
        }
    }
    
    if (celZnaleziony) {
        wynik.znaleziono = true;
        Punkt biezacy = cel;
        
        while (biezacy != start) {
            wynik.najkrotszaSciezka.push_back(biezacy);
            biezacy = rodzic[biezacy.wiersz][biezacy.kolumna];
        }
        wynik.najkrotszaSciezka.push_back(start);
        reverse(wynik.najkrotszaSciezka.begin(), wynik.najkrotszaSciezka.end());
    }
    
    return wynik;
}

// ==========================================
// IMPLEMENTACJA ALGORYTMU DIJKSTRY
// ==========================================

// Pomocnicza struktura węzła dla algorytmu Dijkstry
struct WezelDijkstry {
    Punkt pozycja;
    int dystans; // Rzeczywisty koszt dojścia od startu
    
    // Potrzebne do kolejki priorytetowej (wybieramy najmniejsze dystanse)
    bool operator>(const WezelDijkstry& inny) const {
        return dystans > inny.dystans;
    }
};

WynikWyszukiwania AlgorytmDijkstry::szukaj(const Plansza& plansza, Punkt start, Punkt cel) {
    WynikWyszukiwania wynik;
    
    int wiersze = plansza.pobierzWiersze();
    int kolumny = plansza.pobierzKolumny();
    
    // Tablica najkrótszych znanych dystansów
    vector<vector<int>> dystans(wiersze, vector<int>(kolumny, 1000000));
    vector<vector<bool>> zamkniete(wiersze, vector<bool>(kolumny, false));
    vector<vector<Punkt>> rodzic(wiersze, vector<Punkt>(kolumny, Punkt(-1, -1)));
    
    // Kolejka priorytetowa posortowana rosnąco według dystansu
    priority_queue<WezelDijkstry, vector<WezelDijkstry>, greater<WezelDijkstry>> pq;
    
    dystans[start.wiersz][start.kolumna] = 0;
    pq.push({start, 0});
    
    int ruchWiersz[] = {-1, 1, 0, 0};
    int ruchKolumna[] = {0, 0, -1, 1};
    
    bool celZnaleziony = false;
    
    while (!pq.empty()) {
        WezelDijkstry biezacy = pq.top();
        pq.pop();
        
        Punkt p = biezacy.pozycja;
        
        if (zamkniete[p.wiersz][p.kolumna]) {
            continue;
        }
        zamkniete[p.wiersz][p.kolumna] = true;
        
        if (p != start && p != cel) {
            wynik.kolejnoscOdwiedzania.push_back(p);
        }
        
        if (p == cel) {
            celZnaleziony = true;
            break;
        }
        
        for (int i = 0; i < 4; i++) {
            int nowyWiersz = p.wiersz + ruchWiersz[i];
            int nowaKolumna = p.kolumna + ruchKolumna[i];
            Punkt sasiad(nowyWiersz, nowaKolumna);
            
            if (plansza.czyWGranicach(sasiad)) {
                if (plansza.czyMoznaWejsc(sasiad)) {
                    int alternatywnyDystans = dystans[p.wiersz][p.kolumna] + 1;
                    
                    if (alternatywnyDystans < dystans[sasiad.wiersz][sasiad.kolumna]) {
                        dystans[sasiad.wiersz][sasiad.kolumna] = alternatywnyDystans;
                        rodzic[sasiad.wiersz][sasiad.kolumna] = p;
                        pq.push({sasiad, alternatywnyDystans});
                    }
                }
            }
        }
    }
    
    if (celZnaleziony) {
        wynik.znaleziono = true;
        Punkt biezacy = cel;
        
        while (biezacy != start) {
            wynik.najkrotszaSciezka.push_back(biezacy);
            biezacy = rodzic[biezacy.wiersz][biezacy.kolumna];
        }
        wynik.najkrotszaSciezka.push_back(start);
        reverse(wynik.najkrotszaSciezka.begin(), wynik.najkrotszaSciezka.end());
    }
    
    return wynik;
}
