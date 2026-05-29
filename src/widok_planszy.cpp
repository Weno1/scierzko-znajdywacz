#include "widok_planszy.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPolygon>
#include <cmath>

WidokPlanszy::WidokPlanszy(Plansza& model, QWidget* rodzic)
    : QWidget(rodzic), plansza(model) {
    
    przeciaganieStartu = false;
    przeciaganieCelu = false;
    rysowanieScian = true;
    indeksOdwiedzonych = 0;
    indeksSciezki = 0;
    wTrakcieAnimacji = false;

    // Tworzymy stoper do animacji
    stoperAnimacji = new QTimer(this);
    connect(stoperAnimacji, &QTimer::timeout, this, &WidokPlanszy::krokAnimacji);

    // Włączamy śledzenie myszy bez konieczności klikania
    setMouseTracking(true);
    
    // Określamy politykę rozmiaru widżetu - ma się rozszerzać
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

// Uruchomienie odtwarzania animacji
void WidokPlanszy::uruchomWizualizacje(const WynikWyszukiwania& wynik, int predkoscMs) {
    zatrzymajWizualizacje();

    // Kopiujemy wyniki do zmiennych animacji
    animacjaOdwiedzone = wynik.kolejnoscOdwiedzania;
    animacjaSciezka = wynik.najkrotszaSciezka;
    indeksOdwiedzonych = 0;
    indeksSciezki = 0;

    // Jeśli nic nie zbadano i nie ma ścieżki
    if (animacjaOdwiedzone.empty() && animacjaSciezka.empty()) {
        emit koniecWizualizacji(0, 0);
        return;
    }

    wTrakcieAnimacji = true;
    stoperAnimacji->start(predkoscMs);
}

// Zatrzymanie animacji
void WidokPlanszy::zatrzymajWizualizacje() {
    stoperAnimacji->stop();
    wTrakcieAnimacji = false;
}

// Slot kroku animacji wywoływany cyklicznie
void WidokPlanszy::krokAnimacji() {
    // 1. Najpierw animujemy badanie pól (kolor niebieski)
    if (indeksOdwiedzonych < animacjaOdwiedzone.size()) {
        Punkt p = animacjaOdwiedzone[indeksOdwiedzonych];
        indeksOdwiedzonych++;
        
        // Zmieniamy stan komórki w modelu, jeśli była pusta
        if (plansza.pobierzTypKomorki(p) == TypKomorki::Pusta) {
            plansza.ustawTypKomorki(p, TypKomorki::Odwiedzona);
            update(); // Wymuszamy ponowne przerysowanie widżetu na ekranie
        }
    } 
    // 2. Gdy skończymy animować badanie pól, animujemy ostateczną ścieżkę (kolor złoty)
    else if (indeksSciezki < animacjaSciezka.size()) {
        Punkt p = animacjaSciezka[indeksSciezki];
        indeksSciezki++;
        
        TypKomorki typ = plansza.pobierzTypKomorki(p);
        if (typ == TypKomorki::Odwiedzona || typ == TypKomorki::Pusta) {
            plansza.ustawTypKomorki(p, TypKomorki::Sciezka);
            update();
        }
    } 
    // 3. Po zakończeniu obu faz animacji, wyłączamy stoper
    else {
        stoperAnimacji->stop();
        wTrakcieAnimacji = false;
        
        int dlugoscSciezki = 0;
        if (!animacjaSciezka.empty()) {
            dlugoscSciezki = animacjaSciezka.size();
        }
        
        // Wysyłamy sygnał o ukończeniu wizualizacji z odpowiednimi parametrami statystyk
        emit koniecWizualizacji(dlugoscSciezki, animacjaOdwiedzone.size());
    }
}

// Rysowanie komponentu planszy
void WidokPlanszy::paintEvent(QPaintEvent* zdarzenie) {
    Q_UNUSED(zdarzenie);
    QPainter malarz(this);
    
    // Włączamy antyaliasing (wygładzanie krawędzi) do ładnego rysowania ikon startu/celu
    malarz.setRenderHint(QPainter::Antialiasing);

    int wiersze = plansza.pobierzWiersze();
    int kolumny = plansza.pobierzKolumny();

    // Obliczamy dynamicznie szerokość i wysokość pojedynczego pola planszy
    int szerokoscKomorki = width() / kolumny;
    int wysokoscKomorki = height() / wiersze;

    if (szerokoscKomorki == 0 || wysokoscKomorki == 0) {
        return;
    }

    // Jasnoniebieskie pióro do rysowania siatki
    QPen pioroSiatki(QColor(175, 216, 248, 110));
    pioroSiatki.setWidth(1);

    Punkt start = plansza.pobierzStart();
    Punkt cel = plansza.pobierzCel();

    // Przechodzimy pętlą po wszystkich komórkach planszy
    for (int w = 0; w < wiersze; w++) {
        for (int k = 0; k < kolumny; k++) {
            QRect prostokatKomorki(k * szerokoscKomorki, w * wysokoscKomorki, szerokoscKomorki, wysokoscKomorki);
            QColor kolorWypelnienia = Qt::white; // Domyślny kolor dla komórki pustej
            malarz.setPen(pioroSiatki);

            TypKomorki typ = plansza.pobierzTypKomorki(w, k);
            
            // Dopasowujemy kolor tła pola w zależności od stanu komórki
            if (typ == TypKomorki::Sciana) {
                kolorWypelnienia = QColor(12, 53, 71); // Ciemny granat
                malarz.setPen(Qt::NoPen);              // Brak siatki wokół ścian
            } else if (typ == TypKomorki::Odwiedzona) {
                kolorWypelnienia = QColor(0, 188, 212); // Żywy turkusowy/cyan
            } else if (typ == TypKomorki::Sciezka) {
                kolorWypelnienia = QColor(255, 235, 59); // Złoty/żółty
            }

            malarz.setBrush(kolorWypelnienia);
            malarz.drawRect(prostokatKomorki);

            Punkt aktualny(w, k);
            
            // Rysowanie startu (zielona strzałka)
            if (aktualny == start) {
                malarz.setPen(Qt::NoPen);
                malarz.setBrush(QColor(46, 204, 113)); // Jasna zieleń
                
                QPolygon strzalka;
                strzalka << QPoint(prostokatKomorki.left() + szerokoscKomorki * 0.3, prostokatKomorki.top() + wysokoscKomorki * 0.15)
                         << QPoint(prostokatKomorki.right() - szerokoscKomorki * 0.25, prostokatKomorki.top() + wysokoscKomorki * 0.5)
                         << QPoint(prostokatKomorki.left() + szerokoscKomorki * 0.3, prostokatKomorki.bottom() - wysokoscKomorki * 0.15)
                         << QPoint(prostokatKomorki.left() + szerokoscKomorki * 0.45, prostokatKomorki.top() + wysokoscKomorki * 0.5);
                malarz.drawPolygon(strzalka);
            }
            // Rysowanie celu (czerwona tarcza strzelecka)
            else if (aktualny == cel) {
                // Rysujemy zewnętrzny czerwony okrąg
                malarz.setPen(QPen(QColor(231, 76, 60), 2));
                malarz.setBrush(Qt::NoBrush);
                malarz.drawEllipse(prostokatKomorki.adjusted(3, 3, -3, -3));
                
                // Rysujemy wewnętrzne pełne czerwone kółko
                malarz.setPen(Qt::NoPen);
                malarz.setBrush(QColor(231, 76, 60));
                malarz.drawEllipse(prostokatKomorki.adjusted(7, 7, -7, -7));
            }
        }
    }
}

// Obsługa kliknięcia myszką na planszy
void WidokPlanszy::mousePressEvent(QMouseEvent* zdarzenie) {
    if (wTrakcieAnimacji) return;

    int wiersze = plansza.pobierzWiersze();
    int kolumny = plansza.pobierzKolumny();

    int szerokoscKomorki = width() / kolumny;
    int wysokoscKomorki = height() / wiersze;
    if (szerokoscKomorki == 0 || wysokoscKomorki == 0) return;

    // Ustalamy kliknięty wiersz i kolumnę na podstawie pozycji kursora
    int kolumna = zdarzenie->position().x() / szerokoscKomorki;
    int wiersz = zdarzenie->position().y() / wysokoscKomorki;

    Punkt klikniety(wiersz, kolumna);

    if (plansza.czyWGranicach(klikniety)) {
        if (klikniety == plansza.pobierzStart()) {
            przeciaganieStartu = true;
        } else if (klikniety == plansza.pobierzCel()) {
            przeciaganieCelu = true;
        } else {
            // Rysowanie nowej ściany bądź usuwanie istniejącej
            rysowanieScian = (plansza.pobierzTypKomorki(klikniety) != TypKomorki::Sciana);
            plansza.ustawTypKomorki(klikniety, rysowanieScian ? TypKomorki::Sciana : TypKomorki::Pusta);
            update();
        }
    }
}

// Obsługa ruchu myszką (przeciąganie)
void WidokPlanszy::mouseMoveEvent(QMouseEvent* zdarzenie) {
    if (wTrakcieAnimacji) return;

    int wiersze = plansza.pobierzWiersze();
    int kolumny = plansza.pobierzKolumny();

    int szerokoscKomorki = width() / kolumny;
    int wysokoscKomorki = height() / wiersze;
    if (szerokoscKomorki == 0 || wysokoscKomorki == 0) return;

    int kolumna = zdarzenie->position().x() / szerokoscKomorki;
    int wiersz = zdarzenie->position().y() / wysokoscKomorki;

    Punkt biezacy(wiersz, kolumna);

    if (plansza.czyWGranicach(biezacy)) {
        if (przeciaganieStartu) {
            // Nie możemy postawić startu w miejscu celu
            if (biezacy != plansza.pobierzCel()) {
                plansza.ustawStart(biezacy);
                update();
            }
        } else if (przeciaganieCelu) {
            // Nie możemy postawić celu w miejscu startu
            if (biezacy != plansza.pobierzStart()) {
                plansza.ustawCel(biezacy);
                update();
            }
        } else if (zdarzenie->buttons() & Qt::LeftButton) {
            // Jeśli użytkownik przeciąga kursor z wciśniętym lewym przyciskiem myszy, rysujemy/wymazujemy ściany
            if (biezacy != plansza.pobierzStart() && biezacy != plansza.pobierzCel()) {
                plansza.ustawTypKomorki(biezacy, rysowanieScian ? TypKomorki::Sciana : TypKomorki::Pusta);
                update();
            }
        }
    }
}

// Obsługa puszczenia przycisku myszki
void WidokPlanszy::mouseReleaseEvent(QMouseEvent* zdarzenie) {
    Q_UNUSED(zdarzenie);
    przeciaganieStartu = false;
    przeciaganieCelu = false;
}
