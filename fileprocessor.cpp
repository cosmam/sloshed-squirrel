#include "fileprocessor.h"
#include "Private/fileprocessor_p.h"

#include "fileinfo.h"
#include "processoptions.h"

#include <QDir>
#include <QQmlProperty>

#include <QDebug>

FileProcessor::FileProcessor(QObject *parent)
  : QObject(parent),
    d_ptr(new FileProcessorPrivate(this))
{
    Q_D(FileProcessor);
    d->Init();
}

FileProcessor::~FileProcessor()
{
}


void FileProcessor::setRootItem(QObject *item)
{
    if( item == nullptr )
        return;

    Q_D(FileProcessor);
    d->m_rootItem = item;
    d->m_options->setRootItem(item);

    d->m_progressItem = d->m_rootItem->findChild<QObject*>("progressDialog");
}

/************* Private class implementation *************/


FileProcessorPrivate::FileProcessorPrivate(FileProcessor *parent)
  : QObject(parent),
    q_ptr(parent),
    m_options(nullptr),
    m_rootItem(nullptr)
{

}

FileProcessorPrivate::~FileProcessorPrivate()
{

}

void FileProcessorPrivate::Init()
{
    CreateProcessOptions();
}

void FileProcessorPrivate::CreateProcessOptions()
{
    m_options.reset( new ProcessOptions(this) );
    connect(m_options.data(), SIGNAL(optionsProcessed(bool)), this, SLOT(onOptionsInput(bool)), Qt::UniqueConnection);
    connect(m_options.data(), SIGNAL(processStarted()), this, SLOT(onProcessStarted()), Qt::UniqueConnection);
}

bool FileProcessorPrivate::ProcessProject()
{
    QDir rootDir( m_options->folder() );

    ProcessDirectory( rootDir );

    OutputResults();

    return true;
}

void FileProcessorPrivate::ProcessDirectory(const QDir & dir)
{
    QFileInfoList fileList = dir.entryInfoList(m_fileFilters, QDir::Files);
    for( QFileInfo info : fileList )
    {
        AddFileInfo( dir, info.fileName() );
    }

    QFileInfoList dirList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);
    for( QFileInfo info : dirList )
    {
        QDir tempDir( dir.absolutePath() + "/" + info.fileName() );
        if( tempDir.exists() )
        {
            ProcessDirectory( tempDir );
        }
    }
}

void FileProcessorPrivate::AddFileInfo(const QDir & dir, const QString & filename)
{
    QString fullName = dir.absolutePath() + "/" + filename;
    QFile file(fullName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    bool inComment(false), add(false);
    int locCount(0), commentCount(0), totalLinesCount(0), headerCommentsCount(0);

    QStringList IncludeList;

    QTextStream in(&file);
    while( !in.atEnd() ) {
        QString line = in.readLine().simplified();
        add = false;
        if( !line.isEmpty() && ( line.left(2) != "//" ) )
        {
            add = ( !add && !inComment );

            if( line.contains("/*") )
            {
                inComment = true;
                add = ( line.left(2) != "/*" );
            }

            if( line.contains("*/") )
            {
                inComment = false;
                add = ( line.right(2) != "*/" );
            }
        }

        commentCount += (!add && !line.isEmpty());
        locCount += (add ? 1 : 0);
        totalLinesCount++;

        // count non-empty lines until the first line of code
        if( locCount == 0 )
        {
            headerCommentsCount += (line.isEmpty() ? 0 : 1);
        }
    }

    auto info = new FileInfo();
    info->setFilename( filename );
    info->setFullName( fullName );
    info->setTotalLines( totalLinesCount );
    info->setCodeLines( locCount );
    info->setCommentLines( commentCount - headerCommentsCount );
    info->setHeaderCommentLines( headerCommentsCount );

    m_infoMap.insert(m_currentFileId++, info);
}

void FileProcessorPrivate::OutputResults()
{
    int fileCount(0), totalLines(0), codeLines(0), commentLines(0), headerLines(0);

    for( FileInfo * info : m_infoMap.values() )
    {
        ++fileCount;
        totalLines += info->totalLines();
        codeLines += info->codeLines();
        commentLines += info->commentLines();
        headerLines += info->headerCommentLines();
    }

    auto resultsSummary = m_rootItem->findChild<QObject*>("resultsSummary");
    if( resultsSummary == nullptr )
        return;

    QQmlProperty::write(resultsSummary, "fileCount", fileCount);
    QQmlProperty::write(resultsSummary, "totalLines", totalLines);
    QQmlProperty::write(resultsSummary, "codeLines", codeLines);
    QQmlProperty::write(resultsSummary, "commentLines", commentLines);
    QQmlProperty::write(resultsSummary, "headerLines", headerLines);
    QQmlProperty::write(resultsSummary, "visible", true);
}

void FileProcessorPrivate::onProcessStarted()
{
    QQmlProperty::write(m_progressItem, "visible", QVariant(true) );

    m_currentFileId = 0;
    qDeleteAll( m_infoMap.values() );
    m_infoMap.clear();
}

void FileProcessorPrivate::onOptionsInput(bool success)
{
    if( m_progressItem == nullptr )
        return;

    if( success ) {
        m_fileFilters = m_options->fileTypes();
        ProcessProject();
    }

    QQmlProperty::write(m_progressItem, "visible", QVariant(false) );
}
