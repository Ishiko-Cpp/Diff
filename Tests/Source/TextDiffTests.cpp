/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Diff/blob/main/LICENSE.txt
*/

#include "TextDiffTests.h"
#include "Ishiko/Diff/TextDiff.h"

using namespace Ishiko;
using namespace Ishiko::Diff;
using namespace Ishiko::Tests;

TextDiffTests::TextDiffTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "TextDiff tests", environment)
{
    append<HeapAllocationErrorsTest>("CharacterDiff test 1", CharacterDiffTest1);
    append<HeapAllocationErrorsTest>("CharacterDiff test 2", CharacterDiffTest2);
    append<HeapAllocationErrorsTest>("CharacterDiff test 3", CharacterDiffTest3);
    append<HeapAllocationErrorsTest>("CharacterDiff test 4", CharacterDiffTest4);
    append<HeapAllocationErrorsTest>("CharacterDiff test 5", CharacterDiffTest5);
    append<HeapAllocationErrorsTest>("CharacterDiff test 6", CharacterDiffTest6);
    append<HeapAllocationErrorsTest>("CharacterDiff test 7", CharacterDiffTest7);
    append<HeapAllocationErrorsTest>("CharacterDiff test 8", CharacterDiffTest8);
    append<HeapAllocationErrorsTest>("LineDiffFiles test 1", LineDiffFilesTest1);
    append<HeapAllocationErrorsTest>("LineDiffFiles test 2", LineDiffFilesTest2);
}

void TextDiffTests::CharacterDiffTest1(Test& test)
{
    TextPatch patch = TextDiff::CharacterDiff("", "");

    ISHTF_FAIL_IF(patch.hasChanges());
    ISHTF_FAIL_IF_NEQ(patch.size(), 0);
    ISHTF_PASS();
}

void TextDiffTests::CharacterDiffTest2(Test& test)
{
    TextPatch patch = TextDiff::CharacterDiff("a", "a");

    ISHTF_FAIL_IF(patch.hasChanges());
    ISHTF_FAIL_IF_NEQ(patch.size(), 0);
    ISHTF_PASS();
}

void TextDiffTests::CharacterDiffTest3(Test& test)
{
    TextPatch patch = TextDiff::CharacterDiff("a", "");

    ISHTF_FAIL_IF_NOT(patch.hasChanges());
    ISHTF_FAIL_IF_NEQ(patch.size(), 1);
    ISHTF_FAIL_IF_NEQ(patch[0].originalPosition(), 0);
    ISHTF_FAIL_IF_NEQ(patch[0].newPosition(), 0);
    ISHTF_FAIL_IF_NEQ(patch[0].type(), TextChunk::eDeletion);
    ISHTF_FAIL_IF_NEQ(patch[0].text(), "a");
    ISHTF_PASS();
}

void TextDiffTests::CharacterDiffTest4(Test& test)
{
    TextPatch patch = TextDiff::CharacterDiff("", "a");

    ISHTF_FAIL_IF_NOT(patch.hasChanges());
    ISHTF_FAIL_IF_NEQ(patch.size(), 1);
    ISHTF_FAIL_IF_NEQ(patch[0].originalPosition(), 0);
    ISHTF_FAIL_IF_NEQ(patch[0].newPosition(), 0);
    ISHTF_FAIL_IF_NEQ(patch[0].type(), TextChunk::eInsertion);
    ISHTF_FAIL_IF_NEQ(patch[0].text(), "a");
    ISHTF_PASS();
}

void TextDiffTests::CharacterDiffTest5(Test& test)
{
    TextPatch patch = TextDiff::CharacterDiff("ab", "a");

    ISHTF_FAIL_IF_NOT(patch.hasChanges());
    ISHTF_FAIL_IF_NEQ(patch.size(), 1);
    ISHTF_FAIL_IF_NEQ(patch[0].originalPosition(), 1);
    ISHTF_FAIL_IF_NEQ(patch[0].newPosition(), 1);
    ISHTF_FAIL_IF_NEQ(patch[0].type(), TextChunk::eDeletion);
    ISHTF_FAIL_IF_NEQ(patch[0].text(), "b");
    ISHTF_PASS();
}

