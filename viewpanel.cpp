#include "viewpanel.h"

#include "viewpaneltop.h"
#include "viewpaneltab.h"
#include "viewpaneltabs.h"
#include "viewpanelbottom.h"

#include "utilites.h"

#include <QVBoxLayout>
#include <QDir>

ViewPanel::ViewPanel(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(m_top     = new ViewPanelTop(this, this));
    layout->addWidget(m_tabs    = new ViewPanelTabs);
    layout->addWidget(m_bottom  = new ViewPanelBottom);

    m_top->setFocusPolicy(Qt::ClickFocus);
    m_bottom->setFocusPolicy(Qt::ClickFocus);

    setFocusProxy(m_tabs);

    m_top->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    m_tabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(m_tabs, SIGNAL(tabPressedSignal()), this, SLOT(tabPressedSlot()));
    connect(m_top,  SIGNAL(selectDeviceSignal(QString)), this, SLOT(selectDeviceSlot(QString)));

    setLayout(layout);
}

void ViewPanel::tabPressedSlot()
{
    emit tabPressedSignal();
}

void ViewPanel::selectDeviceSlot(QString val)
{
    m_tabs->setDir(val);
}

void ViewPanel::setDir(const QString &path)
{
    m_tabs->setDir(path);
    m_top->setDir(path);
}

void ViewPanel::showDeviceSelector()
{
    m_top->showDeviceSelector();
}
