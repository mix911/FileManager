#ifndef VIEWPANELTABS_H
#define VIEWPANELTABS_H

#include <QTabWidget>

class ViewPanelTab;

class ViewPanelTabs : public QTabWidget
{
    Q_OBJECT
public:
    explicit        ViewPanelTabs(QWidget *parent = 0);

    void            setDir(const QString& dir);

    virtual void    keyPressEvent(QKeyEvent* event);
    virtual void    keyReleaseEvent(QKeyEvent* event);

signals:
    void            tabPressedSignal();

public slots:
    void            setCurrentIndex(int index);
    void            tabPressedSlot();
    void            changeDirSlot(const QString& path);

private:
    void            changeTab();
    void            createTab();
    void            closeTab();
    ViewPanelTab*   currentViewPanelTab();

private:
    bool            m_pressCtrl;
};

#endif // VIEWPANELTABS_H