void TextDiffTests::CharacterDiffTest6(Test& test)
{
    TextPatch patch = TextDiff::CharacterDiff("a", "ab");

    ISHTF_FAIL_IF_NOT(patch.hasChanges());
    ISHTF_FAIL_IF_NEQ(patch.size(), 1);
    ISHTF_FAIL_IF_NEQ(patch[0].originalPosition(), 1);
    ISHTF_FAIL_IF_NEQ(patch[0].newPosition(), 1);
    ISHTF_FAIL_IF_NEQ(patch[0].type(), TextChunk::eInsertion);
    ISHTF_FAIL_IF_NEQ(patch[0].text(), "b");
    ISHTF_PASS();
}

void TextDiffTests::CharacterDiffTest7(Test& test)
{
    TextPatch patch = TextDiff::CharacterDiff("a", "abc");

    ISHTF_FAIL_IF_NOT(patch.hasChanges());
    ISHTF_FAIL_IF_NEQ(patch.size(), 2);
    ISHTF_FAIL_IF_NEQ(patch[0].originalPosition(), 1);
    ISHTF_FAIL_IF_NEQ(patch[0].newPosition(), 1);
    ISHTF_FAIL_IF_NEQ(patch[0].type(), TextChunk::eInsertion);
    ISHTF_FAIL_IF_NEQ(patch[0].text(), "b");
    ISHTF_FAIL_IF_NEQ(patch[1].originalPosition(), 1);
    ISHTF_FAIL_IF_NEQ(patch[1].newPosition(), 2);
    ISHTF_FAIL_IF_NEQ(patch[1].type(), TextChunk::eInsertion);
    ISHTF_FAIL_IF_NEQ(patch[1].text(), "c");
    ISHTF_PASS();
}

void TextDiffTests::CharacterDiffTest8(Test& test)
{
    TextPatch patch = TextDiff::CharacterDiff("abc", "a");

    ISHTF_FAIL_IF_NOT(patch.hasChanges());
    ISHTF_FAIL_IF_NEQ(patch.size(), 2);
    ISHTF_FAIL_IF_NEQ(patch[0].originalPosition(), 1);
    ISHTF_FAIL_IF_NEQ(patch[0].newPosition(), 1);
    ISHTF_FAIL_IF_NEQ(patch[0].type(), TextChunk::eDeletion);
    ISHTF_FAIL_IF_NEQ(patch[0].text(), "b");
    ISHTF_FAIL_IF_NEQ(patch[1].originalPosition(), 2);
    ISHTF_FAIL_IF_NEQ(patch[1].newPosition(), 1);
    ISHTF_FAIL_IF_NEQ(patch[1].type(), TextChunk::eDeletion);
    ISHTF_FAIL_IF_NEQ(patch[1].text(), "c");
    ISHTF_PASS();
}

void TextDiffTests::LineDiffFilesTest1(Test& test)
{
    boost::filesystem::path originalFile = test.environment().getTestDataPath("File1.txt");
    boost::filesystem::path newFile = test.environment().getTestDataPath("File2.txt");

    Error error;
    TextPatch patch = TextDiff::LineDiffFiles(originalFile, newFile, error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF(patch.hasChanges());
    ISHTF_PASS();
}

void TextDiffTests::LineDiffFilesTest2(Test& test)
{
    boost::filesystem::path originalFile = test.environment().getTestDataPath("File1.txt");
    boost::filesystem::path newFile = test.environment().getTestDataPath("File3.txt");

    Error error;
    TextPatch patch = TextDiff::LineDiffFiles(originalFile, newFile, error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NOT(patch.hasChanges());
    ISHTF_PASS();
}
