#include "tableview.h"

#include "viewpaneltab.h"
#include "tableheaderview.h"

#include <QResizeEvent>

TableView::TableView(QWidget* parent) : QTableView(parent), m_ctrlPress(false)
{
    setShowGrid(false);
    verticalHeader()->hide();

    setTabKeyNavigation(false);
    setAlternatingRowColors(true);
    setWordWrap(false);

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setHorizontalHeader(m_headers = new TableHeaderView(Qt::Horizontal, this));

    connect(this, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(doubleClickedSlot(const QModelIndex&)));
}

void TableView::keyPressEvent(QKeyEvent *event)
{
    if(event == NULL)
        return;

    switch(event->key())
    {
    case Qt::Key_Return:
        openItem(currentIndex());
        break;

    case Qt::Key_Backspace:
        cdUp();
        break;

    default:
        QTableView::keyPressEvent(event);
        break;
    }

    event->ignore();
}

bool TableView::event(QEvent *event)
{
    if(event->type() != QEvent::KeyPress)
        return QTableView::event(event);

    QKeyEvent* key_event = dynamic_cast<QKeyEvent*>(event);
    if(key_event==NULL)
        return QTableView::event(event);

    if(key_event->key() != Qt::Key_Tab)
        return QTableView::event(event);

    QWidget* p = parentWidget();
    if(p == NULL)
        return QTableView::event(event);

    ViewPanelTab* vp = dynamic_cast<ViewPanelTab*>(p);
    if(vp == NULL)
        return QTableView::event(event);

    if(key_event->modifiers() == Qt::NoModifier)
        vp->tabPressed();
    else
        return QTableView::event(event);

    return true;
}

void TableView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QTableView::mouseDoubleClickEvent(event);
    openItem(indexAt(event->pos()));
}

void TableView::keyReleaseEvent(QKeyEvent* event)
{
    if(event == NULL)
        return QTableView::keyReleaseEvent(event);

    event->ignore();
}

void TableView::openItem(const QModelIndex &index)
{
    QWidget* w = parentWidget();
    if(w == NULL)
        return;

    ViewPanelTab* vp = dynamic_cast<ViewPanelTab*>(w);
    if(vp == NULL)
        return;

    setCurrentIndex(model()->index(0, 0, rootIndex()));

    model()->removeRows(0, model()->rowCount());
    vp->openItem(index.row());
}

void TableView::cdUp()
{
    QWidget* w = parentWidget();
    if(w == NULL)
        return;

    ViewPanelTab* vp = dynamic_cast<ViewPanelTab*>(w);
    if(vp == NULL)
        return;

    setCurrentIndex(model()->index(0, 0, rootIndex()));

    model()->removeRows(0, model()->rowCount());
    vp->cdUp();
}

void TableView::resizeEvent(QResizeEvent *event)
{
    QTableView::resizeEvent(event);

    int w = 0;
    for(int i = 1; i < model()->columnCount(); ++i)
         w += columnWidth(i);

    setColumnWidth(0, width() - w - 20);
}

void TableView::setHeaders(const QVector<EHeaders> &headers)
{
    m_headers->setHeaders(headers);
}
