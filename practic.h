#ifndef PRACTIC_H
#define PRACTIC_H
#include <file_data.h>
#include <QWidget>

#include "search_window.h"
#include "delete_window.h"
#include "input_window.h"

#include <QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class Practic; }
QT_END_NAMESPACE

class Practic : public QWidget
{
    Q_OBJECT

public:
    Practic(QWidget *parent = nullptr);
    ~Practic();

private:   
    //windows
    input_window input_win;
    delete_window delete_win;
    search_window search_win;

    //variables
    int open_window;
    QFile file;

    //buttons
    QPushButton *input_button;
    QPushButton *search_button;
    QPushButton *delete_button;
    QPushButton *exit_button;

    //Layout
    QVBoxLayout *layout;
    QHBoxLayout *la;

    //func
    void set();
    void set_input_button();
    void set_search_button();
    void set_delete_button();
    void set_exit_button();
    void window_show(int id);
    void window_hide(int id);
    void window_close();

signals:
    void close_signal();
};

#endif // PRACTIC_H
