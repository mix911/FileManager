#ifndef VIEWPANEL_H
#define VIEWPANEL_H

#include <QWidget>

class ViewPanelTop;
class ViewPanelTabs;
class ViewPanelBottom;

class ViewPanel : public QWidget
{
    Q_OBJECT
public:
    explicit            ViewPanel(QWidget *parent = 0);

    void                setDir(const QString& dir);
    void                showDeviceSelector();

signals:
    void                tabPressedSignal();

public slots:
    void                tabPressedSlot();
    void                selectDeviceSlot(QString val);

private:
    ViewPanelTop*       m_top;
    ViewPanelTabs*      m_tabs;
    ViewPanelBottom*    m_bottom;
};

#endif // VIEWPANEL_H
