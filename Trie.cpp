//
// Created by creeper on 22-9-20.
//
#include "Trie.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include "MyUtils.h"
#include <queue>
//construct a trie by a file
Trie::Trie(const std::string& path)
{
    std::ifstream fin(path, std::ios_base::in);
    std::string cur_word;
    rt = std::make_shared<Node>();
    while(fin >> cur_word)
    {
        for(char& i : cur_word)
            if(i >= 'A' && i <= 'Z') i += 32;
        insert(cur_word);
        word_cnt++;
    }
    fin.close();
}
void Trie::insert(const std::string &str)
{
    std::shared_ptr<Node> cur = rt;
    for(char i : str)
    {
        try
        {
            int idx = char2idx(i);
            if(cur->ch[idx])
                cur = cur->ch[idx];
            else
            {
                cur->ch[idx] = std::make_shared<Node>();
                cur = cur->ch[idx];
            }
        }
        catch(std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            exit(-1);
        }
    }
    if(!cur->word_ptr)
        cur->word_ptr = std::make_shared<Word>(str);
    cur->word_ptr->cnt++; //avoid counting one word repeatedly
}

bool Trie::find(const std::string &str) const
{
    std::shared_ptr<Node> cur = rt;
    for(char i : str)
    {
        try
        {
            int idx = char2idx(i);
            if(cur->ch[idx])
                cur = cur->ch[idx];
            else return false;
        }
        catch(std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            exit(-1);
        }
    }
    return cur->word_ptr != nullptr;
}

//search the strings whose edit distance from str is less than a given number
void Trie::dfs(const std::shared_ptr<Node>& o, const std::string &str, int str_cur,
               int dif, std::vector<std::pair<std::shared_ptr<Word>, int> >& Ans)
{
    if(str_cur == str.length())
    {
        if(o->word_ptr != nullptr && !vis[o->word_ptr])
        {
            Ans.emplace_back(o->word_ptr, dif);
            vis[o->word_ptr] = true;
        }
        return ;
    }
    try
    {
        int idx = char2idx(str[str_cur]);
        bool chk = (dif <= 1);
        for(int i = 0; i < ALPHABET_SZ; i++)
        {
            if(o->ch[i])
            {
                if(i == idx)
                    dfs(o->ch[i], str, str_cur + 1, dif, Ans);
                if(chk)
                {
                    dfs(o, str, str_cur + 1, dif + 1, Ans);
                    dfs(o->ch[i], str, str_cur, dif + 1, Ans);
                    if(i != idx) dfs(o->ch[i], str, str_cur + 1, dif + 1, Ans);
                }
            }
        }
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(-1);
    }
}
void Trie::query(const std::string &str)
{
    std::vector<std::pair<std::shared_ptr<Word>, int> > Ans;
    if(find(str))
        printf("The word \"%s\" is found in the word lib\n", str.c_str());
    else
    {
        printf("Oops, \"%s\" was not found in current word lib. Searching similar words for you.\n", str.c_str());
        vis.clear();
        dfs(rt, str, 0, 0, Ans);
        std::sort(Ans.begin(), Ans.end(), cmp);
        int tot = std::min(10, static_cast<int>(Ans.size()));
        printf("Searching complete. Recommend following %d words for you:\n", tot);
        for(int i = 0; i < tot; i++)
            printf("%s\n", Ans[i].first->word.c_str());
    }
}