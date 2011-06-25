#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "filesystemnode.h"

class FileSystem
{
public:
                            FileSystem();

    const FileSystemNode*   defaultNode()   const;
    const FileSystemNode*   createNode(const QString& path) const;
    const FileSystemNode*   rootNode()  const;

    void                    setDir(const QString& path);

private:
    FileSystemNode          m_root;
};

#endif // FILESYSTEM_H
