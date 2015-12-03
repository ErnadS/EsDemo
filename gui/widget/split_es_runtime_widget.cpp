#include "split_es_runtime_widget.h"
#include <QDebug>

SplitESRuntimeWidget::SplitESRuntimeWidget(QWidget *parent, QSize base_size, echosonarLayout widget_layout) : RuntimeWidget(parent, base_size), m_widget_layout(widget_layout)
{
    QSize widget_size{width(), height()/2};


    m_widget1 = new RuntimeWidgetEs(this, widget_size);

    if(m_widget_layout != SINGLE)
    {
      m_widget2 = new RuntimeWidgetEs(this, widget_size);
    }


    setupLayout();


}

void SplitESRuntimeWidget::setLayout(echosonarLayout layout)
{
    m_widget_layout = layout;
    setupLayout();

}

void SplitESRuntimeWidget::paintEvent(QPaintEvent*)
{
}

void SplitESRuntimeWidget::setupLayout()
{

    if(m_widget_layout==VERTICAL)
    {

      m_widget1->move(0,0);
      m_widget1->resize(width(), height()/2);
      m_widget2->move(0, height()/2);
      m_widget2->resize(width(), height()/2 );
      m_widget1->setFontSize(30 * m_width_scale );
      m_widget2->setFontSize(30 * m_width_scale );



    }
    else if(m_widget_layout==HORIZONTAL)
    {

      m_widget1->move(0,0);
      m_widget1->resize(width()/2, 0.80 * height());
      m_widget2->move(width()/2 , 0);
      m_widget2->resize(width()/2 , 0.80 * height());
      m_widget1->setFontSize(33 * m_height_scale);
     m_widget2->setFontSize(33 * m_height_scale);

    }
    else
    {
        m_widget1->move(0,0);
        m_widget1->resize(width(), height());
    }


}

void SplitESRuntimeWidget::resizeEvent(QResizeEvent *)
{
    updateScale();
    setupLayout();
}

