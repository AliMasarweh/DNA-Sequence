//
// Created by ali-masa on 1/9/21.
//

#ifndef DNA_SEQUENCE_NUCLEOTIDE_H
#define DNA_SEQUENCE_NUCLEOTIDE_H

#include <map>
#include "dna_sequence_exception.h"

class Nucleotide {
public:
    Nucleotide(char c);
    Nucleotide(const Nucleotide& nucleotide);

    Nucleotide& operator=(char c);
    Nucleotide& operator=(const Nucleotide& nucleotide);

    Nucleotide pair() const;

    friend bool operator==(const Nucleotide& nucleotide1, const Nucleotide& nucleotide2);
    friend bool operator!=(const Nucleotide& nucleotide1, const Nucleotide& nucleotide2);

private:
    char m_nucleotideChar;

    static std::map<char, char> m_nucPairs;
};

#endif //DNA_SEQUENCE_NUCLEOTIDE_H
