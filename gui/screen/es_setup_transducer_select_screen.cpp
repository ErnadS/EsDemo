#include "es_setup_transducer_select_screen.h"

#include "gui/widget/selectable_enum_item_widget.h"
#include "gui/widget/selectable_int_item_widget.h"
#include "gui/widget/selectable_float_item_widget.h"
#include "gui/widget/selectable_bool_item_widget.h"

EsSetupTransducerSelectScreen::EsSetupTransducerSelectScreen(QWidget *parent) :
    SetupScreen(parent)
{
    titleWidget()->setTitle("ES1 Echosounder");

    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();

    m_selectable_item_widget_container->addWidget("Connector", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Connector", {"1", "2"}));
    m_selectable_item_widget_container->addWidget("Position", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Position", {"Fore", "Aft", "Port", "Starboard", "Name"}));
    m_selectable_item_widget_container->addWidget("Offset", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Offset", "m", new FloatValidator(0.0f, 100.0f)));
    m_selectable_item_widget_container->addWidget("Part number", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Part number", {"Other", "ETN50200", "ETN050", "ETN200"}));
    m_selectable_item_widget_container->addWidget("Frequency low", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Frequency low", "kHz", new FloatValidator(10.0f, 300.0f)));
    m_selectable_item_widget_container->addWidget("Bandwidth low", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Bandwidth low", "%", new FloatValidator(2.0f, 50.0f)));
    m_selectable_item_widget_container->addWidget("Frequency high", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Frequency high", "kHz", new FloatValidator(10.0f, 300.0f)));
    m_selectable_item_widget_container->addWidget("Bandwidth high", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Bandwidth high", "%", new FloatValidator(2.0f, 50.0f)));
    m_selectable_item_widget_container->addWidget("Max power (W)", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Max power (W)", {"100", "200", "300", "400", "500", "600", "700", "800", "900", "1000"}));
    m_selectable_item_widget_container->addWidget("Approved primary", new SelectableBoolItemWidget(m_selectable_item_widget_container, item_size, "Approved primary", "Yes", "No"));

    setupLayout();
}


void EsSetupTransducerSelectScreen::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int rect_w(200 * m_width_scale), rect_h(260 * m_height_scale), triang_h(70 * m_height_scale);

    QRect rect(0, 0, rect_w, rect_h);
    rect.moveCenter(QPoint(width()/4, height()/2));

    QPolygon triang(4);
    triang[0] = rect.topLeft();
    triang[1] = rect.topRight();
    triang[2] = QPoint(rect.center().x(), rect.top() - triang_h);
    triang[3] = triang[0];

    QBrush gray(Qt::gray);
    QBrush dark_gray(Qt::darkGray);
    QBrush green(Qt::green);
    QBrush yellow(Qt::yellow);

    painter.setBrush(gray);
    painter.drawPolygon(triang);
    painter.drawRect(rect);

    painter.setBrush(dark_gray);
    painter.setPen(QPen(Qt::black, 1));

    painter.drawEllipse(QPoint(rect.center().x() - 2.0f/5 * rect_w, rect.center().y()), rect_w/11, rect_w/11);
    painter.drawEllipse(QPoint(rect.center().x() - 1.0f/5 * rect_w, rect.center().y()), rect_w/11, rect_w/11);
    painter.drawEllipse(QPoint(rect.center().x() + 1.0f/5 * rect_w, rect.center().y()), rect_w/11, rect_w/11);
    painter.drawEllipse(QPoint(rect.center().x() + 2.0f/5 * rect_w, rect.center().y()), rect_w/11, rect_w/11);

    painter.setBrush(green);
    painter.drawEllipse(QPoint(rect.center().x() - 1.0f/10 * rect_w, rect.bottom() - rect_h/9), rect_w/11, rect_w/11);
    QFont font(painter.font());
    font.setPixelSize(rect_h/10);
    painter.setFont(font);
    QRect textRect(0, 0, rect_w/6, rect_w/6);
    textRect.moveCenter(QPoint(rect.center().x() - 1.0f/10 * rect_w, rect.bottom() - rect_h/9));
    painter.drawText(textRect, Qt::AlignCenter, "2");

    painter.setBrush(yellow);
    painter.drawEllipse(QPoint(rect.center().x() - 1.0f/10 * rect_w, rect.top() - rect_h/10), rect_w/11, rect_w/11);
    textRect.moveCenter(QPoint(rect.center().x() - 1.0f/10 * rect_w, rect.top() - rect_h/10));
    painter.drawText(textRect, Qt::AlignCenter, "1");

    painter.setBrush(dark_gray);
    painter.drawEllipse(QPoint(rect.center().x() + 1.0f/10 * rect_w, rect.bottom() - rect_h/9), rect_w/11, rect_w/11);
    painter.drawEllipse(QPoint(rect.center().x() + 1.0f/10 * rect_w, rect.top() - rect_h/10), rect_w/11, rect_w/11);
}
