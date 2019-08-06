#include "analysispage.h"
#include "tradewar.h"


AnalysisPage::AnalysisPage(QWidget* parent) : QWidget(parent) {
    QLabel *descript = new QLabel("Analysis Page");
    v_layout = new QVBoxLayout;
    stocknameLabel = new QLabel;

    descript->setStyleSheet("font-size: 25px;");

    v_layout->addWidget(stocknameLabel,0,Qt::AlignHCenter);
    v_layout->addWidget(descript);
    setLayout(v_layout);
}

void AnalysisPage::displayInfo() {
    // clears data from the peers and news section when you choose a new stock
    if(p_layout == nullptr && n_layout == nullptr && h_layout == nullptr) {
    }
    else {
        delete p_layout;
        delete n_layout;
        delete h_layout;
        p_layout = nullptr;
        n_layout = nullptr;
        h_layout = nullptr;
    }
    v_news.clear();
    v_peers.clear();

    h_layout = new QHBoxLayout;
    p_layout = new QVBoxLayout;
    n_layout = new QVBoxLayout;

    QLabel *p_label = new QLabel("Competitors");
    QLabel *n_label = new QLabel("Recent news");

    p_label->setStyleSheet("font-size:20px;");
    n_label->setStyleSheet("font-size:20px;");

    p_layout->addWidget(p_label);
    n_layout->addWidget(n_label);

    //if the stock has less then 5 news stories, populates a QVector with the available news stories
    if(news_headline.size() < 5) {
        for(int i = 0; i < news_headline.size(); i++) {
            QString headline = news_headline[i];
            QString summary = news_summary[i];
            QString url = news_url[i];

            QString temp = headline + "\n" + "Summary: " + summary + "\n" + url + "\n";

            news_info = new QLabel(temp);
            v_news.push_back(news_info);
        }
    }
    // if the stock has more then 5 news stories, sets a limit of 5 and populates a QVector with the news stories
    else {
        for(int i = 0; i < 5; i++) {
            QString headline = news_headline[i];
            QString summary = news_summary[i];
            QString url = news_url[i];

            QString temp = headline + "\n" + "Summary: " + summary + "\n" + url + "\n";

            news_info = new QLabel(temp);
            v_news.push_back(news_info);

        }
    }
    // populates a vector with the peer info
    for(int i = 0; i < peers.size(); i++) {
        QString temp = peers[i];
        peers_info = new QLabel(temp);

        v_peers.push_back(peers_info);

    }
    // adds news info to the page layout
    for(int i = 0; i < v_news.size(); i++) {
        n_layout->addWidget(v_news[i]);
    }
    // adds peer info to the page layout
    for(int i = 0; i < v_peers.size(); i++) {
        p_layout->addWidget(v_peers[i]);
    }

    h_layout->addLayout(p_layout);
    h_layout->addLayout(n_layout);
    v_layout->addLayout(h_layout);

}

void AnalysisPage::displayProb(QString text) {
    // deletes analysis when stock is changed
    if(textProb == nullptr) {
    }
    else {
        delete textProb;
        textProb = nullptr;
    }

    textProb = new QLabel(text);
    textProb->setStyleSheet("font-size: 30px; font-weight: bold; background-color: #666666;");
    v_layout->addWidget(textProb,0, Qt::AlignHCenter);
}

