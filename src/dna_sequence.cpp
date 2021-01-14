//
// Created by ali-masa on 1/12/21.
//

#include <sstream>
#include <cstring>
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
    size_t index = 0;
    auto it = dnaSequence.cBegin();
    for (; it != dnaSequence.cEnd() && index < this->length(); ++it) {
        m_sequence[index++] = *it;
    }

    // if we need more size than the current length
    for (; it != dnaSequence.cEnd(); ++it, ++index) {
        m_sequence.emplace_back(Nucleotide(*it));
    }

    m_sequence.erase(m_sequence.cbegin() + index, m_sequence.cend());

    return *this;
}

DNASequence &DNASequence::operator=(const char *cStringSequence) {
    size_t index = 0;
    auto it = cStringSequence;
    for (; *it != 0 && index < this->length(); ++it) {
        m_sequence[index++] = *it;
    }

    // if we need more size than the current length
    for (; *it != 0; ++it, ++index) {
        m_sequence.emplace_back(Nucleotide(*it));
    }

    m_sequence.erase(m_sequence.cbegin() + index, m_sequence.cend());

    return *this;
}

DNASequence &DNASequence::operator=(const std::string &stringSequence) {
    size_t index = 0;
    for (; index < stringSequence.length() && index < this->length(); ++index) {
        m_sequence[index] = stringSequence[index];
    }

    // if we need more size than the current length
    for (; index < stringSequence.length(); ++index) {
        m_sequence.emplace_back( Nucleotide(stringSequence[index]) );
    }

    m_sequence.erase(m_sequence.cbegin() + index, m_sequence.cend());

    return *this;
}

Nucleotide &DNASequence::operator[](size_t index) {
    return m_sequence[index];
}

const Nucleotide &DNASequence::operator[](size_t index) const {
    return m_sequence[index];
}

Codon DNASequence::codonAt(size_t index) {
    if(index >= this->length() - Codon::s_codonSize + 1);
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
    return  iterator(m_sequence, this->length());
}

const iterator DNASequence::begin() const {
    return  iterator(m_sequence, 0);
}

const iterator DNASequence::end() const {
    return  iterator(m_sequence, this->length());
}

const iterator DNASequence::cBegin() const {
    return  iterator(m_sequence, 0);
}
const iterator DNASequence::cEnd() const {
    return  iterator(m_sequence, this->length());
}

DNASequence DNASequence::pair() const {
    std::stringstream ss;

    for (size_t i = 0; i < this->length(); ++i)
        ss << m_sequence[i].pair().asCharacter();

    return  DNASequence(ss.str());
}

std::string DNASequence::asString() const {
    std::stringstream ss;

    for (size_t i = 0; i < this->length(); ++i)
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
    for (size_t i = 0; i < dnaSequence.length(); ++i)
        os << dnaSequence.m_sequence[i].asCharacter();

    return os;
}

size_t DNASequence::writeToFile(std::string fileName) const {

}

size_t DNASequence::readFromFile(std::string fileName) {

}