#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QString>

class Validator
{
protected:
    QString m_validation_message;
    void displayError(QString error_message) const;

public:
    Validator(const QString& validation_message);
    virtual bool validate(const QString&) const;
};

class RegexValidator : public Validator
{
    QString m_regex;

public:
    RegexValidator(const QString& regex, const QString& validation_message);
};

class IntValidator : public Validator
{
    int m_min;
    int m_max;

public:
    IntValidator(int min, int max, const QString& validation_message = "Value must be an integer between %1 and %2!");
    bool validate(const QString& value) const;
};

class FloatValidator : public Validator
{
    float m_min;
    float m_max;

public:
    FloatValidator(float min, float max, const QString& validation_message = "Value must be a real number between %1 and %2!");
    bool validate(const QString& value) const;
};

class IpValidator : public Validator
{
public:
    IpValidator(const QString& validation_message);
};

#endif
