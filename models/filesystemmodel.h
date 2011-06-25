#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QAbstractItemModel>
#include <QVector>
#include <QFileIconProvider>

#include "filesystem.h"
#include "general.h"

class QFileSystemModel;
class FileSystemNode;

class FileSystemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit                FileSystemModel(QObject *parent = 0);

    // QAbstractItemModel interface
    virtual QModelIndex     index(int row, int column, const QModelIndex &parent) const;
    virtual int             rowCount(const QModelIndex &parent) const;
    virtual int             columnCount(const QModelIndex &parent) const;
    virtual QModelIndex     parent(const QModelIndex &child) const;
    virtual QVariant        data(const QModelIndex &index, int role) const;
    virtual QVariant        headerData(int section, Qt::Orientation orientation, int role) const;

    // Additional interface
    QModelIndex                     setDir(const QString& path);
    void                            openRow(int row);
    void                            cdUp();
    QString                         path()  const;
    QVector<EHeaders>               headers()   const;

private:

    const FileSystemNode*           index2Node(const QModelIndex& index)    const;
    QVariant                        displayRole(const QModelIndex& index)   const;
    QVariant                        decorationRole(const QModelIndex& index)const;

private:
    FileSystem              m_fileSystem;
    QVector<EHeaders>       m_columns;
    QFileIconProvider       m_iconProvider;

    static QVector<QString> m_allColumns;
    static bool             m_created;
};

#endif // FILESYSTEMMODEL_H
