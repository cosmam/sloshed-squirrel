#include "testcasefactory.h"
#include "testcase.h"
#include "initparams.h"

#include <map>
#include <mutex>

using Test::TestCaseFactory;
using Test::ITestCase;
using Test::InitParams;

class Test::TestCaseFactory::Impl
{
public:
    std::mutex registerMutex;
    std::map<std::string, TestCaseFactory::CreateCallback> callbacks;
};

TestCaseFactory &TestCaseFactory::getInstance()
{
    static TestCaseFactory factory;
    return factory;
}

TestCaseFactory::TestCaseFactory() : m_Impl( new Test::TestCaseFactory::Impl )
{
}

std::unique_ptr<Test::ITestCase> TestCaseFactory::createTestCase( const std::string &type ) const
{
    return createTestCase( type, InitParams() );
}

std::unique_ptr<Test::ITestCase> TestCaseFactory::createTestCase( const std::string &type, const InitParams & data ) const
{
    auto it = m_Impl->callbacks.find( type );
    return ( it == m_Impl->callbacks.end() ? nullptr : ( it->second )( data ) );
}

void TestCaseFactory::registerTestCase( const std::string &type,
                                        TestCaseFactory::CreateCallback cb )
{
    std::lock_guard<std::mutex> lock( m_Impl->registerMutex );
    m_Impl->callbacks[type] = cb;
}
