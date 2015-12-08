#include "base_screen.h"

void BaseScreen::setupLayout()
{
    updateScale();

    m_button->resize(m_button_size.width() * m_width_scale, m_button_size.height() * m_height_scale);
    m_button->move(m_button_pos.x() * m_width_scale, m_button_pos.y() * m_height_scale);

    m_display_alive_widget->resize(m_display_alive_widget_size.width() * m_width_scale, m_display_alive_widget_size.height() * m_height_scale);
    m_display_alive_widget->move(m_display_alive_widget_pos.x() * m_width_scale, m_display_alive_widget_pos.y() * m_height_scale);

    m_title_widget->resize(m_speed_indication_widget_size.width() * m_width_scale, m_speed_indication_widget_size.height() * m_height_scale);
    m_title_widget->move(m_speed_indication_widget_pos.x() * m_width_scale, m_speed_indication_widget_pos.y() * m_height_scale);

    m_password_widget->resize(m_password_widget_size.width() * m_width_scale, m_password_widget_size.height() * m_height_scale);
    m_password_widget->move(m_password_widget_pos.x() * m_width_scale, m_password_widget_pos.y() * m_height_scale);
}

BaseScreen::BaseScreen(QWidget* parent, const QSize speed_indication_widget_size, const QPoint speed_indication_widget_pos) :
    ScalableWidget(parent, parent->size()), m_navigation_controller(Singleton<NavigationController>::instance()),
    m_speed_indication_widget_size(speed_indication_widget_size), m_speed_indication_widget_pos(speed_indication_widget_pos)
{
    setBaseSize(parent->size());

    m_password_widget = new PasswordWidget(this);
    m_password_widget->hide();

    m_button = new Button(this, m_button_size);
    m_display_alive_widget = new DisplayAliveWidget(this, m_display_alive_widget_size);
    m_title_widget = new TitleWidget(this, m_speed_indication_widget_size);

    setupLayout();

    QPalette palette(BaseScreen::palette());
    palette.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(palette);

    connect(m_button, SIGNAL(clicked()), this, SLOT(buttonClicked()));

    connect(m_password_widget, SIGNAL(login()), m_password_widget, SLOT(hide()));
    connect(m_password_widget, SIGNAL(cancel()), m_password_widget, SLOT(hide()));
}

void BaseScreen::resizeEvent(QResizeEvent*)
{
    setupLayout();
}

TitleWidget* BaseScreen::titleWidget() const
{
    return m_title_widget;
}

PasswordWidget *BaseScreen::passwordWidget() const
{
    return m_password_widget;
}

void BaseScreen::changedProtected(QString key)
{
    if (m_password_widget->isLogged())
    {
        emit makeChange(key);
    }
    else
    {
        m_password_widget->show();
        m_password_widget->raise();
        m_password_widget->getKeyboard()->show();
        m_password_widget->getKeyboard()->raise();
    }
}

void BaseScreen::changeValueProtected(QString key, QString layout)
{
    if (m_password_widget->isLogged())
    {
        emit makeChangeValue(key, layout);
    }
    else
    {
        m_password_widget->show();
        m_password_widget->raise();
        m_password_widget->getKeyboard()->show();
        m_password_widget->getKeyboard()->raise();
    }
}
