//
// Created by ali-masa on 1/9/21.
//

#include <gtest/gtest.h>
#include <set>
#include <random>

using namespace std;

#include "../header/dna_sequence.h"
#include "../header/dna_sequence_exception.h"

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
namespace GTestRandomSpace {
    static const default_random_engine generator;
    static std::uniform_int_distribution<size_t> distribution(1, 1000);
    static auto generate = std::bind(distribution, generator);
};

class MyGTestUtil {
public:
    static Nucleotide randomNucleotide() {
        return s_nucleotides[randomNumber()%s_numOfNucleotides];
    }

    static Codon randomCodon(stringstream& ss) {
        for (unsigned char x = 0; x < Codon::s_codonSize; ++x) {
            char c = MyGTestUtil::randomNucleotide().asCharacter();
            ss << c;
        }

        return Codon(ss.str());
    }

    static pair<Codon, Codon> randomCodon(stringstream& ss, stringstream& flipped_ss) {
        for (unsigned char x = 0; x < Codon::s_codonSize; ++x) {
            char c = MyGTestUtil::randomNucleotide().asCharacter();
            ss << c;
            flipped_ss  << MyGTestUtil::s_nucPairs.at(c);
        }

        return pair<Codon, Codon>(Codon(ss.str()), Codon(flipped_ss.str()));
    }

    static DNASequence randomDNASequence(size_t dnaMinLen, size_t dnaMaxLen, stringstream& ss) {
        for (unsigned char x = 0; x < random() % dnaMaxLen + dnaMinLen; ++x) {
            char c = MyGTestUtil::randomNucleotide().asCharacter();
            ss << c;
        }

        return DNASequence(ss.str());
    }

    static pair<DNASequence, DNASequence> randomDNASequence(size_t dnaMinLen, size_t dnaMaxLen, stringstream& ss, stringstream& flipped_ss) {
        for (unsigned char x = 0; x < random() % dnaMaxLen + dnaMinLen; ++x) {
            char c = MyGTestUtil::randomNucleotide().asCharacter();
            ss << c;
            flipped_ss  << MyGTestUtil::s_nucPairs.at(c);
        }

        return pair<DNASequence, DNASequence>(DNASequence(ss.str()), DNASequence(flipped_ss.str()));
    }

    static size_t randomNumber() {
        return GTestRandomSpace::generate();
    }

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

static void emptyStream(stringstream& ss) {
    ss.clear();
    ss.str("");
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
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000;
    stringstream ss, flipped_ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        pair<Codon, Codon> pair1 = MyGTestUtil::randomCodon(ss, flipped_ss);

        ASSERT_TRUE(pair1.first.pair() == pair1.second);
        emptyStream(ss);
        emptyStream(flipped_ss);
    }
}


TEST(CodonBasicTests, RationalOperatorsTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        Codon codon = MyGTestUtil::randomCodon(ss);

        ASSERT_TRUE(codon == ss.str());
        emptyStream(ss);
    }
}

TEST(CodonBasicTests, AsStringMethodTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        Codon codon = MyGTestUtil::randomCodon(ss);

        ASSERT_TRUE(codon.asString() == ss.str());
        emptyStream(ss);
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

    size_t totalRandomTests = 1000, dnaMaxLen = 99, dnaMinLen = 1;
    stringstream ss, flipped_ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        pair<DNASequence, DNASequence> pair1 = MyGTestUtil::randomDNASequence(dnaMinLen, dnaMaxLen, ss, flipped_ss);

        ASSERT_TRUE(pair1.first.pair() == pair1.second);
        emptyStream(ss);
        emptyStream(flipped_ss);
    }
}


TEST(DNASequenceBasicTests, RationalOperatorsTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 99, dnaMinLen = 1;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        DNASequence dnaSequence = MyGTestUtil::randomDNASequence(dnaMinLen, dnaMaxLen, ss);

        ASSERT_TRUE(dnaSequence == ss.str());
        emptyStream(ss);
    }
}

TEST(DNASequenceBasicTests, AsStringMethodTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 99, dnaMinLen = 1;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        DNASequence dnaSequence = MyGTestUtil::randomDNASequence(dnaMinLen, dnaMaxLen, ss);

        ASSERT_TRUE(DNASequence(ss.str()).asString() == ss.str());
        emptyStream(ss);
    }
}

TEST(DNASequenceBasicTests, LengthTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 99, dnaMinLen = 1;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        DNASequence dnaSequence = MyGTestUtil::randomDNASequence(dnaMinLen, dnaMaxLen, ss);

        ASSERT_TRUE(DNASequence(ss.str()).length() == ss.str().length());
        emptyStream(ss);
    }
}

TEST(DNASequenceBasicTests, BracketsOperatorTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 99, dnaMinLen = 1;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        DNASequence dnaSequence = MyGTestUtil::randomDNASequence(dnaMinLen, dnaMaxLen, ss);
        std::string str = ss.str();

        for (size_t i = 0; i < dnaSequence.length(); ++i)
            ASSERT_TRUE(dnaSequence[i] == str[i]);
        emptyStream(ss);
    }
}

