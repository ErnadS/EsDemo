#ifndef SETUPMENUSCREEN_H
#define SETUPMENUSCREEN_H

#include "BaseScreen.h"
#include "SystemWidget.h"

class SetupMenuScreen : public BaseScreen
{
    Q_OBJECT

    SystemWidget* m_dl1_system;
    SystemWidget* m_dl2_system_1;
    SystemWidget* m_dl2_system_2;
    SystemWidget* m_es_system;

    QSize m_system_size{120, 80};

    QPoint m_first_column{15, 100};
    QPoint m_second_column{215, 100};

    int m_vertical_space{10};

    void deactivateSystemWidgets();
    bool changeLayout() const;

public:
    SetupMenuScreen(QWidget* parent);

protected:
    void setupLayout();
    void buttonClicked();

signals:
    void layoutChanged(SystemEnum system);

protected slots:
    void dl1SystemPressed();
    void dl2System1Pressed();
    void dl2System2Pressed();
    void esSystemPressed();

    // QWidget interface
protected:
    void showEvent(QShowEvent*);
};

#endif // SETUPMENUSCREEN_H
