#include "filefactory.h"
#include "Private/filefactory_p.h"

#include "ifile.h"
#include "visibility.h"
#include "codefile.h"

#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include <QDebug>

using namespace Java;
using namespace Java::Impl;

namespace {
    const QString IMPORT_START = "import ";
    const QString PACKAGE_START = "package ";

    QString toString(Visibility visibility) {
        QString text = "";
        switch(visibility) {
        case Visibility::Public: text = "public";
            break;
        case Visibility::Protected: text = "protected";
            break;
        case Visibility::Package: text = "package";
            break;
        case Visibility::Private: text = "private";
            break;
        }

        return text;
    }
}

FileFactory::FileFactory(QObject *parent)
    : QObject(parent),
      d_ptr(new FileFactoryPrivate(this))
{

}

FileFactory::~FileFactory()
{

}

std::unique_ptr<IFile> FileFactory::parseFile(const QString & path) const
{
    if(!QFile::exists(path)) {
        return nullptr;
    }

    Q_D(const FileFactory);
    auto file = d->parseFile(path);

    qDebug() << file->path()
             << file->name()
             << file->package()
             << toString(file->visibility())
             << file->totalLines()
             << file->importLines()
             << file->commentLines()
             << file->blankLines()
             << file->codeLines()
             << file->methodCount()
             << file->interfaceCount()
             << file->classCount();

    return file;
}


/************* Private class implementation *************/


FileFactoryPrivate::FileFactoryPrivate(FileFactory *parent)
    : QObject(parent),
      q_ptr(parent)
{

}

FileFactoryPrivate::~FileFactoryPrivate()
{

}

std::unique_ptr<IFile> FileFactoryPrivate::parseFile(const QString &path) const
{
    auto lines = readFile(path);
    if(lines.isEmpty()) {
        return nullptr;
    }

    QFileInfo info(path);
    auto file = std::make_unique<CodeFile>(info.absolutePath(), info.fileName());

    processFile(file, lines);

    return file;
}

QStringList FileFactoryPrivate::readFile(const QString &path) const
{
    auto lines = QStringList();

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return lines;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        lines.append(in.readLine());
    }

    return lines;
}

void FileFactoryPrivate::processFile(const std::unique_ptr<CodeFile> &file, const QStringList &lines) const
{
    auto paredLines = processEmptyLines(file, lines);
    paredLines = processImportLines(file, paredLines);
    paredLines = processCommentLines(file, paredLines);
    processCodeLines(file, paredLines);
}

QStringList FileFactoryPrivate::processEmptyLines(const std::unique_ptr<CodeFile> & file, const QStringList & lines) const
{
    auto paredLines = QStringList();

    int count = 0;
    for(const QString & line : lines) {
        if(isBlankLine(line)) {
            count++;
        } else {
            paredLines.append(line);
        }
    }

    file->setBlankLines(count);

    return paredLines;
}

QStringList FileFactoryPrivate::processImportLines(const std::unique_ptr<CodeFile> &file, const QStringList &lines) const
{
    auto paredLines = QStringList();

    int count = 0;
    for(const QString & line : lines) {
        if(line.startsWith(IMPORT_START)) {
            count++;
        } else {
            paredLines.append(line);
        }
    }

    file->setImportLines(count);
    return paredLines;
}

QStringList FileFactoryPrivate::processCommentLines(const std::unique_ptr<CodeFile> &file, const QStringList &lines) const
{
    auto paredLines = QStringList();

    int count = 0;
    bool isInComment = false;
    for(const QString & line : lines) {
        if(isFullComment(line) || (isInComment && !containsCommentEnd(line))) {
            count++;
        } else if(isCommentStart(line)) {
            isInComment = true;
            count++;
        } else if(isInComment && containsCommentEnd(line)) {
            if(isCommentEndLast(line)) {
                count++;
            } else {
                paredLines.append(line);
            }
            isInComment = false;
        } else {
            paredLines.append(line);
        }
    }

    file->setCommentLines(count);
    return paredLines;
}

void FileFactoryPrivate::processCodeLines(const std::unique_ptr<CodeFile> &file, const QStringList &lines) const
{
    auto paredLines(lines);

    file->setCodeLines(lines.size());
    file->setPackage(paredLines.takeFirst().simplified().replace(PACKAGE_START, "").replace(";", ""));
    file->setVisibility(getVisibility(paredLines.takeFirst().simplified()));
    paredLines.removeLast();
    processCode(file, paredLines);
}

