#ifndef RUNTIMEWIDGETES_H
#define RUNTIMEWIDGETES_H

#include "ScalableWidget.h"
#include "common/ColorTable.h"
#include "common/Buffer.h"
#include <QVector>
#include <QTimer>
#include <TransparentInfoButton.h>
#include <QFile>

enum class MousePressTarget { Bottom, Right, Top };

class RuntimeWidgetEs : public ScalableWidget
{
    Q_OBJECT

    qreal m_depth{0.0f};

    MousePressTarget m_target{MousePressTarget::Top};

    ColorTable m_color_table_0
    {
        {40, 120, 252},
        {40, 120, 252},
        {40, 120, 252},
        {0, 80, 168},
        {0, 40, 160},
        {0, 0, 128},
        {0, 80, 64},
        {0, 120, 40},
        {40, 160, 0},
        {120, 200, 0},
        {200, 200, 0},
        {240, 240, 0},
        {252, 200, 0},
        {224, 120, 0},
        {180, 80, 0},
        {160, 0, 20},
        {120, 0, 40},
        {80, 0, 20},
        {40, 0, 0}
    };

    ColorTable m_color_table_1
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {47, 79, 2},
        {79, 111, 4},
        {103, 135, 8},
        {114, 146, 10},
        {159, 191, 16},
        {163, 195, 19},
        {207, 239, 24}
    };

    ColorTable m_color_table_2
    {
        {0, 0, 0},
        {9, 15, 0},
        {31, 47, 2},
        {47, 79, 2},
        {79, 111, 4},
        {103, 135, 8},
        {114, 146, 10},
        {159, 191, 16},
        {163, 195, 19},
        {207, 239, 24}
    };

    ColorTable m_color_table_3
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {45, 88, 94},
        {60, 112, 122},
        {85, 138, 150},
        {90, 162, 178},
        {105, 188, 206},
        {120, 214, 234},
        {135, 240, 255}
    };

    LifoBuffer<QVector<QVector<QColor>>> m_buffer{640};
    const int sample_size{512};

    QTimer timer;
    QFile m_bin_file{":/es.bin"};

    TransparentInfoButton* m_range_info;
    TransparentInfoButton* m_power_info;
    TransparentInfoButton* m_transducer_info;
    const QSize m_power_info_button_size{120, 70};
    const QSize m_range_info_button_size{120, 70};
    const QSize m_transducer_info_button_size{240, 70};

    int m_depth_index{4};
    QVector<qreal> m_max_depth_vector{10, 50, 100, 500, 1000, 1600};

    int m_color_index{0};

public:
    explicit RuntimeWidgetEs(QWidget* parent, QSize base_size);

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
    void updateInfo();

protected slots:
    void timeout();
    void rangeChanged();

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent* event);
};

#endif // RUNTIMEWIDGETES_H
