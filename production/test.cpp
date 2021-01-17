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

class MyGTestUtil {
public:
    static const unsigned char s_numOfNucleotides = 4;
    static char s_nucleotides[s_numOfNucleotides];
    static const map<char, char> s_nucPairs;
};

char MyGTestUtil::s_nucleotides[s_numOfNucleotides] = {
        'A', 'T', 'G', 'C'
};

const map<char, char> MyGTestUtil::s_nucPairs = {
        {'A', 'T'},
        {'T', 'A'},
        {'C', 'G'},
        {'G', 'C'}
};

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
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000;
    stringstream ss, flipped_ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < Codon::s_codonSize; ++x) {
            char c = MyGTestUtil::s_nucleotides[random() % MyGTestUtil::s_numOfNucleotides];
            ss << c;
            flipped_ss  << MyGTestUtil::s_nucPairs.at(c);
        }

        ASSERT_TRUE(Codon(ss.str()).pair() == Codon(flipped_ss.str()));
        ss.clear();
        ss.str("");
        flipped_ss.clear();
        flipped_ss.str("");
    }
}


TEST(CodonBasicTests, RationalOperatorsTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < Codon::s_codonSize; ++x)
            ss << MyGTestUtil::s_nucleotides[random() % MyGTestUtil::s_numOfNucleotides];

        ASSERT_TRUE(Codon(ss.str()) == ss.str());
        ss.clear();
        ss.str("");
    }
}

TEST(CodonBasicTests, AsStringMethodTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < Codon::s_codonSize; ++x)
            ss << MyGTestUtil::s_nucleotides[random() % MyGTestUtil::s_numOfNucleotides];

        ASSERT_TRUE(Codon(ss.str()).asString() == ss.str());
        ss.clear();
        ss.str("");
    }
}

// ******************************** DNA-Sequence Tests ********************************
TEST(DNASequenceBasicTests, InitTest) {
    DNASequence dnaSequence("ATG");

    std::string str("AAA");
    dnaSequence = str;
    ASSERT_TRUE(dnaSequence == str);
}

TEST(DNASequenceBasicTests, AssignmentOperators) {
    DNASequence dnaSequence("ATG");

    std::string str("AAA");
    dnaSequence = str;
    ASSERT_TRUE(dnaSequence == str);

    str += "AA";
    dnaSequence = str;
    ASSERT_TRUE(dnaSequence == str);

    str = "A";
    dnaSequence = str;
    ASSERT_TRUE(dnaSequence == str);
    ASSERT_TRUE(dnaSequence.length() == str.length());
}

TEST(DNASequenceBasicTests, PairTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 99;
    stringstream ss, flipped_ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < random() % dnaMaxLen + 1; ++x) {
            char c = MyGTestUtil::s_nucleotides[random() % MyGTestUtil::s_numOfNucleotides];
            ss << c;
            flipped_ss  << MyGTestUtil::s_nucPairs.at(c);
        }

        ASSERT_TRUE(DNASequence(ss.str()).pair() == DNASequence(flipped_ss.str()));
        ss.clear();
        ss.str("");
        flipped_ss.clear();
        flipped_ss.str("");
    }
}


TEST(DNASequenceBasicTests, RationalOperatorsTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 99;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < random() % dnaMaxLen + 1; ++x)
            ss << MyGTestUtil::s_nucleotides[random() % MyGTestUtil::s_numOfNucleotides];

        ASSERT_TRUE(DNASequence(ss.str()) == ss.str());
        ss.clear();
        ss.str("");
    }
}

TEST(DNASequenceBasicTests, AsStringMethodTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 99;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < random() % dnaMaxLen + 1; ++x)
            ss << MyGTestUtil::s_nucleotides[random() % MyGTestUtil::s_numOfNucleotides];

        ASSERT_TRUE(DNASequence(ss.str()).asString() == ss.str());
        ss.clear();
        ss.str("");
    }
}

TEST(DNASequenceBasicTests, LengthTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 99;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < random() % dnaMaxLen + 1; ++x)
            ss << MyGTestUtil::s_nucleotides[random() % MyGTestUtil::s_numOfNucleotides];

        ASSERT_TRUE(DNASequence(ss.str()).length() == ss.str().length());
        ss.clear();
        ss.str("");
    }
}

TEST(DNASequenceBasicTests, BracketsOperatorTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 99;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < random() % dnaMaxLen + 1; ++x)
            ss << MyGTestUtil::s_nucleotides[random() % MyGTestUtil::s_numOfNucleotides];
        std::string str = ss.str();
        DNASequence dnaSequence(str);
        for (size_t i = 0; i < dnaSequence.length(); ++i)
            ASSERT_TRUE(dnaSequence[i] == str[i]);
        ss.clear();
        ss.str("");
    }
}

