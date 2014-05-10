#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <QObject>

class FileProcessorPrivate;
class ProcessOptions;

class FileProcessor : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(FileProcessor)
    Q_DISABLE_COPY(FileProcessor)

public:
    explicit FileProcessor(QObject *parent = 0);

    ~FileProcessor();

    void setRootItem(QObject *item);

public slots:

signals:

private:

    QScopedPointer<FileProcessorPrivate> d_ptr;

};

#endif // FILEPROCESSOR_H
