#ifndef TESTCASEFACTORY_T_H
#define TESTCASEFACTORY_T_H

#include <memory>

namespace Test
{
    class ITestCase;
    class InitParams;

    class TestCaseFactory
    {
    public:
        using CreateCallback = std::unique_ptr<Test::ITestCase>( * )( const InitParams & );

        static TestCaseFactory &getInstance();

        std::unique_ptr<Test::ITestCase> createTestCase( const std::string &type ) const;

        std::unique_ptr<Test::ITestCase> createTestCase( const std::string &type,
                                                         const Test::InitParams &data ) const;

        void registerTestCase( const std::string &type, CreateCallback cb );

    private:
        TestCaseFactory();

        class Impl;
        std::unique_ptr<Impl> m_Impl;
    };
}

#define REGISTER_TestCase( id, func )                                                              \
    bool registerTestCase()                                                                        \
    {                                                                                              \
        Test::TestCaseFactory::getInstance().registerTestCase( id, func );                         \
        return true;                                                                               \
    }                                                                                              \
    bool registered = registerTestCase();

#endif // TESTCASEFACTORY_T_H
