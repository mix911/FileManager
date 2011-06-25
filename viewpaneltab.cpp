#include "viewpaneltab.h"

#include "views/tableview.h"
#include "views/treeview.h"

#include "models/filesystemmodel.h"

#include <QVBoxLayout>
#include <QDir>

ViewPanelTab::ViewPanelTab(QWidget *parent) : QWidget(parent)
{
    TableView* table = NULL;

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);

    m_model = new FileSystemModel;
    m_model->setDir(QDir::rootPath());

    layout->addWidget(m_view = table = new TableView);

    m_view->setModel(m_model);
    m_view->setRootIndex(m_model->index(0, 0, QModelIndex()));

    table->setHeaders(m_model->headers());

    setFocusProxy(m_view);

    setLayout(layout);
}

void ViewPanelTab::tabPressed()
{
    emit tabPressedSignal();
}

void ViewPanelTab::changeDir(const QString& dir)
{
    m_model->setDir(dir);
}

void ViewPanelTab::openItem(int row)
{
    m_model->openRow(row);
    emit changeDirSignal(m_model->path());
}

QString ViewPanelTab::path() const
{
    return m_model->path();
}

void ViewPanelTab::cdUp()
{
    m_model->cdUp();
}
