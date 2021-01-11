//
// Created by ali-masa on 1/9/21.
//

#ifndef DNA_SEQUENCE_DNASEQUENCEEXCEPTION_H
#define DNA_SEQUENCE_DNASEQUENCEEXCEPTION_H


#include <exception>

class DNASequenceException: public std::exception {
public:
    virtual const char * what () const throw () = 0;
};

// might there be a better approach to make invalid nucleotide more modular!
class InvalidNucleotideException: public DNASequenceException {
public:
    const char * what () const throw ();
};

class InvalidCodonLengthException: public DNASequenceException {
public:
    const char * what () const throw ();
};

#endif //DNA_SEQUENCE_DNASEQUENCEEXCEPTION_H
