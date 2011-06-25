#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QWidget>

#include "commandbuttons.h"

class TwoPanel;
class CommandLine;

class QKeyEvent;

class MainPanel : public QWidget
{
    Q_OBJECT
public:
    explicit            MainPanel(QWidget *parent = 0);

    virtual void        keyPressEvent(QKeyEvent* event);
    virtual bool        event(QEvent *event);

signals:

public slots:
    void                pressButtonSlot(int button);

private:
    void                viewCommand();
    void                editCommand();
    void                copyCommand();
    void                moveCommand();
    void                mkdirCommand();
    void                deleteCommand();
    void                exitCommand();

private:
    TwoPanel*           m_two;
    CommandLine*        m_line;
    CommandButtons*     m_buttons;
};

#endif // MAINPANEL_H
