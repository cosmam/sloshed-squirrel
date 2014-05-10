#ifndef PROCESSOPTIONS_H
#define PROCESSOPTIONS_H

#include <QObject>
#include <QStringList>

class ProcessOptionsPrivate;

class ProcessOptions : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ProcessOptions)
    Q_DISABLE_COPY(ProcessOptions)
    Q_PROPERTY(QString folder READ folder WRITE setFolder NOTIFY folderChanged)
    Q_PROPERTY(QStringList fileTypes READ fileTypes WRITE setFileTypes NOTIFY fileTypesChanged)
    Q_PROPERTY(bool fileOutput READ fileOutput WRITE setFileOutput NOTIFY fileOutputChanged)
    Q_PROPERTY(bool classOutput READ classOutput WRITE setClassOutput NOTIFY classOutputChanged)

public:
    explicit ProcessOptions(QObject *parent = 0);

    ~ProcessOptions();

    void setRootItem(QObject *item);

    QString folder() const;

    QStringList fileTypes() const;

    bool fileOutput() const;

    bool classOutput() const;

public slots:

    void setFolder(const QString & folder);

    void setFileTypes(const QStringList & fileTypes);

    void setFileOutput(bool fileOutput);

    void setClassOutput(bool classOuput);

signals:

    void folderChanged();

    void fileTypesChanged();

    void fileOutputChanged();

    void classOutputChanged();

    void processStarted();

    void optionsProcessed(bool success);

private:

    QScopedPointer<ProcessOptionsPrivate> d_ptr;

};

#endif // PROCESSOPTIONS_H
