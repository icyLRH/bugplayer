#ifndef CHECKINMAINWINDOW_H
#define CHECKINMAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "namepassworddata.h"
#include "signupdialog.h"
namespace Ui {
class CheckinMainWindow;
}

class CheckinMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CheckinMainWindow(QWidget *parent = 0);
    ~CheckinMainWindow();
    bool isloggedin = false;

    QString User() const;
    void setUser(const QString &user);

    void animation();

    SignUpDialog* sign;

signals:
    void login();

private slots:
    void on_loginBtn_clicked();
    void on_signupBtn_clicked();
    void getValues(QString name, QString password);

private:
    Ui::CheckinMainWindow *ui;
    QString m_user;
    QString m_password;
    //Link to the NamePasswordData database
    NamePasswordData *m_infodata;

protected:
    bool event(QEvent *event);

};

#endif // CHECKINMAINWINDOW_H
