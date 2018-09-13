#include "signupdialog.h"
#include "ui_signupdialog.h"

#include <QMessageBox>
#include <QDebug>
#include <QRegExp>
#include <QPropertyAnimation>
#include <QBitmap>


SignUpDialog::SignUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

    ui->setupUi(this);
    this->setFixedSize(415,267);
    this->setMask(QPixmap(":/image/src/skin/checkAndSign.png").mask());
    this->setWindowTitle("注册");
    this->initialize();
    ui->usernameLineEdit->setFocus();

    setStyleSheet("QDialog{background-color: rgb(255,255,255);}");

    //set lineedits
    ui->usernameLineEdit->setStyleSheet(
                "QLineEdit{border-radius:9px;background:rgb(192,192,192);height:25px;}"
                "QLineEdit::hover{background:rgb(224,224,224);}"
                "QLineEdit::focus{background:rgb(255,255,255);}");
    ui->passwordLineEdit->setStyleSheet(
                "QLineEdit{border-radius:9px;background:rgb(192,192,192);height:25px;}"
                "QLineEdit::hover{background:rgb(224,224,224);}"
                "QLineEdit::focus{background:rgb(255,255,255);}");
    ui->pwdconfirmLineEdit->setStyleSheet(
                "QLineEdit{border-radius:9px;background:rgb(192,192,192);height:25px;}"
                "QLineEdit::hover{background:rgb(224,224,224);}"
                "QLineEdit::focus{background:rgb(255,255,255);}");

    //set buttons
    ui->signupButton->setStyleSheet(
                "QPushButton{border-radius:9px;background:rgb(55,175,255);height:30px;}"
                "QPushButton::hover{background:rgb(134,219,255);}"
                "QPushButton::pressed{background-color:rgb(54,143,203);}");
    ui->backButton->setStyleSheet(
                "QPushButton{border-radius:9px;background:rgb(55,175,255);height:30px;}"
                "QPushButton::hover{background:rgb(134,219,255);}"
                "QPushButton::pressed{background-color:rgb(54,143,203);}");

    connect(ui->pwdconfirmLineEdit, SIGNAL(returnPressed()), ui->signupButton, SIGNAL(clicked()), Qt::UniqueConnection);

}


SignUpDialog::~SignUpDialog()
{
    delete ui;
}

/*
 * Function Name: checkusername.
 * Description: check whether the user name format is right.
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: bool
 * Author: Icy
*/
bool SignUpDialog::checkusername()
{
    QString username = ui->usernameLineEdit->text();
    if(username.isEmpty())
    {
        ui->namemindLbl->setText("Username cannot be empty!");
        ui->namemindLbl->setStyleSheet("color: rgb(255, 78, 25);");
        return false;
    }
    else
    {
        ui->namemindLbl->setText("");
        if(rxname.exactMatch(username))
        {
            if (m_npdata.isin(username))
            {
                ui->namemindLbl->setText("The username format is Right");
                ui->namemindLbl->setStyleSheet("color: rgb(66, 200, 52);");
                return true;
            }
            else
            {
                ui->namemindLbl->setText("The username has already been used.");
                ui->namemindLbl->setStyleSheet("color: rgb(255, 78, 25);");
                return false;
            }
        }
        else
        {
            ui->namemindLbl->setText("Sorry,The username format is wrong!");
            ui->namemindLbl->setStyleSheet("color: rgb(255, 78, 25);");
            return false;
        }
    }
}

