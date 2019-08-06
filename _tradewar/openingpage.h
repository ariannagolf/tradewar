#ifndef OPENINGPAGE_H
#define OPENINGPAGE_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>

class OpeningPage : public QMainWindow {
    Q_OBJECT
public:
    /* Default constructor to setup ui for start page*/
    OpeningPage(QWidget *parent = nullptr);
    QPushButton *start;
public slots:
    // opens tradewar application from the start page
    void open_TradeWar();
    // opens instruction page
    void gotoHelp();
};


#endif // OPENINGPAGE_H
