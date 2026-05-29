#include "okno_glowne.h"
#include "legend_item.h"
#include "algorytm.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>

OknoGlowne::OknoGlowne() : plansza(12, 12) { // Inicjalizujemy planszę 12 wierszy na 12 kolumn
    
    // Główny kontener przechowujący cały ułożony interfejs okna
    QWidget *glownyKontener = new QWidget(this);
    setCentralWidget(glownyKontener);

    // Pionowy układ (Layout) dzielący okno na sekcje: Navbar, Legenda, Plansza, Stopka
    QVBoxLayout *glownyUklad = new QVBoxLayout(glownyKontener);
    glownyUklad->setContentsMargins(0, 0, 0, 0);
    glownyUklad->setSpacing(0);

    // ==========================================
    // SEKCJA 1: GÓRNY PASEK NAWIGACJI (Navbar)
    // ==========================================
    QWidget *pasekGora = new QWidget(this);
    pasekGora->setObjectName("Navbar");
    
    QHBoxLayout *ukladGora = new QHBoxLayout(pasekGora);
    ukladGora->setContentsMargins(15, 8, 15, 8);
    ukladGora->setSpacing(12);

    QLabel *etykietaTytul = new QLabel("scierzoznajdywarz v2", pasekGora);
    ukladGora->addWidget(etykietaTytul);

    // Rozwijane menu z algorytmami
    wyborAlgorytmu = new QComboBox(pasekGora);
    wyborAlgorytmu->addItems({"Przeszukiwanie Wszerz (BFS)", "Algorytm A*", "Przeszukiwanie w Glab (DFS)", "Algorytm Dijkstry"});
    ukladGora->addWidget(wyborAlgorytmu);

    // Rozwijane menu z prędkościami
    wyborPredkosci = new QComboBox(pasekGora);
    wyborPredkosci->addItems({"Szybko", "Srednio", "Wolno"});
    ukladGora->addWidget(wyborPredkosci);

    // Przycisk uruchomienia animacji
    przyciskStart = new QPushButton("Wizualizuj!", pasekGora);
    przyciskStart->setObjectName("VisualizeButton");
    connect(przyciskStart, &QPushButton::clicked, this, &OknoGlowne::kliknietoWizualizuj);
    ukladGora->addWidget(przyciskStart);

    // Przyciski czyszczenia planszy
    QPushButton *przyciskWyczyscPlansze = new QPushButton("Wyczysc Plansze", pasekGora);
    przyciskWyczyscPlansze->setObjectName("ClearBoardButton");
    connect(przyciskWyczyscPlansze, &QPushButton::clicked, this, &OknoGlowne::kliknietoWyczyscPlansze);
    ukladGora->addWidget(przyciskWyczyscPlansze);

    QPushButton *przyciskWyczyscSciany = new QPushButton("Usun Sciany", pasekGora);
    connect(przyciskWyczyscSciany, &QPushButton::clicked, this, &OknoGlowne::kliknietoWyczyscSciany);
    ukladGora->addWidget(przyciskWyczyscSciany);

    QPushButton *przyciskWyczyscSciezke = new QPushButton("Wyczysc Sciezke", pasekGora);
    connect(przyciskWyczyscSciezke, &QPushButton::clicked, this, &OknoGlowne::kliknietoWyczyscSciezke);
    ukladGora->addWidget(przyciskWyczyscSciezke);

    ukladGora->addStretch(); // Spycha wszystkie elementy w lewą stronę paska
    glownyUklad->addWidget(pasekGora);

    // ==========================================
    // SEKCJA 2: POZIOMY PASEK LEGENDY (Środek-Góra)
    // ==========================================
    QWidget *kontenerLegendy = new QWidget(this);
    kontenerLegendy->setObjectName("LegendContainer");
    
    QHBoxLayout *ukladLegendy = new QHBoxLayout(kontenerLegendy);
    ukladLegendy->setContentsMargins(20, 8, 20, 8);
    ukladLegendy->setSpacing(25);
    ukladLegendy->setAlignment(Qt::AlignCenter); // Środkuje legendę poziomo

    // Dodajemy obiekty LegendItem objaśniające znaczenie poszczególnych komórek
    ukladLegendy->addWidget(new LegendItem(QColor(46, 204, 113), "Poczatek (Start)", true, false, kontenerLegendy));
    ukladLegendy->addWidget(new LegendItem(QColor(231, 76, 60), "Cel wyszukiwania", false, true, kontenerLegendy));
    ukladLegendy->addWidget(new LegendItem(QColor(12, 53, 71), "Sciana (Blokada)", false, false, kontenerLegendy));
    ukladLegendy->addWidget(new LegendItem(QColor(255, 255, 255), "Komorka pusta", false, false, kontenerLegendy));
    ukladLegendy->addWidget(new LegendItem(QColor(0, 188, 212), "Komorka zbadana", false, false, kontenerLegendy));
    ukladLegendy->addWidget(new LegendItem(QColor(255, 235, 59), "Najkrotsza droga", false, false, kontenerLegendy));

    glownyUklad->addWidget(kontenerLegendy);

    // ==========================================
    // SEKCJA 3: CENTRALNY WIDŻET RYSOWANIA PLANSZY
    // ==========================================
    widokPlanszy = new WidokPlanszy(plansza, this);
    connect(widokPlanszy, &WidokPlanszy::koniecWizualizacji, this, &OknoGlowne::wizualizacjaZakonczona);
    glownyUklad->addWidget(widokPlanszy, 1); // Parametr '1' sprawia, że plansza zajmuje całą wolną przestrzeń

    // ==========================================
    // SEKCJA 4: DOLNA STOPKA I PASEK STANU (Footer)
    // ==========================================
    QWidget *kontenerStopki = new QWidget(this);
    kontenerStopki->setObjectName("Footer");
    
    QHBoxLayout *ukladStopki = new QHBoxLayout(kontenerStopki);
    ukladStopki->setContentsMargins(20, 8, 20, 8);

    pasekStanu = new QLabel("Gotowy. Kliknij i przeciagnij myszka, aby postawic sciany. Przeciagaj wezly, aby zmienic ich pozycje.", kontenerStopki);
    ukladStopki->addWidget(pasekStanu);
    ukladStopki->addStretch();

    glownyUklad->addWidget(kontenerStopki);

    // Ładowanie stylów CSS w celu zapewnienia nowoczesnej i estetycznej oprawy
    setStyleSheet(pobierzStyleAplikacji());
}

