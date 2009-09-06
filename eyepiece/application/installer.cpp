#include "installer.h"
#include <QProcess>
#include <QApplication>
#include <QGridLayout>

Installer::Installer(QWidget *parent) : QDialog(parent)
{
    //setWindowOpacity(0.90);
    setFixedSize(420,200);
    setModal(true);
    //setWindowTitle(tr("apt-get output"));
    infoLabel = new QLabel(this);    
    infoLabel->setText("");
    titleLabel = new QLabel(this);
    titleLabel->setText("<font color=\"#F88017\">Installation in progress<br/>Please wait for finish</font>");
    titleLabel->setAlignment(Qt::AlignCenter);

    QGridLayout *grid=new QGridLayout(this);
    grid->addWidget(titleLabel,0,0);
    grid->addWidget(infoLabel,1,0);

    setWindowFlags(Qt::FramelessWindowHint);
    //setWindowFlags(Qt::WindowTitleHint);
}

void Installer::start()
{
    QProcess script(this);
    script.start("apt-get -y install libdjvulibre21");
    while( !script.waitForFinished(500) ) {
        QString txt =  script.readAll().trimmed();
        if (txt != "")
            infoLabel->setText(txt);
        update();
        QApplication::processEvents();
    }
    close();
}
