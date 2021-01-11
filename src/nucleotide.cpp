//
// Created by ali-masa on 1/9/21.
//

#include <map>

#include "../header/nucleotide.h"

using namespace  std;

map<char, char> Nucleotide::m_nucPairs = {
        {'A', 'T'},
        {'T', 'A'},
        {'C', 'G'},
        {'G', 'C'}
};

const char Nucleotide::s_validNucleotide[Nucleotide::s_validNucleotideNum] = {
            'A', 'T', 'C', 'G'
};

Nucleotide::Nucleotide(char c): m_nucleotideChar(c) {
    if(!isValidNucleotide(*this))
        throw InvalidNucleotideException();
}
Nucleotide::Nucleotide(const Nucleotide& nucleotide)
                    :m_nucleotideChar(nucleotide.m_nucleotideChar) {
    if(!isValidNucleotide(*this))
        throw InvalidNucleotideException();
}

Nucleotide& Nucleotide::operator=(char c) {
    m_nucleotideChar = c;

    return *this;
}
Nucleotide& Nucleotide::operator=(const Nucleotide& nucleotide) {
    m_nucleotideChar = nucleotide.m_nucleotideChar;

    return *this;
}

Nucleotide Nucleotide::pair() const {
    /*return (m_nucleotideChar=='A')*'T' + (m_nucleotideChar=='T')*'A'
            + (m_nucleotideChar=='C')*'G' + (m_nucleotideChar=='G')*'C';*/

    return Nucleotide::m_nucPairs[m_nucleotideChar];
}

bool operator==(const Nucleotide& nucleotide1, const Nucleotide& nucleotide2) {
    return  nucleotide1.m_nucleotideChar == nucleotide2.m_nucleotideChar;
}
bool operator!=(const Nucleotide& nucleotide1, const Nucleotide& nucleotide2) {
    return !(nucleotide1 == nucleotide2);
}

bool Nucleotide::isValidNucleotide(const Nucleotide& nucleotide) {
    for (unsigned char i = 0; i < Nucleotide::s_validNucleotideNum; ++i)
        if(nucleotide.m_nucleotideChar == Nucleotide::s_validNucleotide[i])
            return true;

    return false;
}
