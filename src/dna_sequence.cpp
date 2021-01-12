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
    for (auto it = dnaSequence.begin(); it != dnaSequence.end(); ++it) {
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

Codon DNASequence::codonAt(size_t index) {
    if(index >= m_sequence.size() - Codon::s_codonSize + 1);
    std::stringstream ss;

    for (size_t i = index; i < index + Codon::s_codonSize; ++i)
        ss << m_sequence[i].asCharacter();

    return  Codon(ss.str());
}



using iterator=DNASequence::iterator;

iterator::iterator(std::vector<Nucleotide>& m_sequence, size_t index): m_sequenceReference(m_sequence),
                    m_index(index) {}

const Nucleotide &iterator::operator*() const { return m_sequenceReference[m_index]; }

const Nucleotide *iterator::operator->() const { return &(m_sequenceReference[m_index]); }

iterator &iterator::operator++() {
    ++m_index;
    return *this;
}

iterator iterator::operator++(int) {
    iterator it(m_sequenceReference, m_index++);
    return it;
}

iterator &iterator::operator--() {
    --m_index;
    return *this;
}

iterator iterator::operator--(int) {
    iterator it(m_sequenceReference, m_index--);
    return it;
}

iterator &iterator::operator+=(size_t index) {
    m_index += index;
    return *this;
}

iterator &iterator::operator-=(size_t index) {
    m_index -= index;
    return *this;
}

Nucleotide &iterator::operator[](size_t) const {
    return m_sequenceReference[m_index];
}