TEST(DNASequenceBasicTests, CodonAtMethodTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 97;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < random() % dnaMaxLen + Codon::s_codonSize; ++x)
            ss << MyGTestUtil::s_nucleotides[random() % MyGTestUtil::s_numOfNucleotides];
        std::string str = ss.str();
        DNASequence dnaSequence(str);
        Codon codon(str.substr(0, Codon::s_codonSize));
        for (size_t i = 0; i < dnaSequence.length() - Codon::s_codonSize + 1; ++i) {
            ASSERT_TRUE(dnaSequence.codonAt(i) == codon);
            for (size_t j = 0; j < Codon::s_codonSize-1; ++j)
                codon[j] = codon[j+1];

            codon[Codon::s_codonSize-1] = dnaSequence[i+Codon::s_codonSize];
        }
        ss.clear();
        ss.str("");
    }
}

TEST(DNASequenceIteratorTests, BasicIteratorTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 99;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < random() % dnaMaxLen + 1; ++x)
            ss << MyGTestUtil::s_nucleotides[random() % MyGTestUtil::s_numOfNucleotides];
        std::string str = ss.str();
        DNASequence dnaSequence(str);
        DNASequence::iterator it = dnaSequence.begin();
        ASSERT_TRUE(it+dnaSequence.length() == dnaSequence.end());
        for (size_t i = 0; i < dnaSequence.length(); ++i) {
            if(random()%2 >= 1)
                ASSERT_TRUE(*(it++) == dnaSequence[i]);
            else {
                ASSERT_TRUE(*(it) == dnaSequence[i]);
                ++it;
            }
        }
        ss.clear();
        ss.str("");
    }
}

TEST(DNASequenceIteratorTests, ReverseIteratorTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 99;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < random() % dnaMaxLen + 1; ++x)
            ss << MyGTestUtil::s_nucleotides[random() % MyGTestUtil::s_numOfNucleotides];
        std::string str = ss.str();
        DNASequence dnaSequence(str);
        DNASequence::iterator it = dnaSequence.begin() + (dnaSequence.length() - 1);
        ASSERT_TRUE(it - (dnaSequence.length() - 1) == dnaSequence.begin());
        size_t maxSize = -1;
        for (size_t i = dnaSequence.length()-1; i != maxSize; --i) {
            if(random()%2 >= 1)
                ASSERT_TRUE(*(it--) == dnaSequence[i]);
            else {
                ASSERT_TRUE(*(it) == dnaSequence[i]);
                --it;
            }
        }
        ss.clear();
        ss.str("");
    }
}

TEST(DNASequenceIteratorTests, RandmonAcessIteratorTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 99;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < random() % dnaMaxLen + 1; ++x)
            ss << MyGTestUtil::s_nucleotides[random() % MyGTestUtil::s_numOfNucleotides];
        std::string str = ss.str();
        DNASequence dnaSequence(str);
        DNASequence::iterator it = dnaSequence.begin();
        ASSERT_TRUE(it+dnaSequence.length() == dnaSequence.end());
        size_t j = 0;
        for (size_t i = 0; i < dnaSequence.length(); ++i) {
            ASSERT_TRUE((it[i]) == dnaSequence[i]);

        }
        ss.clear();
        ss.str("");
    }
}

TEST(DNASequenceManipulationMethodsTests, SliceMethodTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 90, minLen = 10, slicingIteration = 10;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < random() % dnaMaxLen + minLen; ++x)
            ss << MyGTestUtil::s_nucleotides[random() % MyGTestUtil::s_numOfNucleotides];
        std::string str = ss.str();
        DNASequence dnaSequence(str);
       size_t begin = 0, end = 0, strLen = str.length();
        for (size_t i = 0; i < slicingIteration; ++i) {
            begin = random() % (strLen - 1);
            end = random() % (strLen - begin) + begin + 1;
            ASSERT_TRUE(dnaSequence.slice(begin, end).asString() == str.substr(begin, end-begin));
        }
        ss.clear();
        ss.str("");
    }
}

TEST(DNASequenceManipulationMethodsTests, FindMethodTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 90, minLen = 10, slicingIteration = 10;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < random() % dnaMaxLen + minLen; ++x)
            ss << MyGTestUtil::s_nucleotides[random() % MyGTestUtil::s_numOfNucleotides];
        std::string str = ss.str();
        DNASequence dnaSequence(str);
        size_t begin = 0, end = 0, strLen = str.length();
        for (size_t i = 0; i < slicingIteration; ++i) {
            begin = random() % (strLen - 1);
            end = random() % (strLen - begin) + begin + 1;
            string subStr = str.substr(begin, end-begin);
            size_t indexOfSubStr = str.find(subStr);

            ASSERT_TRUE(dnaSequence.find(subStr) == indexOfSubStr);
        }
        ss.clear();
        ss.str("");
    }
}

