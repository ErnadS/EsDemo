#include "serialreader.h"
#include "nmea/nmea_parser.h"

#include <QDebug>
#include <cstring>
#include <QElapsedTimer>


bool SerialReader::getWaitForAck() const
{
    return waitForMute;
}

void SerialReader::setWaitForAck(bool value)
{
    waitForMute = value;
}

bool SerialReader::getMuteOn() const
{
    return muteOn;
}

void SerialReader::setMuteOn(bool value)
{
    muteOn = value;
}
SerialReader::SerialReader()
{
    bReceivingEnabled = false;
    waitForMute = false;
    muteOn = false;
    m_sensor_port = false;
}


bool SerialReader::validateBaudRate(int nBaudRate) {
    if (nBaudRate != 4800 && nBaudRate != 38400 && nBaudRate != 115200)
        return false;
    return true;
}

void SerialReader::enableReceiving(bool bEnable) {
    bReceivingEnabled = bEnable;
}


// Look at SerialReader.h for possible arguments "nUartPort"
bool SerialReader::init(const char* uartPort, int nBaudRate) {
    if (!validateBaudRate(nBaudRate))
        return false;

    if (strcmp(uartPort, USART_SENSOR) == 0)
    {
        m_sensor_port = true;
    }

    BaudRateType baud = (BaudRateType)nBaudRate;
    sprintf(uartDevicePath, "/dev/%s", uartPort);  // "/dev/pts/%s"
    port = new QextSerialPort(uartDevicePath);

    port->setBaudRate(baud);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);

    bool result;
    result = port->open(QIODevice::ReadWrite);

    if (result == true)
    {
        QObject::connect(port, SIGNAL(readyRead()), this, SLOT(readNmeaPacket()));

        qDebug() << "Opened port for reading: " << uartDevicePath;
        return true;
    }
    else
    {
        qDebug() << "Error opening port: " << uartDevicePath;
        return false;
    }
}

void SerialReader::close() {
    try {
        port->close();
        qDebug() << "Closed port " << uartDevicePath;
    } catch (int e){
         qDebug() << "Error closing port " << uartDevicePath << " . Exception: " << e;
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Used for reading of known number of bytes. It will wait until nCount bytes has been received or timeout (nMaxTime).
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QByteArray SerialReader::readAvaiable(int nCount, int nMaxTime) {
    QElapsedTimer timer;
    timer.start();

    while (port->bytesAvailable() < nCount) {
        if (timer.elapsed() > nMaxTime)
            break;
    }
    int nAvaiable = port->bytesAvailable();
    if (nAvaiable > nCount)
        nAvaiable = nCount;

    char buff[1000 ]; //nAvaiable];

    port->read(buff, nAvaiable);

    return buff;
}

void SerialReader::discast() {
    if (port->bytesAvailable() > 0)
        port->readAll(); // read but not use it
}

int SerialReader::sendMessage(QString msg) {
    // Logger& logger = Logger::instance();

    if (m_sensor_port == true)
    {
        // logger.append("Sent message to sensor: " + msg);
    }

    return port->write(msg.toLatin1(), msg.length());
}

int SerialReader::sendByteArray(QByteArray msg) {
    return port->write(msg, msg.length());
}
/*
// removing garbage
int SerialReader::getIndexOfStartChar(QString qstrBuffer) {
    int index = qstrBuffer.indexOf('$');
    // int index2 = qstrBuffer.indexOf('!');
    return index; // return minimum of index and index2
}*/

void SerialReader::readNmeaPacket() {
    QByteArray data = port->readAll();
  /*  if(waitForMute)
    {
        for (int i = 0; i < data.length(); i++)
        {
            if(!muteOn)
            {
                if(data[i] == (char)0x13)   // ACK on Mute command (DL2 sensor)
                {
                    emit sigSynchConfirmed(true);
                    waitForMute =false;
                    muteOn = true;
                    return;
                }
            }
            else
            {
                if(data[i] == (char)0x11)   // ACK on Un Mute command (DL2 sensor)
                {
                    emit sigSynchConfirmed(false);
                    waitForMute =false;
                    muteOn = false;
                    return;
                }
            }
        }
    }

   //  Logger& logger = Logger::instance();

    buffer.append(QString::fromAscii(data));
    int nStartInd = buffer.indexOf("$");
    if (nStartInd > 0)
    {
        if (m_sensor_port == true)
        {
            // logger.append("Rejected message from sensor: " + buffer.left(nStartInd), LOG_ERROR);
        }

        buffer = buffer.mid(nStartInd);
    }

    // qDebug() << buffer.toAscii();

    int index = buffer.indexOf("\n");
    while (index != -1)
    {
        QString message = buffer.mid(0, index + 1);

        buffer.remove(0, index + 1);

        NmeaMessage* nmeaMessage = NmeaParser::parse(message);
        //NmeaMessage nmeaMessage(message.toAscii().data());
        // message_buffer.enqueue(nmeaMessage);

        // Test
        if(nmeaMessage->error_ID != NO_ERROR)
        {
            qDebug()<<"Error NMEA:";
            qDebug()<<nmeaMessage->m_message;
            qDebug()<<"Error index: "<<QString(int(nmeaMessage->error_ID));

            if (m_sensor_port == true)
            {
                logger.appendNmeaError("Invalid message from sensor", nmeaMessage->m_message, nmeaMessage->error_ID);
                emit receivedInvalidDataFromSensor();
            }
        }

        if (nmeaMessage != NULL) {
            if (m_sensor_port == true)
            {
                logger.append("Received message from sensor: " + nmeaMessage->m_message);
                emit receivedValidDataFromSensor();
            }

            if (nmeaMessage->messageType() == "DAT")  {
                qDebug() << "REC DAT";
                SensorCommandsThread::setDatReceived();
                //emit sigReceivedDat();
            }


            if (bReceivingEnabled)
                emit receivedSerialNmea(nmeaMessage);
        }

        index = buffer.indexOf('\n');
    }*/
}
