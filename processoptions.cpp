#include "processoptions.h"
#include "Private/processoptions_p.h"

#include <QFile>
#include <QQmlProperty>

ProcessOptions::ProcessOptions(QObject *parent)
  : QObject(parent),
    d_ptr(new ProcessOptionsPrivate(this))
{
    Q_D(ProcessOptions);
    d->Init();
}

ProcessOptions::~ProcessOptions()
{
}

void ProcessOptions::setRootItem(QObject * item)
{
    if( item == nullptr )
        return;

    Q_D(ProcessOptions);
    d->m_item = item;

    auto processButton = d->m_item->findChild<QObject*>("processButton");
    if( processButton != nullptr ) {
        connect(processButton, SIGNAL(clicked()), d, SLOT(onProcessClicked()));
    }
}

QString ProcessOptions::folder() const
{
    Q_D(const ProcessOptions);
    return d->m_folder;
}

QStringList ProcessOptions::fileTypes() const
{
    Q_D(const ProcessOptions);
    return d->m_fileTypes;
}

bool ProcessOptions::fileOutput() const
{
    Q_D(const ProcessOptions);
    return d->m_fileOutput;
}

bool ProcessOptions::classOutput() const
{
    Q_D(const ProcessOptions);
    return d->m_classOutput;
}

void ProcessOptions::setFolder(const QString & folder)
{
    Q_D(ProcessOptions);
    if( folder != d->m_folder ) {
        d->m_folder = folder;
        emit folderChanged();
    }
}

void ProcessOptions::setFileTypes(const QStringList & fileTypes)
{
    Q_D(ProcessOptions);
    if( fileTypes != d->m_fileTypes ) {
        d->m_fileTypes = fileTypes;
        emit fileTypesChanged();
    }
}

void ProcessOptions::setFileOutput(bool fileOutput)
{
    Q_D(ProcessOptions);
    if( fileOutput != d->m_fileOutput ) {
        d->m_fileOutput = fileOutput;
        emit fileOutputChanged();
    }
}

void ProcessOptions::setClassOutput(bool classOutput)
{
    Q_D(ProcessOptions);
    if( classOutput != d->m_classOutput ) {
        d->m_classOutput = classOutput;
        emit classOutputChanged();
    }
}

/************* Private class implementation *************/


ProcessOptionsPrivate::ProcessOptionsPrivate(ProcessOptions *parent)
  : QObject(parent),
    q_ptr(parent),
    m_item(nullptr),
    m_fileOutput(false),
    m_classOutput(false)
{

}

ProcessOptionsPrivate::~ProcessOptionsPrivate()
{

}

void ProcessOptionsPrivate::Init()
{

}

bool ProcessOptionsPrivate::ExtractOptions()
{
    if( m_item == nullptr )
        return false;

    auto directoryInput = m_item->findChild<QObject*>("directoryInput");
    m_folder = QQmlProperty::read(directoryInput, "text").toString();

    auto fileTypesInput = m_item->findChild<QObject*>("fileTypesInput");
    m_fileTypes = QQmlProperty::read(fileTypesInput, "text").toString().remove(' ').split(',', QString::SkipEmptyParts);

    auto fileOutput = m_item->findChild<QObject*>("fileOutput");
    m_fileOutput = QQmlProperty::read(fileOutput, "checked").toBool();

    auto classOutput = m_item->findChild<QObject*>("classOutput");
    m_classOutput = QQmlProperty::read(classOutput, "checked").toBool();

    return (QFile::exists(m_folder) && !m_fileTypes.isEmpty());
}

void ProcessOptionsPrivate::onProcessClicked()
{
    Q_Q(ProcessOptions);
    emit q->processStarted();
    emit q->optionsProcessed( ExtractOptions() );
}
