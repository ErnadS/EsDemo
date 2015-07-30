#include "base_screen.h"

void BaseScreen::setupLayout()
{
    updateScale();

    m_button->resize(m_button_size.width() * m_width_scale, m_button_size.height() * m_height_scale);
    m_button->move(m_button_pos.x() * m_width_scale, m_button_pos.y() * m_height_scale);

    m_display_alive_widget->resize(m_display_alive_widget_size.width() * m_width_scale, m_display_alive_widget_size.height() * m_height_scale);
    m_display_alive_widget->move(m_display_alive_widget_pos.x() * m_width_scale, m_display_alive_widget_pos.y() * m_height_scale);

    m_speed_indication_widget->resize(m_speed_indication_widget_size.width() * m_width_scale, m_speed_indication_widget_size.height() * m_height_scale);
    m_speed_indication_widget->move(m_speed_indication_widget_pos.x() * m_width_scale, m_speed_indication_widget_pos.y() * m_height_scale);
}

BaseScreen::BaseScreen(QWidget* parent) :
    ScalableWidget(parent, parent->size()), m_navigation_controller(Singleton<NavigationController>::instance())
{
    setBaseSize(parent->size());

    m_button = new Button(this, m_button_size);
    m_display_alive_widget = new DisplayAliveWidget(this, m_display_alive_widget_size);
    m_speed_indication_widget = new SpeedIndicationWidget(this, m_speed_indication_widget_size);

    setupLayout();

    QPalette palette(BaseScreen::palette());
    palette.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(palette);

    connect(m_button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

void BaseScreen::resizeEvent(QResizeEvent*)
{
    setupLayout();
}
