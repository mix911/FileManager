#include "commandline.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QEvent>
#include <QKeyEvent>

#include "combobox.h"

CommandLine::CommandLine(QWidget *parent, QWidget* mainPanel) : QWidget(parent), m_mainPanel(mainPanel)
{
    QHBoxLayout* layout = new QHBoxLayout;

    QString path = "/home/mix";

    layout->addWidget(m_label   = new QLabel(path + ">"));
    layout->addWidget(m_edit    = new ComboBox(this, m_mainPanel));

    m_label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    m_edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    m_edit->setEditable(true);

    m_label->setContentsMargins(0, 0, 5, 0);
    m_edit->setContentsMargins(0, 0, 0, 0);
    layout->setMargin(0);

    setFocusProxy(m_edit);

    setLayout(layout);
}
