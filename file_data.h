#ifndef FILE_DATA_H
#define FILE_DATA_H
#include <QWidget>

char* sum(char* a,QString str);
bool equal(QString str,char* a);

//data to work with files
struct data{
public:
    char place[200];
    char team_1[200], team_2[200];

    int score_1,score_2;
};

struct data_qstring{
    QString place,team_1,team_2;
    int score_1,score_2;
};
void transform(data* from,data_qstring* to);


#endif // FILE_DATA_H
