#include "parser.h"

#include "Private/parser_p.h"

#include <QDir>

#include <QDebug>

using namespace Java;

namespace {
    const QString JAVA_SUFFIX = "java";
}

Parser::Parser(QObject *parent)
  : QObject(parent),
    d_ptr(new ParserPrivate(this))
{

}

Parser::~Parser()
{

}

bool Parser::parse(const QString & path)
{
    Q_D(Java::Parser);
    d->findFiles(path);

    qDebug() << "Found:" << d->m_files.size() << "files total";

    return !(d->m_files.isEmpty());
}

/************* Private class implementation *************/


Java::ParserPrivate::ParserPrivate(Java::Parser *parent)
  : QObject(parent),
    q_ptr(parent)
{

}

Java::ParserPrivate::~ParserPrivate()
{

}

void ParserPrivate::findFiles(const QString & path)
{
    m_files.clear();
    if(!QDir(path).exists()) {
        return;
    }

    parseDirectory(path);
}

void ParserPrivate::parseDirectory(const QString &path)
{
    QDir dir(path);
    for(const QFileInfo & info : dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries)) {
        if(info.isDir()) {
            parseDirectory(info.absoluteFilePath());
        } else if(info.completeSuffix() == JAVA_SUFFIX) {
            m_files.append(info.absoluteFilePath());
        }
    }
}
