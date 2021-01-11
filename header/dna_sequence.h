//
// Created by ali-masa on 1/9/21.
//

#ifndef DNA_SEQUENCE_DNA_SEQUENCE_H
#define DNA_SEQUENCE_DNA_SEQUENCE_H

#include <string>
#include <vector>

#include "nucleotide.h"
#include "codon.h"

class DNASequence {
public:
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


    class iterator {
    public:
        std::vector<Nucleotide>::iterator operator*() const;
        std::vector<Nucleotide>::iterator operator->() const;

    private:
        std::vector<Nucleotide>::iterator m_sequenceIterator;
    };

    // might change the return value to bool
    size_t writeToFile(std::string fileName) const;
    size_t readFromFile(std::string fileName);

    DNASequence slice(size_t start, size_t end);
    DNASequence pairSequence() const;

    // might be better to return an iterator!
    iterator find(DNASequence subSequence) const;

    size_t count(DNASequence subSequence) const;

    std::vector<iterator> findAll(DNASequence subSequence) const;

    iterator begin() const;
    iterator end() const;

private:
    std::vector<Nucleotide> m_sequence;
};

#endif //DNA_SEQUENCE_DNA_SEQUENCE_H
