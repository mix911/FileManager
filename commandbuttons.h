#ifndef COMMANDBUTTONS_H
#define COMMANDBUTTONS_H

#include <QWidget>

class QPushButton;

class CommandButtons : public QWidget
{
    Q_OBJECT
public:
    explicit        CommandButtons(QWidget *parent = 0);

    enum EButton
    {
        BUTTON_VIEW,
        BUTTON_EDIT,
        BUTTON_COPY,
        BUTTON_MOVE,
        BUTTON_MK_DIR,
        BUTTON_DELETE,
        BUTTON_EXIT
    };

signals:
    void            pushButtonSignal(int button);

public slots:
    void            pushView();
    void            pushEdit();
    void            pushCopy();
    void            pushMove();
    void            pushMkDir();
    void            pushDelete();
    void            pushExit();

private:
    QPushButton*    m_view;
    QPushButton*    m_edit;
    QPushButton*    m_copy;
    QPushButton*    m_move;
    QPushButton*    m_mkdir;
    QPushButton*    m_delete;
    QPushButton*    m_exit;
};

#endif // COMMANDBUTTONS_H
