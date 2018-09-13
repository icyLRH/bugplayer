#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include <QString>
#include <QRegExp>
#include "namepassworddata.h"

namespace Ui {
class SignUpDialog;
}

class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = 0);
    ~SignUpDialog();


    void getinfo();
    void initialize();

    QString name() const;
    void setName(const QString &name);

    QString password() const;
    void setPassword(const QString &password);

    void animation();
signals:
    void returnValues(QString name, QString password);

private slots:
    void on_signupButton_clicked();
    void on_backButton_clicked();
    bool checkusername();
    bool checkpassword();
    bool confirmpwd();

private:
    Ui::SignUpDialog *ui;
    QString m_name;
    QString m_password;
    NamePasswordData m_npdata;
    QRegExp rxname;
    QRegExp rxpass;

};

#endif // SIGNUPDIALOG_H
