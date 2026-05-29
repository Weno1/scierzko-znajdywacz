#include "plansza.h"

// Konstruktor klasy Plansza
Plansza::Plansza(int w, int k) {
    wiersze = w;
    kolumny = k;
    
    // Domyślne rozmieszczenie punktów: start w lewym górnym rogu, cel w prawym dolnym
    punktStartowy = Punkt(0, 0);
    punktDocelowy = Punkt(w - 1, k - 1);
    
    // Inicjalizacja siatki komórkami ustawionymi jako Pusta
    siatka.resize(wiersze);
    for (int i = 0; i < wiersze; i++) {
        siatka[i].resize(kolumny, TypKomorki::Pusta);
    }
}

// Czyszczenie całej planszy do zera
void Plansza::wyczyscWszystko() {
    for (int w = 0; w < wiersze; w++) {
        for (int k = 0; k < kolumny; k++) {
            siatka[w][k] = TypKomorki::Pusta;
        }
    }
    // Przywracamy punkty na ich domyślne startowe pozycje
    punktStartowy = Punkt(0, 0);
    punktDocelowy = Punkt(wiersze - 1, kolumny - 1);
}

// Czyszczenie samych śladów przeszukiwania (odwiedzone pola i ścieżka)
void Plansza::wyczyscSciezkeIOdwiedzone() {
    for (int w = 0; w < wiersze; w++) {
        for (int k = 0; k < kolumny; k++) {
            // Jeśli pole jest oznaczone jako odwiedzone lub należy do ścieżki, to je czyścimy
            if (siatka[w][k] == TypKomorki::Odwiedzona || siatka[w][k] == TypKomorki::Sciezka) {
                siatka[w][k] = TypKomorki::Pusta;
            }
        }
    }
}

// Czyszczenie samych ścian
void Plansza::wyczyscSciany() {
    for (int w = 0; w < wiersze; w++) {
        for (int k = 0; k < kolumny; k++) {
            if (siatka[w][k] == TypKomorki::Sciana) {
                siatka[w][k] = TypKomorki::Pusta;
            }
        }
    }
}

// Bezpieczne ustawianie punktu startowego
void Plansza::ustawStart(Punkt p) {
    if (czyWGranicach(p)) {
        punktStartowy = p;
        // Gdy start ląduje na jakimś polu, pole to nie może być ścianą
        siatka[p.wiersz][p.kolumna] = TypKomorki::Pusta;
    }
}

// Bezpieczne ustawianie punktu docelowego
void Plansza::ustawCel(Punkt p) {
    if (czyWGranicach(p)) {
        punktDocelowy = p;
        // Gdy cel ląduje na jakimś polu, pole to nie może być ścianą
        siatka[p.wiersz][p.kolumna] = TypKomorki::Pusta;
    }
}

// Pobieranie typu komórki na podstawie współrzędnych
TypKomorki Plansza::pobierzTypKomorki(int w, int k) const {
    if (!czyWGranicach(w, k)) {
        return TypKomorki::Sciana; // Bezpieczny fallback w razie wyjścia poza tablicę
    }
    return siatka[w][k];
}

// Pobieranie typu komórki na podstawie punktu
TypKomorki Plansza::pobierzTypKomorki(Punkt p) const {
    return pobierzTypKomorki(p.wiersz, p.kolumna);
}

// Ustawianie typu komórki na podstawie współrzędnych
void Plansza::ustawTypKomorki(int w, int k, TypKomorki typ) {
    if (czyWGranicach(w, k)) {
        siatka[w][k] = typ;
    }
}

// Ustawianie typu komórki na podstawie punktu
void Plansza::ustawTypKomorki(Punkt p, TypKomorki typ) {
    ustawTypKomorki(p.wiersz, p.kolumna, typ);
}

// Sprawdzanie czy współrzędne nie wykraczają poza planszę
bool Plansza::czyWGranicach(int w, int k) const {
    bool wierszOk = (w >= 0) && (w < wiersze);
    bool kolumnaOk = (k >= 0) && (k < kolumny);
    return wierszOk && kolumnaOk;
}

// Sprawdzanie czy punkt nie wykracza poza planszę
bool Plansza::czyWGranicach(Punkt p) const {
    return czyWGranicach(p.wiersz, p.kolumna);
}

// Sprawdzanie czy ruch na to pole jest dozwolony (nie ma tam ściany)
bool Plansza::czyMoznaWejsc(int w, int k) const {
    if (!czyWGranicach(w, k)) {
        return false;
    }
    return siatka[w][k] != TypKomorki::Sciana;
}

// Sprawdzanie czy ruch na ten punkt jest dozwolony
bool Plansza::czyMoznaWejsc(Punkt p) const {
    return czyMoznaWejsc(p.wiersz, p.kolumna);
}
