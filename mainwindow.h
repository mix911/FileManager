#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class MainPanel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
                            MainWindow(QWidget *parent = 0);
                           ~MainWindow();

private:
    void                    createMenus();
    void                    createToolbar();
private:
    MainPanel*              m_panel;
    QToolBar*               m_toolbar;
};

#endif // MAINWINDOW_H
