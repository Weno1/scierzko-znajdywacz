#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>

class PathfinderGrid : public QFrame
{ 
public:
    PathfinderGrid(QWidget *parent = nullptr) : QFrame(parent)
    {
        setFrameStyle(QFrame::Panel | QFrame::Sunken);
    }
};
class ColorSwatch : public QFrame
{
public:
    ColorSwatch(QWidget *parent = nullptr) : QFrame(parent)
    {
        setFrameStyle(QFrame::Panel | QFrame::Raised);
        setFixedSize(30,30);
    }
};

class PathFinderWindow : public QMainWindow
{
public:
    PathFinderWindow()
    {
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

        QHBoxLayout *topRegionLayout = new QHBoxLayout();
        mainLayout->addLayout(topRegionLayout);

        PathfinderGrid *grid = new PathfinderGrid();

        topRegionLayout->addWidget(grid, 5);

        QVBoxLayout *statsLayout = new QVBoxLayout();
        QWidget *statsContainer = new QWidget();
        statsContainer->setLayout(statsLayout);
        statsContainer->setFixedWidth(150);
        topRegionLayout->addWidget(statsContainer);

        statsLayout->addWidget(new QLabel("Stats 1: --"));
        statsLayout->addWidget(new QLabel("Stats 2: --"));
        statsLayout->addStretch();

        QHBoxLayout *bottomControlLayout = new QHBoxLayout();
        mainLayout->addLayout(bottomControlLayout);

        // 3. Color Picker Panel
        QVBoxLayout *colorPickerPanel = new QVBoxLayout();
        QWidget *colorPickerContainer = new QWidget();
        colorPickerContainer->setLayout(colorPickerPanel);
        bottomControlLayout->addWidget(colorPickerContainer);

        colorPickerPanel->addWidget(new QLabel("Tile Palette:"));
        QHBoxLayout *swatches = new QHBoxLayout();
        swatches->addWidget(new ColorSwatch());
        swatches->addWidget(new ColorSwatch());
        colorPickerPanel->addLayout(swatches);
        colorPickerPanel->addWidget(new QLabel("Text at Bottom"));

        QVBoxLayout *algoPanel = new QVBoxLayout();
        QWidget *algoContainer = new QWidget();
        algoContainer->setLayout(algoPanel);
        bottomControlLayout->addWidget(algoContainer);

        algoPanel->addWidget(new QLabel("Select Algorithm:"));
        algoPanel->addWidget(new QComboBox());

        QVBoxLayout *buttonPanel = new QVBoxLayout();
        QWidget *buttonContainer = new QWidget();
        buttonContainer->setLayout(buttonPanel);
        bottomControlLayout->addWidget(buttonContainer);

        buttonPanel->addWidget(new QPushButton("Start"));
        buttonPanel->addWidget(new QPushButton("Stop"));
        buttonPanel->addWidget(new QPushButton("Step"));
        buttonPanel->addStretch();
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PathFinderWindow window;

    window.resize(1000, 700);

    window.show();

    return app.exec();
}