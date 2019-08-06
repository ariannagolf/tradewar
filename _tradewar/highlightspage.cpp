#include "highlightspage.h"
#include "tradewar.h"
#include "json/json.h"
#include "IEX.h"

HighlightsPage::HighlightsPage(QWidget* parent) : QWidget(parent) {
    grabData();
    layout = new QVBoxLayout(this);
    h_layout = new QHBoxLayout;
    QLabel *welcome_label = new QLabel(tr("Choose a ticker: "));

    highlights_label = new QLabel(tr("Today's market highlights:"));
    highlights_label->setStyleSheet("font-size: 25px;");

    layout->addStretch();
    layout->addWidget(welcome_label);
    layout->addWidget(stock_options, 0, Qt::AlignCenter);
    layout->addStretch();
    layout->setSpacing(10);


    grid = new QGridLayout;
    grid->addWidget(marketGroup(), 0,0);
    grid->addWidget(sectorGroup(), 1,0);
    grid->addWidget(gainersGroup(), 0,1);
    grid->addWidget(losersGroup(), 1,1);
    grabSymbols();
    layout->addLayout(grid);
}

void HighlightsPage::grabSymbols() {
    // API Call
    curl_global_init(CURL_GLOBAL_DEFAULT);
    Json::Value symbols;
    symbols = IEX::refData::symbols();
    curl_global_cleanup();

    QVector<std::string> name;
    // populates a vector with data pulled from API
    for(int i = 0; i < symbols.size(); i++) {
        name.push_back(symbols[i]["name"].asString());
        ticker.push_back(symbols[i]["symbol"].asString());
    }

    stock_options = new QComboBox;
    stock_options->addItem("Choose a ticker below");
    // populates a combobox with tickers for user to choose from
    for(int i = 0; i < symbols.size(); i++) {
        std::string options = name[i] + " (" + ticker[i] + ")";
        QString qstr = QString::fromStdString(options);
        stock_options->addItem(qstr);
    }

    goButton = new QPushButton("Go");
    h_layout->addWidget(stock_options);
    h_layout->addWidget(goButton);

    layout->addLayout(h_layout);
    layout->addWidget(highlights_label);
}

void HighlightsPage::grabData() {
    // API Call
    curl_global_init(CURL_GLOBAL_DEFAULT);
    //venueName, marketPercent
    Json::Value market;
    market = IEX::markets::market();

    //name, performance
    Json::Value sector;
    sector = IEX::stocks::sectorPerformance();

    //companyName, changePercent; returns 10
    Json::Value gainers;
    gainers = IEX::stocks::list("gainers");
    Json::Value losers;
    losers = IEX::stocks::list("losers");
    curl_global_cleanup();
    // populates a vector with data pulled from API
    for(int i = 0; i < market.size(); i++) {
        venueName.push_back(QString::fromStdString(market[i]["venueName"].asString()));
        marketPercent.push_back(QString::fromStdString(market[i]["marketPercent"].asString()));
    }
    // populates a vector with data pulled from API
    for(int i = 0; i < sector.size(); i++) {
        name.push_back(QString::fromStdString(sector[i]["name"].asString()));
        performance.push_back(QString::fromStdString(sector[i]["performance"].asString()));
    }
    // populates a vector with data pulled from API
    for(int i = 0; i < gainers.size(); i++) {
        g_companyName.push_back(QString::fromStdString(gainers[i]["companyName"].asString()));
        g_changePercent.push_back(QString::fromStdString(gainers[i]["changePercent"].asString()));
        l_companyName.push_back(QString::fromStdString(losers[i]["companyName"].asString()));
        l_changePercent.push_back(QString::fromStdString(losers[i]["changePercent"].asString()));
    }
}

QGroupBox *HighlightsPage::marketGroup() {
    QGroupBox *groupBox = new QGroupBox(tr("Market Data"));
    QVBoxLayout *m_layout = new QVBoxLayout;

    QStandardItemModel *model = new QStandardItemModel;
    // populates table with market data
    for(int i = 0; i < venueName.size(); i++) {
        QStandardItem *name = new QStandardItem(venueName[i]);
        QStandardItem *percent = new QStandardItem(marketPercent[i]);

        model->setItem(i, 0, name);
        model->setItem(i, 1, percent);
    }

    QTableView *marketView = new QTableView();

    marketView->setModel(model);
    marketView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    marketView->horizontalHeader()->setStyleSheet("background-color: #6b9657;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Ticker"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("% Change"));

    marketView->verticalHeader()->hide();


    m_layout->addWidget(marketView);
    groupBox->setLayout(m_layout);


    return groupBox;
}

QGroupBox *HighlightsPage::sectorGroup() {
    QGroupBox *groupBox = new QGroupBox(tr("Sector Data"));
    QVBoxLayout *m_layout = new QVBoxLayout;

    QStandardItemModel *model = new QStandardItemModel;
    // populates table with sector data
    for(int i = 0; i < name.size(); i++) {
        QStandardItem *sector = new QStandardItem(name[i]);
        QStandardItem *s_performance = new QStandardItem(performance[i]);

        model->setItem(i, 0, sector);
        model->setItem(i, 1, s_performance);
    }

    QTableView *sectorView = new QTableView();

    sectorView->setModel(model);
    sectorView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    sectorView->horizontalHeader()->setStyleSheet("background-color: #6b9657;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Sector"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("% Change"));

    sectorView->verticalHeader()->hide();


    m_layout->addWidget(sectorView);
    groupBox->setLayout(m_layout);

    return groupBox;
}

QGroupBox *HighlightsPage::gainersGroup() {
    QGroupBox *groupBox = new QGroupBox(tr("Gainers Data"));
    QVBoxLayout *m_layout = new QVBoxLayout;

    QStandardItemModel *model = new QStandardItemModel;
    // populates table with top stock gainers data
    for(int i = 0; i < g_companyName.size(); i++) {
        QStandardItem *g_name = new QStandardItem(g_companyName[i]);
        QStandardItem *percent = new QStandardItem(g_changePercent[i]);

        model->setItem(i, 0, g_name);
        model->setItem(i, 1, percent);
    }

    QTableView *gainersView = new QTableView();

    gainersView->setModel(model);
    gainersView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    gainersView->horizontalHeader()->setStyleSheet("background-color: #6b9657;");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Ticker"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("% Change"));

    gainersView->verticalHeader()->hide();

    m_layout->addWidget(gainersView);
    groupBox->setLayout(m_layout);

    return groupBox;
}

QGroupBox *HighlightsPage::losersGroup() {
    QGroupBox *groupBox = new QGroupBox(tr("Losers Data"));
    QVBoxLayout *m_layout = new QVBoxLayout;


    QStandardItemModel *model = new QStandardItemModel;
    // populates table with top stock losers data
    for(int i = 0; i < l_companyName.size(); i++) {
        QStandardItem *l_name = new QStandardItem(l_companyName[i]);
        QStandardItem *percent = new QStandardItem(l_changePercent[i]);

        model->setItem(i, 0, l_name);
        model->setItem(i, 1, percent);
    }

    QTableView *losersView = new QTableView();

    losersView->setModel(model);
    losersView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    losersView->horizontalHeader()->setStyleSheet("background-color: #6b9657;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Ticker"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("% Change"));

    losersView->verticalHeader()->hide();

    m_layout->addWidget(losersView);
    groupBox->setLayout(m_layout);

    return groupBox;
}
