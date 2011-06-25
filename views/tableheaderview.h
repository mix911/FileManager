#ifndef TABLEHEADERVIEW_H
#define TABLEHEADERVIEW_H

#include <QHeaderView>

#include "general.h"

class TableHeaderView : public QHeaderView
{
public:
    explicit        TableHeaderView(Qt::Orientation orientaion, QWidget* parent = 0);

    virtual void    mousePressEvent(QMouseEvent *e);

    void            addHeadersCheckBox(const QString& name);
    void            setHeaders(const QVector<EHeaders>& headers);

public slots:
    void            triggeredHeaderSlog(QAction* a);

    void            actionNameSlot(bool val);
    void            actionExtSlot(bool val);
    void            actionSizeSlot(bool val);
    void            actionTypeSlot(bool val);
    void            actionDateSlot(bool val);
    void            actionRwxSlot(bool val);
    void            actionPermSlot(bool val);
    void            actionOwnerSlot(bool val);
    void            actionGroupSlot(bool val);

private:
    QMenu*          m_contextMenu;

    QAction*        m_name;
    QAction*        m_ext;
    QAction*        m_size;
    QAction*        m_type;
    QAction*        m_date;
    QAction*        m_rwx;
    QAction*        m_perm;
    QAction*        m_owner;
    QAction*        m_group;
    QMap<EPanels, QAction*> m_actions;
};

#endif // TABLEHEADERVIEW_H
