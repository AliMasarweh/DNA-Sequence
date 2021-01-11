//
// Created by ali-masa on 1/10/21.
//

#include "../header/codon.h"

Codon::Codon(char codon[Codon::s_codonSize]) {
    for (unsigned  char i = 0; i < s_codonSize; ++i)
        m_codonSeq.push_back(Nucleotide(codon[i]));
}

