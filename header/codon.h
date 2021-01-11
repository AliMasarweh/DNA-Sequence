//
// Created by ali-masa on 1/9/21.
//

#ifndef DNA_SEQUENCE_CODON_H
#define DNA_SEQUENCE_CODON_H

#include <string>
#include <vector>

#include "nucleotide.h"

class Codon {
public:
    const static unsigned char s_codonSize = 4;
    Codon(char codon[Codon::s_codonSize]);
    Codon(std::string codon);
    Codon(const Codon& codon);

    Codon& operator=(char codon[Codon::s_codonSize]);
    Codon& operator=(std::string codon);
    Codon& operator=(const Codon& codon);

    Codon pair() const;

    Nucleotide& operator[](size_t index);

    static bool isStartingCodon(const Codon& codon);
    static bool isEndingCodon(const Codon& codon);
private:
    std::vector<Nucleotide> m_codonSeq;
};

#endif //DNA_SEQUENCE_CODON_H
