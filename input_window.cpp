#include "input_window.h"


input_window::input_window(QWidget *parent)
    : QWidget(parent)
{
    set();
    setLayout(&main_lay);
    setWindowTitle("Input");
}

void input_window::create_labels(){
    label_place=new QLabel("Place");
    label_teams=new QLabel("Teams");
    label_scores=new QLabel("Scores");

    grid_layout->addWidget(label_place,0,0);
    grid_layout->addWidget(label_teams,1,0);
    grid_layout->addWidget(label_scores,2,0);
    }

void input_window::create_lines(){
    line_place=new QLineEdit;
    line_score_1=new QLineEdit;
    line_score_2=new QLineEdit;
    line_team_1=new QLineEdit;
    line_team_2=new QLineEdit;

    horizontal_for_scores->addWidget(line_score_1);
    horizontal_for_scores->addWidget(line_score_2);

    horizontal_for_teams->addWidget(line_team_1);
    horizontal_for_teams->addWidget(line_team_2);

    grid_layout->addWidget(line_place,0,1);
    grid_layout->addLayout(horizontal_for_teams,1,1);
    grid_layout->addLayout(horizontal_for_scores,2,1);
}

void input_window::create_layouts(){
    grid_layout=new QGridLayout;
    horizontal_for_scores=new QHBoxLayout;
    horizontal_for_teams=new QHBoxLayout;
    horizontal_for_buttons=new QHBoxLayout;
    vertical_layout=new QVBoxLayout;
}

void input_window::create_buttons(){
    exit_button=new QPushButton;
    input_button=new QPushButton;

    exit_button->setText("Exit to main");
    input_button->setText("Input data in file");

    connect(exit_button,&QPushButton::clicked,[this]{file.close();close();});
    connect(input_button,&QPushButton::clicked,[this]{input_in_file();});
}

void input_window::input_in_file(){

    sum(data_to_work.place,line_place->text());
    data_to_work.score_1=line_score_1->text().toInt();
    data_to_work.score_2=line_score_2->text().toInt();
    sum(data_to_work.team_1,line_team_1->text());
    sum(data_to_work.team_2,line_team_2->text());

    if(!file.isOpen())
    {
        file.open(QIODevice::ReadWrite);
    }
    file.seek(file.size());

    file.write((char*)&data_to_work,sizeof(data_to_work));

    line_place->setText("");
    line_score_1->setText("");
    line_score_2->setText("");
    line_team_1->setText("");
    line_team_2->setText("");
}


void input_window::set(){
    //open file
    file.setFileName("file.dat");
    file.close();
    file.open(QIODevice::WriteOnly);

    //Creates interface
    create_layouts();
    create_labels();
    create_lines();
    create_buttons();

    //add layout
    vertical_layout->addLayout(grid_layout);
    vertical_layout->addWidget(input_button);
    vertical_layout->addWidget(exit_button);
    main_lay.addLayout(vertical_layout);
}



input_window::~input_window(){

}
