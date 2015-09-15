#include "runtime_screen.h"
#include <stdexcept>

QWidget* RuntimeScreen::createRuntimeWidget(RuntimeScreenType runtime_screen_type)
{
    switch (runtime_screen_type)
    {
        case RuntimeScreenType::RUNTIME_A:
            return new RuntimeWidgetA(this, m_runtime_widget_size);

        case RuntimeScreenType::RUNTIME_B:
            return new RuntimeWidgetB(this, m_runtime_widget_size);

        case RuntimeScreenType::RUNTIME_C:
            return new RuntimeWidgetC(this, m_runtime_widget_size);

        case RuntimeScreenType::RUNTIME_D:
            return new RuntimeWidgetD(this, m_runtime_widget_size);

        case RuntimeScreenType::RUNTIME_E:
            return new RuntimeWidgetE(this, m_runtime_widget_size, false);

        case RuntimeScreenType::RUNTIME_DL1:
            return new RuntimeWidgetDl1(this, m_runtime_widget_size);

        case RuntimeScreenType::RUNTIME_ES:
            return new RuntimeWidgetEs(this, m_runtime_widget_size);

        case RUNTIME_DL1_B:
            return new Dl1RuntimeWidgetB(this, m_runtime_widget_size);

        case RUNTIME_ES_B:
            return new EsRuntimeWidgetB(this, m_runtime_widget_size);
    }

    throw std::invalid_argument("Provided argument is not in enum range.");
}

RuntimeScreen::RuntimeScreen(QWidget* parent, RuntimeScreenType runtime_screen_type) :
    BaseScreen(parent)
{
    int information_widget_count = m_navigation_controller.isEmbedded() ? 5 : 6;
    m_information_widget_vector = QVector<InformationWidget*>(information_widget_count, nullptr);

    m_runtime_screen_type = runtime_screen_type;

    m_button->setTitle("Config");

    if ((m_runtime_screen_type == RuntimeScreenType::RUNTIME_E) || (m_runtime_screen_type == RuntimeScreenType::RUNTIME_ES))
    {
        m_unit_button = new Button(this, m_unit_button_size, "m", false);
    }
    else
    {
        m_unit_button = new Button(this, m_unit_button_size, "kn", false);
    }

    for (int i = 0; i < m_information_widget_vector.size(); i++)
    {
        m_information_widget_vector[i] = new InformationWidget(this, m_right_widget_size, runtime_screen_type);
    }

    m_brightness_widget = m_navigation_controller.isEmbedded() ? new BrightnessWidget(this, m_right_widget_size) : nullptr;
    m_navigation_widget = new NavigationWidget(this, m_right_widget_size);

    m_runtime_widget = createRuntimeWidget(runtime_screen_type);

    connect(m_unit_button, SIGNAL(clicked()), this, SLOT(unitButtonClicked()));

    setupLayout();
}

void RuntimeScreen::setupLayout()
{
    BaseScreen::setupLayout();

    m_unit_button->resize(m_unit_button_size.width() * m_width_scale, m_unit_button_size.height() * m_height_scale);
    m_unit_button->move(m_unit_button_pos.x() * m_width_scale, m_unit_button_pos.y() * m_height_scale);

    QSize size(m_right_widget_size.width() * m_width_scale, m_right_widget_size.height() * m_height_scale);

    for (int i = 0; i < m_information_widget_vector.size(); i++)
    {
        m_information_widget_vector[i]->resize(size);
        m_information_widget_vector[i]->move(m_right_widget_pos.x() * m_width_scale, (m_right_widget_pos.y() + i * (m_right_widget_size.height() + m_vertical_padding)) * m_height_scale);
    }

    m_navigation_widget->resize(size);
    m_navigation_widget->move(m_right_widget_pos.x() * m_width_scale, (m_right_widget_pos.y() + (m_information_widget_vector.size()) * (m_right_widget_size.height() + m_vertical_padding)) * m_height_scale);

    if (m_navigation_controller.isEmbedded() == true)
    {
        m_brightness_widget->resize(size);
        m_brightness_widget->move(m_right_widget_pos.x() * m_width_scale, (m_right_widget_pos.y() + m_information_widget_vector.size() * (m_right_widget_size.height() + m_vertical_padding)) * m_height_scale);

        m_navigation_widget->move(m_right_widget_pos.x() * m_width_scale, (m_right_widget_pos.y() + (m_information_widget_vector.size() + 1) * (m_right_widget_size.height() + m_vertical_padding)) * m_height_scale);
    }

    m_runtime_widget->resize(m_runtime_widget_size.width() * m_width_scale, m_runtime_widget_size.height() * m_height_scale);
    m_runtime_widget->move(m_runtime_widget_pos.x() * m_width_scale, m_runtime_widget_pos.y() * m_height_scale);
}

void RuntimeScreen::buttonClicked()
{
    m_navigation_controller.navigate(SetupMenuType::SETUP_MENU, true);
}

void RuntimeScreen::unitButtonClicked()
{

}
