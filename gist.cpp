#include "gist.h"
#include <QLabel>

gist::gist(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Gist");
    lay1=new QVBoxLayout;
    grid=new QGridLayout;

    series=new QBarSeries;
    chart= new QChart;
    chartView = new QChartView(chart);
    axisX=new QBarCategoryAxis;
    axisY=new QValueAxis;


    exit=new QPushButton("exit");
    next=new QPushButton("next");
    connect(exit,&QPushButton::clicked,[this]{this->close();});
    connect(next,&QPushButton::clicked,[this]{this->next_gist();});
    lay1->addWidget(exit);
    lay1->addWidget(next);

    for(int i=0;i<10;++i){
        set[i]=new QBarSet("");
        series->append(set[i]);
    }

    chart->addSeries(series);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    grid->addWidget(chartView,0,0);

    grid->addLayout(lay1,0,1);
    setLayout(grid);
    this->resize(600,600);
}

void gist::create(list *start_of_list){
    start_list=start_of_list;
    stop=start_list;
    next->setVisible(1);
    next_gist();
    this->show();
}

void gist::next_gist(){
    int max=0;
    int i=0;
    list *start,*current;
    start=stop;
    current=start;
    delete chartView;

    series=new QBarSeries;
    chart= new QChart;
    axisX=new QBarCategoryAxis;
    axisY=new QValueAxis;

    while(current!=NULL&&i<2)
    {
       if(current->count>max){
           max=current->count;
       }
       set[i]=new QBarSet(current->str);
       *set[i]<<current->count;

       series->append(set[i]);

       ++i;
       current=current->next;
    }
    stop=current;

    if(current==NULL){
        next->setVisible(0);
    }

    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY->setRange(0,(max+max/2));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    grid->addWidget(chartView,0,0);
}


gist::~gist(){};

