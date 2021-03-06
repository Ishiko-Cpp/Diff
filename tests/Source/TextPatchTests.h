/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Diff/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_DIFF_TESTS_TEXTPATCHTESTS_H_
#define _ISHIKO_DIFF_TESTS_TEXTPATCHTESTS_H_

#include <Ishiko/TestFramework/TestFrameworkCore.h>

class TextPatchTests : public Ishiko::Tests::TestSequence
{
public:
    TextPatchTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
};

#endif
