#ifndef SYSTEM_SETUP_SCREEN_H
#define SYSTEM_SETUP_SCREEN_H

#include "setup_screen.h"
#include <QPushButton>
#include <QVector>
#include "gui/widget/system_setup_widget_container.h"


class SystemSetupScreen : public SetupScreen
{
    Q_OBJECT

private slots:
    void slotSystemSelected(int index);
    void slotSetupSelected(systemConnection status);
    void slotRefreshSystems();

signals:
    void signalSystemSelected(int);
    void signalSetupSelected(systemConnection);
    void signalRefreshSystems();

public:
    explicit SystemSetupScreen(QWidget* parent);

    // QWidget interface
protected:
    SystemSetupWidgetContainer* m_system_setup_widget_container;
    QVector <systemConnection> m_status_vector;
    QVector <bool> m_selection_vector;
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void drawConnections(QPainter& painter);
    void setupLayout();
    void resizeEvent(QResizeEvent*);
};

#endif
