#ifndef SELECTABLE_ITEM_WIDGET_H
#define SELECTABLE_ITEM_WIDGET_H

#include "scalable_widget.h"
#include "gui/widget_enum.h"
#include "gui/widget/validator.h"

class SelectableItemWidget : public ScalableWidget
{
    Q_OBJECT

protected:
    QString m_title;
    QString m_unit;
    RowIndexParity m_row_index_parity{ODD};
    Validator* m_validator;
    bool m_password_protected;

    void paintBorderRectangle(QPainter& painter, int x, int y, int width, int height, QColor borderColor, QColor backgroundlColor);
    virtual QString getValueString() const = 0;

    explicit SelectableItemWidget(QWidget* parent, QSize base_size, QString title, QString unit, bool password_protected, Validator* validator);

public:
    virtual void getValue(void* v) const = 0;
    void setRowIndexParity(RowIndexParity parity);

    virtual QString getKeyboardString() const = 0;
    virtual void setValueFromString(const QString& value) = 0;

    QString getUnit();

    Validator* validator() const;

    bool isProtected() const;

signals:
    void changed(QString key);
    void changeValue(QString key, QString layout);

protected:
    void paintEvent(QPaintEvent*);
};

#endif
