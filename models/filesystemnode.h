#ifndef FILESYSTEMNODE_H
#define FILESYSTEMNODE_H

#include <QVector>
#include <QString>
#include <QFileInfo>
#include <QDir>

class FileSystemNode
{
public:

    static FileSystemNode*              createNode(const QString& path);

                                        FileSystemNode();
                                        FileSystemNode(const FileSystemNode* parent, const QString& path);
                                       ~FileSystemNode();


    int                                 childrenCount() const;
    const FileSystemNode*               child(int index)const;
    const FileSystemNode*               child(const QString& name)  const;
    int                                 index(const QString& path)  const;
    bool                                isValide()      const;
    QString                             path()  const;
    const FileSystemNode*               parent()        const;
    bool                                isDir()         const;

    QString                             fileName()      const;
    QString                             fileExt()       const;
    QString                             fileSize()      const;
    QString                             fileType()      const;
    QString                             fileDate()      const;
    QString                             filePermExt()   const;
    QString                             filePerm()      const;
    QString                             fileOwner()     const;
    QString                             fileGroup()     const;

    void                                setDir(const QString& path);

private:
    QVector<QFileInfo>                  m_files;
    mutable QVector<FileSystemNode*>    m_children;
    bool                                m_is_dir;
    bool                                m_is_valid;
    QFileInfo                           m_info;
    QDir                                m_dir;
    const FileSystemNode*               m_parent;
};

#endif // FILESYSTEMNODE_H
