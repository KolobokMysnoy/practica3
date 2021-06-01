#include "practic.h"



Practic::Practic(QWidget *parent)
    : QWidget(parent)
{
    set();
    this->resize(200,200);

}
void Practic::set_input_button(){
    input_button=new QPushButton;
    input_button->setText("Input");
    input_button->setMaximumSize(300,40);
}

void Practic::set_exit_button(){
    exit_button=new QPushButton;
    exit_button->setText("EXIT");
    exit_button->setMaximumSize(300,40);
}

void Practic::set_search_button(){
    search_button=new QPushButton;
    search_button->setText("Search");
    search_button->setMaximumSize(300,40);
}

void Practic::set_delete_button(){
    delete_button=new QPushButton;
    delete_button->setText("Delete");
    delete_button->setMaximumSize(300,40);
}

void Practic::set(){
    open_window=0;

    set_delete_button();
    set_input_button();
    set_search_button();
    set_exit_button();

    connect(exit_button,&QPushButton::clicked,[this]{emit close_signal();});
    connect(input_button,&QPushButton::clicked,[this]{this->window_show(1);});
    connect(search_button,&QPushButton::clicked,[this]{this->window_show(2);});
    connect(delete_button,&QPushButton::clicked,[this]{this->window_show(3);});
    connect(this, &Practic::close_signal,[this]{this->window_close();});

    layout=new QVBoxLayout;
    layout->addWidget(input_button);
    layout->addWidget(search_button);
    layout->addWidget(delete_button);
    layout->addWidget(exit_button);

    la=new QHBoxLayout;
    la->addLayout(layout);
    setLayout(la);
}

void Practic::window_show(int id){
   /// MainWin=0
   /// InputWin=1
   /// SearchWin=2
   /// DeleteWin=3

    window_hide(open_window);
    open_window=id;

    switch (id) {
    case 1:
        input_win.show();
        break;
    case 2:
        search_win.show();
        break;
    case 3:
        delete_win.show();
        break;
    }

}

void Practic::window_hide(int id){
    switch (id) {
    case 1:
        input_win.hide();
        break;
    case 2:
        search_win.hide();
        break;
    case 3:
        delete_win.hide();
        break;
    }
}

void Practic::window_close(){
    file.close();
    search_win.close();
    delete_win.close();
    input_win.close();
    this->close();
}

Practic::~Practic()
{

}

