#include "tradewar.h"
#include "highlightspage.h"
#include "homepage.h"
#include "testpage.h"
#include "analysispage.h"
#include "openingpage.h"
#include "IEX.h"
#include "json/json.h"
#include <string>
#include <iostream>


TradeWar::TradeWar(): QWidget() {
    QFile file(":/style/stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    qApp->setStyleSheet(styleSheet);
    // checks if file opens properly
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "stylesheet not open" << file.error();
    }
    else{
       qDebug() << "stylesheet is open";
    }
    file.close();

    // import custom fonts
    int id2 = QFontDatabase::addApplicationFont(":/font/ubuntu-regular.ttf");
    QString family2 = QFontDatabase::applicationFontFamilies(id2).at(0);
    QFont ubuntu(family2, 15);
    QApplication::setFont(ubuntu);


    QGridLayout *layout = new QGridLayout(this);

    pages = new QStackedWidget();

    layout->addWidget(pages);

    highlight = new QPushButton("Daily Highlights");
    home = new QPushButton("Home");
    test = new QPushButton("Test");
    analysis = new QPushButton("Analysis");

    highlight->setMinimumWidth(68);

    layout->addWidget(highlight);
    layout->addWidget(home);
    layout->addWidget(analysis);
    //layout->addWidget(test);

    highlightsPage = new HighlightsPage(pages);
    homePage = new HomePage(pages);
    testPage = new TestPage(pages);
    analysisPage = new AnalysisPage(pages);

    pages->addWidget(highlightsPage);
    pages->addWidget(homePage);
    pages->addWidget(testPage);
    pages->addWidget(analysisPage);


    connect(highlightsPage->stock_options, SIGNAL(currentIndexChanged(int)), this, SLOT(stock_changed(int)));
    connect(homePage->onemonth, SIGNAL(clicked()), this, SLOT(range_changed()));
    connect(homePage->threemonth, SIGNAL(clicked()), this, SLOT(range_changed()));
    connect(homePage->sixmonth, SIGNAL(clicked()), this, SLOT(range_changed()));
    connect(homePage->oneyear, SIGNAL(clicked()), this, SLOT(range_changed()));
    connect(homePage->fiveyear, SIGNAL(clicked()), this, SLOT(range_changed()));


    connect(highlight, SIGNAL(clicked()), this, SLOT(to_highlightsPage()));
    connect(home,SIGNAL(clicked()),this,SLOT(to_homePage()));
    connect(highlightsPage->goButton,SIGNAL(clicked()),this,SLOT(to_homePage()));
    connect(test,SIGNAL(clicked()),this,SLOT(to_testPage()));
    connect(analysis,SIGNAL(clicked()),this,SLOT(to_analysisPage()));

    pages->setCurrentIndex(0);
}

void TradeWar::to_TradeWar() {
    pages->show();
}

void TradeWar::to_highlightsPage() {
    pages->setCurrentIndex(0);
}

void TradeWar::to_homePage() {
    pages->setCurrentIndex(1);
}

void TradeWar::to_testPage() {
    pages->setCurrentIndex(2);
}

void TradeWar::to_analysisPage() {
    pages->setCurrentIndex(3);
}

void TradeWar::stock_changed(int index) {
    homePage->stocknameLabel->setText(highlightsPage->stock_options->itemText(index));
    analysisPage->stocknameLabel->setText(highlightsPage->stock_options->itemText(index));
    testPage->stocknameLabel->setText(highlightsPage->stock_options->itemText(index));

    homePage->stocknameLabel->setStyleSheet("font: url(:/font/ubuntu-bold.ttf); font-size: 30px; color: white;");
    analysisPage->stocknameLabel->setStyleSheet("font: url(:/font/ubuntu-bold.ttf); font-size: 30px; color: white;");
    testPage->stocknameLabel->setStyleSheet("font: url(:/font/ubuntu-bold.ttf); 30px; color: white;");

    QString temp = highlightsPage->stock_options->itemText(index);

    //parses out the ticker symbol
    QStringList list = temp.split("(");
    QStringList temp_list = list[list.size()-1].split(")");

    QString temp2 = temp_list[0];

    *ticker = temp2.toUtf8().constData();

    grabHistoricalData(*ticker, "3m");
    populate_table();
    probability();

//    delete analysisPage->v_layout;
//    analysisPage->v_layout = nullptr;
    analysisPage->displayInfo();


    homePage->threemonth->setChecked(true);
    homePage->onemonth->setChecked(false);
    homePage->sixmonth->setChecked(false);
    homePage->oneyear->setChecked(false);
    homePage->fiveyear->setChecked(false);
}

