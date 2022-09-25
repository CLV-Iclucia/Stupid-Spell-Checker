#include <iostream>
#include "Trie.h"
int main(int argc, char** argv)
{
    if(argc == 1)
    {
        printf("Error: please rerun properly with your path of word lib as an argument\n");
        return 0;
    }
    else
    {
        static Trie trie(argv[1]);
        printf("Welcome to this demo!\n");
        printf("If you want to quit, type \"#quit\"\n");
        std::string word;
        while(true)
        {
            printf("Please input the word you want to query:");
            std::cin >> word;
            if(word == "#quit")break;
            else trie.query(word);
        }
        return 0;
    }
}
