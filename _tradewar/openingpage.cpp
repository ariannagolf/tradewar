#include "openingpage.h"
#include "tradewar.h"

OpeningPage::OpeningPage(QWidget *parent): QMainWindow(parent) {
    int id2 = QFontDatabase::addApplicationFont(":/font/ubuntu-regular.ttf");
    QString family2 = QFontDatabase::applicationFontFamilies(id2).at(0);
    QFont ubuntu(family2, 15);
    QApplication::setFont(ubuntu);
    QFile file(":/style/opening_page.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    qApp->setStyleSheet(styleSheet);

    QPixmap bkgnd(":/pics/two.png");
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    QWidget *widget = new QWidget(this);
    QLabel *logo = new QLabel("tradewar");
    QPushButton *help = new QPushButton("Help");
    start = new QPushButton("Start");
    setCentralWidget(widget);

    QVBoxLayout *layout = new QVBoxLayout(widget);
    QHBoxLayout *h_layout = new QHBoxLayout;

    layout->addWidget(logo,0,Qt::AlignCenter);
    layout->addWidget(start);
    layout->addWidget(help);
    layout->addLayout(h_layout);

    connect(start, SIGNAL(clicked()), this, SLOT(open_TradeWar()));
    connect(help, SIGNAL(clicked()), this, SLOT(gotoHelp()));
}

void OpeningPage::open_TradeWar() {
    TradeWar *w = new TradeWar();
    w->show();

    this->hide();
}

void OpeningPage::gotoHelp() {
    QWidget *instructionPage = new QWidget;
    QVBoxLayout *instruction_layout = new QVBoxLayout;
    instruction_layout->addStretch();
    QString readme = "Welcome to tradewar! \n Once you press the start button you will be taken to a page that displays the current day's market highlights, \n such as composites, sector performances, and today's top gaining and losing stocks. \n Choose a ticker symbol to see individual stock details as well the historical stock prices in table form.\n Navigate to the analysis to see what we think about your chosen stock.\n Make sure to have the latest versions of Boost and Libcurl libraries. \n Check README for more detailed instructions.";

    QLabel *instruct_text = new QLabel(readme);
    QPushButton *close_instruct = new QPushButton("Close");

    instruct_text->setStyleSheet("font-size: 25px;");
    instructionPage->setStyleSheet("background-color: #0f5257");

    instruction_layout->addWidget(instruct_text,0, Qt::AlignCenter);
    instruction_layout->addWidget(close_instruct,0,Qt::AlignCenter);
    instructionPage->setLayout(instruction_layout);
    connect(close_instruct, SIGNAL(clicked()), instructionPage, SLOT(close()));
    instructionPage->setWindowTitle("Instructions");
    instructionPage->show();
}