/*
 * Function Name: checkpassword.
 * Description: check whether the password format is right.
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: bool
 * Author: Icy
*/
bool SignUpDialog::checkpassword()
{
    QString pwd = ui->passwordLineEdit->text();
    if(pwd.isEmpty())
    {
        ui->pswmindLbl->setText("Password cannot be empty!");
        ui->pswmindLbl->setStyleSheet("color: rgb(255, 78, 25);");;
        return false;
    }
    else
    {
        ui->pswmindLbl->setText("");
        if(rxpass.exactMatch(pwd))
        {
            ui->pswmindLbl->setText("The password format is Right");
            ui->pswmindLbl->setStyleSheet("color: rgb(66, 200, 52);");
            return true;
        }
        else
        {
            ui->pswmindLbl->setText("Sorry,The password format is wrong!!");
            ui->pswmindLbl->setStyleSheet("color: rgb(255, 78, 25);");
            return false;
        }
    }
}

/*
 * Function Name: checkpassword.
 * Description: check whether the password confirm is consistent with password.
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: bool
 * Author: Icy
*/
bool SignUpDialog::confirmpwd()
{
    if (ui->pwdconfirmLineEdit->text() == ui->passwordLineEdit->text())
    {
        ui->pwdconmindLbl->setText("OK!");
        ui->pwdconmindLbl->setStyleSheet("color: rgb(66, 200, 52);");
        return true;
    }
    else
    {
        ui->pwdconmindLbl->setText("The passwords are not consistent.");
        ui->pwdconmindLbl->setStyleSheet("color: rgb(255, 78, 25);");
        return false;
    }
}

/*
 * Function Name: getinfo.
 * Description: get the information of two lineedits.
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Icy
*/
void SignUpDialog::getinfo()
{
    m_name = ui->usernameLineEdit->text();
    m_password = ui->passwordLineEdit->text();
}

/*
 * Function Name: initialize.
 * Description: initialize the dialog.
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Icy
*/
void SignUpDialog::initialize()
{
    //the username can only be "以字母开头由数字和26个英文字母组成的字符串"
    rxname.setPattern(QString("^[a-zA-Z][a-zA-Z0-9_]*$"));
    //the password can only be "以字母开头，长度在6~18之间，只能包含字符、数字和下划线"
    rxpass.setPattern(QString("^[a-zA-Z]\\w{5,17}$"));

    //set connection
    connect(ui->usernameLineEdit,SIGNAL(textEdited(QString)),this,SLOT(checkusername()));
    connect(ui->passwordLineEdit,SIGNAL(textEdited(QString)),this,SLOT(checkpassword()));
    connect(ui->pwdconfirmLineEdit,SIGNAL(textEdited(QString)),this,SLOT(confirmpwd()));
}

/*
 * Function Name: on_signupButton_clicked.
 * Description: check whether the infomation is right and give respond.
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Icy
*/
void SignUpDialog::on_signupButton_clicked()
{
    getinfo();
    qDebug()<<checkpassword();
    qDebug()<<checkusername();
    qDebug()<<confirmpwd();
    if (checkpassword() && checkusername() && confirmpwd())
    {
        m_npdata.insertinfo(m_name,m_password);
        animation();

        emit returnValues(m_name,m_password);
    }
    else
    {}
}

/*
 * Function Name: animation.
 * Description: the animation when switching .
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Icy
*/
void SignUpDialog::animation()
{

    QLabel *label = new QLabel (parentWidget());
    label->resize(size());
    label->setPixmap(grab());
    label->show();

    //Attention:geometry is a relatively value
    QPropertyAnimation *animation = new QPropertyAnimation(label,"geometry");
    animation->setDuration(300);
    animation->setStartValue(QRect(0,0,width(),height()));
    QRect RectEnd = QRect(-width(),0,width(),height());
    animation->setEndValue(RectEnd);

    //Attention:order
    hide();
    parentWidget()->show();
    animation->start();
    connect(animation,&QPropertyAnimation::finished,this,&SignUpDialog::hide);
}

QString SignUpDialog::password() const
{
    return m_password;
}

void SignUpDialog::setPassword(const QString &password)
{
    m_password = password;
}

QString SignUpDialog::name() const
{
    return m_name;
}

void SignUpDialog::setName(const QString &name)
{
    m_name = name;
}

void SignUpDialog::on_backButton_clicked()
{
    animation();
}
