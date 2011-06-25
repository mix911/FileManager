#ifndef OVERVIEWPANEL_H
#define OVERVIEWPANEL_H

#include <QWidget>

class ViewPanel;

class OverviewPanel : public QWidget
{
    Q_OBJECT
public:
    explicit OverviewPanel(QWidget *parent = 0);

private:
    ViewPanel*  m_view;
};

#endif // OVERVIEWPANEL_H
