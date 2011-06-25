#include "viewpaneltabs.h"

#include "viewpaneltab.h"

#include <QKeyEvent>
#include <QDir>

ViewPanelTabs::ViewPanelTabs(QWidget *parent) : QTabWidget(parent), m_pressCtrl(false)
{
    ViewPanelTab* first = NULL;

    addTab(first    = new ViewPanelTab, "123");

    QWidget* w = currentWidget();

    if(w != NULL)
        setFocusProxy(w);

    connect(this,   SIGNAL(currentChanged(int)),            this, SLOT(setCurrentIndex(int)));
    connect(first,  SIGNAL(tabPressedSignal()),             this, SLOT(tabPressedSlot()));
    connect(first,  SIGNAL(changeDirSignal(const QString&)),this, SLOT(changeDirSlot(const QString&)));

    changeDirSlot(first->path());
}

void ViewPanelTabs::setCurrentIndex(int index)
{
    QWidget* w = widget(index);

    if(w == NULL)
        return;

    ViewPanelTab* tab = dynamic_cast<ViewPanelTab*>(w);
    Q_ASSERT(tab);

    setFocusProxy(tab);
    tab->setFocus();
}

void ViewPanelTabs::tabPressedSlot()
{
    if(m_pressCtrl)
        changeTab();
    else
        emit tabPressedSignal();
}

void ViewPanelTabs::setDir(const QString& dir)
{
    QWidget* w = currentWidget();
    if(w == NULL)
        return;

    ViewPanelTab* vp = dynamic_cast<ViewPanelTab*>(w);
    if(vp == NULL)
        return;

    vp->changeDir(dir);
    changeDirSlot(dir);
}

void ViewPanelTabs::keyPressEvent(QKeyEvent *event)
{
    if(event == NULL)
        return QTabWidget::keyPressEvent(event);

    switch(event->key())
    {
    case Qt::Key_Control:
        m_pressCtrl = true;
        break;

    case Qt::Key_T:
        if(m_pressCtrl)
            createTab();
        break;

    case Qt::Key_W:
        if(m_pressCtrl)
            closeTab();
        break;

    default:
        QTabWidget::keyPressEvent(event);
    }

    event->ignore();
}

void ViewPanelTabs::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control)
        m_pressCtrl = false;

    event->ignore();
}

void ViewPanelTabs::changeTab()
{
    int idx = (currentIndex() + 1) % count();
    setCurrentWidget(widget(idx));
}

void ViewPanelTabs::changeDirSlot(const QString& path)
{
    QDir dir(path);

    QString dirName = dir.dirName();
    if(dirName.isEmpty())
    {
        QFileInfoList list = dir.drives();

        QFileInfoList::iterator i = qFind(list.begin(), list.end(), QFileInfo(path));
        if(i != list.end())
            dirName = path;
        else
            Q_ASSERT(false);
    }

    setTabText(currentIndex(), dirName);
}

void ViewPanelTabs::createTab()
{
    ViewPanelTab* vp = currentViewPanelTab();
    Q_ASSERT(vp);

    ViewPanelTab* new_vp = NULL;

    addTab(new_vp = new ViewPanelTab, "");
    setCurrentWidget(new_vp);

    setDir(vp->path());
}

void ViewPanelTabs::closeTab()
{
    if(count() == 1)
        return;

    removeTab(currentIndex());
}

ViewPanelTab* ViewPanelTabs::currentViewPanelTab()
{
    QWidget* w = currentWidget();
    if(w == NULL)
        return NULL;

    return dynamic_cast<ViewPanelTab*>(w);
}
