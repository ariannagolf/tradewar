#ifndef TESTPAGE_H
#define TESTPAGE_H

/* Test Page is in development*/

#include <QWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

using namespace QtCharts;

class TestPage: public QWidget {
public:
    // Default constructor for setting up ui of test page
    TestPage(QWidget *parent = nullptr);
    // displays the graph of the stocks historical data
    void displayGraph();
    // displays test results
    void displayTest();

private:
    QLabel *stocknameLabel = nullptr;

    QVBoxLayout *layout;
    QChartView *chartView;
    QChart *chart;

    friend class TradeWar;
};

#endif //TESTPAGE_H
