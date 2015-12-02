#ifndef SELECTABLE_ITEM_WIDGET_CONTAINER_H
#define SELECTABLE_ITEM_WIDGET_CONTAINER_H

#include "scalable_widget.h"
#include "gui/widget_enum.h"
#include "gui/keyboard/QVirtualKeyboard.h"
#include "selectable_item_widget.h"
#include "arrow_widget.h"
#include <QHash>

class SelectableItemWidgetContainer : public ScalableWidget
{
    Q_OBJECT

    QVirtualKeyboard* m_keyboard;
    QString m_key;
    QString m_buffer;
    QString m_unit;
    int m_display_size;
    QVector<SelectableItemWidget*> m_item_widget_vector;
    QHash<QString, int> m_item_map;

    ArrowWidget* m_up_arrow;
    ArrowWidget* m_down_arrow;

    void setupLayout();

    int m_rotation_offset{0};

public:
    explicit SelectableItemWidgetContainer(QWidget* parent, QSize base_size, QVirtualKeyboard* keyboard, int display_size);

    void addWidget(QString key, SelectableItemWidget* item_widget);
    SelectableItemWidget* getWidget(const QString& key) const;
    int getItemVectorSize() const;

    QSize getItemBaseSize() const;
    QVirtualKeyboard* getKeyboard() const;

private slots:
    void upPressed();
    void downPressed();
    void changed(QString key);
    void changeValue(QString key, QString layout);
    void keyPressed(QKeyEvent*);
    void makeChange(QString key);
    void makeChangeValue(QString key, QString layout);

protected:
    void resizeEvent(QResizeEvent* event);

signals:
    void changedProtected(QString key);
    void changeValueProtected(QString key, QString layout);
    void signalLowerParent();
};

#endif
