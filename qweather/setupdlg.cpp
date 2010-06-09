#include "setupdlg.h"
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSettings>
#include <QMenu>
#include <QAction>
#include <QDebug>


SetupDlg::SetupDlg(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    tempTypeLbl = new QLabel(tr("Temperature type:"));
    cityCodeLbl = new QLabel(tr("City code:"));
    cityCode = new QLineEdit;
    tempCB = new QComboBox;
    tempCB->addItem(tr("Fahrenheit"), "f");
    tempCB->addItem(tr("Celsius"), "c");
    saveBtn = new QPushButton(tr("Save"));
    cancelBtn = new QPushButton(tr("Cancel"));
    settings = new QSettings("TQWeather", "YahooWeather");
    cityCode->setText(settings->value("City", "MGXX0003").toString());
    int selectedItem = tempCB->findData(settings->value("TempType", "c").toString());
    selectedItem > -1 ? tempCB->setCurrentIndex(selectedItem) : tempCB->setCurrentIndex(0);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(cityCodeLbl);
    layout->addWidget(cityCode);
    layout->addWidget(tempTypeLbl);
    layout->addWidget(tempCB);
    layout->addStretch();
    layout->addWidget(saveBtn);
    layout->addWidget(cancelBtn);
    setLayout(layout);
    setWindowIcon(QIcon("img/settings.png"));
    setWindowTitle(tr("Weather Settings"));
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(btnSaveClick()));
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
}

SetupDlg::~SetupDlg()
{
}

void SetupDlg::btnSaveClick()
{
    settings->setValue("City", cityCode->text());
    QString type = tempCB->itemData(tempCB->currentIndex()).toString();
    qDebug() << "Temp type" << type;
    settings->setValue("TempType", type);
    this->close();
}



