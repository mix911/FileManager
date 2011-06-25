#include "filesystem.h"

#include <QDir>

FileSystem::FileSystem()
{
}

const FileSystemNode* FileSystem::defaultNode() const
{
    return &m_root;
}

const FileSystemNode* FileSystem::createNode(const QString&)    const
{
    return defaultNode();
}

void FileSystem::setDir(const QString &path)
{
    m_root.setDir(path);
}

const FileSystemNode* FileSystem::rootNode() const
{
    return &m_root;
}
