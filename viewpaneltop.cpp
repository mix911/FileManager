#include "viewpaneltop.h"

#include "utilites.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QDir>

ViewPanelTop::ViewPanelTop(QWidget* parent, QWidget* mainPanel) : QWidget(parent), m_mainPanel(mainPanel)
{
    QHBoxLayout* layout = new QHBoxLayout;

    layout->addWidget(m_device  = new QComboBox);
    layout->addWidget(m_info    = new QLabel("[_none_] 4 249 988 k of 34 599 416 free"));
    layout->setStretch(1, 1);
    layout->addWidget(m_toRoot  = new QToolButton);
    layout->addWidget(m_toUp    = new QToolButton);

    m_device->setContentsMargins(0, 0, 10, 0);
    m_toRoot->setContentsMargins(0, 0, 0, 0);
    m_toUp->setContentsMargins(0, 0, 0, 0);

    m_device->setMinimumWidth(70);

    m_device->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    m_toRoot->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    m_toUp->setSizePolicy(QSizePolicy::Fixed,   QSizePolicy::Minimum);

    QSize btnSize(20, 20);
    \
    m_toRoot->resize(btnSize);
    m_toUp->resize(btnSize);

    m_toRoot->setText("\\");
    m_toUp->setText("..");

    layout->setMargin(0);

    QFileInfoList list = QDir::drives();

    foreach(const QFileInfo& device, list)
        m_device->addItem(device.filePath());

    connect(m_device,   SIGNAL(currentIndexChanged(QString)),   this, SLOT(selectDeviceSlot(QString)));
    connect(m_toUp,     SIGNAL(pressed()),                      this, SLOT(goUpSlot()));
    connect(m_toRoot,   SIGNAL(pressed()),                      this, SLOT(goRootSlot()));

    setLayout(layout);
}

void ViewPanelTop::selectDeviceSlot(QString val)
{
    emit selectDeviceSignal(val);
}

void ViewPanelTop::goUpSlot()
{
    not_implemented("Go up");
}

void ViewPanelTop::goRootSlot()
{
    not_implemented("Go root");
}

void ViewPanelTop::setDir(const QString& path)
{
    QDir dir(path);
    while(dir.cdUp())
    {
    }

    int i = m_device->findText(dir.path());
    if(i >= 0)
        m_device->setCurrentIndex(i);
}

void ViewPanelTop::showDeviceSelector()
{
    m_device->showPopup();
}
