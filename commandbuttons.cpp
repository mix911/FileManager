#include "commandbuttons.h"

#include <QPushButton>
#include <QHBoxLayout>

CommandButtons::CommandButtons(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout;

    layout->addWidget(m_view    = new QPushButton(tr("F3 View")));
    layout->addWidget(m_edit    = new QPushButton(tr("F4 Edit")));
    layout->addWidget(m_copy    = new QPushButton(tr("F5 Copy")));
    layout->addWidget(m_move    = new QPushButton(tr("F6 Move")));
    layout->addWidget(m_mkdir   = new QPushButton(tr("F7 New Folder")));
    layout->addWidget(m_delete  = new QPushButton(tr("F8 Delete")));
    layout->addWidget(m_exit    = new QPushButton(tr("Alt+F4 Exit")));

    QMargins margins(0, 0, 0, 0);

    m_view->setContentsMargins(margins);
    m_edit->setContentsMargins(margins);
    m_copy->setContentsMargins(margins);
    m_move->setContentsMargins(margins);
    m_mkdir->setContentsMargins(margins);
    m_delete->setContentsMargins(margins);
    m_exit->setContentsMargins(margins);

    layout->setMargin(0);

    setLayout(layout);

    connect(m_view,     SIGNAL(pressed()), this, SLOT(pushView()));
    connect(m_edit,     SIGNAL(pressed()), this, SLOT(pushEdit()));
    connect(m_copy,     SIGNAL(pressed()), this, SLOT(pushCopy()));
    connect(m_move,     SIGNAL(pressed()), this, SLOT(pushMove()));
    connect(m_mkdir,    SIGNAL(pressed()), this, SLOT(pushMkDir()));
    connect(m_delete,   SIGNAL(pressed()), this, SLOT(pushDelete()));
    connect(m_exit,     SIGNAL(pressed()), this, SLOT(pushExit()));
}

void CommandButtons::pushView()
{
    emit pushButtonSignal(BUTTON_VIEW);
}

void CommandButtons::pushEdit()
{
    emit pushButtonSignal(BUTTON_EDIT);
}

void CommandButtons::pushCopy()
{
    emit pushButtonSignal(BUTTON_COPY);
}

void CommandButtons::pushMove()
{
    emit pushButtonSignal(BUTTON_MOVE);
}

void CommandButtons::pushMkDir()
{
    emit pushButtonSignal(BUTTON_MK_DIR);
}

void CommandButtons::pushDelete()
{
    emit pushButtonSignal(BUTTON_DELETE);
}

void CommandButtons::pushExit()
{
    emit pushButtonSignal(BUTTON_EXIT);
}
