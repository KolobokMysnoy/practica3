#include "search_window.h"


search_window::search_window(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Search");
    start_set();
}

void search_window::start_set(){
    file.setFileName("file.dat");
    if(file.NotOpen)
    {
        file.open(QIODevice::ReadWrite);
    }

    teams=NULL;
    places=NULL;


    create_layouts();
    input_set();
    set_radio();
    buttons_set();
    output_set();

    vertical_layout->addLayout(horizontal_layout_for_radio_and_buttons);
    vertical_layout->addLayout(horizontal_layout_for_buttons);
    setLayout(vertical_layout);
}

void search_window::create_layouts(){
    horizontal_layout_for_buttons=new QHBoxLayout;
    horizontal_layout_for_radio_and_buttons=new QHBoxLayout;
    vertical_layout=new QVBoxLayout;
    vertical_layout_for_input=new QVBoxLayout;
}

void search_window::set_radio(){
    vertical_layout_for_buttons_in_box=new QVBoxLayout;
    equal_show_radio=new QRadioButton;
    more_or_equal_show_radio=new QRadioButton;
    place_show_radio=new QRadioButton;
    team_show_radio=new QRadioButton;

    equal_show_radio->setText("==");
    more_or_equal_show_radio->setText("<=");
    place_show_radio->setText("place");
    team_show_radio->setText("team");

    connect(equal_show_radio,&QRadioButton::clicked,[this]{change_line(1);});
    connect(more_or_equal_show_radio,&QRadioButton::clicked,[this]{change_line(2);});
    connect(place_show_radio,&QRadioButton::clicked,[this]{change_line(3);});
    connect(team_show_radio,&QRadioButton::clicked,[this]{change_line(4);});

    vertical_layout_for_buttons_in_box->addWidget(equal_show_radio);
    vertical_layout_for_buttons_in_box->addWidget(more_or_equal_show_radio);
    vertical_layout_for_buttons_in_box->addWidget(place_show_radio);
    vertical_layout_for_buttons_in_box->addWidget(team_show_radio);
    horizontal_layout_for_radio_and_buttons->addLayout(vertical_layout_for_buttons_in_box);
}

void search_window::output_set(){
    output_table=new QTableWidget;

    column_count=5;
    row_count=0;

    output_table->setColumnCount(column_count);
    vertical_layout->addWidget(output_table);
};

void search_window::input_set(){
    int_line=new QLineEdit;
    str_line= new QLineEdit;

    vertical_layout_for_input->addWidget(int_line);
    vertical_layout_for_input->addWidget(str_line);
    horizontal_layout_for_radio_and_buttons->addLayout(vertical_layout_for_input);

}

void search_window::buttons_set(){
    exit_button=new QPushButton;
    search_button=new QPushButton;

    exit_button->setText("Exit");
    search_button->setText("Search");

    connect(exit_button,&QPushButton::clicked,[this]{file.close();delete_list(&places);this->close();});
    connect(search_button,&QPushButton::clicked,[this]{table_refresh(); what_to_search();});

    horizontal_layout_for_buttons->addWidget(search_button);
    horizontal_layout_for_buttons->addWidget(exit_button);
};

void search_window::what_to_search(){
    if(!file.isOpen())
    {
        file.open(QIODevice::ReadWrite);
    }
    file.seek(0);

    row_count=0;
    while(!file.atEnd()){

        file.read((char*)&non_transform_data,sizeof(non_transform_data));
        transform(&non_transform_data,&read_data);

        switch (choose) {
        case 1:
            search_for_equals();
        break;
        case 2:
            search_for_equals_and_more();
        break;
        case 3:
            search_for_place();
        break;
        case 4:
            search_for_team();
        break;
        }
    }

};

void search_window::change_line(int id){
    ///place and team 3 4
    /// == and <= 1 2
    choose=id;
    switch (id) {
    case 1:
    {
        str_line->setReadOnly(1);
        int_line->setReadOnly(1);
    }
    break;
    case 2:
    {
        str_line->setReadOnly(1);
        int_line->setReadOnly(0);
    }
    break;
    case 3:
    {
        str_line->setReadOnly(1);
        int_line->setReadOnly(1);
    }
    break;
    case 4:
    {
        int_line->setReadOnly(1);
        str_line->setReadOnly(0);
    }
    break;
    }

}

