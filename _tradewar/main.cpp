#include "openingpage.h"
#include "tradewar.h"
#include "curl/curl.h"

#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    OpeningPage *p = new OpeningPage;
    p->showFullScreen();

    return a.exec();
}
