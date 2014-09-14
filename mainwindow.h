#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <QDate>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int day, month, year;

    QAction *quitAction;
    QAction *recoverAction;
    QAction *aboutAction;

    QSpinBox *yearBox;
    QSpinBox *monthBox;
    QSpinBox *dayBox ;

    QDate nowDate, targetDate;
    void count();
    int days;
    QLabel result;

private slots:
    void recover();
    void about();
    void setYear(int y);
    void setMonth(int m);
    void setDay(int d);
};


#endif // MAINWINDOW_H
