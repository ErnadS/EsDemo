#ifndef ES_AUX_SETUP_SCREEN_H
#define ES_AUX_SETUP_SCREEN_H

#include "setup_screen.h"
#include <QVector>

class EsAuxSetupScreen : public SetupScreen
{
    Q_OBJECT

    QVector<bool> m_state_vector;

public:
    explicit EsAuxSetupScreen(QWidget* parent);

signals:
    void mouseClicked(QMouseEvent *event);
protected:
  void paintEvent(QPaintEvent *);

};

#endif