void search_window::search_for_equals(){
    if(read_data.score_1==read_data.score_2){
        add_to_table();
    }
};

void search_window::search_for_equals_and_more(){
    if(read_data.score_1!=read_data.score_2){
        if(read_data.score_1>read_data.score_2){
          add_to_list(&teams,read_data.team_1);
        }
        else{
            add_to_list(&teams,read_data.team_2);
        }
    }
     if(file.atEnd()){
         add_to_table_more_or_equals();
         delete_list(&teams);
     }


};

void search_window::search_for_team(){
    if((str_line->text()==read_data.team_1)||
        (str_line->text()==read_data.team_2)){
        add_to_table();
    }

};

void search_window::search_for_place(){
    add_to_list(&places,read_data.place);
    if(file.atEnd())
    {
        set_gistogramm();

    }

};

void search_window::add_to_table(){
    QStringList list_str;
    list_str<<"Place" <<"Team 1" <<"Team 2"<<"Score 1"<<"Score 2";
    output_table->setHorizontalHeaderLabels(list_str);

    output_table->setColumnCount(column_count);
    output_table->setRowCount(row_count+1);
    item_of_the_table=new QTableWidgetItem;
    item_of_the_table->setText(read_data.place);
    output_table->setItem(row_count,column_count-5,item_of_the_table);
    item_of_the_table=new QTableWidgetItem;
    item_of_the_table->setText(read_data.team_1);
    output_table->setItem(row_count,column_count-4,item_of_the_table);
    item_of_the_table=new QTableWidgetItem;
    item_of_the_table->setText(read_data.team_2);
    output_table->setItem(row_count,column_count-3,item_of_the_table);
    item_of_the_table=new QTableWidgetItem;
    item_of_the_table->setText(QString::number(read_data.score_1));
    output_table->setItem(row_count,column_count-2,item_of_the_table);
    item_of_the_table=new QTableWidgetItem;
    item_of_the_table->setText(QString::number(read_data.score_2));
    output_table->setItem(row_count,column_count-1,item_of_the_table);

    row_count+=1;

}

void search_window::add_to_table_more_or_equals(){
    output_table->setColumnCount(0);
    output_table->setRowCount(0);
    output_table->setColumnCount(2);
    output_table->setHorizontalHeaderItem(0,new QTableWidgetItem("Team"));
    output_table->setHorizontalHeaderItem(1,new QTableWidgetItem("Wins"));

    int row_to_add=0;
    list *current,*start;
    start=teams;
    current=start;
    while(current!=NULL){
        output_table->setRowCount(row_to_add+1);
        output_table->setItem(row_to_add,0,new QTableWidgetItem(current->str));
        output_table->setItem(row_to_add,1,new QTableWidgetItem(QString::number(current->count)));

        ++row_to_add;
        current=current->next;
    }
}

void search_window::add_to_list(list **list_to_do, QString string){
    list *start,*current,*prev;
    start=*list_to_do;
    current=start;
    int flag=0;

    if(current!=NULL){
       while(current!=NULL){
           if(current->next==NULL){
               prev=current;
           }
           if(current->str==string){
               current->count+=1;
               flag=1;
           }
           current=current->next;
       }
       if(flag!=1){
            current=new list;
            current->str=read_data.place;
            current->count=1;
            current->next=NULL;
            prev->next=current;
       }

    }
    else
    {
        list *tmp;
        tmp=new list;
        tmp->str=read_data.place;
        tmp->count=1;
        tmp->next=NULL;
        *list_to_do=tmp;
    }
}

void search_window::delete_list(list **list_to_delete)
{
    list *start,*current;
    start=*list_to_delete;

    while(start!=NULL){
        current=start;
        start=start->next;
        delete current;
    }

}

void search_window::set_gistogramm(){

    gistogramm.create(places);
}

void search_window::table_refresh(){
    row_count=1;
    output_table->setRowCount(0);

    QStringList list_str;
    list_str<<"Place" <<"Team 1" <<"Team 2"<<"Score 1"<<"Score 2";
    output_table->setHorizontalHeaderLabels(list_str);

}

