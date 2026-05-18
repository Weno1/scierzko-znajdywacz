#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Scierzko znajdywacz");
    window.resize(300, 200);

    QPushButton *button = new QPushButton("Kliknij mnie!");

    QObject::connect(button, &QPushButton::clicked, [&window]() {
        QMessageBox::information(&window, "Wiadomość", "Witaj w świecie Qt!");
    });

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(button);
    window.setLayout(layout);

    window.show();

    return app.exec();
}