// Uruchamianie algorytmu szukania drogi
void OknoGlowne::kliknietoWizualizuj() {
    if (widokPlanszy->czyAnimuje()) return;

    // Przed każdym nowym wyszukiwaniem czyścimy z planszy stary wynik (zostawiając ściany)
    plansza.wyczyscSciezkeIOdwiedzone();
    widokPlanszy->update();

    QString nazwaAlgorytmu = wyborAlgorytmu->currentText();
    QString szybkoscText = wyborPredkosci->currentText();

    // Dobieramy czas trwania ramki animacji w milisekundach
    int predkoscMs = 25;
    if (szybkoscText == "Szybko") predkoscMs = 8;
    else if (szybkoscText == "Srednio") predkoscMs = 25;
    else if (szybkoscText == "Wolno") predkoscMs = 70;

    // Dynamicznie przydzielamy odpowiedni algorytm (Paradygmat POLIMORFIZMU)
    AlgorytmSciezki* algorytm = nullptr;

    if (nazwaAlgorytmu == "Przeszukiwanie Wszerz (BFS)") {
        algorytm = new AlgorytmBFS();
    } else if (nazwaAlgorytmu == "Algorytm A*") {
        algorytm = new AlgorytmAStar();
    } else if (nazwaAlgorytmu == "Przeszukiwanie w Glab (DFS)") {
        algorytm = new AlgorytmDFS();
    } else if (nazwaAlgorytmu == "Algorytm Dijkstry") {
        algorytm = new AlgorytmDijkstry();
    }

    if (algorytm != nullptr) {
        pasekStanu->setText(QString("Trwa wyszukiwanie drogi algorytmem %1...").arg(nazwaAlgorytmu));
        
        // Wywołujemy szukanie drogi. Logika jest oddzielona (Plansza przekazywana przez referencję)
        WynikWyszukiwania wynik = algorytm->szukaj(plansza, plansza.pobierzStart(), plansza.pobierzCel());
        
        // Przekazujemy wynik do widżetu Qt, aby odtworzyć płynną animację
        widokPlanszy->uruchomWizualizacje(wynik, predkoscMs);

        // Zwalniamy zaalokowaną pamięć dynamiczną po algorytmie
        delete algorytm;
    }
}

