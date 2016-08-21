#ifndef TESTCASE_TI_H
#define TESTCASE_TI_H

#include "unittests/src/core/testcase.h"

#include <QObject>

namespace Test
{
    namespace Impl
    {
        class TestCase : public ITestCase
        {
        public:
            TestCase();

            virtual ~TestCase();
        };
    }
}

#endif // TESTCASE_TI_H
