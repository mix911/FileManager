#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>
#include <QKeyEvent>

#include "general.h"

struct KeySignal
{
    Qt::Key key;
};

class TableHeaderView;

class TableView : public QTableView
{
public:
    explicit        TableView(QWidget* parent = NULL);

    virtual void    keyPressEvent(QKeyEvent* event);
    virtual void    keyReleaseEvent(QKeyEvent* event);
    virtual bool    event(QEvent *event);
    virtual void    mouseDoubleClickEvent(QMouseEvent *event);
    virtual void    resizeEvent(QResizeEvent *event);

    void            setHeaders(const QVector<EHeaders>& headers);

private:

    void            openItem(const QModelIndex& index);
    void            cdUp();

private:
    bool                m_ctrlPress;
    TableHeaderView*    m_headers;
};

#endif // TABLEVIEW_H
