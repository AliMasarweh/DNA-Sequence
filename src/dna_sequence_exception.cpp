//
// Created by ali-masa on 1/11/21.
//

#include "../header/dna_sequence_exception.h"
#include "../header/codon.h"

const char * InvalidNucleotideException::what () const throw () {
    return "Invalid Nucleotide Exception";
}

const char * InvalidCodonLengthException::what () const throw () {
    return "Invalid Codon Length Exception! Length should be: " + Codon::s_codonSize;
}

const char * IteratorOutOfBoundsException::what () const throw () {
    return "Iterator is out of bounds! (use end iterator to avoid this exception)";
}