#ifndef SERIALIZATION_CONTROLLER_H
#define SERIALIZATION_CONTROLLER_H

#include <QDir>
#include <QDebug>
#include <QMetaProperty>
#include <QJsonDocument>
#include <QCoreApplication>
#include <QJsonObject>

class IntWrapper: public QObject
{
    Q_OBJECT

    int m_value;

    Q_PROPERTY(int value READ getValue WRITE setValue)

public:
    IntWrapper(int value);
    explicit IntWrapper(QObject* parent = 0);
    IntWrapper(const IntWrapper& wrapper);
    IntWrapper& operator =(const IntWrapper& wrapper);

    int getValue() const;
    void setValue(int value);
};

class BoolWrapper: public QObject
{
    Q_OBJECT

    bool m_value;

    Q_PROPERTY(int value READ getValue WRITE setValue)

public:
    BoolWrapper(bool value);
    explicit BoolWrapper(QObject* parent = 0);
    BoolWrapper(const BoolWrapper& wrapper);
    BoolWrapper& operator =(const BoolWrapper& wrapper);

    bool getValue() const;
    void setValue(bool value);
};

class FloatWrapper: public QObject
{
    Q_OBJECT

    float m_value;

    Q_PROPERTY(float value READ getValue WRITE setValue)

public:
    FloatWrapper(float value);
    explicit FloatWrapper(QObject* parent = 0);
    FloatWrapper(const FloatWrapper& wrapper);
    FloatWrapper& operator =(const FloatWrapper& wrapper);

    float getValue() const;
    void setValue(float value);
};

class SerializationHelper
{
public:
    static QVariantMap toQVariantMap(const QObject* object);
    static void toQObject(const QVariantMap& variant, QObject* object);
};

class SerializationController
{
    static void writeToFile(const QString& file_path, const QString& json);
    static QString readFromFile(const QString& file_path);

public:
    static bool Serialize(const QObject &object, QString path, QString pathPrefix ="/configuration_files/",
                          bool checkSystemType = true);

    template <typename T>
    static bool Serialize(const QList<T>& object_list, QString path, QString pathPrefix ="/configuration_files/",
                          bool checkSystemType = true);
    template <typename T>
    static bool Deserialize(T& object, QString path, QString pathPrefix ="/configuration_files/",
                            bool checkSystemType = true);

    template <typename anyType>
    static bool Deserialize(QList<anyType>& object_list, QString path, QString pathPrefix ="/configuration_files/",
                            bool checkSystemType = true);
};

template <typename T>
bool SerializationController::Serialize(const QList<T>& object_list, QString path, QString pathPrefix, bool checkSystemType)
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

    QVariantList variant_list;
    for (int i = 0; i < object_list.length(); i++)
    {
        variant_list.append(SerializationHelper::toQVariantMap(&object_list[i]));
    }

    QJsonObject json_object;
    json_object.insert("list", QJsonValue::fromVariant(variant_list));

    QString json = QJsonDocument(json_object).toJson();

    SerializationController::writeToFile(file_path, json);

    return true;
}

template <typename T>
bool SerializationController::Deserialize(T& object, QString path, QString pathPrefix, bool checkSystemType)
{
    // Todo: Fix
    if(checkSystemType == true)
    {
        //return false;
    }

    QString file_path = QCoreApplication::applicationDirPath() + pathPrefix + path;
    QString json = readFromFile(file_path);

    if(json.isEmpty() == true)
    {
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(json.toLatin1());
    QVariantMap map = doc.toVariant().toMap();
    SerializationHelper::toQObject(map, &object);

    return true;
}

template <typename T>
bool SerializationController::Deserialize(QList<T>& object_list, QString path, QString pathPrefix, bool checkSystemType)
{
    // Todo: Fix
    if(checkSystemType == true)
    {
        //return false;
    }

    QString file_path = QCoreApplication::applicationDirPath() + pathPrefix + path;
    QString json = readFromFile(file_path);

    QJsonDocument doc = QJsonDocument::fromJson(json.toLatin1());
    QVariant var = doc.toVariant();

    // Preparing result list to have the same size as variant list
    QVariantList variant_list = var.toMap()["list"].toList();

    if(object_list.isEmpty() || object_list.length() != variant_list.length())
    {
        if(object_list.length() != variant_list.length())
        {
            object_list.empty();
        }

        for (int i = 0; i < variant_list.length(); i++)
        {
            object_list.append(T());
        }
    }

    for (int i = 0; i < variant_list.length(); i++)
    {
        QVariantMap map = variant_list[i].toMap();
        SerializationHelper::toQObject(map, &object_list[i]);
    }

    return true;
}

#endif
