#include "mainwindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QToolBar>

#include "mainpanel.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_panel = new MainPanel(this);

    setCentralWidget(m_panel);
    m_panel->setContentsMargins(0, 0, 0, 0);
    setContentsMargins(0, 0, 0, 0);

    createMenus();
    createToolbar();

    resize(800, 600);
    showMaximized();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createMenus()
{
    menuBar()->addMenu(tr("&Files"));
    menuBar()->addMenu(tr("&Help"));
}

void MainWindow::createToolbar()
{
    m_toolbar = addToolBar("Hello");

    m_toolbar->addAction(QIcon("./icons/back.ico"),   tr("Back"));
    m_toolbar->addAction(QIcon("./icons/forward.ico"),tr("Forward"));
}
