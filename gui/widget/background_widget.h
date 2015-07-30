#ifndef BACKGROUND_WIDGET_H
#define BACKGROUND_WIDGET_H

#include <QWidget>

class BackgroundWidget : public QWidget
{
    Q_OBJECT

    QColor m_color;

public:
    explicit BackgroundWidget(QColor color = Qt::black, QWidget* parent = 0);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent*);
};

#endif
