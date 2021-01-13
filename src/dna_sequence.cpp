//
// Created by ali-masa on 1/12/21.
//

#include <sstream>
#include "../header/dna_sequence.h"

DNASequence::DNASequence(const char *cStringSequence) {
    while (! *cStringSequence)
        m_sequence.emplace_back( Nucleotide(* (cStringSequence++)) );
}

DNASequence::DNASequence(const std::string &stringSequence) {
    for (auto it = stringSequence.begin(); it != stringSequence.end(); ++it)
        m_sequence.emplace_back( Nucleotide(*it) );
}

DNASequence::DNASequence(const DNASequence &dnaSequence) {
    for (auto it = dnaSequence.cBegin(); it != dnaSequence.cEnd(); ++it) {
        m_sequence.emplace_back(Nucleotide(*it));
    }
}

DNASequence &DNASequence::operator=(const DNASequence &dnaSequence) {
    return *this;
}

DNASequence &DNASequence::operator=(const char *cStringSequence) {
    return *this;
}

DNASequence &DNASequence::operator=(const std::string &stringSequence) {
    return *this;
}

Nucleotide &DNASequence::operator[](size_t index) {
    return m_sequence[index];
}

const Nucleotide &DNASequence::operator[](size_t index) const {
    return m_sequence[index];
}

Codon DNASequence::codonAt(size_t index) {
    if(index >= m_sequence.size() - Codon::s_codonSize + 1);
    std::stringstream ss;

    for (size_t i = 0; i < Codon::s_codonSize; ++i)
        ss << m_sequence[index + i].asCharacter();

    return  Codon(ss.str());
}


using iterator=DNASequence::iterator;

iterator DNASequence::begin() {
    return  iterator(m_sequence, 0);
}

iterator DNASequence::end() {
    return  iterator(m_sequence, m_sequence.size());
}

const iterator DNASequence::cBegin() const {
    return  iterator(m_sequence, 0);
}
const iterator DNASequence::cEnd() const {
    return  iterator(m_sequence, m_sequence.size());
}

DNASequence DNASequence::pair() const {
    std::stringstream ss;

    for (size_t i = 0; i < m_sequence.size(); ++i)
        ss << m_sequence[i].pair().asCharacter();

    return  DNASequence(ss.str());
}

std::string DNASequence::asString() const {
    std::stringstream ss;

    for (size_t i = 0; i < m_sequence.size(); ++i)
        ss << m_sequence[i].asCharacter();

    return  ss.str();
}

bool operator==(const DNASequence &dnaSequence1, const DNASequence &dnaSequence2) {
    if (dnaSequence1.length() != dnaSequence2.length())
        return false;

    for (size_t i = 0; i < dnaSequence1.length(); ++i)
        if (dnaSequence1[i] != dnaSequence2[i])
            return false;

    return true;
}

bool operator!=(const DNASequence &dnaSequence1, const DNASequence &dnaSequence2) {
    return !(dnaSequence1 == dnaSequence2);
}

std::ostream & operator<<(std::ostream & os, const DNASequence& dnaSequence) {
    for (size_t i = 0; i < dnaSequence.m_sequence.size(); ++i)
        os << dnaSequence.m_sequence[i].asCharacter();

    return os;
}