#include "twopanel.h"
#include "viewpanel.h"

#include <QSplitter>
#include <QVBoxLayout>
#include <QDir>
#include <QKeyEvent>

TwoPanel::TwoPanel(QWidget *parent) : QWidget(parent), m_pressAlt(false)
{
    QVBoxLayout* layout = new QVBoxLayout;

    m_splitter = new QSplitter(Qt::Horizontal, this);

    m_splitter->setContentsMargins(0, 0, 0, 0);

    m_splitter->addWidget(m_left    = new ViewPanel(m_splitter));
    m_splitter->addWidget(m_right   = new ViewPanel(m_splitter));

    m_left->setDir(QDir::rootPath());
    m_right->setDir(QDir::rootPath());

    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_splitter);

    connect(m_left, SIGNAL(tabPressedSignal()), this, SLOT(tabPressedSlot()));
    connect(m_right,SIGNAL(tabPressedSignal()), this, SLOT(tabPressedSlot()));

    selectPanel(PANEL_LEFT);

    setLayout(layout);
}

void TwoPanel::selectPanel(TwoPanel::EPanel panel)
{
    m_selectedPanel = panel;

    if(panel == PANEL_LEFT)
        m_left->setFocus();
    else
        m_right->setFocus();
}

void TwoPanel::tabPressedSlot()
{
    if(m_selectedPanel==PANEL_LEFT)
        selectPanel(PANEL_RIGHT);
    else
        selectPanel(PANEL_LEFT);
}

void TwoPanel::keyPressEvent(QKeyEvent *event)
{
    if(event == NULL)
        return QWidget::keyPressEvent(event);

    switch(event->key())
    {
    case Qt::Key_Alt:
        m_pressAlt = true;
        event->ignore();
        break;

    case Qt::Key_1:
        selectPanel(PANEL_LEFT);
        showDeviceSelector(PANEL_LEFT);
        break;

    case Qt::Key_2:
        selectPanel(PANEL_RIGHT);
        showDeviceSelector(PANEL_RIGHT);
        break;

    default:
        QWidget::keyPressEvent(event);
        event->ignore();
        break;
    }
}

void TwoPanel::keyReleaseEvent(QKeyEvent *event)
{
    if(event == NULL)
        return QWidget::keyReleaseEvent(event);

    switch(event->key())
    {
    case Qt::Key_Alt:
        m_pressAlt = false;
        break;

    default:
        QWidget::keyReleaseEvent(event);
        break;
    }

    event->ignore();
}

void TwoPanel::showDeviceSelector(TwoPanel::EPanel panel)
{
    viewPanel(panel)->showDeviceSelector();
}

ViewPanel* TwoPanel::viewPanel(TwoPanel::EPanel panel)
{
    if(panel == PANEL_LEFT)
        return m_left;
    else
        return m_right;
}
