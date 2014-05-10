#ifndef FILEPROCESSOR_P_H
#define FILEPROCESSOR_P_H

#include <QMap>
#include <QObject>
#include <QStringList>

class FileInfo;
class FileProcessor;
class ProcessOptions;
class QDir;

class FileProcessorPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(FileProcessor)
    Q_DISABLE_COPY(FileProcessorPrivate)

public:

    explicit FileProcessorPrivate(FileProcessor * parent);

    ~FileProcessorPrivate();

    void Init();

    void CreateProcessOptions();

    bool ExtractOptions();

    bool ProcessProject();

    void ProcessDirectory( const QDir & dir );

    void AddFileInfo( const QDir & dir, const QString & filename );

    void OutputResults();

    FileProcessor * q_ptr;

    QScopedPointer<ProcessOptions> m_options;

    QObject * m_rootItem;

    QObject * m_progressItem;

    QStringList m_fileFilters;

    int m_currentFileId;

    QMap<int, FileInfo *> m_infoMap;

public slots:

    void onProcessStarted();

    void onOptionsInput(bool success);

};

#endif // FILEPROCESSOR_P_H
