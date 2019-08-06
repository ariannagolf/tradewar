#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QPushButton>
#include <QWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QStandardItemModel>
#include <QRadioButton>
#include <QTableWidgetItem>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

using namespace QtCharts;

class HomePage: public QWidget {
public:
    // Default constructor for setting up ui of home page
    HomePage( QWidget *parent = nullptr );
    /* given the stock the user chose create a table of the historical data
             * @param filename - QString*/
    // displays the graph created in graphHistoricalData()
    void displayGraph();
    // displays the table created in populate_table()
    void displayTable();

private:
    QTableView *tableView = nullptr;
    QStandardItemModel *model = nullptr;

    QString* filename = nullptr;
    QHBoxLayout *h_layout;
    QVBoxLayout *v_layout;
    QHBoxLayout *r_layout;
    QLabel* stocknameLabel = nullptr;
    QChart *chart = nullptr;
    QChartView *chartView = nullptr;

    QRadioButton *onemonth;
    QRadioButton *threemonth;
    QRadioButton *sixmonth;
    QRadioButton *oneyear;
    QRadioButton *fiveyear;

    friend class TradeWar;
    friend class TestPage;
    friend class AnalysisPage;

};

#endif //HOMEPAGE_H
