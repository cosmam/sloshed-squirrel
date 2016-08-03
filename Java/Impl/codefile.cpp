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
    int import = 0;
    int comment = 0;
    int blank = 0;
    int code = 0;
    int method = 0;
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
    return m_data->import + m_data->comment + m_data->blank + m_data->code;
}

int CodeFile::importLines() const
{
    return m_data->import;
}

void CodeFile::setImportLines(int importLines)
{
    m_data->import = importLines;
}

int CodeFile::commentLines() const
{
    return m_data->comment;
}

void CodeFile::setCommentLines(int commentLines)
{
    m_data->comment = commentLines;
}

int CodeFile::blankLines() const
{
    return m_data->blank;
}

void CodeFile::setBlankLines(int blankLines)
{
    m_data->blank = blankLines;
}

int CodeFile::codeLines() const
{
    return m_data->code;
}

void CodeFile::setCodeLines(int codeLines)
{
    m_data->code = codeLines;
}

int CodeFile::methodCount() const
{
    return m_data->method;
}

void CodeFile::setMethodCount(int methodCount)
{
    m_data->method = methodCount;
}
