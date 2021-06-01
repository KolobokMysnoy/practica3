#include "delete_window.h"

delete_window::delete_window(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Delete");
    set();
    setLayout(&main_lay);

    file.setFileName("file.dat");
}

void delete_window::create_labels(){
    label_place=new QLabel("Place");
    label_teams=new QLabel("Teams");
    label_scores=new QLabel("Scores");

    grid_layout->addWidget(label_place,0,0);
    grid_layout->addWidget(label_teams,1,0);
    grid_layout->addWidget(label_scores,2,0);
    }

void delete_window::create_lines(){
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

void delete_window::create_layouts(){
    grid_layout=new QGridLayout;
    horizontal_for_scores=new QHBoxLayout;
    horizontal_for_teams=new QHBoxLayout;
    horizontal_for_buttons=new QHBoxLayout;
    vertical_layout=new QVBoxLayout;
}

void delete_window::create_buttons(){
    exit_button=new QPushButton;
    delete_button=new QPushButton;
    delete_all=new QPushButton;

    exit_button->setText("Exit to main");
    delete_button->setText("Delete this data");
    delete_all->setText("Delete all data");

    connect(delete_all, &QPushButton::clicked,[this]{delete_all_data();});
    connect(exit_button,&QPushButton::clicked,[this]{close();});
    connect(delete_button,&QPushButton::clicked,[this]{delete_data();});
}

void delete_window::delete_data(){
    data_input.place = line_place->text();
    data_input.score_1=(line_score_1->text().toInt());
    data_input.score_2=line_score_2->text().toInt();
    data_input.team_1=line_team_1->text();
    data_input.team_2=line_team_2->text();

    if(!tmp_file.isOpen()){
        tmp_file.setFileName("tmp.dat");
        tmp_file.open(QIODevice::ReadWrite);
    }
    if(!file.isOpen()){
        file.open(QIODevice::ReadWrite);

    }
    file.seek(0);
    while(!file.atEnd()){
        file.read((char*)&read_data,sizeof(read_data));
        transform(&read_data,&transform_data);
        if(!((data_input.score_1==transform_data.score_1)&&(data_input.score_2==transform_data.score_2)&&
                (data_input.place==transform_data.place)&&(data_input.team_1==transform_data.team_1)&&
                (data_input.team_2==transform_data.team_2)))
        {
            tmp_file.write((char*)&read_data,sizeof(read_data));
        }



    }
    file.close();
    file.remove();
    tmp_file.close();
    file.setFileName("tmp.dat");
    file.open(QIODevice::ReadWrite);
    file.rename("file.dat");
    file.close();

    line_place->setText("");
    line_score_1->setText("");
    line_score_2->setText("");
    line_team_1->setText("");
    line_team_2->setText("");

}

void delete_window::set(){
   //Creates interface
    create_layouts();
    create_labels();
    create_lines();
    create_buttons();

    //add layout
    vertical_layout->addLayout(grid_layout);
    vertical_layout->addWidget(delete_button);
    vertical_layout->addWidget(delete_all);
    vertical_layout->addWidget(exit_button);
    main_lay.addLayout(vertical_layout);
}
void delete_window::delete_all_data(){
    file.close();
    file.remove();
}
