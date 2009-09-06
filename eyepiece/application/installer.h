#ifndef INSTALLER_H
#define INSTALLER_H

#include <QDialog>
#include <QLabel>

class Installer : public QDialog
{
    Q_OBJECT
    private:
        QLabel *infoLabel;
        QLabel *titleLabel;
    public:
        Installer(QWidget *);
        void start();
};

#endif
