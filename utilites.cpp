#include "utilites.h"

#include <QMessageBox>

void not_implemented(const QString& message, QWidget* parent)
{
    QMessageBox mb(parent);

    if(message.isEmpty())
        mb.setText("Not implemented");
    else
        mb.setText(message);

    mb.setModal(true);
    mb.exec();
}
