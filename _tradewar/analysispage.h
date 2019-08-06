#ifndef ANALYSISPAGE_H
#define ANALYSISPAGE_H

#include <QWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>

class AnalysisPage: public QWidget {
public:
    /* Default constructor that sets up the ui for the Analysis page*/
    AnalysisPage(QWidget *parent = nullptr);
    // Displays news and peers for the chosen stock
    void displayInfo();
    /* Displays the analysis of the stock
     * @param text - QString
     */
    void displayProb(QString text);
    
private:
    QLabel *stocknameLabel = nullptr;

    QLabel *textProb = nullptr;

    QVBoxLayout *v_layout;
    QHBoxLayout *h_layout = nullptr;
    QVBoxLayout *p_layout = nullptr;
    QVBoxLayout *n_layout = nullptr;

    QLabel *peers_info = nullptr;
    QLabel *news_info = nullptr;

    QVector <QString> peers;

    QVector <QString> news_headline;
    QVector <QString> news_summary;
    QVector <QString> news_url;

    QVector <QLabel*> v_peers;
    QVector <QLabel*> v_news;

    friend class TradeWar;
    friend class HomePage;
};

#endif // ANALYSISPAGE_H
