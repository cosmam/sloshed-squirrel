#ifndef CODEFILE_H
#define CODEFILE_H

#include "ifile.h"

#include <memory>

namespace Java
{
    namespace Impl
    {

        class CodeFile : public Java::IFile
        {
        public:
            CodeFile(const QString & path, const QString & name);

            virtual ~CodeFile();

            virtual QString path() const override final;

            virtual QString name() const override final;

            virtual Java::Visibility visibility() const override final;

            void setVisibility(Java::Visibility visibility);

            virtual QString package() const override final;

            void setPackage(const QString & package);

            virtual int totalLines() const override final;

            virtual int importLines() const override final;

            void setImportLines(int importLines);

            virtual int commentLines() const override final;

            void setCommentLines(int commentLines);

            virtual int blankLines() const override final;

            void setBlankLines(int blankLines);

            virtual int codeLines() const override final;

            void setCodeLines(int codeLines);

            virtual int methodCount() const override final;

            void setMethodCount(int methodCount);

            virtual int interfaceCount() const override final;

            void setInterfaceCount(int interfaceCount);

            virtual int classCount() const override final;

            void setClassCount(int classCount);

        private:

            class Impl;
            std::unique_ptr<Impl> m_data;
        };
    }
}

#endif // CODEFILE_H
