#include "filesystemnode.h"

#include <QDir>
#include <QFileInfo>
#include <QDateTime>

FileSystemNode* FileSystemNode::createNode(const QString &path)
{
    return new FileSystemNode(NULL, path);
}

FileSystemNode::FileSystemNode() : m_parent(NULL)
{
}

FileSystemNode::FileSystemNode(const FileSystemNode* parent, const QString& path) : m_info(path), m_parent(parent)
{
    m_is_dir    = m_info.isDir();
    m_is_valid  = m_info.exists();

    if(m_is_dir)
    {
        QDir dir(path);
        QFileInfoList list = dir.entryInfoList(QDir::NoFilter, QDir::DirsFirst);

        m_files.resize(list.size());
        qCopy(list.begin(), list.end(), m_files.begin());

        m_children.fill(NULL, m_files.size());
    }
}

FileSystemNode::~FileSystemNode()
{
    foreach(FileSystemNode* node, m_children)
        delete node;
}

int FileSystemNode::childrenCount() const
{
    return m_files.size();
}

const FileSystemNode* FileSystemNode::parent()  const
{
    return m_parent;
}

const FileSystemNode* FileSystemNode::child(int index) const
{
    if(index >= m_files.size() || index < 0)
        return NULL;

    if(m_children[index] != NULL)
        return m_children[index];

    QString path = m_files[index].path() + QDir::separator() + m_files[index].fileName();

    if(m_children[index]==NULL)
        m_children[index] = new FileSystemNode(this, m_files[index].path() + QDir::separator() + m_files[index].fileName());

    return m_children[index];
}

const FileSystemNode* FileSystemNode::child(const QString &name) const
{
    int i = 0;
    for(; i < m_files.size(); ++i)
        if(m_files[i].fileName() == name)
            break;

    if(i >= m_files.size())
        return NULL;

    QString path = m_files[i].path() + QDir::separator() + name;

    if(m_children[i] == NULL)
        m_children[i] = new FileSystemNode(this, path);

    return m_children[i];
}

bool FileSystemNode::isValide() const
{
    return m_info.exists();
}

int FileSystemNode::index(const QString& path)  const
{
    return m_files.indexOf(QFileInfo(path));
}

QString FileSystemNode::path() const
{
    return m_info.filePath();
}

QString FileSystemNode::fileName() const
{
    return m_info.fileName();
}

QString FileSystemNode::fileExt() const
{
    if(!m_info.isDir())
        return m_info.suffix();
    return "";
}

QString FileSystemNode::fileSize() const
{
    if(m_info.isDir())
        return "<DIR>";

    qint64 sz = m_info.size();
    QString res;

    if(sz < 1000)
        res = "%1 B";
    else if(sz < 1000000)
    {
        res = "%1 KB";
        sz /= 1000;
    }
    else if(sz < 1000000000)
    {
        res = "%1 MB";
        sz /= 1000000;
    }
    else
    {
        res = "%1 GB";
        sz /= 1000000000;
    }

    return res.arg(sz);
}

QString FileSystemNode::fileType() const
{
    return "<type>";
}

QString FileSystemNode::fileDate() const
{
    return m_info.lastModified().toString();
}

QString FileSystemNode::filePermExt() const
{
    char res[] = "---";

    QFile::Permissions perm = m_info.permissions();

    if(perm & QFile::ReadUser)
        res[0] = 'r';
    if(perm & QFile::WriteUser)
        res[1] = 'w';
    if(perm & QFile::ExeUser)
        res[2] = 'x';

    return res;
}

QString FileSystemNode::filePerm() const
{
    return "<perm>";
}

QString FileSystemNode::fileOwner() const
{
    return m_info.owner();
}

QString FileSystemNode::fileGroup() const
{
    return m_info.group();
}

bool FileSystemNode::isDir() const
{
    return m_is_dir;
}

void FileSystemNode::setDir(const QString& path)
{   
    QDir dir(path);
    QFileInfoList list = dir.entryInfoList(QDir::NoFilter, QDir::DirsFirst);
    if(list.empty())
        return;

    m_children.clear();

    m_info.setFile(path);

    QString str = dir.path() + ".";

    list.removeOne(QFileInfo(dir.path() + QDir::separator() + "."));

    if(m_info.isRoot())
        list.removeOne(QFileInfo(dir.path() + QDir::separator() + ".."));

    m_is_valid = m_info.exists();
    m_is_dir    = m_info.isDir();

    if(!(m_is_valid && m_is_dir))
    {
        m_info.setFile(QDir::homePath());
        m_is_valid = true;
    }

    m_files.resize(list.size());
    qCopy(list.begin(), list.end(), m_files.begin());

    m_children.fill(NULL, m_files.size());
}
