#include "gui/widget/validator.h"
#include <QMessageBox>
#include <QDebug>

void Validator::displayError(QString error_message) const
{
    QMessageBox message_box(QMessageBox::Critical,
                            "",
                            error_message,
                            QMessageBox::Ok, 0,
                            Qt::FramelessWindowHint);

    // TODO: Generalize style through controller class
    message_box.setStyleSheet("QPushButton { color: rgb(255, 255, 255); background-color: rgb(20, 20, 20); font: 16px; min-width: 230px; min-height: 40px;} QMessageBox { background-color: black; border: 2px solid rgb(80, 80, 80);} QLabel { color: rgb(255, 255, 255); font: 16px; text-align: justify; }");

    message_box.exec();
}

Validator::Validator(const QString& validation_message) : m_validation_message(validation_message)
{

}

bool Validator::validate(const QString&) const
{
    displayError(m_validation_message);

    return true;
}

RegexValidator::RegexValidator(const QString& regex, const QString& validation_message) : Validator(validation_message), m_regex(regex)
{

}
bool RegexValidator::validate(const QString& regex) const
{
    QRegExp validation(m_regex);
    if(!validation.exactMatch(regex))
            {
                displayError(m_validation_message);
                return false;
            }
    else return true;

}

IntValidator::IntValidator(int min, int max, const QString& validation_message) : Validator(validation_message), m_min(min), m_max(max)
{

}

bool IntValidator::validate(const QString& value) const
{
    bool ok;
    int int_value = value.toInt(&ok);

    if ((ok == false) || (int_value < m_min) || (int_value > m_max))
    {
        displayError(m_validation_message.arg(m_min).arg(m_max));
        return false;
    }

    return true;
}

FloatValidator::FloatValidator(float min, float max, const QString& validation_message) : Validator(validation_message), m_min(min), m_max(max)
{

}

bool FloatValidator::validate(const QString &value) const
{
    bool ok;
    float int_value = value.toFloat(&ok);

    if ((ok == false) || (int_value < m_min) || (int_value > m_max))
    {
        displayError(m_validation_message.arg(m_min).arg(m_max));
        return false;
    }

    return true;
}

IpValidator::IpValidator(const QString& validation_message) : Validator(validation_message)
{

}

bool IpValidator::validate(const QString &value) const
{

    if (value.split(".").size() != 4)
        return false;


    int ip_byte_3 = (value.split(".")[0]).toInt();
    int ip_byte_2 = (value.split(".")[1]).toInt();
    int ip_byte_0 = (value.split(".")[3]).toInt();


    qDebug()<<"ip byte 0"<<ip_byte_0<<" ip byte 2  "<<ip_byte_2<<" ip byte 3  "<<ip_byte_3;
    if ((ip_byte_3 == 172) && (ip_byte_2 >= 16) && (ip_byte_2 <= 31) && (ip_byte_0 >= 1) && (ip_byte_0 <= 254))
    {
        return true;
    }

    displayError(m_validation_message);
    return false;

}
