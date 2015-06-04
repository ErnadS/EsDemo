#include "RuntimeScreen.h"
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

        case RUNTIME_MULTI:
            return new MultiRuntimeWidget(this, m_runtime_widget_size);

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

        if ((runtime_screen_type == RUNTIME_ES) || (runtime_screen_type == RUNTIME_ES_B))
        {
            m_information_widget_vector[i]->setIndex(i);
        }
        else
        {
            switch(i)
            {
                case 0:
                    m_information_widget_vector[i]->setIndex(0);
                    break;

                case 1:
                    m_information_widget_vector[i]->setIndex(8);
                    break;

                case 2:
                    m_information_widget_vector[i]->setIndex(9);
                    break;

                case 3:
                    m_information_widget_vector[i]->setIndex(11);
                    break;

                case 4:
                    m_information_widget_vector[i]->setIndex(12);
                    break;
            }
        }
    }

    m_brightness_widget = new BrightnessWidget(this, m_right_widget_size);
    m_navigation_widget = new NavigationWidget(this, m_right_widget_size);

    m_runtime_widget = createRuntimeWidget(runtime_screen_type);

    if (m_runtime_screen_type == RuntimeScreenType::RUNTIME_MULTI)
    {
        m_unit_button->hide();
    }

    if (m_runtime_screen_type == RuntimeScreenType::RUNTIME_ES)
    {
        m_unit_button->setTitle("Boat");
    }

    m_heading_button = new Button(this, m_heading_button_size, "ABSOLUTE");

    connect(m_navigation_widget, SIGNAL(navigateLeft()), &m_navigation_controller, SLOT(navigateLeft()));
    connect(m_navigation_widget, SIGNAL(navigateRight()), &m_navigation_controller, SLOT(navigateRight()));
    connect(m_unit_button, SIGNAL(pressed()), this, SLOT(unitButtonClicked()));
    connect(m_heading_button, SIGNAL(pressed()), this, SLOT(headingButtonClicked()));

    if (runtime_screen_type != RuntimeScreenType::RUNTIME_C)
    {
        m_heading_button->hide();
    }

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

    m_brightness_widget->resize(size);
    m_brightness_widget->move(m_right_widget_pos.x() * m_width_scale, (m_right_widget_pos.y() + m_information_widget_vector.size() * (m_right_widget_size.height() + m_vertical_padding)) * m_height_scale);
    m_brightness_widget->hide();

    m_navigation_widget->resize(size);
    m_navigation_widget->move(m_right_widget_pos.x() * m_width_scale, (m_right_widget_pos.y() + (m_information_widget_vector.size() + 1) * (m_right_widget_size.height() + m_vertical_padding)) * m_height_scale);

    m_runtime_widget->resize(m_runtime_widget_size.width() * m_width_scale, m_runtime_widget_size.height() * m_height_scale);
    m_runtime_widget->move(m_runtime_widget_pos.x() * m_width_scale, m_runtime_widget_pos.y() * m_height_scale);

    m_heading_button->resize(m_heading_button_size.width() * m_width_scale, m_heading_button_size.height() * m_height_scale);
    m_heading_button->move(m_heading_button_pos.x() * m_width_scale, m_heading_button_pos.y() * m_height_scale);
}

void RuntimeScreen::buttonClicked()
{
    emit navigate(SetupMenuType::SETUP_MENU);
}

void RuntimeScreen::unitButtonClicked()
{
    if (m_runtime_screen_type == RuntimeScreenType::RUNTIME_ES)
    {
        emit navigate(SetupMenuType::BOAT_MENU);
    }
}

void RuntimeScreen::headingButtonClicked()
{
    if (m_heading_button->title() == "RELATIVE")
    {
        m_heading_button->setTitle("ABSOLUTE");
        RuntimeWidgetC::setTrueHeading(false);
    }
    else
    {
        m_heading_button->setTitle("RELATIVE");
        RuntimeWidgetC::setTrueHeading(true);
    }
}

