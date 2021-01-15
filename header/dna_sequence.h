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
    ConstIterator begin() const;
    ConstIterator end() const;
    ConstIterator cBegin() const;
    ConstIterator cEnd() const;

    DNASequence pair() const;
    std::string asString() const;

    // might change the return value to bool
    void writeToFile(std::string fileName) const;
    DNASequence & readFromFile(std::string fileName);

    DNASequence slice(size_t start, size_t end);
    DNASequence pairSequence() const;

    // might be better to return an iterator!
    size_t find(const DNASequence& subSequence, size_t startIndex = 0) const;

    size_t count(const DNASequence& subSequence) const;

    std::vector<size_t> findAll(const DNASequence& subSequence) const;

private:
    std::vector<size_t> m_sequence;

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
        ConstIterator operator++(int) const;

        const ConstIterator& operator--() const;
        ConstIterator operator--(int) const;

        friend void swap(ConstIterator& lhs, ConstIterator& rhs);

        friend bool operator==(const ConstIterator& iterator1, const ConstIterator& iterator2);
        friend bool operator!=(const ConstIterator& iterator1, const ConstIterator& iterator2);

        const ConstIterator& operator+=(size_t) const;

        friend ConstIterator operator+(const ConstIterator&, size_t);
        friend ConstIterator operator+(size_t, const ConstIterator&);

        const ConstIterator& operator-=(size_t) const;
        friend ConstIterator operator-(const ConstIterator&, size_t);

        const Nucleotide& operator[](size_t) const;

    private:
        mutable size_t m_index;
        std::vector<Nucleotide>& m_sequenceReference;
    };
};

#endif //DNA_SEQUENCE_DNA_SEQUENCE_H
