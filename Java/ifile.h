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

        virtual Java::Visibility visibility() = 0;

        virtual QString path() = 0;

        virtual QString name() = 0;

        virtual QString package() = 0;

        virtual int totalLines() = 0;

        virtual int importLines() = 0;

        virtual int commentLines() = 0;

        virtual int blankLines() = 0;

        virtual int codeLines() = 0;

        virtual int methodCount() = 0;
    };
}

#endif // IFILE_H
