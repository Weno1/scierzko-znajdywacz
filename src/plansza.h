#ifndef PLANSZA_H
#define PLANSZA_H

#include <vector>
#include "punkt.h"

/**
 * @brief Typy komórek na planszy.
 * 
 * Określa stan, w jakim może znajdować się dane pole na planszy.
 */
enum class TypKomorki {
    Pusta,       ///< Komórka nieodwiedzona (tło planszy)
    Sciana,      ///< Przeszkoda, której nie można przejść ani zbadać
    Odwiedzona,  ///< Komórka zbadana przez algorytm w trakcie szukania drogi
    Sciezka      ///< Komórka należąca do ostatecznej najkrótszej drogi
};

/**
 * @class Plansza
 * @brief Klasa zarządzająca stanem siatki (planszy) do wyszukiwania drogi.
 * 
 * Ta klasa w pełni realizuje paradygmat HERMETYZACJI (kapsułkowania). Wszystkie
 * wrażliwe dane, takie jak dwuwymiarowy wektor reprezentujący siatkę oraz
 * współrzędne startu i celu, są prywatne. Komunikacja z obiektem odbywa się
 * wyłącznie za pomocą metod publicznych (getterów i setterów).
 * 
 * Klasa jest całkowicie odseparowana od interfejsu graficznego (nie importuje Qt),
 * dzięki czemu reprezentuje czystą logikę biznesową (Model).
 */
class Plansza {
private:
    int wiersze; ///< Całkowita liczba wierszy planszy
    int kolumny; ///< Całkowita liczba kolumn planszy
    
    // Dwuwymiarowy wektor przechowujący stany poszczególnych komórek
    std::vector<std::vector<TypKomorki>> siatka;

    Punkt punktStartowy; ///< Współrzędne punktu początkowego (Start)
    Punkt punktDocelowy; ///< Współrzędne punktu docelowego (Cel)

public:
    /**
     * @brief Konstruktor tworzący planszę o zadanych wymiarach.
     * @param w Liczba wierszy (domyślnie 15).
     * @param k Liczba kolumn (domyślnie 20).
     */
    Plansza(int w = 15, int k = 20);

    /**
     * @brief Czyści planszę (ustawia wszystkie pola na Pusta) oraz resetuje start i cel.
     */
    void wyczyscWszystko();

    /**
     * @brief Usuwa z planszy stany Odwiedzona i Sciezka, zostawiając ściany oraz punkty start/cel.
     */
    void wyczyscSciezkeIOdwiedzone();

    /**
     * @brief Usuwa wszystkie ściany z planszy, zostawiając resztę bez zmian.
     */
    void wyczyscSciany();

    // --- GETTERY I SETTERY (Hermetyzacja) ---

    /**
     * @brief Pobiera liczbę wierszy planszy.
     */
    int pobierzWiersze() const {
        return wiersze;
    }

    /**
     * @brief Pobiera liczbę kolumn planszy.
     */
    int pobierzKolumny() const {
        return kolumny;
    }

    /**
     * @brief Pobiera punkt startowy.
     */
    Punkt pobierzStart() const {
        return punktStartowy;
    }

    /**
     * @brief Ustawia punkt startowy w nowym miejscu.
     * @param p Nowy punkt startu.
     */
    void ustawStart(Punkt p);

    /**
     * @brief Pobiera punkt docelowy.
     */
    Punkt pobierzCel() const {
        return punktDocelowy;
    }

    /**
     * @brief Ustawia punkt docelowy w nowym miejscu.
     * @param p Nowy punkt celu.
     */
    void ustawCel(Punkt p);

    /**
     * @brief Pobiera typ komórki na podanych współrzędnych.
     * @param w Indeks wiersza.
     * @param k Indeks kolumny.
     */
    TypKomorki pobierzTypKomorki(int w, int k) const;

    /**
     * @brief Pobiera typ komórki w podanym punkcie.
     * @param p Współrzędne punktu.
     */
    TypKomorki pobierzTypKomorki(Punkt p) const;

    /**
     * @brief Ustawia stan komórki na podanych współrzędnych.
     * @param w Indeks wiersza.
     * @param k Indeks kolumny.
     * @param typ Nowy typ komórki.
     */
    void ustawTypKomorki(int w, int k, TypKomorki typ);

    /**
     * @brief Ustawia stan komórki w podanym punkcie.
     * @param p Współrzędne punktu.
     * @param typ Nowy typ komórki.
     */
    void ustawTypKomorki(Punkt p, TypKomorki typ);

    /**
     * @brief Sprawdza, czy współrzędne mieszczą się w granicach planszy.
     */
    bool czyWGranicach(int w, int k) const;

    /**
     * @brief Sprawdza, czy punkt mieści się w granicach planszy.
     */
    bool czyWGranicach(Punkt p) const;

    /**
     * @brief Sprawdza, czy na dane pole można wejść (czyli czy nie jest to ściana).
     */
    bool czyMoznaWejsc(int w, int k) const;

    /**
     * @brief Sprawdza, czy na dany punkt można wejść.
     */
    bool czyMoznaWejsc(Punkt p) const;
};

#endif // PLANSZA_H
