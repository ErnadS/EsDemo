#include "msg_alc.h"
#include "nmea/nmea_parser.h"

// SINGLE
MsgSingleALC::MsgSingleALC(QString manufacturerMnemonicCode, int alertIdendtifyer, int alertInstance, int revisionCounter)
{
    this->manufacturerMnemonicCode      = manufacturerMnemonicCode;
    this->alertIdendtifyer              = alertIdendtifyer;
    this->alertInstance                 = alertInstance;
    this->revisionCounter               = revisionCounter;
}

QString MsgSingleALC::getEntryBuffer() {
    return manufacturerMnemonicCode + "," + QString::number(alertIdendtifyer) + "," + QString::number(alertInstance) +  "," + QString::number(revisionCounter);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// ALC
////////////////////////////////////////////////////////////////////////////////////////////////////
MsgALC::MsgALC()
{
    // TODO: FIX NMEA attribute
    //this->m_talker_id           = SystemConfiguration::getSourceTalker();
    this->m_message_type_hash   = MsgALC::ALChash;
    this->m_message_type        = TYPE_ALC;

    totalNumberOfSentences = 0;
}

void MsgALC::addSentence(const MsgSingleALC &sentence)
{
    totalNumberOfSentences ++;
    sentenceList.append(sentence);
}

QString MsgALC::getMsgBuffer()
{
    QString msg_body= QString(m_talker_id) + QString(TYPE_ALC) + "," +
            "1,1,0" +  // We probably can send all entry in the same message
            QString::number(totalNumberOfSentences);

    for (int i = 0; i < sentenceList.length(); i++)
        msg_body += "," + sentenceList[i].getEntryBuffer();

    return (this->addCrcToMsgBuffer(msg_body));
}

bool MsgALC::setParams(QStringList)
{
    return false;
}
