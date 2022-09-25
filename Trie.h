#pragma once
#include <string>
#include <memory>
#include "WordNode.h"
#include <vector>
#include <utility>
#include <unordered_map>
class Trie
{
    private:
        std::shared_ptr<Node> rt = nullptr;
        int word_cnt = 0;
        int distinct_word_cnt = 0;
        void insert(const std::string&);
        void dfs(const std::shared_ptr<Node>&, const std::string&, int, int,
             std::vector<std::pair<std::shared_ptr<Word>, int> >&);
        std::unordered_map<std::shared_ptr<Word>, bool> vis;
    public:
        explicit Trie(const std::string&);
        bool find(const std::string&) const;// traverse the trie to find a string
        int count_words() const { return word_cnt; }
        int count_distinct_words() const { return distinct_word_cnt; }
        void query(const std::string&);
};