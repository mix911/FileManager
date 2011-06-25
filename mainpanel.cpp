#include "mainpanel.h"

#include <QBoxLayout>
#include <QKeyEvent>

#include "twopanel.h"
#include "commandline.h"
#include "utilites.h"

MainPanel::MainPanel(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;

    layout->addWidget(m_two     = new TwoPanel(this));
    layout->addWidget(m_line    = new CommandLine(this, this));
    layout->addWidget(m_buttons = new CommandButtons(this));

    // Setup sizePolicy
    m_two->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    m_line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    m_two->selectPanel(TwoPanel::PANEL_LEFT);

    //
    QMargins margins(0, 0, 0, 0);

    m_two->setContentsMargins(margins);
    m_line->setContentsMargins(margins);
    m_buttons->setContentsMargins(margins);
    layout->setMargin(0);

    setLayout(layout);

    connect(m_buttons, SIGNAL(pushButtonSignal(int)), this, SLOT(pressButtonSlot(int)));
}

void MainPanel::keyPressEvent(QKeyEvent* event)
{
    if(event == NULL)
        return QWidget::keyPressEvent(event);

    switch(event->key())
    {
    case Qt::Key_Left:
    case Qt::Key_Right:
        m_line->setFocus();
        break;

    case Qt::Key_F3:
        viewCommand();
        break;

    case Qt::Key_F4:
        editCommand();
        break;

    case Qt::Key_F5:
        copyCommand();
        break;

    case Qt::Key_F6:
        moveCommand();
        break;

    case Qt::Key_F7:
        mkdirCommand();
        break;

    case Qt::Key_F8:
        deleteCommand();
        break;
    }

    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
        m_line->setFocus();
}

bool MainPanel::event(QEvent *event)
{
    if(event == NULL)
        return QWidget::event(event);

    int type = event->type();

    switch(type)
    {
    case QEvent::User+1:
        m_two->tabPressedSlot();
        break;

    default:
        return QWidget::event(event);
    }
    return true;
}

void MainPanel::pressButtonSlot(int button)
{
    switch(button)
    {
    case CommandButtons::BUTTON_VIEW:
        viewCommand();
        break;

    case CommandButtons::BUTTON_EDIT:
        editCommand();
        break;

    case CommandButtons::BUTTON_COPY:
        copyCommand();
        break;

    case CommandButtons::BUTTON_MOVE:
        moveCommand();
        break;

    case CommandButtons::BUTTON_MK_DIR:
        mkdirCommand();
        break;

    case CommandButtons::BUTTON_DELETE:
        deleteCommand();
        break;

    case CommandButtons::BUTTON_EXIT:
        exitCommand();
        break;
    }
}

void MainPanel::viewCommand()
{
    not_implemented("View", this);
}

void MainPanel::editCommand()
{
    not_implemented("Edit", this);
}

void MainPanel::copyCommand()
{
    not_implemented("Copy", this);
}

void MainPanel::moveCommand()
{
    not_implemented("Move", this);
}

void MainPanel::mkdirCommand()
{
    not_implemented("Make dir", this);
}

void MainPanel::deleteCommand()
{
    not_implemented("Delete", this);
}

void MainPanel::exitCommand()
{
    not_implemented("Exit", this);
}
