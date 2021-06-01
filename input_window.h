#ifndef INPUT_WINDOW_H
#define INPUT_WINDOW_H
#include <file_data.h>

#include <QWidget>

#include <QPushButton>
#include <QLabel>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>
#include <QFile>


class input_window: public QWidget
{
    Q_OBJECT
public:
    input_window(QWidget *parent = nullptr);
    ~input_window();
private:
    struct data data_to_work;
    QFile file;

    //labels
    QLabel *label_place;
    QLabel *label_teams;
    QLabel *label_scores;

    //lines
    QLineEdit * line_place;
    QLineEdit * line_team_1;
    QLineEdit * line_team_2;
    QLineEdit * line_score_1;
    QLineEdit * line_score_2;

    //buttons
    QPushButton *exit_button;
    QPushButton *input_button;

    //layouts
    QGridLayout *grid_layout;
    QVBoxLayout *vertical_layout;
    QHBoxLayout *horizontal_for_teams;
    QHBoxLayout *horizontal_for_scores;
    QHBoxLayout *horizontal_for_buttons;
    QHBoxLayout main_lay;

    //functions
    void create_labels();
    void create_lines();
    void create_layouts();
    void create_buttons();
    void set();

    void input_in_file();
};

#endif // INPUT_WINDOW_H
