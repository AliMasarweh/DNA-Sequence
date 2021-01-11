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
    const static unsigned char s_codonSize = 3;
    Codon(const char* codon);
    Codon(std::string codon);
    Codon(const Codon& codon);

    Codon& operator=(const char* codon);
    Codon& operator=(std::string codon);
    Codon& operator=(const Codon& codon);

    friend bool operator==(const Codon& codon1, const Codon& codon2);
    friend bool operator!=(const Codon& codon1, const Codon& codon2);

    Codon pair() const;
    std::string asString() const;

    Nucleotide& operator[](size_t index);
    const Nucleotide& operator[](size_t index) const;

    enum class CodonTypes {normalCodon, startingCodon, endingCodon, pairOfStartingCodon, pairOfEndingCodon};

    static bool isStartingCodon(const Codon& codon);
    static bool isEndingCodon(const Codon& codon);
    static CodonTypes typeOfCodon(const Codon& codon);

    static bool isValidCodonSequence(const Codon& codon);
private:
    const static std::vector<Codon> s_startingCodons;
    const static std::vector<Codon> s_endingCodons;
    std::vector<Nucleotide> m_codonSeq;
};

#endif //DNA_SEQUENCE_CODON_H
