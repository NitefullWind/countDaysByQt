#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolBar>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialog>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //今日
    nowDate = QDate::currentDate();

    //窗口
    ui->setupUi(this);
    setWindowTitle(tr("计算天数"));

    QToolBar *toolbar = addToolBar(tr("toolbar"));
    recoverAction = new QAction(QIcon(":icon/recover"),tr("恢复"),this);
    recoverAction->setStatusTip(tr("恢复至今日"));
    connect(recoverAction,SIGNAL(triggered()),this,SLOT(recover()));
    toolbar->addAction(recoverAction);
    aboutAction = new QAction(QIcon(":icon/about"),tr("关于"),this);
    aboutAction->setStatusTip(tr("查看程序与作者介绍"));
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(about()));
    toolbar->addAction(aboutAction);
    quitAction = new QAction(QIcon(":icon/quit"),tr("退出"),this);
    quitAction->setStatusTip(tr("退出应用程序"));
    connect(quitAction,&QAction::triggered,&QApplication::quit);
    toolbar->addAction(quitAction);

    QLabel *nowDateLabel = new QLabel(QString(tr("今天：%1").arg(nowDate.toString("yyyy-MM-dd ddd"))));
    QLabel *targetDateLabel = new QLabel(tr("目标日期："));

    yearBox = new QSpinBox();
    yearBox->setRange(-10000,10000);
    monthBox = new QSpinBox();
    monthBox->setRange(1,12);
    dayBox = new QSpinBox();

    QLabel *yearLabel = new QLabel(tr("年"));
    QLabel *monthLabel = new QLabel(tr("月"));
    QLabel *dayLabel = new QLabel(tr("日"));

    QHBoxLayout *HLayout1 = new QHBoxLayout();
    HLayout1->addWidget(targetDateLabel);
    HLayout1->addWidget(yearBox);
    HLayout1->addWidget(yearLabel);
    HLayout1->addWidget(monthBox);
    HLayout1->addWidget(monthLabel);
    HLayout1->addWidget(dayBox);
    HLayout1->addWidget(dayLabel);

    QHBoxLayout *HLayout2 = new QHBoxLayout();
    HLayout2->addWidget(&result);

    QVBoxLayout *VLayout = new QVBoxLayout();
    VLayout->addWidget(nowDateLabel);
    VLayout->addLayout(HLayout1);
    VLayout->addLayout(HLayout2);

    QWidget *widget = new QWidget();
    widget->setLayout(VLayout);
    setCentralWidget(widget);

    //初始化
    connect(yearBox,SIGNAL(valueChanged(int)),this,SLOT(setYear(int)));
    connect(monthBox,SIGNAL(valueChanged(int)),this,SLOT(setMonth(int)));
    connect(dayBox,SIGNAL(valueChanged(int)),this,SLOT(setDay(int)));

    yearBox->setValue(nowDate.year());
    monthBox->setValue(nowDate.month());
    dayBox->setValue(nowDate.day());
}

void MainWindow::count()
{
    //范围设定
    if(month==2)
    {
        if((year%4 == 0 && year%100 != 0) || ( year%400 == 0))
            dayBox->setRange(1,29);
        else
            dayBox->setRange(1,28);
    }
    else if(month==4||month==6||month==9||month==11)
            dayBox->setRange(1,30);
    else
        dayBox->setRange(1,31);

    //计算
    targetDate.setDate(year,month,day);
    days = targetDate.daysTo(nowDate);
    if(days >= 0)
        result.setText(QString(tr("目标日期与今日相差： %1 天").arg(days)));
    else
        result.setText(QString(tr("今日与目标日期相差： %1 天").arg(-days)));
}

void MainWindow::setYear(int y)
{
    year = y;
    count();
}

void MainWindow::setMonth(int m)
{
    month = m;
    count();
}

void MainWindow::setDay(int d)
{
    day = d;
    count();
}

void MainWindow::recover()
{
    yearBox->setValue(nowDate.year());
    monthBox->setValue(nowDate.month());
    dayBox->setValue(nowDate.day());
}

void MainWindow::about()
{
    QDialog *aboutWindow = new QDialog;
    aboutWindow->setWindowTitle(tr("关于 计算天数"));
    QLabel *information = new QLabel(tr("<h4>程序名：计算天数<br>功能：计算目标日期与今日相隔的天数<br>作者：默雨暮风<br>邮箱：<a href=1181566496@qq.com>1181566496@qq.com</a></h4>"));
    QHBoxLayout *aboutLayout = new QHBoxLayout;
    aboutLayout->addWidget(information);
    QPushButton *close = new QPushButton(tr("关闭"));
    connect(close,&QPushButton::clicked,aboutWindow,&QDialog::close);
    QVBoxLayout *Vlayout = new QVBoxLayout();
    Vlayout->addLayout(aboutLayout);
    Vlayout->addWidget(close);
    aboutWindow->setLayout(Vlayout);
    aboutWindow->exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
