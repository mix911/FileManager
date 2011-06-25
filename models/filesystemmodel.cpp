#include "filesystemmodel.h"

#include "filesystemnode.h"

#include <QVariant>
#include <QDir>

QVector<QString>    FileSystemModel::m_allColumns;
bool                FileSystemModel::m_created      = false;

FileSystemModel::FileSystemModel(QObject *parent) : QAbstractItemModel(parent)
{
    m_columns.reserve(HEADER_COUNT);

    m_columns.push_back(HEADER_NAME);
    m_columns.push_back(HEADER_EXT);
    m_columns.push_back(HEADER_SIZE);
    m_columns.push_back(HEADER_RWX);

    if(!m_created)
    {
        m_created = true;

        m_allColumns.push_back("Name");
        m_allColumns.push_back("Ext");
        m_allColumns.push_back("Size");
        m_allColumns.push_back("Type");
        m_allColumns.push_back("Date");
        m_allColumns.push_back("rwx");
        m_allColumns.push_back("Perm");
        m_allColumns.push_back("Owner");
        m_allColumns.push_back("Group");
    }
}

QModelIndex FileSystemModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!parent.isValid())
        return createIndex(0, 0, const_cast<FileSystemNode*>(m_fileSystem.defaultNode()));

    if(row < 0 || column < 0 || row >= rowCount(parent) || column >= columnCount(parent))
        return QModelIndex();

    const FileSystemNode* parendNode = index2Node(parent);

    const FileSystemNode* childNode = parendNode->child(row);
    Q_ASSERT(childNode);

    if(childNode==NULL)
        childNode = m_fileSystem.defaultNode();

    return createIndex(row, column, const_cast<FileSystemNode*>(childNode));
}

int FileSystemModel::rowCount(const QModelIndex &parent) const
{
    // Only first column have children
    if(parent.column() > 0)
        return 0;
    return index2Node(parent)->childrenCount();
}

int FileSystemModel::columnCount(const QModelIndex &parent) const
{
    // Only first column have children
    if(parent.column() > 0)
        return 0;
    return m_columns.size();
}

const FileSystemNode* FileSystemModel::index2Node(const QModelIndex &index) const
{
    if(index.isValid())
        return static_cast<const FileSystemNode*>(index.internalPointer());
    return m_fileSystem.defaultNode();
}

QModelIndex FileSystemModel::setDir(const QString &path)
{
    m_fileSystem.setDir(path);

    const FileSystemNode* node      = m_fileSystem.defaultNode();
    const FileSystemNode* parentNode= node->parent();

    int row = 0;
    if(parentNode)
        row = parentNode->index(node->path());

    emit layoutChanged();

    return createIndex(row, 0, const_cast<FileSystemNode*>(node));
}

QModelIndex FileSystemModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
        return QModelIndex();

    const FileSystemNode* node = index2Node(child);

    if(node==NULL || !node->isValide())
        return QModelIndex();

    const FileSystemNode* parent = node->parent();
    if(parent==0 || !parent->isValide())
        return QModelIndex();

    int row = 0;

    const FileSystemNode* grandparent = parent->parent();
    if(grandparent != NULL && grandparent->isValide())
        row = grandparent->index(parent->path());

    if(row == -1)
        return QModelIndex();

    return createIndex(row, 0, const_cast<FileSystemNode*>(node->parent()));
}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{
    if(index.column() > m_columns.size())
        return QVariant::Invalid;

    switch(role)
    {
    case Qt::DisplayRole:
        return displayRole(index);

    case Qt::DecorationRole:
        return decorationRole(index);

    default:
        return QVariant::Invalid;
    }
}

QVariant FileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant::Invalid;

    if(orientation == Qt::Vertical)
        return "";

    if(m_columns.size() < section)
        return QVariant::Invalid;

    return m_allColumns[m_columns[section]];
}

QVariant FileSystemModel::displayRole(const QModelIndex &index) const
{
    const FileSystemNode* node = index2Node(index);

    if(node==NULL || !node->isValide())
        return QVariant::Invalid;

    switch(m_columns[index.column()])
    {
    case HEADER_NAME:
        return node->fileName();

    case HEADER_EXT:
        return node->fileExt();

    case HEADER_SIZE:
        return node->fileSize();

    case HEADER_TYPE:
        return node->fileType();

    case HEADER_DATE:
        return node->fileDate();

    case HEADER_RWX:
        return node->filePermExt();

    case HEADER_PERM:
        return node->filePerm();

    case HEADER_OWNER:
        return node->fileOwner();

    case HEADER_GROUP:
        return node->fileGroup();

    case HEADER_COUNT:
    default:
        return QVariant::Invalid;
    }
}

QVariant FileSystemModel::decorationRole(const QModelIndex &index)  const
{
    if(m_columns.size() < index.column() || m_columns.size() < 0 || m_columns[index.column()] != HEADER_NAME)
        return QVariant::Invalid;


    const FileSystemNode* node = index2Node(index);

    if(node==NULL || !node->isValide())
        return QVariant::Invalid;

    if(node->isDir())
        return m_iconProvider.icon(QFileIconProvider::Folder);
    else
        return m_iconProvider.icon(QFileInfo(node->path()));
}

void FileSystemModel::openRow(int row)
{
    const FileSystemNode* root = m_fileSystem.defaultNode();
    if(root == NULL)
        return;

    const FileSystemNode* node = root->child(row);
    if(node == NULL)
        return;

    if(!node->isDir())
        return;

    QString name = node->fileName();
    QString path = node->path();

    if(name == "..")
    {
        QDir dir(path);
        path = dir.absolutePath();
    }

    setDir(path);
}

QString FileSystemModel::path() const
{
    return m_fileSystem.rootNode()->path();
}

QVector<EHeaders> FileSystemModel::headers() const
{
    return m_columns;
}

void FileSystemModel::cdUp()
{
    const FileSystemNode* root = m_fileSystem.defaultNode();
    if(root == NULL)
        return;

    const FileSystemNode* node = root->child("..");
    if(node == NULL)
        return;

    if(!node->isDir())
        return;

    setDir(QDir(node->path()).absolutePath());
}
