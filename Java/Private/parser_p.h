#ifndef PARSER_P_H
#define PARSER_P_H

#include <QObject>

namespace Java
{
    class Parser;

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

        Java::Parser * q_ptr;

        QStringList m_files;
    };
}

#endif // PARSER_P_H
