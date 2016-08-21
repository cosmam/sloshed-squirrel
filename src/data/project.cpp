#include "project.h"

using namespace Data;

class Project::Impl
{
public:

    Impl(const QString & inName) : name(inName) {}

    QString name;
};

Project::Project(const QString &name)
  : m_data(std::make_unique<Impl>(name))
{

}
