#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QWidget>

class ComboBox;
class QLabel;

class CommandLine : public QWidget
{
    Q_OBJECT
public:
    explicit        CommandLine(QWidget *parent, QWidget* mainPanel);

private:
    ComboBox*       m_edit;
    QLabel*         m_label;
    QWidget*        m_mainPanel;
};

#endif // COMMANDLINE_H