TEST(DNASequenceManipulationMethodsTests, CountMethodTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 90, minLen = 15, slicingIteration = 5;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < random() % dnaMaxLen + minLen; ++x)
            ss << MyGTestUtil::s_nucleotides[random() % MyGTestUtil::s_numOfNucleotides];
        std::string randomString = ss.str();
        DNASequence dnaSequence(randomString);
        size_t maxSubStringLen = 15, minSubStringLen = 5;
        // to slice the string
        size_t beginSlicing = 0, endSlicing = 0;
        // sub string length is between minSubStringLen (5) and maxSubStringLen(15)
        size_t subStrLen = randomString.length()%maxSubStringLen + minSubStringLen;
        for (size_t i = 0; i < slicingIteration; ++i) {
            beginSlicing = random() % (subStrLen - 1);
            endSlicing = random() % (subStrLen - beginSlicing) + beginSlicing + 1;

            string subStrOfRandomString = randomString.substr(beginSlicing, endSlicing-beginSlicing);

            size_t count = 0, pos=0;
            while((pos = randomString.find(subStrOfRandomString, pos)) != string::npos) {
                ++pos;
                ++count;
            }

            ASSERT_TRUE(dnaSequence.count(subStrOfRandomString) == count);
        }
        ss.clear();
        ss.str("");
    }
}

TEST(DNASequenceManipulationMethodsTests, FindAllMethodTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 90, minLen = 15, slicingIteration = 5;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < random() % dnaMaxLen + minLen; ++x)
            ss << MyGTestUtil::s_nucleotides[random() % MyGTestUtil::s_numOfNucleotides];
        std::string randomString = ss.str();
        DNASequence dnaSequence(randomString);
        size_t maxSubStringLen = 15, minSubStringLen = 5;
        // to slice the string
        size_t beginSlicing = 0, endSlicing = 0;
        // sub string length is between minSubStringLen (5) and maxSubStringLen(15)
        size_t subStrLen = randomString.length()%maxSubStringLen + minSubStringLen;
        for (size_t i = 0; i < slicingIteration; ++i) {
            beginSlicing = random() % (subStrLen - 1);
            endSlicing = random() % (subStrLen - beginSlicing) + beginSlicing + 1;

            string subStrOfRandomString = randomString.substr(beginSlicing, endSlicing-beginSlicing);
            vector<size_t> allIndexesOfSubString;
            size_t pos=0;
            while((pos = randomString.find(subStrOfRandomString, pos)) != string::npos) {
                allIndexesOfSubString.push_back(pos);
                ++pos;
            }

            ASSERT_TRUE(dnaSequence.findAll(subStrOfRandomString) == allIndexesOfSubString);
        }
        ss.clear();
        ss.str("");
    }
}

TEST(DNASequenceAdvancedMethodsTests, WriteToReadFromFilesTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 66, dnaMinLen = 35;
    vector<DNASequence> dnaSequences;
    stringstream ss;

    string fileName = "DNA-DataBase/DNA-Sequence-";
    for (size_t index = 0; index < totalRandomTests; ++index) {
        for (unsigned char x = 0; x < random() % dnaMaxLen + dnaMinLen; ++x)
            ss << MyGTestUtil::s_nucleotides[random() % MyGTestUtil::s_numOfNucleotides];

        dnaSequences.emplace_back(DNASequence(ss.str()));
        dnaSequences[index].writeToFile(fileName+to_string(index));

        ss.clear();
        ss.str("");
    }

    for (size_t index = 0; index < totalRandomTests; ++index) {
        DNASequence dnaSequence = DNASequence::readFromFile(fileName+to_string(index));
        ASSERT_TRUE(dnaSequences[index] == dnaSequence);
    }
}

TEST(DNASequenceManipulationMethodsTests, FindAllConsensusMethodTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 90, minLen = 15, slicingIteration = 5;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        for (unsigned char x = 0; x < random() % dnaMaxLen + minLen; ++x)
            ss << MyGTestUtil::s_nucleotides[random() % MyGTestUtil::s_numOfNucleotides];
        std::string randomString = ss.str();
        DNASequence dnaSequence(randomString);



        for (size_t i = 0; i < slicingIteration; ++i) {
            vector<pair<size_t, size_t>> allIndexesConsensus;


//            ASSERT_TRUE(dnaSequence.findConsensusSequences() == allIndexesConsensus);
        }
        ss.clear();
        ss.str("");
    }
}
