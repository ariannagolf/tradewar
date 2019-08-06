#ifndef HIGHLIGHTSPAGE_H
#define HIGHLIGHTSPAGE_H

#include <QWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QVector>
#include <QString>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QComboBox>
#include <QPushButton>
#include <QGroupBox>
#include <QApplication>
#include <QDesktopWidget>

using namespace QtCharts;

class HighlightsPage : public QWidget {
public:
    /*Default constructor; contains all layouts for the highlights from IEX API*/
    HighlightsPage(QWidget *parent = nullptr);
    // makes an API call to grab ticker symbols and stock names from IEX
    void grabSymbols();
    // makes an API call to grab stock data
    void grabData();

public slots:

    
private:
    QVBoxLayout *layout;
    QHBoxLayout *h_layout;
    QGridLayout *grid;
    QPushButton *goButton = nullptr;
    QComboBox *stock_options = nullptr;
    QLabel *highlights_label = nullptr;

    //displays market data
    QGroupBox *marketGroup();
    //displays sector data
    QGroupBox *sectorGroup();
    //displays top stock gainers data
    QGroupBox *gainersGroup();
    //displays top stock losers data
    QGroupBox *losersGroup();

    QVector<std::string> ticker;

    QVector <QString> venueName;
    QVector <QString> marketPercent;
    QVector <QString> name;
    QVector <QString> performance;
    QVector <QString> g_companyName;
    QVector <QString> g_changePercent;
    QVector <QString> l_companyName;
    QVector <QString> l_changePercent;

    QString *stock_name = nullptr;

    friend class TradeWar;
};

#endif //HIGHLIGHTSPAGE_H
