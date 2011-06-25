#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>

class ComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit        ComboBox(QWidget* parent, QWidget* mainPanel);

    virtual bool    event(QEvent *event);

signals:

public slots:


private:
    QWidget*        m_mainPanel;
};

#endif // COMBOBOX_H
