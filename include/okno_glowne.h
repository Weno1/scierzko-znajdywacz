#ifndef OKNO_GLOWNE_H
#define OKNO_GLOWNE_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include "plansza.h"
#include "widok_planszy.h"

/**
 * @class OknoGlowne
 * @brief Główne okno graficzne aplikacji Pathfinding Visualizer (Kontroler).
 * 
 * Ta klasa łączy wszystkie komponenty interfejsu graficznego użytkownika. Zarządza
 * paskiem nawigacyjnym z kontrolkami (wybór algorytmu, prędkości, przyciski sterujące),
 * legendą, dolnym paskiem stanu oraz centralnym widżetem rysującym planszę (`WidokPlanszy`).
 * 
 * Przy kliknięciu "Wizualizuj!" dynamicznie tworzy odpowiednie instancje klas algorytmów
 * przy użyciu paradygmatu polimorfizmu, wywołuje wyszukiwanie ścieżki i przekazuje
 * dane do animacji do widoku planszy.
 */
class OknoGlowne : public QMainWindow {
    Q_OBJECT

private:
    Plansza plansza;             ///< Obiekt logiczny planszy (Model)
    WidokPlanszy* widokPlanszy;  ///< Wskaźnik na graficzny widżet planszy (Widok)

    QComboBox* wyborAlgorytmu;   ///< Rozwijana lista do wyboru algorytmu
    QComboBox* wyborPredkosci;   ///< Rozwijana lista do wyboru tempa animacji
    QPushButton* przyciskStart;  ///< Przycisk "Wizualizuj!"
    QLabel* pasekStanu;          ///< Dolny napis ze statystykami i komunikatami dla użytkownika

public:
    /**
     * @brief Konstruktor głównego okna graficznego aplikacji.
     */
    OknoGlowne();

private slots:
    /**
     * @brief Wywoływany po kliknięciu przycisku "Wizualizuj!". Uruchamia wybrany algorytm.
     */
    void kliknietoWizualizuj();

    /**
     * @brief Wywoływany po kliknięciu "Wyczysc Plansze". Czyści całą siatkę.
     */
    void kliknietoWyczyscPlansze();

    /**
     * @brief Wywoływany po kliknięciu "Usun Sciany". Usuwa same przeszkody z planszy.
     */
    void kliknietoWyczyscSciany();

    /**
     * @brief Wywoływany po kliknięciu "Wyczysc Sciezke". Usuwa żółte i turkusowe pola drogi.
     */
    void kliknietoWyczyscSciezke();

    /**
     * @brief Slot przechwytujący sygnał zakończenia odtwarzania animacji w celu wyświetlenia statystyk.
     * @param dlugoscSciezki Liczba pól w najkrótszej drodze.
     * @param liczbaOdwiedzonych Liczba zbadanych wierzchołków.
     */
    void wizualizacjaZakonczona(int dlugoscSciezki, int liczbaOdwiedzonych);
};

/**
 * @brief Zwraca łańcuch stylów CSS (Stylesheet) nadający nowoczesny wygląd aplikacji.
 */
QString pobierzStyleAplikacji();

#endif // OKNO_GLOWNE_H
