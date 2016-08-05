#include "codefile.h"

using namespace Java;
using namespace Java::Impl;

class CodeFile::Impl
{
public:
    Impl(const QString & inPath, const QString & inName) : path(inPath), name(inName) {}

    ~Impl() {}

    const QString path;
    const QString name;
    Java::Visibility visibility = Java::Visibility::Package;
    QString package = "";
    int importLines = 0;
    int commentLines = 0;
    int blankLines = 0;
    int codeLines = 0;
    int methodCount = 0;
    int interfaceCount = 0;
    int classCount = 0;
};

CodeFile::CodeFile(const QString &path, const QString &name)
  : m_data(std::make_unique<CodeFile::Impl>(path, name))
{

}

CodeFile::~CodeFile()
{

}

QString CodeFile::path() const
{
    return m_data->path;
}

QString CodeFile::name() const
{
    return m_data->name;
}

Java::Visibility CodeFile::visibility() const
{
    return m_data->visibility;
}

void CodeFile::setVisibility(Java::Visibility visibility)
{
    m_data->visibility = visibility;
}

QString CodeFile::package() const
{
    return m_data->package;
}

void CodeFile::setPackage(const QString & package)
{
    m_data->package = package;
}

int CodeFile::totalLines() const
{
    return m_data->importLines + m_data->commentLines + m_data->blankLines + m_data->codeLines;
}

int CodeFile::importLines() const
{
    return m_data->importLines;
}

void CodeFile::setImportLines(int importLines)
{
    m_data->importLines = importLines;
}

int CodeFile::commentLines() const
{
    return m_data->commentLines;
}

void CodeFile::setCommentLines(int commentLines)
{
    m_data->commentLines = commentLines;
}

int CodeFile::blankLines() const
{
    return m_data->blankLines;
}

void CodeFile::setBlankLines(int blankLines)
{
    m_data->blankLines = blankLines;
}

int CodeFile::codeLines() const
{
    return m_data->codeLines;
}

void CodeFile::setCodeLines(int codeLines)
{
    m_data->codeLines = codeLines;
}

int CodeFile::methodCount() const
{
    return m_data->methodCount;
}

void CodeFile::setMethodCount(int methodCount)
{
    m_data->methodCount = methodCount;
}

int CodeFile::interfaceCount() const
{
    return m_data->interfaceCount;
}

void CodeFile::setInterfaceCount(int interfaceCount)
{
    m_data->interfaceCount = interfaceCount;
}

int CodeFile::classCount() const
{
    return m_data->classCount;
}

void CodeFile::setClassCount(int classCount)
{
    m_data->classCount = classCount;
}
