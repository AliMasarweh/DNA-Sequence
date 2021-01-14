include_directories(${MyProject_SOURCE_DIR}/header)

add_library(SRC nucleotide.cpp codon.cpp dna_sequence_exception.cpp dna_sequence.cpp dna_sequence_iterator.cpp
            dna_sequence_const_iterator.cpp)