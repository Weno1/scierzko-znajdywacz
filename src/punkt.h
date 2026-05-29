#ifndef PUNKT_H
#define PUNKT_H

/**
 * @brief Struktura reprezentująca współrzędne dwuwymiarowe (punkt na planszy).
 * 
 * Służy do przechowywania pozycji komórki (wiersz i kolumna) zamiast używania
 * bardziej skomplikowanych typów jak std::pair. Ułatwia to zrozumienie kodu.
 */
struct Punkt {
    int wiersz;   ///< Indeks wiersza na planszy (od góry do dołu, zaczyna się od 0)
    int kolumna;  ///< Indeks kolumny na planszy (od lewej do prawej, zaczyna się od 0)

    /**
     * @brief Domyślny konstruktor, inicjalizuje punkt wartościami (0, 0).
     */
    Punkt() {
        wiersz = 0;
        kolumna = 0;
    }

    /**
     * @brief Konstruktor parametryczny.
     * @param w Wiersz punktu.
     * @param k Kolumna punktu.
     */
    Punkt(int w, int k) {
        wiersz = w;
        kolumna = k;
    }

    /**
     * @brief Operator porównania czy dwa punkty są w tym samym miejscu.
     * @param inny Drugi punkt do porównania.
     * @return Zwraca true jeśli współrzędne są identyczne.
     */
    bool operator==(const Punkt& inny) const {
        return (wiersz == inny.wiersz) && (kolumna == inny.kolumna);
    }

    /**
     * @brief Operator porównania czy punkty są w różnych miejscach.
     * @param inny Drugi punkt do porównania.
     * @return Zwraca true jeśli współrzędne się różnią.
     */
    bool operator!=(const Punkt& inny) const {
        return !(*this == inny);
    }
};

#endif // PUNKT_H