// Obsługa czyszczenia planszy
void OknoGlowne::kliknietoWyczyscPlansze() {
    if (widokPlanszy->czyAnimuje()) return;
    plansza.wyczyscWszystko();
    widokPlanszy->update();
    pasekStanu->setText("Plansza zostala w pelni zresetowana.");
}

// Obsługa usuwania ścian
void OknoGlowne::kliknietoWyczyscSciany() {
    if (widokPlanszy->czyAnimuje()) return;
    plansza.wyczyscSciany();
    widokPlanszy->update();
    pasekStanu->setText("Wszystkie sciany zostaly wyczyszczone.");
}

// Obsługa czyszczenia ścieżki
void OknoGlowne::kliknietoWyczyscSciezke() {
    if (widokPlanszy->czyAnimuje()) return;
    plansza.wyczyscSciezkeIOdwiedzone();
    widokPlanszy->update();
    pasekStanu->setText("Trasa wyszukiwania zostala wyczyszczona.");
}

// Slot reagujący na ukończenie animacji
void OknoGlowne::wizualizacjaZakonczona(int dlugoscSciezki, int liczbaOdwiedzonych) {
    if (dlugoscSciezki == 0) {
        pasekStanu->setText("Koniec pracy algorytmu: Cel jest zablokowany i nieosiagalny!");
    } else {
        pasekStanu->setText(QString("Sukces! Przeszukano %1 pol. Dlugosc najkrotszej sciezki: %2 komorek.")
                            .arg(liczbaOdwiedzonych)
                            .arg(dlugoscSciezki));
    }
}

// Style CSS dla okna głównego i jego kontrolek (vibrant dark navbar, glassmorphism hints)
QString pobierzStyleAplikacji() {
    return R"(
        QMainWindow {
            background-color: #f7fafc;
        }

        #Navbar {
            background-color: #1a202c; 
            border-bottom: 3px solid #2d3748;
            padding: 8px 15px;
        }

        #Navbar QLabel {
            color: #ffffff;
            font-family: 'Segoe UI', system-ui, sans-serif;
            font-size: 16px;
            font-weight: 800;
            margin-right: 15px;
        }

        QComboBox {
            background-color: #2d3748;
            color: #e2e8f0;
            border: 1px solid #4a5568;
            border-radius: 5px;
            padding: 6px 12px;
            font-family: 'Segoe UI', sans-serif;
            font-size: 13px;
            font-weight: 500;
            min-width: 160px;
        }

        QComboBox:hover {
            background-color: #4a5568;
            border-color: #cbd5e0;
        }

        QComboBox QAbstractItemView {
            background-color: #1a202c;
            color: #e2e8f0;
            selection-background-color: #3182ce;
            selection-color: white;
            border: 1px solid #4a5568;
        }

        QPushButton {
            background-color: #2d3748;
            color: #e2e8f0;
            border: 1px solid #4a5568;
            border-radius: 5px;
            padding: 7px 14px;
            font-family: 'Segoe UI', sans-serif;
            font-size: 13px;
            font-weight: 600;
        }

        QPushButton:hover {
            background-color: #4a5568;
            color: white;
        }

        QPushButton:pressed {
            background-color: #1a202c;
        }

        #VisualizeButton {
            background-color: #3182ce; 
            border: 1px solid #2b6cb0;
            color: white;
            font-size: 14px;
            font-weight: 700;
            padding: 8px 20px;
        }

        #VisualizeButton:hover {
            background-color: #4299e1;
            border-color: #3182ce;
        }

        #VisualizeButton:pressed {
            background-color: #2b6cb0;
        }

        #ClearBoardButton {
            background-color: #e53e3e; 
            border: 1px solid #c53030;
            color: white;
        }

        #ClearBoardButton:hover {
            background-color: #f56565;
        }

        #LegendContainer {
            background-color: #ffffff;
            border-bottom: 1px solid #e2e8f0;
            padding: 10px 20px;
        }

        #Footer {
            background-color: #ffffff;
            border-top: 1px solid #e2e8f0;
            padding: 10px 20px;
        }

        #Footer QLabel {
            color: #4a5568;
            font-family: 'Segoe UI', sans-serif;
            font-size: 13px;
            font-weight: 600;
        }
    )";
}
