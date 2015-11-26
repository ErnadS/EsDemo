#ifndef ES_HISTORY_SETUP_SCREEN_H
#define ES_HISTORY_SETUP_SCREEN_H

#include "setup_screen.h"
#include <QVector>

class EsHistorySetupScreen : public SetupScreen
{
    Q_OBJECT

    QVector<bool> m_state_vector;

public:
    explicit EsHistorySetupScreen(QWidget* parent);

protected:
  void paintEvent(QPaintEvent *);
};

#endif
