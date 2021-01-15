//
// Created by ali-masa on 1/14/21.
//

#include "../header/dna_sequence.h"
#include "../header/dna_sequence_exception.h"

using CIterator=DNASequence::ConstIterator;

CIterator::ConstIterator(const std::vector<Nucleotide>& m_sequence, size_t index)
        : m_sequenceReference(const_cast<std::vector<Nucleotide>&>(m_sequence)), m_index(index) {}


const Nucleotide &CIterator::operator*() const {
    if(m_index > m_sequenceReference.size()) { throw IteratorOutOfBoundsException(); }

    return m_sequenceReference[m_index];
}

const Nucleotide *CIterator::operator->() const {
    if(m_index > m_sequenceReference.size()) { throw IteratorOutOfBoundsException(); }

    return &(m_sequenceReference[m_index]);
}

const CIterator &CIterator::operator++() const {
    ++m_index;
    return *this;
}

CIterator CIterator::operator++(int) const {
    CIterator it(m_sequenceReference, m_index++);
    return it;
}

const CIterator &CIterator::operator--() const{
    --m_index;
    return *this;
}

CIterator CIterator::operator--(int) const{
    CIterator it(m_sequenceReference, m_index--);
    return it;
}

void swap(CIterator& lhs, CIterator& rhs) {
    size_t index = lhs.m_index;
    lhs.m_index = rhs.m_index;
    rhs.m_index = index;
}

CIterator operator+(const CIterator& it, size_t index) {
    return CIterator(it.m_sequenceReference, it.m_index + index);
}

CIterator operator+(size_t index, const CIterator& it) {
    return CIterator(it.m_sequenceReference, it.m_index + index);
}

const CIterator &CIterator::operator+=(size_t index) const {
    m_index += index;
    return *this;
}

const CIterator &CIterator::operator-=(size_t index) const {
    m_index -= index;
    return *this;
}

CIterator operator-(const CIterator& it, size_t index) {
    return CIterator(it.m_sequenceReference, it.m_index-index);
}

const Nucleotide &CIterator::operator[](size_t index) const {
    if(m_index + index > m_sequenceReference.size()) { throw IteratorOutOfBoundsException(); }

    return m_sequenceReference[m_index + index];
}

bool operator==(const CIterator& it1, const CIterator& it2) {
    return (& it1.m_sequenceReference) == (& it2.m_sequenceReference) && (it1.m_index == it2.m_index) ||
           (it1.m_index > it1.m_sequenceReference.size() && it2.m_index > it2.m_sequenceReference.size());
}

bool operator!=(const CIterator& it1, const CIterator& it2) {
    return !(it1 == it2);
}


DNASequence DNASequence::slice(size_t start, size_t end) {
    char seq[end - start];
    for (size_t i = start; i < end - 1; ++i) {
        seq[i-start] = m_sequence[i].asCharacter();
    }
    seq[end - start - 1] = 0;

    return DNASequence(seq);
}

DNASequence DNASequence::pairSequence() const {
    char seq[this->length()+1];
    for (size_t i = 0; i < this->length(); ++i) {
        seq[i] = m_sequence[i].pair().asCharacter();
    }
    seq[this->length()] = 0;

    return DNASequence(seq);
}

DNASequence::iterator DNASequence::find(DNASequence subSequence) const {
    return DNASequence::iterator();
}

size_t DNASequence::count(DNASequence subSequence) const {
    return 0;
}

std::vector<iterator> DNASequence::findAll(DNASequence subSequence) const {
    return std::vector<iterator>();
}
