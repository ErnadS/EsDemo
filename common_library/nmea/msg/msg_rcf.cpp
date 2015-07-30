#include "msg_rcf.h"
#include "nmea/nmea_parser.h"

MsgRCF::MsgRCF()
{
    this->m_message_type_hash   = MsgRCF::RCFhash;
    this->m_message_type        = TYPE_RCF;
}

MsgRCF::MsgRCF(quint8 systemType, QString systemName, QString serialNo, QString ip, QString mac,
    QString sfi, QString destSfi, QString firmwareVer, quint8 group, QString dl2_serNo, QString dl2_firmwVer)

{
    this->m_message_type_hash   = MsgRCF::RCFhash;
    this->m_message_type        = TYPE_RCF;

    this->systemType    = systemType;
    this->systemName    = systemName;
    this->serialNo      = serialNo;
    this->ip            = ip;
    this->mac           = mac;


    this->sfi           = sfi;
    this->destSfi       = destSfi;
    this->firmwareVer   = firmwareVer;

    this->group = group;
    this->dl2_serNo = dl2_serNo;            // !!! Not used on display (sensor is not connected to the display)
    this->dl2_firmwVer = dl2_firmwVer;      // !!! Not used on display (sensor is not connected to the display)
}

// Not used (only in service software)
bool MsgRCF::setParams(QStringList)
{
    return false;
}

QString MsgRCF::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;

    QString ipCommaSepar = ip.replace(".", ",");
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_RCF) + "," + NmeaParser::NumberToString(systemType) + "," +
            systemName  + "," + serialNo +  "," + ipCommaSepar + "," + mac + "," +
            sfi + "," + destSfi + "," + firmwareVer + "," + NmeaParser::NumberToString(group) + "," + dl2_serNo +  "," + dl2_firmwVer;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
