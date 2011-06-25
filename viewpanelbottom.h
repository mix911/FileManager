#ifndef VIEWPANELBOTTOM_H
#define VIEWPANELBOTTOM_H

#include <QWidget>

class QLabel;

class ViewPanelBottom : public QWidget
{
    Q_OBJECT
public:
    explicit    ViewPanelBottom(QWidget *parent = 0);

signals:

public slots:

private:
    QLabel*     m_info;
};

#endif // VIEWPANELBOTTOM_H
