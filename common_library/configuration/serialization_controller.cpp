#include "serialization_controller.h"
#include <QDebug>
#include <QJsonObject>
#include <QSaveFile>

IntWrapper::IntWrapper(int value)
{
    m_value = value;
}

IntWrapper::IntWrapper(QObject* parent): QObject(parent)
{
    m_value = 0;
}

IntWrapper::IntWrapper(const IntWrapper& wrapper) : QObject(wrapper.parent())
{
    m_value = wrapper.m_value;
}

IntWrapper& IntWrapper::operator =(const IntWrapper& wrapper)
{
    m_value = wrapper.m_value;

    return *this;
}

int IntWrapper::getValue() const
{
    return m_value;
}

void IntWrapper::setValue(int value)
{
    m_value = value;
}


BoolWrapper::BoolWrapper(bool value)
{
    m_value = value;
}

BoolWrapper::BoolWrapper(QObject* parent) : QObject(parent)
{
    m_value = false;
}

BoolWrapper::BoolWrapper(const BoolWrapper& wrapper) : QObject(wrapper.parent())
{
    m_value = wrapper.m_value;
}

BoolWrapper& BoolWrapper::operator =(const BoolWrapper& wrapper)
{
    m_value = wrapper.m_value;

    return *this;
}

bool BoolWrapper::getValue() const
{
    return m_value;
}

void BoolWrapper::setValue(bool value)
{
    m_value = value;
}


FloatWrapper::FloatWrapper(float value)
{
    m_value = value;
}

FloatWrapper::FloatWrapper(QObject* parent) : QObject(parent)
{
    m_value = 0.0f;
}

FloatWrapper::FloatWrapper(const FloatWrapper& wrapper) : QObject(wrapper.parent())
{
    m_value = wrapper.m_value;
}

FloatWrapper& FloatWrapper::operator =(const FloatWrapper& wrapper)
{
    m_value = wrapper.m_value;

    return *this;
}

float FloatWrapper::getValue() const
{
    return m_value;
}

void FloatWrapper::setValue(float value)
{
    m_value = value;
}

void SerializationController::writeToFile(const QString& file_path, const QString& json)
{
    QSaveFile file(file_path);
    file.open(QIODevice::WriteOnly);

    file.write(json.toLatin1());
    file.commit();
}

QString SerializationController::readFromFile(const QString &file_path)
{
    QFile file(file_path);

    if (file.open(QFile::ReadOnly | QFile::Text) == false)
    {
        return "";
    }

    QTextStream input_stream(&file);

    return input_stream.readAll();
}

bool SerializationController::Serialize(const QObject &object, QString path, QString pathPrefix,
                                        bool checkSystemType)
{
    // TODO: Fix
    if (checkSystemType == true)
    {
        //return false;
    }

    // Creating folder in file system in case it doesn't exist
    QString folder_path = QCoreApplication::applicationDirPath() + "/" + pathPrefix;
    QString file_path = folder_path + path;

    if(QDir(folder_path).exists() == false)
    {
        QDir().mkdir(folder_path);
    }

    // Creating QJsonObject from QObject class
    QVariantMap v = SerializationHelper::toQVariantMap(&object);
    QJsonObject json_object;

    foreach(QString key, v.keys())
    {
        json_object.insert(key, QJsonValue::fromVariant(v[key]));
    }

    QString json = QJsonDocument(json_object).toJson();

    SerializationController::writeToFile(file_path, json);

    return true;
}


QVariantMap SerializationHelper::toQVariantMap(const QObject *object)
{
    QVariantMap map;

    for (int i = 0; i < object->metaObject()->propertyCount(); ++i)
    {
        QMetaProperty meta_property = object->metaObject()->property(i);

        const char* key = meta_property.name();
        QVariant value = object->property(key);

        map[QString(key)] = value;
    }

    map.remove("objectName");

    return map;
}

void SerializationHelper::toQObject(const QVariantMap &variant, QObject *object)
{
    const QMetaObject* meta_object = object->metaObject();

    for (QVariantMap::const_iterator it = variant.constBegin(); it != variant.constEnd(); ++it)
    {
        int index = meta_object->indexOfProperty(it.key().toLatin1());
        QMetaProperty metaproperty = meta_object->property(index);

        QVariant value = it.value();
        metaproperty.write(object, value);
    }
}
