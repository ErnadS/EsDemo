#ifndef SERIALREADER_H
#define SERIALREADER_H

// From Putty log (booting):
////////////////////////////////////////////////////////////////////////////////////////
// [    0.550000] ffffee00.serial: ttyS0 at MMIO 0xffffee00 (irq = 38) is a ATMEL_SERIAL
// [    0.540000] f001c000.serial: ttyS1 at MMIO 0xf001c000 (irq = 23) is a ATMEL_SERIAL
// [    0.540000] f0020000.serial: ttyS2 at MMIO 0xf0020000 (irq = 24) is a ATMEL_SERIAL
// [    0.550000] f8020000.serial: ttyS3 at MMIO 0xf8020000 (irq = 31) is a ATMEL_SERIAL
////////////////////////////////////////////////////////////////////////////////////////
// =====>
// ttyS0  =  dbg     (PB30, PB31)  // if default (R15 and R19 mounted), it's RS232
// ttyS1  =  USART0  (PD17, PD18)  // NMEA 1 IN/OUT (wrong on old schematic)
// ttyS2  =  USART1  (PB28, PB29)  // if R14 and R18 are mounted it's RS232
// ttyS3  =  USART2  (PE25, PE26)  // NMEA 2 IN (PE25). Not used PE26

#define USART_DBG       "ttyS0"  // PB30 and PB31, default as RS232 (R15 and R19)
#define USART_NMEA_1    "ttyS1"  // PD17, PD18
#define USART_NMEA_2    "ttyS2"  // PB28 and PB29, !!! Only usede if R14 and R18 are mounted (RS232)
#define USART_SENSOR    "ttyS3"  // NMEA 2 IN (PE25). Not used PE26


#include "qextserialport.h"
#include "nmea/nmea_message.h"
#include "cstdio"
#include <QDebug>
#include <QQueue>

class SerialReader : public QObject
{
    Q_OBJECT

    QextSerialPort *port;
    bool m_sensor_port;
    QString buffer;
    QQueue<NmeaMessage> message_buffer;
    bool lock;

    bool waitForMute;
    bool muteOn;

public:
    SerialReader();
    ~SerialReader()
    {
        port->close();
        delete port;
    }

    bool init(const char*  nUartPort, int nBaudRate);
    void close();
    int  sendMessage(QString msg);
    int  sendByteArray(QByteArray msg);
    void enableReceiving(bool bEnable);

    QByteArray readAvaiable(int nCount, int nMaxTime);
    void discast();

/*
    QQueue<NmeaMessage>& getMessageBuffer()
    {
        return message_buffer;
    }

    bool isLocked() const
    {
        return lock;
    }

    void setLock(bool lock)
    {
        this->lock = lock;
    }*/

    bool getWaitForAck() const;
    void setWaitForAck(bool value);

    bool getMuteOn() const;
    void setMuteOn(bool value);

signals:
    void receivedSerialNmea(NmeaMessage* nmeaMsg);
    void sigSynchConfirmed(bool synchOn);
    void sigReceivedDat();

    void receivedInvalidDataFromSensor();
    void receivedValidDataFromSensor();

public slots:
    void readNmeaPacket();

private:
    char uartDevicePath [30];
    bool validateBaudRate(int nBaudRate);

    bool bReceivingEnabled;
};

#endif // SERIALREADER_H