void FileFactoryPrivate::processCode(const std::unique_ptr<CodeFile> &file, const QStringList &lines) const
{
    auto closures = binClosures(lines);

    closures = processAnonymous(file, closures);
    closures = processInterfaces(file, closures);
    closures = processClasses(file, closures);
    closures = processMethods(file, closures);
}

QList<QStringList> FileFactoryPrivate::binClosures(const QStringList &lines) const
{
    QList<QStringList> closures;
    QStringList closure;
    int bracketCount = 0;

    for(const QString & line : lines) {
        if(line.contains("{")) {
            ++bracketCount;
        }

        if(bracketCount > 0) {
            closure.append(line);
        }

        if(line.contains("}") && ((--bracketCount) == 0)) {
            closures.append(closure);
            closure.clear();
        }
    }

    if(closures.isEmpty()) {
        closures.append(lines);
    }

    return closures;
}

QList<QStringList> FileFactoryPrivate::processAnonymous(const std::unique_ptr<CodeFile> &file, const QList<QStringList> &closures) const
{
    Q_UNUSED(file);

    QList<QStringList> paredClosures;

    for(const QStringList & closure : closures) {
        if(!closure.first().contains("=")) {
            paredClosures.append(closure);
        }
    }

    return paredClosures;
}

QList<QStringList> FileFactoryPrivate::processInterfaces(const std::unique_ptr<CodeFile> &file, const QList<QStringList> &closures) const
{
    QList<QStringList> paredClosures;

    int count = 0;
    for(const QStringList & closure : closures) {
        if(closure.first().contains(" interface ")) {
            QStringList code(closure);
            code.removeFirst();
            code.removeLast();
            processCode(file, code);
            ++count;
        } else {
            paredClosures.append(closure);
        }
    }

    file->setInterfaceCount(count + file->interfaceCount());

    return paredClosures;
}

QList<QStringList> FileFactoryPrivate::processClasses(const std::unique_ptr<CodeFile> &file, const QList<QStringList> &closures) const
{
    QList<QStringList> paredClosures;

    int count = 0;
    for(const QStringList & closure : closures) {
        if(closure.first().contains(" class ")) {
            QStringList code(closure);
            code.removeFirst();
            code.removeLast();
            processCode(file, code);
            ++count;
        } else {
            paredClosures.append(closure);
        }
    }

    file->setClassCount(count + file->classCount());

    return paredClosures;
}

QList<QStringList> FileFactoryPrivate::processMethods(const std::unique_ptr<CodeFile> &file, const QList<QStringList> &closures) const
{
    QList<QStringList> paredClosures;

    int count = 0;
    for(const QStringList & closure : closures) {
        if(closure.first().contains("(") && closure.first().contains(")")) {
            ++count;
        } else {
            paredClosures.append(closure);
        }
    }

    file->setMethodCount(count + file->methodCount());

    return paredClosures;
}

Visibility FileFactoryPrivate::getVisibility(const QString &line) const
{
    Visibility visibility(Visibility::Package);

    if(line.contains("public")) {
        visibility = Visibility::Public;
    } else if(line.contains("protected")) {
        visibility = Visibility::Protected;
    } else if(line.contains("private")){
        visibility = Visibility::Private;
    }

    return visibility;
}

bool FileFactoryPrivate::isBlankLine(const QString &line) const
{
    return line.simplified().replace(" ", "").isEmpty();
}

bool FileFactoryPrivate::isFullComment(const QString &line) const
{
    QString text(line.simplified());
    return (text.startsWith("//") || (text.startsWith("/*") && text.endsWith("*/")));
}

bool FileFactoryPrivate::isCommentStart(const QString &line) const
{
    QString text(line.simplified());
    return (text.startsWith("/*") && !text.endsWith("*/"));
}

bool FileFactoryPrivate::containsCommentEnd(const QString &line) const
{
    return line.simplified().contains("*/");
}

bool FileFactoryPrivate::isCommentEndLast(const QString &line) const
{
    return line.simplified().endsWith("*/");
}
