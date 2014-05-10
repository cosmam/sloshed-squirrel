#include "fileinfo.h"

#include <QString>

class FileInfo::Impl
{
public:

    QString filename;
    QString fullName;
    QString className;
    int totalLines;
    int codeLines;
    int commentLines;
    int headerCommentLines;
};

FileInfo::FileInfo(QObject * parent)
  : QObject(parent),
    m_Impl(new FileInfo::Impl)
{
}

FileInfo::~FileInfo()
{
}

QString FileInfo::filename() const
{
    return m_Impl->filename;
}

QString FileInfo::fullName() const
{
    return m_Impl->fullName;
}

QString FileInfo::className() const
{
    return m_Impl->className;
}

int FileInfo::totalLines() const
{
    return m_Impl->totalLines;
}

int FileInfo::codeLines() const
{
    return m_Impl->codeLines;
}

int FileInfo::commentLines() const
{
    return m_Impl->commentLines;
}

int FileInfo::headerCommentLines() const
{
    return m_Impl->headerCommentLines;
}

void FileInfo::setFilename(const QString & filename)
{
    m_Impl->filename = filename;
}

void FileInfo::setFullName(const QString & fullName)
{
    m_Impl->fullName = fullName;
}

void FileInfo::setClassName(const QString & className)
{
    m_Impl->className = className;
}

void FileInfo::setTotalLines(int totalLines)
{
    m_Impl->totalLines = totalLines;
}

void FileInfo::setCodeLines(int codeLines)
{
    m_Impl->codeLines = codeLines;
}

void FileInfo::setCommentLines(int commentLines)
{
    m_Impl->commentLines = commentLines;
}

void FileInfo::setHeaderCommentLines(int headerCommentLines)
{
    m_Impl->headerCommentLines = headerCommentLines;
}
