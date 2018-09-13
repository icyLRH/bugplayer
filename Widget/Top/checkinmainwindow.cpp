#include "checkinmainwindow.h"
#include "ui_checkinmainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QBitmap>


CheckinMainWindow::CheckinMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CheckinMainWindow),
    sign(new SignUpDialog (this)),
    m_user("guest"),
    m_infodata(new NamePasswordData (this))
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

    //Set the main window style
    this->setFixedSize(415,267);
    this->setMask(QPixmap(":/image/src/skin/checkAndSign.png").mask());
    this->setWindowTitle("登陆");

    setStyleSheet("QMainWindow{background-color: rgb(255,255,255);}");

    //Set control styles
    ui->userEdit->setFocus();
    ui->userEdit->setStyleSheet(
                "QLineEdit{border-radius:5px;background:rgb(192,192,192);height:20px;}"
                "QLineEdit::hover{background:rgb(224,224,224);}"
                "QLineEdit::focus{background:rgb(255,255,255);}");
    ui->passwordEdit->setStyleSheet(
                "QLineEdit{border-radius:5px;background:rgb(192,192,192);height:20px;}"
                "QLineEdit::hover{background:rgb(224,224,224);}"
                "QLineEdit::focus{background:rgb(255,255,255);}");
    ui->loginBtn->setStyleSheet(
                "QPushButton{border-radius:5px;background:rgb(55,175,255);height:30px;}"
                "QPushButton::hover{background:rgb(134,219,255);}"
                "QPushButton::pressed{background-color:rgb(54,143,203);}");
    ui->signupBtn->setStyleSheet(
                "QPushButton{border-radius:5px;background:rgb(55,175,255);height:30px;}"
                "QPushButton::hover{background:rgb(134,219,255);}"
                "QPushButton::pressed{background-color:rgb(54,143,203);}");

    ui->label_2->setStyleSheet(
                "QLabel{font-size:25px;color:black;font-weight:bold;}");

    ui->label_3->setStyleSheet(
                "QLabel{font-size:12px;color:gray;}");


    //Enter = log in
    connect(ui->passwordEdit, SIGNAL(returnPressed()), ui->loginBtn, SIGNAL(clicked()), Qt::UniqueConnection);

    //Status display
    connect(m_infodata,&NamePasswordData::message,ui->label_4,&QLabel::setText);

}

CheckinMainWindow::~CheckinMainWindow()
{
    delete ui;
}

/*
 * Function Name: on_loginBtn_clicked.
 * Description: estimate wheather the username and password are right, then give corresponding responds.
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Icy
*/
void CheckinMainWindow::on_loginBtn_clicked()
{
    QString user = ui->userEdit->text();
    QString password = ui->passwordEdit->text();
    bool checking = m_infodata->checkUser(user,password);
    if (checking == true)
    {
        m_user = user;
        m_password = password;
        qDebug()<<"登陆成功";
        isloggedin = true;
        emit login();
        this->close();
    }
    else
    {}
}

/*
 * Function Name: getValues.
 * Description: set LineEdits values.
 * Created: 18/09/09
 * Parameter: name QString
 *            password QString
 * Return Code: VOID
 * Author: Icy
*/
void CheckinMainWindow::getValues(QString name, QString password)
{
    ui->userEdit->setText(name);
    ui->passwordEdit->setText(password);
    ui->passwordEdit->setFocus();
}

/*
 * Function Name: events.
 * Description: close the window when clicked outside.
 * Created: 18/09/09
 * Parameter: event QEvent
 * Return Code: VOID
 * Author: Icy
*/
bool CheckinMainWindow::event(QEvent *event)
{
    if(event->type() == QEvent::ActivationChange)
    {
        if(QApplication::activeWindow()!= this)
        {
            this->hide();
        }
    }
    return QMainWindow::event(event);
}


QString CheckinMainWindow::User() const
{
    return m_user;
}

void CheckinMainWindow::setUser(const QString &user)
{
    m_user = user;
}

/*
 * Function Name: on_signupBtn_clicked.
 * Description: connect two values of LineEdits, trigger animation.
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Icy
*/
void CheckinMainWindow::on_signupBtn_clicked()
{
    connect(sign,&SignUpDialog::returnValues,this,&CheckinMainWindow::getValues);

    animation();
}

/*
 * Function Name: animation.
 * Description: set the animation of switching between windows.
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Icy
*/
void CheckinMainWindow::animation()
{

    sign->move(this->pos());

    QLabel *label = new QLabel (sign);
    label->resize(size());
    label->setPixmap(grab());
    label->show();

    //Attention: geometry is a relative value
    QPropertyAnimation *animation = new QPropertyAnimation(label,"geometry");
    animation->setDuration(300);
    animation->setStartValue(QRect(0,0,width(),height()));
    QRect RectEnd = QRect(-width(),0,width(),height());
    animation->setEndValue(RectEnd);

    //Attention to the order
    sign->show();
    animation->start();
    connect(animation,&QPropertyAnimation::finished,this,&CheckinMainWindow::hide);

}

