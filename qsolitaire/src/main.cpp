/*
 * Copyright (c) 2009 Nokia Corporation.
 */

// INCLUDE FILES
#include <QApplication>
#include "TableauWidget.h"

int main(int argc, char *argv[])
    {
    int ret(0);

    QApplication app(argc, argv);

    // Create widget into heap
    TableauWidget *tableauWidget = new TableauWidget;

    app.setActiveWindow(tableauWidget);

    #if defined(Q_OS_WIN32)
    tableauWidget->setFixedSize(640,320);
    tableauWidget->show();
    #elif defined(Q_OS_SYMBIAN)
    tableauWidget->showFullScreen();
    #else
    tableauWidget->showMaximized();
    #endif

    ret = app.exec();
    delete tableauWidget;

    return ret;
    }

// End of file
