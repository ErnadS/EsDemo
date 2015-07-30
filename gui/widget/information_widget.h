#ifndef INFORMATION_WIDGET_H
#define INFORMATION_WIDGET_H

#include "scalable_widget.h"
#include "gui/widget_enum.h"
#include <QVector>

class InformationWidget : public ScalableWidget
{
    Q_OBJECT

    QString m_title{"Title"};
    QString m_value{"Value"};
    QString m_unit{"Unit"};

    QVector<InformationSource> m_source_vector{InformationSource::W_TEMP, InformationSource::SOG_LONG, InformationSource::SOG_TRA, InformationSource::SOG, InformationSource::STW_LONG, InformationSource::STW_TRA, InformationSource::STW, InformationSource::STW_DL1, InformationSource::ALARM_HIGH, InformationSource::ALARM_LOW, InformationSource::DEPTH, InformationSource::TRIP, InformationSource::TOTAL};
    int m_index{0};

    QString getDescription(InformationSource source);
    QString getUnit(InformationSource source);
    qreal getValue(InformationSource source);

    RuntimeScreenType m_screen_type;

public:
    explicit InformationWidget(QWidget* parent, QSize base_size, RuntimeScreenType screen_type);

    void setIndex(int index);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);
};

#endif
