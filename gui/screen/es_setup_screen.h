#ifndef ES_SETUP_SCREEN_H
#define ES_SETUP_SCREEN_H

#include "multi_setup_screen.h"

class EsSetupScreen : public MultiSetupScreen
{
    Q_OBJECT

    const QSize m_item_size{110, 50};
    const int m_item_count{5};
    const int m_item_sep{3};
    const QSize m_item_container_size{m_item_count * m_item_size.width() + (m_item_count - 1) * m_item_sep, m_item_size.height()};
    const QPoint m_item_container_pos{0, 430};

private slots:
    void menuClicked(int index);

public:
    explicit EsSetupScreen(QWidget* parent);

protected:
    void setupLayout();
};

#endif
