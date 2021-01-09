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
    DNASequence(const string& stringSequence);

    DNASequence(const DNASequence& dnaSequence);
    DNASequence& operator=(const DNASequence& dnaSequence);

    DNASequence& operator=(const char * cStringSequence);
    DNASequence& operator=(const string& stringSequence);

    friend ostream & operator<<(ostream & os, const DNASequence& dnaSequence);
    friend bool operator==(const DNASequence& dnaSequence1, const DNASequence& dnaSequence2);
    friend bool operator!=(const DNASequence& dnaSequence1, const DNASequence& dnaSequence2);

    Nucleotide& operator[](size_t index) const;
    Codon& codonAt(size_t index) const;
private:
};

#endif //DNA_SEQUENCE_DNA_SEQUENCE_H
