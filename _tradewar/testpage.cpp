#include "testpage.h"
#include "tradewar.h"

/***** still in development ******/

TestPage::TestPage(QWidget* parent) : QWidget(parent) {
    QLabel *descript = new QLabel("Test Page");
    layout = new QVBoxLayout();

    stocknameLabel = new QLabel;

    QString ref_data;
    QStringList rowOfData;

    QFile file(":/test/questions.txt");
    //checks if the file opens properly and parses the file based on new lines
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ref_data = file.readAll();
        rowOfData = ref_data.split("\n");
        file.close();
    }
    // random integer from 0 to max number of lines
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    int randomInt = qrand() % ((rowOfData.size() + 1)-0) + 0;

    QLabel *question_label = new QLabel("Q: ");
    QLabel *question = new QLabel(rowOfData[randomInt]);

    layout->addWidget(stocknameLabel,0,Qt::AlignHCenter);
    layout->addWidget(descript);
    layout->addWidget(question_label);
    layout->addWidget(question);
}

void TestPage::displayGraph() {
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(chartView);
}

