#include "tableheaderview.h"

#include <QMouseEvent>
#include <QMenu>

TableHeaderView::TableHeaderView(Qt::Orientation orientaion, QWidget* parent) : QHeaderView(orientaion, parent)
{
    m_contextMenu = new QMenu("title", this);

    (m_name = m_contextMenu->addAction(tr("Name")))->setCheckable(true);

//    m_actions.insert(HEADER_NAME, m_name);
//    m_actions.insert(HEADER_EXT,  m_ext);
//    m_actions.insert(HEADER_SIZE, m_size);
//    m_actions.insert(HEADER_TYPE, m_type);
//    m_actions.insert(HEADER_DATE, m_date);
//    m_actions.insert(HEADER_RWX,  m_rwx);
//    m_actions.insert(HEADER_PERM, m_perm);
//    m_actions.insert(HEADER_OWNER,m_owner);
//    m_actions.insert(HEADER_GROUP,m_group);

//    connect(m_name, SIGNAL(toggled(bool)), this, SLOT(actionNameSlot(bool)));
//    connect(m_ext,  SIGNAL(toggled(bool)), this, SLOT(actionExtSlot(bool)));
//    connect(m_size, SIGNAL(toggled(bool)), this, SLOT(actionSizeSlot(bool)));
//    connect(m_type, SIGNAL(toggled(bool)), this, SLOT(actionTypeSlot(bool)));
//    connect(m_date, SIGNAL(toggled(bool)), this, SLOT(actionDateSlot(bool)));
//    connect(m_rwx,  SIGNAL(toggled(bool)), this, SLOT(actionRwxSlot(bool)));
//    connect(m_perm, SIGNAL(toggled(bool)), this, SLOT(actionPermSlot(bool)));
//    connect(m_owner,SIGNAL(toggled(bool)), this, SLOT(actionOwnerSlot(bool)));
//    connect(m_group,SIGNAL(toggled(bool)), this, SLOT(actionGroupSlot(bool)));
}

void TableHeaderView::mousePressEvent(QMouseEvent *e)
{
    if(e == NULL)
        return QHeaderView::mousePressEvent(e);

    QHeaderView::mousePressEvent(e);

    if(e->button() != Qt::RightButton)
        return;

    m_contextMenu->popup(e->globalPos());
}

void TableHeaderView::addHeadersCheckBox(const QString &name)
{
    m_contextMenu->addAction(name)->setCheckable(true);
}

void TableHeaderView::setHeaders(const QVector<EHeaders>& headers)
{

}

void TableHeaderView::actionNameSlot(bool val)
{
}

void TableHeaderView::actionExtSlot(bool val)
{
}

void TableHeaderView::actionSizeSlot(bool val)
{
}

void TableHeaderView::actionTypeSlot(bool val)
{
}

void TableHeaderView::actionDateSlot(bool val)
{
}

void TableHeaderView::actionRwxSlot(bool val)
{
}

void TableHeaderView::actionPermSlot(bool val)
{
}

void TableHeaderView::actionOwnerSlot(bool val)
{
}

void TableHeaderView::actionGroupSlot(bool val)
{
}