void TradeWar::range_changed() {
    // checks if a user picks the specified radio button and changes the range based on the choice
    if(homePage->onemonth->isChecked() == true) {
        *range = "1m";
    }
    else if(homePage->threemonth->isChecked() == true) {
        *range = "3m";
    }
    else if(homePage->sixmonth->isChecked() == true) {
        *range = "6m";
    }
    else if(homePage->oneyear->isChecked() == true) {
        *range = "1y";
    }
    else if(homePage->fiveyear->isChecked() == true) {
        *range = "5y";
    }
    else {
        *range = "3m";
    }

    grabHistoricalData(*ticker, *range);
    probability();
    populate_table();

}

void TradeWar::grabHistoricalData(std::string symbol, std::string range) {
    // API CALL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    Json::Value chartData;
    chartData = IEX::stocks::chartRange(symbol, range);

    Json::Value a_peers;
    a_peers = IEX::stocks::peers(symbol);

    Json::Value a_news;
    a_news = IEX::stocks::news(symbol);
    curl_global_cleanup();

    // clears data to prevent data appending when a stock is changed
    close.clear();
    date.clear();
    label.clear();
    percent.clear();
    analysisPage->peers.clear();
    analysisPage->news_headline.clear();
    analysisPage->news_summary.clear();
    analysisPage->news_url.clear();

    // pushes data from the api call into vectors
    for(int i = 0; i < chartData.size(); i++) {
        label.push_back(QString::fromStdString(chartData[i]["label"].asString()));
        close.push_back(chartData[i]["close"].asDouble());
        percent.push_back(chartData[i]["changePercent"].asDouble());
        date.push_back(QString::fromStdString(chartData[i]["date"].asString()));
    }
    // pushes data from the api call into vectors
    for(int i = 0; i < a_peers.size(); i++) {
        analysisPage->peers.push_back(QString::fromStdString(a_peers[i].asString()));
    }
    // pushes data from the api call into vectors
    for(int i = 0; i < a_news.size(); i++) {
        analysisPage->news_headline.push_back(QString::fromStdString(a_news[i]["headline"].asString()));
        analysisPage->news_summary.push_back(QString::fromStdString(a_news[i]["summary"].asString()));
        analysisPage->news_url.push_back(QString::fromStdString(a_news[i]["url"].asString()));
    }

    graphHistoricalData();
}

void TradeWar::graphHistoricalData() {
    QLineSeries *series = new QLineSeries();
    // creates a series from user chosen data
    for(int i = 0; i < close.size(); i++) {
        series->append(i,close[i]);
    }

    homePage->chart = new QChart();
    homePage->chart->legend()->hide();
    homePage->chart->addSeries(series);
    homePage->chart->setTitle(QString::fromStdString(*ticker));

    QCategoryAxis *Xaxis = new QCategoryAxis;
    // creates labels for the charts x axis from data
    for(int j = 1; j < label.size(); j++) {
        Xaxis->append(label[j],j);
    }

    Xaxis->setTickCount(10);
    Xaxis->setTitleText("Date");
    homePage->chart->addAxis(Xaxis, Qt::AlignBottom);
    series->attachAxis(Xaxis);

    homePage->chart->createDefaultAxes();

    //connection stuff to get param name for settitletext
    homePage->chart->axisY()->setTitleText("Price ($)");
    homePage->chart->setAxisX(Xaxis, series);

    homePage->displayGraph();
}

void TradeWar::populate_table() {
    homePage->model = new QStandardItemModel;
    // populates table with data
    for(int j = 0; j < date.size(); j++) {
        QStandardItem *t_date = new QStandardItem(date[j]);
        QStandardItem *t_close = new QStandardItem(QString::number(close[j]));
        QStandardItem *t_percent = new QStandardItem(QString::number(percent[j]));
        homePage->model->setItem(j, 0, t_date);
        homePage->model->setItem(j, 1, t_close);
        homePage->model->setItem(j, 2, t_percent);

    }

    homePage->displayTable();
}

void TradeWar::probability() {
    // sort percent vector
    qSort(percent.begin(), percent.end());

    // count vector to calculate distribution of percent change
    double length = percent.size();
    std::vector<double> count;
    for(int i = 0; i < length; i++) {
        count.push_back(i/length);
    }

    std::vector<double> v_percent = percent.toStdVector();
    auto const it = std::lower_bound(v_percent.begin(), v_percent.end(), 0.5);
    double val = *(it - 1);
    int index = std::distance(v_percent.begin(), it);

    QString num = QString::number(count[index]*100) + "%.";
    QString prob_text = "The probability the stock will increase by more than 0.5% is " + num;

    analysisPage->displayProb(prob_text);

}

//void TradeWar::testFunction() {} to be implemented later

TradeWar::~TradeWar() {
    delete ticker;
    delete range;
}



