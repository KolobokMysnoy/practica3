#ifndef SEARCH_WINDOW_H
#define SEARCH_WINDOW_H
#include <file_data.h>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QRadioButton>
#include<QTableView>
#include<QTableWidget>

#include <QFile>
#include "gist.h"
#include "list.h"

class search_window:public QWidget
{
public:
    search_window(QWidget *parent = nullptr);
private:
    QFile file;
    int choose;
    list *teams;
    struct data_qstring read_data;
    struct data non_transform_data;


    //output
    QLineEdit *str_line;
    QLineEdit *int_line;

    //table
    QTableWidget *output_table;
    QTableWidgetItem *item_of_the_table;
    int row_count, column_count;


    //Radio buttons box
    QRadioButton *team_show_radio;
    QRadioButton *more_or_equal_show_radio;
    QRadioButton *equal_show_radio;
    QRadioButton *place_show_radio;

    //buttons
    QPushButton *search_button;
    QPushButton *exit_button;

    //layouts
    QHBoxLayout *horizontal_layout_for_buttons;
    QHBoxLayout *horizontal_layout_for_radio_and_buttons;
    QVBoxLayout *vertical_layout;
    QVBoxLayout *vertical_layout_for_buttons_in_box;
    QVBoxLayout *vertical_layout_for_input;

    //Gistogramma
    list *places;
    class gist gistogramm;
    void set_gistogramm();


    //functions
    void start_set();
    void set_radio();
    void output_set();
    void buttons_set();
    void input_set();
    void create_layouts();

    void what_to_search();
    void change_line(int id);

    void search_for_equals();
    void search_for_equals_and_more();
    void search_for_team();
    void search_for_place();

    void add_to_table();
    void table_refresh();
    void add_to_table_more_or_equals();

    void add_to_list(list **list_to_do,QString string);
    void delete_list(list ** list_to_delete);
};


#endif // SEARCH_WINDOW_H
