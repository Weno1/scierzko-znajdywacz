#ifndef ALGORYTM_H
#define ALGORYTM_H

#include <vector>
#include "plansza.h"
#include "punkt.h"

using namespace std;

/**
 * @brief Przykładowa struktura przechowująca wyniki szukania drogi.
 */
struct WynikWyszukiwania {
    vector<Punkt> kolejnoscOdwiedzania; ///< Lista zbadanych wierzchołków
    vector<Punkt> najkrotszaSciezka;    ///< Wyznaczona ścieżka
    bool znaleziono;                    ///< Czy znaleziono drogę
    
    /**
     * @brief Domyślny konstruktor struktury wyniku.
     */
    WynikWyszukiwania() {
        znaleziono = false;
    }
};

/**
 * @class AlgorytmSciezki
 * @brief Abstrakcyjna klasa bazowa dla wszystkich algorytmów szukania drogi.
 * 
 * Ta klasa w pełni realizuje paradygmaty ABSTRAKCJI oraz POLIMORFIZMU. Definiuje
 * czysto wirtualną metodę `szukaj`, dzięki czemu cała aplikacja graficzna
 * oraz konsolowa może wywoływać dowolne algorytmy szukania drogi w ten sam,
 * ujednolicony sposób za pomocą wskaźnika typu `AlgorytmSciezki*`.
 */
class AlgorytmSciezki {
public:
    /**
     * @brief Wirtualny destruktor klasy bazowej (wymagany przy polimorfizmie).
     */
    virtual ~AlgorytmSciezki() {}

    /**
     * @brief Metoda czysto wirtualna do wyszukiwania drogi na planszy.
     * @param plansza Stała referencja do obiektu planszy (hermetyzacja).
     * @param start Współrzędne punktu startowego.
     * @param cel Współrzędne punktu docelowego.
     * @return Zwraca strukturę z rezultatami wyszukiwania.
     */
    virtual WynikWyszukiwania szukaj(const Plansza& plansza, Punkt start, Punkt cel) = 0;
};

/**
 * @class AlgorytmBFS
 * @brief Klasa implementująca algorytm przeszukiwania wszerz (BFS).
 * 
 * Dziedziczy z klasy AlgorytmSciezki (paradygmat DZIEDZICZENIA).
 * BFS znajduje zawsze najkrótszą ścieżkę w grafie o niezważonych krawędziach.
 */
class AlgorytmBFS : public AlgorytmSciezki {
public:
    /**
     * @brief Nadpisana funkcja szukająca drogi przy użyciu algorytmu BFS.
     */
    virtual WynikWyszukiwania szukaj(const Plansza& plansza, Punkt start, Punkt cel) override;
};

/**
 * @class AlgorytmDFS
 * @brief Klasa implementująca algorytm przeszukiwania w głąb (DFS).
 * 
 * Dziedziczy z klasy AlgorytmSciezki (paradygmat DZIEDZICZENIA).
 * DFS przeszukuje najgłębsze gałęzie przed cofaniem się, nie gwarantuje najkrótszej drogi.
 */
class AlgorytmDFS : public AlgorytmSciezki {
public:
    /**
     * @brief Nadpisana funkcja szukająca drogi przy użyciu algorytmu DFS.
     */
    virtual WynikWyszukiwania szukaj(const Plansza& plansza, Punkt start, Punkt cel) override;
};

/**
 * @class AlgorytmAStar
 * @brief Klasa implementująca algorytm A* (A-Star).
 * 
 * Dziedziczy z klasy AlgorytmSciezki (paradygmat DZIEDZICZENIA).
 * Używa heurystyki odległości Manhattan, aby kierować wyszukiwaniem w stronę celu.
 */
class AlgorytmAStar : public AlgorytmSciezki {
private:
    /**
     * @brief Oblicza odległość Manhattan pomiędzy dwoma punktami.
     * 
     * Służy jako heurystyka szacująca koszt pozostałej drogi.
     * @param a Pierwszy punkt.
     * @param b Drugi punkt.
     * @return Odległość Manhattan w postaci liczby całkowitej.
     */
    int obliczManhattan(Punkt a, Punkt b);

public:
    /**
     * @brief Nadpisana funkcja szukająca drogi przy użyciu algorytmu A*.
     */
    virtual WynikWyszukiwania szukaj(const Plansza& plansza, Punkt start, Punkt cel) override;
};

/**
 * @class AlgorytmDijkstry
 * @brief Klasa implementująca algorytm Dijkstry szukania najkrótszej drogi.
 * 
 * Dziedziczy z klasy AlgorytmSciezki (paradygmat DZIEDZICZENIA).
 * Działa analogicznie do BFS na siatce bez wag, ale z użyciem kolejki priorytetowej dystansów.
 */
class AlgorytmDijkstry : public AlgorytmSciezki {
public:
    /**
     * @brief Nadpisana funkcja szukająca drogi przy użyciu algorytmu Dijkstry.
     */
    virtual WynikWyszukiwania szukaj(const Plansza& plansza, Punkt start, Punkt cel) override;
};

#endif // ALGORYTM_H
