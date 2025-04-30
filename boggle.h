#ifndef BOGGLE_H
#define BOGGLE_H

#ifndef RECCHECK
#include <vector>
#include <set>
#include <utility>
#include <string>
#endif

std::vector<std::vector<char> > genBoard(unsigned int n, int seed);
void printBoard(const std::vector<std::vector<char> >& board);
std::pair<std::set<std::string>, std::set<std::string> > parseDict(std::string fname);
std::set<std::string> boggle(const std::set<std::string>& dict, const std::set<std::string>& prefix, const std::vector<std::vector<char> >& board);

/**
 * @brief Recursive helper for Boggle word search in a fixed direction.
 *
 * Builds a word starting from (r, c) along direction (dr, dc), adding letters
 * as long as the string remains a valid prefix. If a valid word is found and
 * it's the longest from this path, it's inserted into the result set.
 *
 * @param dict    Set of all valid dictionary words.
 * @param prefix  Set of all valid word prefixes.
 * @param board   2D grid of letters representing the Boggle board.
 * @param word    Word built so far in the current recursion path.
 * @param result  Set to collect the longest valid word from this path.
 * @param r       Current row index on the board.
 * @param c       Current column index on the board.
 * @param dr      Row direction (0 = horizontal, 1 = vertical/diagonal).
 * @param dc      Column direction (0 = vertical, 1 = horizontal/diagonal).
 * @return true   If a valid word was found from this path; false otherwise.
 *
 * Notes:
 * - Words must be ≥ 2 letters to be considered.
 * - Stops if current word is not a prefix (backtracking).
 * - Only one direction is followed; no turning or reusing letters.
 */
bool boggleHelper(const std::set<std::string>& dict, const std::set<std::string>& prefix, const std::vector<std::vector<char> >& board, std::string word, std::set<std::string>& result, unsigned int r, unsigned int c, int dr, int dc);
#endif