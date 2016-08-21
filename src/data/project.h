#ifndef PROJECT_H
#define PROJECT_H

#include <QString>

#include <memory>

namespace Data
{

    class Project
    {
    public:
        Project(const QString & name);

    private:

        class Impl;
        std::unique_ptr<Impl> m_data;
    };

}

#endif // PROJECT_H
