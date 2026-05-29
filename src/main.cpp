#include <QApplication>
#include <iostream>
#include <string>
#include "okno_glowne.h"
#include "tester_konsolowy.h"

/**
 * @file main.cpp
 * @brief Główny plik wejściowy do programu.
 * 
 * Ten plik uruchamia aplikację w jednym z dwóch trybów w zależności od
 * przekazanych argumentów wywołania w linii komend:
 * 
 * 1. Tryb tekstowy / konsolowy: Uruchamiany, gdy podano argument '--konsola' lub '--test'.
 *    W tym trybie program wywołuje TesterKonsolowy, który weryfikuje poprawne
 *    działanie planszy i algorytmu w czystej konsoli za pomocą znaków ASCII, bez
 *    żadnej zależności od powłoki graficznej (Qt).
 * 
 * 2. Tryb graficzny GUI: Uruchamiany domyślnie, w którym inicjalizowany jest
 *    silnik graficzny QApplication i otwierane jest główne okno programu (OknoGlowne).
 */
int main(int argc, char *argv[]) {
    bool uruchomKonsolowyTest = false;
    
    // Iterujemy po argumentach wywołania programu
    for (int i = 1; i < argc; i++) {
        std::string argument = argv[i];
        if (argument == "--konsola" || argument == "--test" || argument == "--console") {
            uruchomKonsolowyTest = true;
            break;
        }
    }

    // 1. Tryb testowy / konsolowy (separacja logiki biznesowej od graficznej)
    if (uruchomKonsolowyTest) {
        TesterKonsolowy::uruchomTest();
        return 0;
    }

    // 2. Tryb graficzny GUI (domyślny) oparty na bibliotece Qt
    QApplication aplikacja(argc, argv);

    OknoGlowne oknoProgramu;
    oknoProgramu.setWindowTitle("scierzoznajdywarz v2");
    oknoProgramu.resize(1100, 750);
    oknoProgramu.show();

    // Uruchomienie pętli zdarzeń Qt
    return aplikacja.exec();
}