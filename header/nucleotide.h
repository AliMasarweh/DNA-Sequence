//
// Created by ali-masa on 1/9/21.
//

#ifndef DNA_SEQUENCE_NUCLEOTIDE_H
#define DNA_SEQUENCE_NUCLEOTIDE_H

#include <map>

class Nucleotide {
public:
    Nucleotide(char c);
    Nucleotide(const Nucleotide& nucleotide);

    Nucleotide& operator=(char c);
    Nucleotide& operator=(const Nucleotide& nucleotide);

    Nucleotide pair() const;
    char asCharacter() const;

    friend bool operator==(const Nucleotide& nucleotide1, const Nucleotide& nucleotide2);
    friend bool operator!=(const Nucleotide& nucleotide1, const Nucleotide& nucleotide2);

    const static unsigned char s_validNucleotidesNum = 4;

    static bool isValidNucleotide(const Nucleotide& nucleotide);

private:
    char m_nucleotideChar;

    const static char s_validNucleotide[s_validNucleotidesNum];
    static std::map<char, char> m_nucPairs;
};

#endif //DNA_SEQUENCE_NUCLEOTIDE_H
