#ifndef GIST_H
#define GIST_H

#include <QObject>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include "list.h"
#include<QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>

class gist:public QWidget
{
    Q_OBJECT
public:
    gist(QWidget *parent = nullptr);
    void create(list *start_of_list);
    ~gist();
private:
     QPushButton *exit,*next;
     list *stop,*start_list;

     //layouts
     QVBoxLayout *lay1;
     QHBoxLayout *lay2;
     QGridLayout *grid;

     //gistogramm
     QChartView *chartView;
     QBarSeries *series;
     QBarSet* set[10];
     QBarCategoryAxis *axisX;
     QChart *chart;
     QValueAxis *axisY;

     void next_gist();
};

#endif // GIST_H
