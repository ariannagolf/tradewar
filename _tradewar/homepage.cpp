#include "homepage.h"
#include "tradewar.h"

HomePage::HomePage(QWidget *parent): QWidget(parent) {
    QLabel *descript = new QLabel(tr("Here are the historical prices for: "));
    stocknameLabel = new QLabel;

    onemonth = new QRadioButton(tr("1 month"));
    threemonth = new QRadioButton(tr("3 month"));
    sixmonth = new QRadioButton(tr("6 month"));
    oneyear = new QRadioButton(tr("1 year"));
    fiveyear = new QRadioButton(tr("5 year"));

    threemonth->setChecked(true);

    v_layout = new QVBoxLayout;
    v_layout->addWidget(descript);

    r_layout = new QHBoxLayout;
    h_layout = new QHBoxLayout;
    v_layout->addWidget(stocknameLabel,0,Qt::AlignHCenter);
    v_layout->addLayout(r_layout);
    v_layout->addLayout(h_layout);

    setLayout(v_layout);
}

void HomePage::displayGraph() {
    // deletes graph if a stock is changed
    if(chartView == nullptr) {}
    else {
        delete chartView;
        chartView = nullptr;
    }

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    r_layout->addWidget(onemonth);
    r_layout->addWidget(threemonth);
    r_layout->addWidget(sixmonth);
    r_layout->addWidget(oneyear);
    r_layout->addWidget(fiveyear);

    h_layout->addWidget(chartView);
}

void HomePage::displayTable() {
    //deletes a table if the stock is changed
    if(tableView == nullptr) {}
    else {
        delete tableView;
        tableView = nullptr;
    }

    tableView = new QTableView();

    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Close"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("% Change"));

    tableView->verticalHeader()->hide();
    tableView->horizontalHeader()->setStyleSheet("background-color: #6b9657;");

    h_layout->addWidget(tableView);

}
