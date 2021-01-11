//
// Created by ali-masa on 1/10/21.
//

#include <cstring>
#include <sstream>

#include "../header/codon.h"
#include "../header/dna_sequence_exception.h"

// you can add GTG and TTG
const std::vector<Codon> Codon::s_startingCodons = { "ATG" };
const std::vector<Codon> Codon::s_endingCodons = { "TAG", "TAA" , "TGA" };

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

std::string Codon::asString() const {
    std::stringstream ss;
    for(auto it = m_codonSeq.begin(); it != m_codonSeq.end(); ++it)
        ss << it->asCharacter();

    return ss.str();
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
    return find(s_startingCodons.begin(), s_startingCodons.end(), codon) != s_startingCodons.end();
}

bool Codon::isEndingCodon(const Codon &codon) {
    return find(s_endingCodons.begin(), s_endingCodons.end(), codon) != s_endingCodons.end();
}

Codon::CodonTypes Codon::typeOfCodon(const Codon& codon) {
    static std::map<std::string, CodonTypes> codonToTypeMap;
    for (auto it = s_startingCodons.begin(); it != s_startingCodons.end(); ++it) {
        codonToTypeMap.emplace(std::pair<std::string, CodonTypes>(it->asString(), CodonTypes::startingCodon));
        codonToTypeMap.emplace(std::pair<std::string, CodonTypes>(it->asString(), CodonTypes::pairOfStartingCodon));
    }

    for (auto it = s_endingCodons.begin(); it != s_endingCodons.end(); ++it) {
        codonToTypeMap.emplace(std::pair<std::string, CodonTypes>(it->asString(), CodonTypes::endingCodon));
        codonToTypeMap.emplace(std::pair<std::string, CodonTypes>(it->asString(), CodonTypes::pairOfEndingCodon));
    }

    std::string codonAsString = codon.asString();
    if(codonToTypeMap.find(codonAsString) != codonToTypeMap.end())
        return codonToTypeMap.at(codonAsString);

    return CodonTypes::normalCodon;
}

bool Codon::isValidCodonSequence(const Codon &codon) {
    // nucleotide creation already validates characters of sequence
    return codon.m_codonSeq.size() == s_codonSize;
}

