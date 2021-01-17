//
// Created by ali-masa on 1/12/21.
//

#include <sstream>
#include <cstring>
#include <iostream>
#include <fstream>

#include "../header/dna_sequence.h"
#include "../header/utility/KMPSearcher.h"

DNASequence::DNASequence(const char *cStringSequence) {
    while (*cStringSequence)
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
using CItertor=DNASequence::ConstIterator;

iterator DNASequence::begin() {
    return  iterator(m_sequence, 0);
}

iterator DNASequence::end() {
    return  iterator(m_sequence, this->length());
}

CItertor DNASequence::begin() const {
    return  CItertor(m_sequence, 0);
}

CItertor DNASequence::end() const {
    return  CItertor(m_sequence, this->length());
}

CItertor DNASequence::cBegin() const {
    return  CItertor(m_sequence, 0);
}
CItertor DNASequence::cEnd() const {
    return  CItertor(m_sequence, this->length());
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

void DNASequence::writeToFile(const std::string& fileName) const {
    std::ofstream file(fileName);
    if (file.is_open())
        file << this->asString();
    file.close();
}

DNASequence DNASequence::readFromFile(const std::string& fileName) {
    DNASequence ret("A");
    std::string line;
    std::ifstream file (fileName);
    if (file.is_open())
    {
        if(getline (file,line)) {
            std::cout << "LINE " << line << std::endl;
            ret = line;
        }
        file.close();
    }

    return ret;
}


DNASequence DNASequence::slice(size_t start, size_t end) {
    char seq[end - start + 1];
    for (size_t i = start; i < end; ++i) {
        seq[i-start] = m_sequence[i].asCharacter();
    }
    seq[end - start] = 0;

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

size_t DNASequence::find(const DNASequence& subSequence, size_t startIndex) const {
    for (; startIndex < this->length() - subSequence.length() + 1; ++startIndex) {
        size_t subSeqIndex = 0;
        for (; subSeqIndex < subSequence.length(); ++subSeqIndex) {
            if((*this)[startIndex+subSeqIndex] != subSequence[subSeqIndex]) {
                break;
            }
        }

        if (subSeqIndex == subSequence.length())
            return startIndex;
    }

    return std::string::npos;
}

std::pair<size_t, size_t> DNASequence::findKMPS(const DNASequence& subSequence,
                                                size_t startIndex, size_t startIndexLPS) const {
    std::vector<size_t> lpsArray;
    KMPSearcher<DNASequence>::computeLPSArray(subSequence, lpsArray);

    return KMPSearcher<DNASequence>::KMPSearch(*this, subSequence, lpsArray, startIndex, startIndexLPS);
}

size_t DNASequence::count(const DNASequence& subSequence) const {
    size_t count = 0;

    std::pair<size_t, size_t> p(-subSequence.length(),0);
    while((p = this->findKMPS(subSequence, p.first+subSequence.length(), p.second)) != KMPSearcher<DNASequence>::s_endPair) {
        ++count;
    }

    return count;
}

std::vector<size_t> DNASequence::findAll(const DNASequence& subSequence) const {
    /*std::vector<size_t> ret;
    size_t i = 0;
    while((i = this->find(subSequence, i)) != std::string::npos) {
        ret.push_back(i);
        ++i;
    }

    return ret;*/

    std::vector<size_t> ret;

    std::pair<size_t, size_t> p(-subSequence.length(),0);
    while((p = this->findKMPS(subSequence, p.first+subSequence.length(), p.second)) != KMPSearcher<DNASequence>::s_endPair) {
        ret.push_back(p.first);
    }

    return ret;
}

std::vector<std::pair<size_t, size_t>> DNASequence::findConsensusSequences() const {
    std::vector<std::pair<size_t, size_t>> ret;
    size_t start = 0;
    while((start = minStartingCodonIndex(start)) != std::string::npos) {
        size_t end = start;
        if((end = minEndingCodonIndex(end)) == std::string::npos)
            break;
        ret.emplace_back(start, end);
        ++start;
    }

    return ret;
}

size_t DNASequence::minStartingCodonIndex(size_t start) const {
    size_t minIndex = std::string::npos;

    for (Codon codon: Codon::s_startingCodons)
        minIndex = std::min(minIndex, this->find(DNASequence(codon.asString()), start));

    return minIndex;
}

size_t DNASequence::minEndingCodonIndex(size_t start) const {
    size_t minIndex = std::string::npos;

    for (Codon codon: Codon::s_endingCodons)
        minIndex = std::min(minIndex, this->find(DNASequence(codon.asString()), start));

    return minIndex;
}
