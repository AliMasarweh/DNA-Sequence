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
    const Nucleotide& operator[](size_t index) const;
    size_t length() const { return m_sequence.size(); }

    // might not be that useful for phase 2
    // codons can start at any index
    Codon codonAt(size_t index);

    class iterator;
    class ConstIterator;
    iterator begin();
    iterator end();
    const ConstIterator begin() const;
    const ConstIterator end() const;
    const ConstIterator cBegin() const;
    const ConstIterator cEnd() const;

    DNASequence pair() const;
    std::string asString() const;

    // might change the return value to bool
    size_t writeToFile(std::string fileName) const;
    size_t readFromFile(std::string fileName);

    DNASequence slice(size_t start, size_t end);
    DNASequence pairSequence() const;

    // might be better to return an iterator!
    iterator find(DNASequence subSequence) const;

    size_t count(DNASequence subSequence) const;

    std::vector<iterator> findAll(DNASequence subSequence) const;

private:
    std::vector<Nucleotide> m_sequence;

public:
    class iterator {
    public:
        iterator(std::vector<Nucleotide>& m_sequence, size_t index);

        Nucleotide& operator*();
        Nucleotide* operator->();

        iterator& operator++();
        iterator operator++(int);

        iterator& operator--();
        iterator operator--(int);

        friend void swap(iterator& lhs, iterator& rhs);

        friend bool operator==(const iterator& iterator1, const iterator& iterator2);
        friend bool operator!=(const iterator& iterator1, const iterator& iterator2);

        iterator& operator+=(size_t);

        friend iterator operator+(const iterator&, size_t);
        friend iterator operator+(size_t, const iterator&);

        iterator& operator-=(size_t);
        friend iterator operator-(const iterator&, size_t);
        friend size_t operator-(const iterator&, const iterator&);

        Nucleotide& operator[](size_t);

    private:
        size_t m_index;
        std::vector<Nucleotide>& m_sequenceReference;
    };

    class ConstIterator {
    public:
        ConstIterator(const std::vector<Nucleotide>& m_sequence, size_t index);

        const Nucleotide& operator*() const;
        const Nucleotide* operator->() const;

        const ConstIterator& operator++() const;
        const ConstIterator operator++(int) const;

        const ConstIterator& operator--() const;
        const ConstIterator operator--(int) const;

        friend void swap(ConstIterator& lhs, ConstIterator& rhs);

        friend bool operator==(const ConstIterator& iterator1, const ConstIterator& iterator2);
        friend bool operator!=(const ConstIterator& iterator1, const ConstIterator& iterator2);

        const ConstIterator& operator+=(size_t) const;

        friend const ConstIterator operator+(const ConstIterator&, size_t);

        friend const ConstIterator operator+(size_t, const ConstIterator&);
        friend ConstIterator operator+(size_t, ConstIterator&);

        const ConstIterator& operator-=(size_t) const;
        friend const ConstIterator operator-(const ConstIterator&, size_t);

        const Nucleotide& operator[](size_t) const;

    private:
        mutable size_t m_index;
        std::vector<Nucleotide>& m_sequenceReference;
    };
};

#endif //DNA_SEQUENCE_DNA_SEQUENCE_H
