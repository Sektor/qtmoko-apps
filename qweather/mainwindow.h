#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
//#include <QMainWindow>
#include "weatherinfowidget.h"

class QPushButton;
class QLabel;
class QPicture;
class QGridLayout;
class QAction;
class QMenu;
class QRect;
class QWeather;

class MainWindow : public //QMainWindow
        QWidget
{
    Q_OBJECT
    public:
//        MainWindow(QMainWindow *parent = 0, Qt::WFlags flags = Qt::Window);
        MainWindow(QWidget *parent = 0, Qt::WFlags flags = Qt::Window);
        virtual ~MainWindow();
    private:
        QAction *refreshAction;
        QAction *exitAction;
        QAction *aboutAction;
        QAction *settingsAction;
        QAction *aboutQtAction;
        QMenu   *mainMenu;
        QMenu   *menu;
        QWeather *we;
        YWeatherInfo *weatherInfo;
        QStringList   weather;
        void createActions();
        void createMenu();
    private slots:
        void about();
        void aboutQt();
        void settings();
        void refresh();
};

#endif // MAINWINDOW_H
