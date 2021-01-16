//
// Created by ali-masa on 1/16/21.
//

#ifndef DNA_SEQUENCE_KMPSEARCHER_H
#define DNA_SEQUENCE_KMPSEARCHER_H

#include <vector>
#include <string>

template<class T>
class KMPSearcher{
public:
    static std::pair<size_t, size_t> KMPSearch(const T& str, const T& subString,
                                               const std::vector<size_t>& lps, size_t i = 0, size_t j = 0)
    {
        size_t M = subString.length();
        size_t N = str.length();

        // create lps[] that will hold the longest prefix suffix
        // values for pattern;

        while (i < N) {
            if (subString[j] == str[i]) {
                j++;
                i++;
            }

            if (j == M) {
                return std::pair<size_t, size_t>(i-j, lps[j - 1]);
            }

                // mismatch after j matches
            else if (i < N && subString[j] != str[i]) {
                // Do not match lps[0..lps[j-1]] characters,
                // they will match anyway
                if (j != 0)
                    j = lps[j - 1];
                else
                    i = i + 1;
            }
        }

        return s_endPair;
    }

// Fills lps[] for given pattern subString[0..M-1]
    static void computeLPSArray(const T& subString, std::vector<size_t>& lps)
    {
        // length of the previous longest prefix suffix
        lps.reserve(subString.length());
        size_t len = 0;

        lps[0] = 0; // lps[0] is always 0

        // the loop calculates lps[i] for i = 1 to M-1
        size_t i = 1;
        while (i < subString.length()) {
            if (subString[i] == subString[len]) {
                len++;
                lps[i] = len;
                i++;
            }
            else // (subString[i] != subString[len])
            {
                // This is tricky. Consider the example.
                // AAACAAAA and i = 7. The idea is similar
                // to search step.
                if (len != 0) {
                    len = lps[len - 1];

                    // Also, note that we do not increment
                    // i here
                }
                else // if (len == 0)
                {
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }

    const static std::pair<size_t, size_t> s_endPair;
};
template<class T>
const std::pair<size_t, size_t> KMPSearcher<T>::s_endPair(std::string::npos, 0);

#endif //DNA_SEQUENCE_KMPSEARCHER_H
