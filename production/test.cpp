//
// Created by ali-masa on 1/9/21.
//

#include <gtest/gtest.h>
#include <set>

using namespace std;

#include "../header/dna_sequence.h"
#include "../header/dna_sequence_exception.h"

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// ******************************** Nucleotide Tests ********************************
TEST(NucleotideBasicTests, InitTest) {
    Nucleotide nucleotideA('A'), nucleotideC('C'),
            nucleotideT('T'), nucleotideG('G');

    Nucleotide copA(nucleotideA);
    nucleotideA = 'A';
}

TEST(NucleotideBasicTests, InvalidNucleotideTest) {
    set<char> validNucleotide;

    validNucleotide.insert('A');
    validNucleotide.insert('C');
    validNucleotide.insert('T');
    validNucleotide.insert('G');

    for(unsigned char character = 0; character < 255; ++character) {
        if(!validNucleotide.contains(character))
            ASSERT_THROW(Nucleotide nucleotide(character), InvalidNucleotideException);
    }

    Nucleotide nucleotide('A');
    for(unsigned char character = 0; character < 255; ++character) {
        if(!validNucleotide.contains(character))
            ASSERT_THROW(nucleotide = character, InvalidNucleotideException);
    }
}

TEST(NucleotideBasicTests, PairTest) {
    Nucleotide nucleotideA('A'), nucleotideC('C'),
            nucleotideT('T'), nucleotideG('G');

    ASSERT_TRUE(nucleotideA.pair() == nucleotideT);
    ASSERT_TRUE(nucleotideT.pair() == nucleotideA);

    ASSERT_TRUE(nucleotideC.pair() == nucleotideG);
    ASSERT_TRUE(nucleotideG.pair() == nucleotideC);
}

TEST(NucleotideBasicTests, RationalOperatorsTest) {
    Nucleotide nucleotideA('A'), nucleotideC('C'),
            nucleotideT('T'), nucleotideG('G');

    ASSERT_TRUE(nucleotideA == 'A');
    ASSERT_TRUE(nucleotideT == 'T');
    ASSERT_TRUE(nucleotideC == 'C');
    ASSERT_TRUE(nucleotideG == 'G');
}

TEST(NucleotideBasicTests, AsCharacterMethodTest) {
    Nucleotide nucleotideA('A'), nucleotideC('C'),
            nucleotideT('T'), nucleotideG('G');

    ASSERT_TRUE(nucleotideA.asCharacter() == 'A');
    ASSERT_TRUE(nucleotideT.asCharacter() == 'T');
    ASSERT_TRUE(nucleotideC.asCharacter() == 'C');
    ASSERT_TRUE(nucleotideG.asCharacter() == 'G');
}

// ******************************** Codon Tests ********************************
TEST(CodonBasicTests, InitTest) {
    Codon codon("ATG");
}

TEST(CodonBasicTests, InvalidCodonTest) {
    stringstream ss;
    ss << "";
    for (int i = 0; i < Codon::s_codonSize - 1; ++i) {
        ASSERT_THROW(Codon(ss.str()), InvalidCodonLengthException);
    }

    ss << "AA";
    ASSERT_THROW(Codon(ss.str()), InvalidCodonLengthException);
}

TEST(CodonBasicTests, PairTest) {
    srand((unsigned ) time(0));
    const unsigned char numOfNucleotides = 4;
    char nucleotides[numOfNucleotides] = {
      'A', 'T', 'G', 'C'
    };

    map<char, char> nucPairs = {
            {'A', 'T'},
            {'T', 'A'},
            {'C', 'G'},
            {'G', 'C'}
    };

    size_t totalRandomTests = 1000;
    stringstream ss, flipped_ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < Codon::s_codonSize; ++x) {
            char c = nucleotides[random() % numOfNucleotides];
            ss << c;
            flipped_ss  << nucPairs[c];
        }

        ASSERT_TRUE(Codon(ss.str()).pair() == Codon(flipped_ss.str()));
        ss.clear();
        ss.str("");
        flipped_ss.clear();
        flipped_ss.str("");
    }
}


TEST(CodonBasicTests, RationalOperatorsTest) {
    srand((unsigned ) time(0));
    const unsigned char numOfNucleotides = 4;
    char nucleotides[numOfNucleotides] = {
            'A', 'T', 'G', 'C'
    };

    size_t totalRandomTests = 1000;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < Codon::s_codonSize; ++x)
            ss << nucleotides[random() % numOfNucleotides];

        ASSERT_TRUE(Codon(ss.str()) == ss.str());
        ss.clear();
        ss.str("");
    }
}

TEST(CodonBasicTests, AsStringMethodTest) {
    srand((unsigned ) time(0));
    const unsigned char numOfNucleotides = 4;
    char nucleotides[numOfNucleotides] = {
            'A', 'T', 'G', 'C'
    };

    size_t totalRandomTests = 1000;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < Codon::s_codonSize; ++x)
            ss << nucleotides[random() % numOfNucleotides];

        ASSERT_TRUE(Codon(ss.str()).asString() == ss.str());
        ss.clear();
        ss.str("");
    }
}

// ******************************** DNA-Sequence Tests ********************************
TEST(DNASequenceBasicTests, InitTest) {
    DNASequence codon("ATG");
}

TEST(DNASequenceBasicTests, PairTest) {
    srand((unsigned ) time(0));
    const unsigned char numOfNucleotides = 4;
    char nucleotides[numOfNucleotides] = {
            'A', 'T', 'G', 'C'
    };

    map<char, char> nucPairs = {
            {'A', 'T'},
            {'T', 'A'},
            {'C', 'G'},
            {'G', 'C'}
    };

    size_t totalRandomTests = 1000, dnaMaxLen = 100;
    stringstream ss, flipped_ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < random() % dnaMaxLen; ++x) {
            char c = nucleotides[random() % numOfNucleotides];
            ss << c;
            flipped_ss  << nucPairs[c];
        }

        ASSERT_TRUE(DNASequence(ss.str()).pair() == DNASequence(flipped_ss.str()));
        ss.clear();
        ss.str("");
        flipped_ss.clear();
        flipped_ss.str("");
    }
}


TEST(DNASequenceBasicTests, RationalOperatorsTest) {
    srand((unsigned ) time(0));
    const unsigned char numOfNucleotides = 4;
    char nucleotides[numOfNucleotides] = {
            'A', 'T', 'G', 'C'
    };

    size_t totalRandomTests = 1000;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < Codon::s_codonSize; ++x)
            ss << nucleotides[random() % numOfNucleotides];

        ASSERT_TRUE(DNASequence(ss.str()) == ss.str());
        ss.clear();
        ss.str("");
    }
}

TEST(DNASequenceBasicTests, AsStringMethodTest) {
    srand((unsigned ) time(0));
    const unsigned char numOfNucleotides = 4;
    char nucleotides[numOfNucleotides] = {
            'A', 'T', 'G', 'C'
    };

    size_t totalRandomTests = 1000;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < Codon::s_codonSize; ++x)
            ss << nucleotides[random() % numOfNucleotides];

        ASSERT_TRUE(DNASequence(ss.str()).asString() == ss.str());
        ss.clear();
        ss.str("");
    }
}