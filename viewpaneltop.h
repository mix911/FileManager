#ifndef VIEWPANELTOP_H
#define VIEWPANELTOP_H

#include <QWidget>

class QComboBox;
class QLabel;
class QPushButton;
class QToolButton;

class ViewPanelTop : public QWidget
{
    Q_OBJECT
public:
    explicit        ViewPanelTop(QWidget* parent, QWidget* mainPanel);

    void            setDir(const QString& path);
    void            showDeviceSelector();

signals:
    void            selectDeviceSignal(QString val);

public slots:
    void            selectDeviceSlot(QString val);
    void            goUpSlot();
    void            goRootSlot();

private:
    QComboBox*      m_device;
    QLabel*         m_info;
    QToolButton*    m_toRoot;
    QToolButton*    m_toUp;
    QWidget*        m_mainPanel;
};

#endif // VIEWPANELTOP_H
