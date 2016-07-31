#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QScopedPointer>

namespace Java
{
    class ParserPrivate;

    class Parser : public QObject
    {
        Q_OBJECT
        Q_DECLARE_PRIVATE(Java::Parser)
        Q_DISABLE_COPY( Parser )

    public:
        explicit Parser(QObject *parent = 0);

        virtual ~Parser();

        bool parse(const QString & path);

    signals:

    public slots:

    private:

        QScopedPointer<ParserPrivate> d_ptr;
    };
}

#endif // PARSER_H
