#include "selectable_item_widget_container.h"
#include "selectable_bool_item_widget.h"
#include "selectable_enum_item_widget.h"
#include "gui/screen/setup_screen.h"
#include "password_widget.h"
#include <QDebug>

void SelectableItemWidgetContainer::setupLayout()
{
    QSize item_size(0.9f * baseSize().width() * m_width_scale, baseSize().height() / m_display_size * m_height_scale + 0.5f);
    QSize arrow_size(0.1f * baseSize().width() * m_scale, 0.1f * baseSize().width() * m_scale);

    for (int i = 0; i < m_item_widget_vector.size(); i++)
    {
        m_item_widget_vector[i]->resize(item_size);
        m_item_widget_vector[i]->move(0, (i - m_rotation_offset) * item_size.height());

        if ((i - m_rotation_offset >= 0) && (i - m_rotation_offset < m_item_widget_vector.size()))
        {
            m_item_widget_vector[i]->setVisible(true);
        }
        else
        {
            m_item_widget_vector[i]->setVisible(false);
        }
    }

    m_up_arrow->resize(arrow_size);
    m_down_arrow->resize(arrow_size);

    m_up_arrow->move(item_size.width(), 0);
    m_down_arrow->move(item_size.width(), height() - arrow_size.height());

    m_rotation_offset == 0 ? m_up_arrow->setVisible(false) : m_up_arrow->setVisible(true);
    m_rotation_offset == m_item_widget_vector.size() - m_display_size ? m_down_arrow->setVisible(false) : m_down_arrow->setVisible(true);

    if (m_item_widget_vector.size() <= m_display_size)
    {
        m_up_arrow->setVisible(false);
        m_down_arrow->setVisible(false);
    }
}

SelectableItemWidgetContainer::SelectableItemWidgetContainer(QWidget* parent, QSize base_size, QVirtualKeyboard* keyboard, int display_size) : ScalableWidget(parent, base_size), m_keyboard(keyboard), m_display_size(display_size)
{
    QSize arrow_size(0.1f * base_size.width(), 0.1f * base_size.width());

    m_up_arrow = new ArrowWidget(this, arrow_size, FORWARD);
    m_down_arrow = new ArrowWidget(this, arrow_size, BACKWARD);

    connect(m_up_arrow, SIGNAL(pressed()), this, SLOT(upPressed()));
    connect(m_down_arrow, SIGNAL(pressed()), this, SLOT(downPressed()));

    connect(m_keyboard, SIGNAL(keyPressed(QKeyEvent*)), this, SLOT(keyPressed(QKeyEvent*)));

    if(SetupScreen *p = qobject_cast<SetupScreen *>(parentWidget()))
    {
        connect(p, SIGNAL(makeChange(QString)), this, SLOT(makeChange(QString)));
        connect(p, SIGNAL(makeChangeValue(QString, QString)), this, SLOT(makeChangeValue(QString,QString)));
    }
    setupLayout();
}

void SelectableItemWidgetContainer::addWidget(QString key, SelectableItemWidget* item_widget)
{
    if (m_item_map.contains(key) == true)
        throw std::invalid_argument("Key already exists in map!");

    if (m_item_widget_vector.size() % 2 == 1)
        item_widget->setRowIndexParity(EVEN);

    m_item_widget_vector.push_back(item_widget);

    m_item_map.insert(key, m_item_widget_vector.size() - 1);

    connect(item_widget, SIGNAL(changed(QString)), this, SLOT(changed(QString)));
    connect(item_widget, SIGNAL(changeValue(QString, QString)), this, SLOT(changeValue(QString, QString)));

    setupLayout();
}


SelectableItemWidget* SelectableItemWidgetContainer::getWidget(const QString &key) const
{
    if (m_item_map.contains(key) == false)
        throw std::range_error("Key does not exist in map!");

    int index = m_item_map[key];
    return m_item_widget_vector[index];
}

int SelectableItemWidgetContainer::getItemVectorSize() const
{
    return m_item_widget_vector.size();
}

QSize SelectableItemWidgetContainer::getItemBaseSize() const
{
    return QSize(0.9f * baseSize().width(), baseSize().height() / m_display_size + 0.5f);
}

