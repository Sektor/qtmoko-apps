#ifndef SETUPDLG_H
#define SETUPDLG_H

#include <QDialog>


class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
class QSettings;

class SetupDlg: public QDialog
{
    Q_OBJECT
    public:
        SetupDlg(QWidget *parent = 0, Qt::WindowFlags f = 0);
        ~SetupDlg();
    private:
        QLabel      *tempTypeLbl;
        QLabel      *cityCodeLbl;
	QLabel	    *runType;
        QLineEdit   *cityCode;
        QComboBox   *tempCB;
	QComboBox   *runTypeCB;
        QSettings   *settings;
        QPushButton *saveBtn;
        QPushButton *cancelBtn;
        QPushButton *helpBtn;
    private slots:
        void btnSaveClick();
        void btnHelpClick();
};

#endif // SETUPDLG_H
