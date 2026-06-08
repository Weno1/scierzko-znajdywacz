#ifndef LEGEND_ITEM_H
#define LEGEND_ITEM_H

#include <QWidget>
#include <QColor>
#include <QString>

/**
 * @class LegendItem
 * @brief Pomocniczy widżet reprezentujący pojedynczy wpis w legendzie kolorów.
 * 
 * Rysuje małą próbkę koloru (lub ikonę startu/celu) oraz stowarzyszoną z nią etykietę tekstową.
 */
class LegendItem : public QWidget {
public:
    /**
     * @brief Konstruktor elementu legendy.
     * @param kolor Kolor kwadracika próbki.
     * @param tekst Opis słowny elementu planszy.
     * @param czyStart Czy ma rysować zieloną ikonkę startu.
     * @param czyCel Czy ma rysować czerwoną ikonkę celu.
     * @param rodzic Wskaźnik na obiekt rodzica Qt (domyślnie nullptr).
     */
    LegendItem(const QColor &kolor, const QString &tekst, bool czyStart = false, bool czyCel = false, QWidget *rodzic = nullptr);
};

#endif // LEGEND_ITEM_H
