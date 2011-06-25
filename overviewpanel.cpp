#include "overviewpanel.h"
#include "viewpanel.h"

#include <QVBoxLayout>

OverviewPanel::OverviewPanel(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_view = new ViewPanel(this));

    setFocusProxy(m_view);

    setLayout(layout);
}
