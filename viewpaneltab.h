#ifndef VIEWPANELTAB_H
#define VIEWPANELTAB_H

#include <QWidget>

class QAbstractItemView;
class FileSystemModel;

class ViewPanelTab : public QWidget
{
    Q_OBJECT
public:
    explicit            ViewPanelTab(QWidget *parent = 0);

    void                tabPressed();
    void                changeDir(const QString& dir);
    void                openItem(int row);
    QString             path()  const;
    void                cdUp();

signals:
    void                tabPressedSignal();
    void                changeDirSignal(const QString& dir);

public slots:

private:
    QAbstractItemView*  m_view;
    FileSystemModel*    m_model;
};

#endif // VIEWPANELTAB_H
