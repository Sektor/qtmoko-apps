#include "mainwindow.h"
#include "setupdlg.h"
#include "qweather.h"
#include <QPushButton>
#include <QLabel>
#include <QPicture>
#include <QHBoxLayout>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QSoftMenuBar>
//#include <QMenuBar>
#include <QDebug>
#include <QHBoxLayout>



MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
        : QWidget(parent, flags)
//MainWindow::MainWindow(QMainWindow *parent, Qt::WFlags flags)
//    : QMainWindow(parent, flags)
{
    setWindowIcon(QIcon("img/main.png"));
    weatherInfo = new YWeatherInfo();
    we = new QWeather;
    setWindowTitle(tr("Weather from Yahoo!"));
    createActions();
    createMenu();
    weatherInfo->show();
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(weatherInfo);
     
    refresh();
}


MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    exitAction = new QAction(tr("Exit"), this);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    aboutAction = new QAction(tr("About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    aboutQtAction = new QAction(tr("About Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered()), this, SLOT(aboutQt()));
    settingsAction = new QAction(tr("Settings"), this);
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(settings()));
    refreshAction = new QAction(tr("Refresh"), this);
    connect(refreshAction, SIGNAL(triggered()), this, SLOT(refresh()));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"), tr("<b>Author:</b> trollsid<br>"\
                                                              "<b>Email:</b><a href=\"trollsid@gmail.com\">Email</a>"));
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::settings()
{
    SetupDlg *setDlg = new SetupDlg;
    setDlg->exec();
}

void MainWindow::createMenu()
{
    mainMenu = QSoftMenuBar::menuFor(this);
//    mainMenu = QMainWindow::menuBar()->addMenu(tr("Main"));
    mainMenu->addAction(refreshAction);
    mainMenu->addAction(settingsAction);
    mainMenu->addAction(aboutAction);
    mainMenu->addAction(aboutQtAction);
    mainMenu->addAction(exitAction);
}

void MainWindow::refresh()
{

    we->exec();
    weather = we->getToday();
    if(!weather.isEmpty())
    {
        weatherInfo->getInfo(weather);
    }
}
