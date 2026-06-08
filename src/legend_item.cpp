#include "legend_item.h"
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>

LegendItem::LegendItem(const QColor &kolor, const QString &tekst, bool czyStart, bool czyCel, QWidget *rodzic)
    : QWidget(rodzic) {
    
    // Tworzymy poziomy układ elementów
    QHBoxLayout *uklad = new QHBoxLayout(this);
    uklad->setContentsMargins(0, 0, 0, 0);
    uklad->setSpacing(6);

    // Tworzymy ramkę, która będzie kolorowym kwadracikiem próbki
    QFrame *probka = new QFrame(this);
    probka->setFixedSize(20, 20);
    
    if (czyStart) {
        // Zielony zaokrąglony prostokąt imitujący ikonę startu
        probka->setStyleSheet("background-color: #2ecc71; border-radius: 3px;");
    } else if (czyCel) {
        // Okrągła tarcza imitująca ikonę celu
        probka->setStyleSheet("background-color: #e74c3c; border-radius: 10px;");
    } else {
        // Zwykły prostokącik z obramowaniem w odpowiednim kolorze komórki
        QString styl = QString("background-color: %1; border: 1px solid #afe7f8; border-radius: 3px;")
                        .arg(kolor.name());
        probka->setStyleSheet(styl);
    }

    // Tworzymy etykietę tekstową
    QLabel *etykieta = new QLabel(tekst, this);
    etykieta->setStyleSheet("color: #4a5568; font-family: 'Segoe UI', Arial; font-size: 13px; font-weight: 500;");

    // Dodajemy widżety do układu
    uklad->addWidget(probka);
    uklad->addWidget(etykieta);
}
