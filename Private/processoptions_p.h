#ifndef PROCESSOPTIONS_P_H
#define PROCESSOPTIONS_P_H

#include <QObject>
#include <QStringList>
#include <QUrl>

class ProcessOptions;

class ProcessOptionsPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(ProcessOptions)
    Q_DISABLE_COPY(ProcessOptionsPrivate)

public:

    explicit ProcessOptionsPrivate(ProcessOptions * parent);

    ~ProcessOptionsPrivate();

    void Init();

    bool ExtractOptions();

    ProcessOptions * q_ptr;

    QObject * m_item;

    QString m_folder;

    QStringList m_fileTypes;

    bool m_fileOutput;

    bool m_classOutput;

public slots:

    void onProcessClicked();

};

#endif // PROCESSOPTIONS_P_H