TEST(DNASequenceBasicTests, CodonAtMethodTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 97, dnaMinLen = Codon::s_codonSize;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        DNASequence dnaSequence = MyGTestUtil::randomDNASequence(dnaMinLen, dnaMaxLen, ss);
        std::string str = ss.str();
        Codon codon(str.substr(0, Codon::s_codonSize));

        for (size_t i = 0; i < dnaSequence.length() - Codon::s_codonSize + 1; ++i) {
            ASSERT_TRUE(dnaSequence.codonAt(i) == codon);
            for (size_t j = 0; j < Codon::s_codonSize-1; ++j)
                codon[j] = codon[j+1];

            codon[Codon::s_codonSize-1] = dnaSequence[i+Codon::s_codonSize];
        }
        emptyStream(ss);
    }
}

TEST(DNASequenceIteratorTests, BasicIteratorTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 99, dnaMinLen = 1;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        DNASequence dnaSequence = MyGTestUtil::randomDNASequence(dnaMinLen, dnaMaxLen, ss);
        std::string str = ss.str();
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
        emptyStream(ss);
    }
}

TEST(DNASequenceIteratorTests, ReverseIteratorTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 99, dnaMinLen = 1;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        DNASequence dnaSequence = MyGTestUtil::randomDNASequence(dnaMinLen, dnaMaxLen, ss);
        std::string str = ss.str();
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
        emptyStream(ss);
    }
}

TEST(DNASequenceIteratorTests, RandmonAcessIteratorTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 99, dnaMinLen = 1;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        DNASequence dnaSequence = MyGTestUtil::randomDNASequence(dnaMinLen, dnaMaxLen, ss);
        std::string str = ss.str();
        DNASequence::iterator it = dnaSequence.begin();

        ASSERT_TRUE(it+dnaSequence.length() == dnaSequence.end());
        size_t j = 0;
        for (size_t i = 0; i < dnaSequence.length(); ++i) {
            ASSERT_TRUE((it[i]) == dnaSequence[i]);

        }
        emptyStream(ss);
    }
}

TEST(DNASequenceManipulationMethodsTests, SliceMethodTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 90, minLen = 10, slicingIteration = 10;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        DNASequence dnaSequence = MyGTestUtil::randomDNASequence(minLen, dnaMaxLen, ss);
        std::string str = ss.str();
        size_t begin = 0, end = 0, strLen = str.length();
        for (size_t i = 0; i < slicingIteration; ++i) {
            begin = random() % (strLen - 1);
            end = random() % (strLen - begin) + begin + 1;
            ASSERT_TRUE(dnaSequence.slice(begin, end).asString() == str.substr(begin, end-begin));
        }
        emptyStream(ss);
    }
}

TEST(DNASequenceManipulationMethodsTests, FindMethodTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 90, minLen = 10, slicingIteration = 10;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        DNASequence dnaSequence = MyGTestUtil::randomDNASequence(minLen, dnaMaxLen, ss);
        std::string str = ss.str();
        size_t begin = 0, end = 0, strLen = str.length();

        for (size_t i = 0; i < slicingIteration; ++i) {
            begin = random() % (strLen - 1);
            end = random() % (strLen - begin) + begin + 1;
            string subStr = str.substr(begin, end-begin);

            ASSERT_TRUE(dnaSequence.find(subStr) == str.find(subStr));
        }
        emptyStream(ss);
    }
}

TEST(DNASequenceManipulationMethodsTests, CountMethodTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 90, minLen = 15, slicingIteration = 5;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        DNASequence dnaSequence = MyGTestUtil::randomDNASequence(minLen, dnaMaxLen, ss);
        std::string randomString = ss.str();
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
        emptyStream(ss);
    }
}

TEST(DNASequenceManipulationMethodsTests, FindAllMethodTest) {
    srand((unsigned ) time(nullptr));

    size_t totalRandomTests = 1000, dnaMaxLen = 90, minLen = 15, slicingIteration = 5;
    stringstream ss;

    for (size_t i = 0; i < totalRandomTests; ++i) {
        DNASequence dnaSequence = MyGTestUtil::randomDNASequence(minLen, dnaMaxLen, ss);
        std::string randomString = ss.str();
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
        emptyStream(ss);
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
            ss << MyGTestUtil::randomNucleotide().asCharacter();

        dnaSequences.emplace_back(DNASequence(ss.str()));
        dnaSequences[index].writeToFile(fileName+to_string(index));

        emptyStream(ss);
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
        DNASequence dnaSequence = MyGTestUtil::randomDNASequence(minLen, dnaMaxLen, ss);
        std::string randomString = ss.str();

        for (size_t i = 0; i < slicingIteration; ++i) {
            vector<pair<size_t, size_t>> allIndexesConsensus;


//            ASSERT_TRUE(dnaSequence.findConsensusSequences() == allIndexesConsensus);
        }
        emptyStream(ss);
    }
}
