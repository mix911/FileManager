#include "viewpanelbottom.h"

#include <QLabel>
#include <QHBoxLayout>

ViewPanelBottom::ViewPanelBottom(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout*    layout = new QHBoxLayout;

    layout->addWidget(m_info = new QLabel("0 out 17, 0 B (0) out of 80,0 KiB (81 920)"));

    layout->setMargin(0);
    setLayout(layout);
}
