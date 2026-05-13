#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    // 1. Inicjalizacja głównego obiektu aplikacji (wymagane w każdym programie Qt)
    QApplication app(argc, argv);

    // 2. Tworzenie głównego okna
    QWidget window;
    window.setWindowTitle("Moja pierwsza aplikacja Qt");
    window.resize(300, 200); // Szerokość: 300px, Wysokość: 200px

    // 3. Tworzenie przycisku
    QPushButton *button = new QPushButton("Kliknij mnie!");

    // 4. Łączenie akcji: co ma się stać po kliknięciu przycisku? (Sygnały i Sloty)
    QObject::connect(button, &QPushButton::clicked, [&window]() {
        QMessageBox::information(&window, "Wiadomość", "Witaj w świecie Qt!");
    });

    // 5. Zarządzanie układem (Layout) okna, aby przycisk był ładnie wyśrodkowany
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(button);
    window.setLayout(layout);

    // 6. Wyświetlenie okna na ekranie
    window.show();

    // 7. Uruchomienie głównej pętli zdarzeń aplikacji
    return app.exec();
}