#ifndef WIDOK_PLANSZY_H
#define WIDOK_PLANSZY_H

#include <QWidget>
#include <QTimer>
#include "plansza.h"
#include "algorytm.h"

/**
 * @class WidokPlanszy
 * @brief Klasa odpowiedzialna za wizualną prezentację siatki (widok Qt).
 * 
 * Ta klasa rysuje siatkę pól, stany komórek (ściany, odwiedzone pola, ścieżkę)
 * oraz ikony Start/Cel przy pomocy klasy QPainter. Reaguje również na zdarzenia
 * myszy, umożliwiając interaktywne rysowanie ścian oraz przeciąganie punktów.
 * 
 * Dodatkowo zarządza własnym stoperem `QTimer` w celu odtwarzania animacji
 * wyszukiwania krok po kroku na podstawie wyników dostarczonych przez algorytm.
 */
class WidokPlanszy : public QWidget {
    Q_OBJECT

private:
    Plansza& plansza; ///< Stała referencja do modelu biznesowego planszy (Model)
    
    bool przeciaganieStartu;  ///< Czy trwa przeciąganie ikony startowej
    bool przeciaganieCelu;    ///< Czy trwa przeciąganie ikony celu
    bool rysowanieScian;      ///< Czy rysujemy ściany (true) czy je wymazujemy (false)

    // --- Zmienne sterujące animacją ---
    QTimer* stoperAnimacji;              ///< Stoper odmierzający klatki animacji
    std::vector<Punkt> animacjaOdwiedzone; ///< Kopiowana lista zbadanych pól
    std::vector<Punkt> animacjaSciezka;    ///< Kopiowana wyznaczona trasa końcowa
    size_t indeksOdwiedzonych;           ///< Aktualna klatka dla zbadanych pól
    size_t indeksSciezki;                ///< Aktualna klatka dla trasy końcowej
    bool wTrakcieAnimacji;               ///< Czy animacja jest obecnie odtwarzana

public:
    /**
     * @brief Konstruktor widoku planszy.
     * @param model Referencja do logicznego obiektu planszy.
     * @param rodzic Wskaźnik na widżet nadrzędny Qt (domyślnie nullptr).
     */
    WidokPlanszy(Plansza& model, QWidget* rodzic = nullptr);

    /**
     * @brief Zwraca informację, czy trwa odtwarzanie animacji.
     */
    bool czyAnimuje() const { 
        return wTrakcieAnimacji; 
    }

    /**
     * @brief Rozpoczyna odtwarzanie wizualizacji algorytmu.
     * @param wynik Zapisane kroki algorytmu.
     * @param predkoscMs Odstęp czasowy między klatkami w milisekundach.
     */
    void uruchomWizualizacje(const WynikWyszukiwania& wynik, int predkoscMs);

    /**
     * @brief Bezwarunkowo zatrzymuje odtwarzanie animacji.
     */
    void zatrzymajWizualizacje();

signals:
    /**
     * @brief Sygnał wysyłany automatycznie po zakończeniu całej animacji.
     * @param dlugoscSciezki Długość najkrótszej drogi.
     * @param liczbaOdwiedzonych Liczba zbadanych komórek.
     */
    void koniecWizualizacji(int dlugoscSciezki, int liczbaOdwiedzonych);

protected:
    // --- Przeciążone metody obsługi zdarzeń Qt ---
    void paintEvent(QPaintEvent* zdarzenie) override;
    void mousePressEvent(QMouseEvent* zdarzenie) override;
    void mouseMoveEvent(QMouseEvent* zdarzenie) override;
    void mouseReleaseEvent(QMouseEvent* zdarzenie) override;

private slots:
    /**
     * @brief Slot wywoływany cyklicznie przez QTimer w celu dodania kolejnego pola do animacji.
     */
    void krokAnimacji();
};

#endif // WIDOK_PLANSZY_H
