#pragma once
#include <string>
#include <memory>
#include <optional>
#include <unordered_map>
const int ALPHABET_SZ = 28;
struct Word
{
    std::string word;
    int cnt = 0;
    explicit Word(std::string&& str) : word(str) {}
    explicit Word(const std::string& str) : word(str) {}
    Word(std::string&& str, int _cnt) : word(str), cnt(_cnt) {}
    Word(const std::string& str, int _cnt) : word(str), cnt(_cnt) {}
};
struct Node
{
    std::shared_ptr<Node> ch[ALPHABET_SZ];
    std::shared_ptr<Word> word_ptr = nullptr; //idx > 0 marks the end of a word
};