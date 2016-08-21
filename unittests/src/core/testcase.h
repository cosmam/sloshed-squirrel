#ifndef TESTCASE_T_H
#define TESTCASE_T_H

#include "testtypes.h"

#include <QString>

namespace Test
{
    class ITestCase
    {
    public:
        virtual ~ITestCase() {}

        virtual bool isValid() = 0;

        virtual QString name() = 0;

        virtual Test::TestType type() = 0;

        virtual int level() = 0;

        virtual QString module() = 0;

        virtual int runTests() = 0;
    };
}

#endif // TESTCASE_T_H
