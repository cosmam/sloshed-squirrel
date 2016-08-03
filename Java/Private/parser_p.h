#ifndef PARSER_P_H
#define PARSER_P_H

#include <QObject>

#include <memory>

namespace Java
{
    class Parser;

    namespace Impl
    {
        class FileFactory;
    }

    class ParserPrivate : public QObject
    {
        Q_OBJECT
        Q_DECLARE_PUBLIC( Java::Parser )
        Q_DISABLE_COPY( ParserPrivate )

    public:

        explicit ParserPrivate(Java::Parser * parent);

        virtual ~ParserPrivate();

        void findFiles(const QString & path);

        void parseDirectory(const QString & path);

        void addFile(const QString & path);

        Java::Parser * q_ptr;

        std::unique_ptr<Java::Impl::FileFactory> m_factory;

        QStringList m_files;
        QStringList m_testFiles;
    };
}

#endif // PARSER_P_H
