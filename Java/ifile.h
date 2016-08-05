#ifndef IFILE_H
#define IFILE_H

#include "visibility.h"

#include <QString>

namespace Java
{
    class IFile
    {
    public:

        virtual ~IFile() = 0;

        virtual QString path() const = 0;

        virtual QString name() const = 0;

        virtual Java::Visibility visibility() const = 0;

        virtual QString package() const = 0;

        virtual int totalLines() const = 0;

        virtual int importLines() const = 0;

        virtual int commentLines() const = 0;

        virtual int blankLines() const = 0;

        virtual int codeLines() const = 0;

        virtual int methodCount() const = 0;

        virtual int interfaceCount() const = 0;

        virtual int classCount() const = 0;
    };
}

#endif // IFILE_H
