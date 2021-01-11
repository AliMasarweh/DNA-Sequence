//
// Created by ali-masa on 1/10/21.
//

#include <cstring>
#include <sstream>

#include "../header/codon.h"
#include "../header/dna_sequence_exception.h"

#include <iostream>
Codon::Codon(const char* codon) {
    size_t index = 0;
    while(codon[index++] && index < Codon::s_codonSize);

    if(index != Codon::s_codonSize)
        throw InvalidCodonLengthException();

    for (unsigned  char i = 0; i < s_codonSize; ++i)
        m_codonSeq.emplace_back(codon[i]);
}

Codon::Codon(std::string codon) {
    if(codon.length() != s_codonSize)
        throw InvalidCodonLengthException();

    for (unsigned  char i = 0; i < s_codonSize; ++i)
        m_codonSeq.emplace_back(codon[i]);
}

Codon::Codon(const Codon &codon): m_codonSeq(codon.m_codonSeq) {}

Codon &Codon::operator=(const char *codon) {
    size_t index = 0;
    while(!codon[index++] && index < Codon::s_codonSize);

    if(index - 1 != Codon::s_codonSize)
        throw InvalidCodonLengthException();

    for (unsigned  char i = 0; i < s_codonSize; ++i)
        m_codonSeq.emplace_back(codon[i]);

    return *this;
}

Codon &Codon::operator=(std::string codon) {
    if(codon.length() != s_codonSize)
        throw InvalidCodonLengthException();

    for (unsigned  char i = 0; i < s_codonSize; ++i)
        m_codonSeq.emplace_back(codon[i]);

    return *this;
}

Codon &Codon::operator=(const Codon &codon) {
    for (unsigned  char i = 0; i < s_codonSize; ++i)
        m_codonSeq.emplace_back(codon[i]);

    return *this;
}

Codon Codon::pair() const {
    std::stringstream ss;
    for(auto it = m_codonSeq.begin(); it != m_codonSeq.end(); ++it)
        ss << it->pair().asCharacter();

    return Codon(ss.str());
}

Nucleotide &Codon::operator[](size_t index) {
    return m_codonSeq[index];
}

const Nucleotide &Codon::operator[](size_t index) const {
    return m_codonSeq[index];
}

bool operator==(const Codon& codon1, const Codon& codon2) {
    for (unsigned char i = 0; i < codon1.m_codonSeq.size(); ++i)
        if(codon1[i] != codon2[i])
            return false;

    return true;
}

bool operator!=(const Codon& codon1, const Codon& codon2) {
    return !(codon1 == codon2);
}

bool Codon::isStartingCodon(const Codon &codon) {
    return false;
}

bool Codon::isEndingCodon(const Codon &codon) {
    return false;
}

bool Codon::isValidCodonSequence(const Codon &codon) {
    // nucleotide creation already validates characters of sequence
    return codon.m_codonSeq.size() == s_codonSize;
}

