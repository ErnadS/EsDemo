#include "nmea_message.h"

int NmeaMessage::number_of_decimals() const
{
    return m_number_of_decimals;
}

void NmeaMessage::setNumber_of_decimals(int number_of_decimals)
{
    m_message = "";
    m_number_of_decimals = number_of_decimals;
}

bool NmeaMessage::propriatary() const
{
    return m_proprietary;
}

void NmeaMessage::setPropriatary(bool propriatary)
{
    m_proprietary = propriatary;
}
NmeaMessage::NmeaMessage()
{
    m_error_id = NmeaMessageErrorType::NO_NMEA_ERROR;
    m_number_of_decimals = 1;
}

NmeaMessage::~NmeaMessage()
{
    
}

void NmeaMessage::setMsgInfo(QString m_talker_id, QString m_manufacturer_id, QString crc, QString m_messageString, bool m_propriatary) {
    this->m_talker_id = m_talker_id;
    this->m_manufacturer_id = m_manufacturer_id;
    this->m_proprietary = m_propriatary;
    this->m_checksum = crc;
    this->m_message = m_messageString;
}

QString NmeaMessage::talkerId() const
{
    return m_talker_id;
}

QString NmeaMessage::manufacturerId() const
{
    return m_manufacturer_id;
}

QString NmeaMessage::messageType() const
{
    return m_message_type;
}

bool NmeaMessage::isPropriatary() const
{
    return m_proprietary;
}

NmeaMessageErrorType NmeaMessage::errorType() const
{
    return m_error_id;
}

QString NmeaMessage::checksum() const
{
    return m_checksum;
}

unsigned long NmeaMessage::messageTypeHash() const
{
    return m_message_type_hash;
}

QString NmeaMessage::addCrcToMsgBuffer(QString body)
{
    return ( QString("$") +body + QString("*") + CRC8::calculateChecksum(body) + QString("\r\n"));
}
