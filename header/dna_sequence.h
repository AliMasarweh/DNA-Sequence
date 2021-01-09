//
// Created by ali-masa on 1/9/21.
//

#ifndef DNA_SEQUENCE_DNA_SEQUENCE_H
#define DNA_SEQUENCE_DNA_SEQUENCE_H

#include <string>
class Nucleotide;
class Codon;

class DNASequence {
public:
    DNASequence();

    DNASequence(const char * cStringSequence);
    DNASequence(const std::string& stringSequence);

    DNASequence(const DNASequence& dnaSequence);
    DNASequence& operator=(const DNASequence& dnaSequence);

    DNASequence& operator=(const char * cStringSequence);
    DNASequence& operator=(const std::string& stringSequence);

    friend std::ostream & operator<<(std::ostream & os, const DNASequence& dnaSequence);
    friend bool operator==(const DNASequence& dnaSequence1, const DNASequence& dnaSequence2);
    friend bool operator!=(const DNASequence& dnaSequence1, const DNASequence& dnaSequence2);

    Nucleotide& operator[](size_t index);

    // might not be that useful for phase 2
    // codons can start at any index
    Codon& codonAt(size_t index);
private:
};

#endif //DNA_SEQUENCE_DNA_SEQUENCE_H
