#ifndef FILEFACTORY_P_H
#define FILEFACTORY_P_H

#include "visibility.h"

#include <QObject>

#include <memory>

namespace Java
{
    class IFile;

    namespace Impl
    {
        class CodeFile;
        class FileFactory;

        class FileFactoryPrivate : public QObject
        {
            Q_OBJECT
            Q_DECLARE_PUBLIC( Java::Impl::FileFactory )
            Q_DISABLE_COPY( FileFactoryPrivate )

        public:

            explicit FileFactoryPrivate(Java::Impl::FileFactory * parent);

            virtual ~FileFactoryPrivate();

            Java::Impl::FileFactory * q_ptr;

            std::unique_ptr<Java::IFile> parseFile(const QString & path) const;

            QStringList readFile(const QString & path) const;

            void processFile(const std::unique_ptr<Java::Impl::CodeFile> & file, const QStringList & lines) const;

            QStringList processEmptyLines(const std::unique_ptr<Java::Impl::CodeFile> & file, const QStringList & lines) const;

            QStringList processImportLines(const std::unique_ptr<Java::Impl::CodeFile> & file, const QStringList & lines) const;

            QStringList processCommentLines(const std::unique_ptr<Java::Impl::CodeFile> & file, const QStringList & lines) const;

            void processCodeLines(const std::unique_ptr<Java::Impl::CodeFile> & file, const QStringList & lines) const;

            void processCode(const std::unique_ptr<Java::Impl::CodeFile> & file, const QStringList & lines) const;

            QList<QStringList> binClosures(const QStringList & lines) const;

            QList<QStringList> processAnonymous(const std::unique_ptr<Java::Impl::CodeFile> & file, const QList<QStringList> & closures) const;

            QList<QStringList> processInterfaces(const std::unique_ptr<Java::Impl::CodeFile> & file, const QList<QStringList> & closures) const;

            QList<QStringList> processClasses(const std::unique_ptr<Java::Impl::CodeFile> & file, const QList<QStringList> & closures) const;

            QList<QStringList> processMethods(const std::unique_ptr<Java::Impl::CodeFile> & file, const QList<QStringList> & closures) const;

            Java::Visibility getVisibility(const QString & line) const;

            bool isBlankLine(const QString & line) const;

            bool isFullComment(const QString & line) const;

            bool isCommentStart(const QString & line) const;

            bool containsCommentEnd(const QString & line) const;

            bool isCommentEndLast(const QString & line) const;
        };
    }
}

#endif // FILEFACTORY_P_H
