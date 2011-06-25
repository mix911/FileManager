#include "combobox.h"

#include <QEvent>
#include <QKeyEvent>
#include <QCoreApplication>

class TabEvent : public QEvent
{
public:
    TabEvent() : QEvent(static_cast<QEvent::Type>(QEvent::User + 1))
    {

    }
};

ComboBox::ComboBox(QWidget* parent, QWidget* mainPanel) :   QComboBox(parent), m_mainPanel(mainPanel)
{
}

bool ComboBox::event(QEvent *event)
{
    if(event == NULL || event->type() != QEvent::KeyPress)
        return QWidget::event(event);

    QKeyEvent* key_event = dynamic_cast<QKeyEvent*>(event);
    if(key_event == NULL || key_event->key() != Qt::Key_Tab)
        return QWidget::event(event);

    TabEvent evt;
    QCoreApplication::sendEvent(m_mainPanel, &evt);

    return true;
}
