#include "file_data.h"

char* sum(char* a,QString str){
    QByteArray strar=str.toLocal8Bit();
    int i=0;
    do {
        a[i]=strar.data()[i];
        ++i;
    } while (strar.data()[i]!='\0');
    a[i]=strar.data()[i];
    return a;
}


void transform(data* from,data_qstring* to){
     to->score_1=from->score_1;
     to->score_2=from->score_2;
     to->team_1="";
     to->team_2="";
     to->place="";
     to->place.append(from->place);
     to->team_1.append(from->team_1);
     to->team_2.append(from->team_2);
}
