#ifndef FILEFACTORY_H
#define FILEFACTORY_H

#include <QObject>
#include <QScopedPointer>

#include <memory>

namespace Java
{
    class IFile;

    namespace Impl
    {
        class FileFactoryPrivate;

        class FileFactory : public QObject
        {
            Q_OBJECT
            Q_DECLARE_PRIVATE(Java::Impl::FileFactory)
            Q_DISABLE_COPY( FileFactory )

        public:
            explicit FileFactory(QObject *parent = 0);

            virtual ~FileFactory();

            std::unique_ptr<Java::IFile> parseFile(const QString & path) const;

        signals:

        public slots:

        private:

            QScopedPointer<FileFactoryPrivate> d_ptr;
        };
    }
}


#endif // FILEFACTORY_H
