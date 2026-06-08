#ifndef TESTER_KONSOLOWY_H
#define TESTER_KONSOLOWY_H

/**
 * @class TesterKonsolowy
 * @brief Klasa pozwalająca na uruchomienie i przetestowanie logiki aplikacji w trybie tekstowym.
 * 
 * Klasa weryfikuje oddzielenie interfejsu graficznego od logiki gry. Uruchamia mały,
 * tekstowy test, w którym rysuje planszę za pomocą znaków ASCII bezpośrednio na konsoli.
 */
class TesterKonsolowy {
public:
    /**
     * @brief Główna metoda statyczna uruchamiająca test działania planszy oraz algorytmów.
     * 
     * Tworzy planszę, stawia ściany przeszkód, wywołuje algorytm A* w sposób polimorficzny
     * i drukuje wynikowy stan planszy na standardowe wyjście (konsolę).
     */
    static void uruchomTest();
};

#endif // TESTER_KONSOLOWY_H
