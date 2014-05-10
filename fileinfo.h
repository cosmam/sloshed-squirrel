#ifndef FILEINFO_H
#define FILEINFO_H

#include <QObject>

class FileInfo : public QObject
{
    Q_OBJECT

public:

    /// Default constructor
    FileInfo(QObject * parent = nullptr);

    /// Destructor
    ~FileInfo();

    /// Gets the filename
    QString filename() const;

    /// Gets the full file name and path
    QString fullName() const;

    /// Gets the class name
    QString className() const;

    /// Gets the total line count
    int totalLines() const;

    /// Gets the number of lines of code
    int codeLines() const;

    /// Gets the number of lines of comments
    int commentLines() const;

    /// Gets the number of lines in the header comments
    int headerCommentLines() const;

    /// Sets the filename
    void setFilename(const QString & filename);

    /// Sets the full name
    void setFullName(const QString & fullName);

    /// Sets the class name
    void setClassName(const QString & className);

    /// Sets the total line count
    void setTotalLines(int totalLines);

    /// Sets the number of lines of code
    void setCodeLines(int codeLines);

    /// Sets the number of comment lines
    void setCommentLines(int commentLines);

    /// Sets the number of header comment lines
    void setHeaderCommentLines(int headerCommentLines);

private:

    class Impl;
    QScopedPointer<Impl> m_Impl;
};

#endif // FILEINFO_H