QVirtualKeyboard *SelectableItemWidgetContainer::getKeyboard() const
{
    return m_keyboard;
}

void SelectableItemWidgetContainer::resizeEvent(QResizeEvent*)
{
    ScalableWidget::resizeEvent(nullptr);
    setupLayout();
}

void SelectableItemWidgetContainer::upPressed()
{
    m_rotation_offset--;

    if (m_rotation_offset < 0)
    {
        m_rotation_offset = 0;
    }

    setupLayout();
}

void SelectableItemWidgetContainer::downPressed()
{
    m_rotation_offset++;

    if (m_display_size + m_rotation_offset >= m_item_widget_vector.size())
    {
        m_rotation_offset = m_item_widget_vector.size() - m_display_size;
    }

    setupLayout();
}

void SelectableItemWidgetContainer::changed(QString key)
{
    m_key = key;
    auto widget = m_item_widget_vector[m_item_map[key]];

    if (widget->isProtected())
    {
        emit changedProtected(key);
        if (!PasswordWidget::isLogged())
        {
            parentWidget()->raise();
        }
    }
    else
    {
        if (SelectableEnumItemWidget *p = qobject_cast<SelectableEnumItemWidget *>(widget))
        {
            p->setNextValue();
        }

        if (SelectableBoolItemWidget *p = qobject_cast<SelectableBoolItemWidget *>(widget))
        {
            p->setNextValue();
        }
        qDebug() << "Changed unprotected item with key: " << key;
    }
}

void SelectableItemWidgetContainer::changeValue(QString key, QString layout)
{
    m_key = key;
    auto widget = m_item_widget_vector[m_item_map[key]];

    parentWidget()->raise();

    if (widget->isProtected())
    {
        emit changeValueProtected(key, layout);
    }
    else
    {        
        m_buffer = widget->getKeyboardString();
        m_unit = widget->getUnit();

        setDisabled(true);

        m_keyboard->setLayout(layout);
        m_keyboard->slotSetText(m_buffer + m_unit);
        m_keyboard->show();
        m_keyboard->raise();
    }
}

void SelectableItemWidgetContainer::keyPressed(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Cancel)
    {
        setEnabled(true);
        m_keyboard->hide();
    }
    else if (event->key() == Qt::Key_Backspace)
    {
        m_buffer.remove(m_buffer.length() - 1, 1);
        m_keyboard->slotSetText(m_buffer + m_unit);
    }
    else if (event->key() == Qt::Key_Enter)
    {
        auto widget = m_item_widget_vector[m_item_map[m_key]];
        auto validator = widget->validator();

        if (validator->validate(m_buffer) == true)
        {
            widget->setValueFromString(m_buffer);
            qDebug() << "value in range..." << "    buffer is " << m_buffer;
        }
        else
        {
            qDebug() << "not in range!";
        }
        setEnabled(true);
        m_keyboard->hide();
    }
    else
    {
        QString new_char = event->text();
        m_buffer.append(new_char);
        m_keyboard->slotSetText(m_buffer + m_unit);
    }
}

void SelectableItemWidgetContainer::makeChange(QString key)
{
    m_key = key;
    auto widget = m_item_widget_vector[m_item_map[key]];

    if (SelectableEnumItemWidget *p = qobject_cast<SelectableEnumItemWidget *>(widget))
    {
        p->setNextValue();
    }

    if (SelectableBoolItemWidget *p = qobject_cast<SelectableBoolItemWidget *>(widget))
    {
        p->setNextValue();
    }

    qDebug() << "Changed item with key: " << key;
}

void SelectableItemWidgetContainer::makeChangeValue(QString key, QString layout)
{
    parentWidget()->raise();

    m_key = key;
    auto widget = m_item_widget_vector[m_item_map[key]];
    m_buffer = widget->getKeyboardString();
    m_unit = widget->getUnit();

    setDisabled(true);

    m_keyboard->setLayout(layout);
    m_keyboard->slotSetText(m_buffer + m_unit);
    m_keyboard->show();
    m_keyboard->raise();
}
