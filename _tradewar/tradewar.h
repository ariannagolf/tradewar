#ifndef TRADEWAR_H
#define TRADEWAR_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QStackedLayout>
#include <QComboBox>
#include <QStringList>
#include <QString>
#include <string>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QFile>
#include <QDebug>
#include <QTableView>
#include <QHeaderView>
#include <QLabel>
#include <QDialog>
#include <QFont>
#include <QFontDatabase>
#include <QVector>
#include <QApplication>
#include <QRadioButton>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QCategoryAxis>
#include <QHBoxLayout>
#include <QTime>
#include <QRegExp>
#include <string>
#include <vector>
#include <QScrollArea>


//make all connections here
//parse all data from IEX here
class AnalysisPage;
class HighlightsPage;
class TestPage;
class HomePage;


class TradeWar: public QWidget {
    Q_OBJECT
public:
    // default constructor that constructs the stacked widget
    TradeWar();
    // destructor
    ~TradeWar();
    /* makes API call to grab the historical stock data specified by symbol and range
     * @param symbol - std::string
     * range - std::string
     */
    void grabHistoricalData(std::string symbol, std::string range);
    // populates the chart with historical data and calls displayGraph() in homepage
    void graphHistoricalData();
    // populates the table with historical data  and calls displayTable() in homepage
    void populate_table();
    // creates and populates a vector to calculate CDF for each stock
    void probability();
    //void testFunction(); to be implemented later

    
public slots:
    /* registers when a user picks a different stock in the combo box
     * @param index - int
     */
    void stock_changed(int index);
    // Detects when user picks a different range calls the appropriate functions to update the chart and table with the new time range
    void range_changed();
    // opens tradewar from OpeningPage
    void to_TradeWar();
    // Goes to highlightsPage
    void to_highlightsPage();
    // Goes to homePage
    void to_homePage();
    // goes to analysisPage
    void to_analysisPage();
    // to be implemented later :)
    void to_testPage();
    
    
private:
    QStackedWidget *pages;
    
    HighlightsPage *highlightsPage = nullptr;
    HomePage *homePage = nullptr;
    AnalysisPage *analysisPage = nullptr;
    TestPage *testPage = nullptr;
    
    QPushButton *highlight;
    QPushButton *home;
    QPushButton *analysis;
    QPushButton *test;
    
    QString temp_range;
    
    QVector <QString> label;
    QVector <QString> date;
    QVector <double> close;
    QVector <double> percent;
    QVector <int> numDays;

    std::string* ticker = new std::string();
    std::string* range = new std::string();

    
    friend class HightlightsPage;
    friend class HomePage;
    friend class AnalysisPage;
    friend class TestPage;
};

#endif // TRADEWAR_H

