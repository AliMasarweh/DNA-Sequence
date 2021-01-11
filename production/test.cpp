//
// Created by ali-masa on 1/9/21.
//

#include "../header/dna_sequence.h"
#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(NecleotideBasicTests, InitTest) {
    Nucleotide necleotide('A');
}

TEST(NecleotideBasicTests, PairTest) {
    Nucleotide necleotideA('A'), necleotideC('C'),
            necleotideT('T'), necleotideG('G');

    ASSERT_TRUE(necleotideA.pair() == necleotideT);
    ASSERT_TRUE(necleotideT.pair() == necleotideA);

    ASSERT_TRUE(necleotideC.pair() == necleotideG);
    ASSERT_TRUE(necleotideG.pair() == necleotideC);
}

TEST(NecleotideBasicTests, InvalidNecleotideTest) {
    ASSERT_THROW(Nucleotide('x'), InvalidNucleotideException);
}