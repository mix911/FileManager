#ifndef TWOPANEL_H
#define TWOPANEL_H

#include <QWidget>

class QSplitter;
class ViewPanel;

class TwoPanel : public QWidget
{
    Q_OBJECT
public:
    enum EPanel
    {
        PANEL_LEFT,
        PANEL_RIGHT
    };

public:
    explicit        TwoPanel(QWidget *parent = 0);

    virtual void    keyPressEvent(QKeyEvent* event);
    virtual void    keyReleaseEvent(QKeyEvent* event);

    void            selectPanel(EPanel panel);

public slots:
    void            tabPressedSlot();

private:
    void            showDeviceSelector(EPanel panel);
    ViewPanel*      viewPanel(EPanel panel);

private:
    QSplitter*      m_splitter;
    ViewPanel*      m_left;
    ViewPanel*      m_right;
    EPanel          m_selectedPanel;
    bool            m_pressAlt;
};

#endif // TWOPANEL_H
