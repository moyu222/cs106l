#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source)
{
    /* TODO: Implement this method */
    const auto begin = source.begin();
    const auto end = source.end();
    // auto space_it = find_all(begin, end, isspace);
    auto space_it_v = find_all(begin, end, [](unsigned char c)
    {
        return std::isspace(c);
    });
    auto start_bit = space_it_v.begin();
    auto start_eit = space_it_v.end() - 1;
    auto end_bit = space_it_v.begin() + 1;
    Corpus tokens;
    std::transform(start_bit, start_eit, end_bit,
                   std::inserter(tokens, tokens.end()),
                   [&source](auto it1, auto it2) { return Token{source, it1, it2}; });
    std::erase_if(tokens, [](const Token& t) { return t.content.empty(); });
    return tokens;
}

Corpus tokenize1(std::string& source)
{
    Corpus tokens;
    auto it = source.begin();
    while (it != source.end())
    {
        // 跳过前导空白
        it = std::find_if_not(it, source.end(),
                              [](unsigned char c) { return std::isspace(c); });
        if (it == source.end()) break;

        // 找到下一个空白
        auto jt = std::find_if(it, source.end(),
                               [](unsigned char c) { return std::isspace(c); });

        tokens.insert(Token(source, it, jt));
        it = jt;
    }
    return tokens;
}


std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary)
{
    /* TODO: Implement this method */
    // auto skip_correct = std::ranges::views::filter(source,
    //     [&dictionary](const Token &t)
    //     { return dictionary.contains(t.content);});
    namespace rv = std::ranges::views;
    auto view = source
        |
        rv::filter(
            [&dictionary](const Token& t)
            {
                return !dictionary.contains(t.content);
            })
        |
        rv::transform(
            [&dictionary](const Token& t) -> Misspelling
            {
                auto suggs = dictionary | rv::filter(
                    [&t](const std::string& s)
                    {
                        return levenshtein(s, t.content) == 1;
                    });
                std::set<std::string> suggestions(suggs.begin(), suggs.end());
                return Misspelling{t, suggestions};
            })
        |
        rv::filter(
            [](const Misspelling& m)
            {
                return !m.suggestions.empty();
            });
    std::set<Misspelling> res{view.begin(), view.end()};
    return res;
};

std::set<Misspelling> spellcheck1(const Corpus& source, const Dictionary& dictionary)
{
    std::set<Misspelling> res;
    for (const auto& t : source)
    {
        if (dictionary.contains(t.content)) continue; // 跳过正确词

        std::set<std::string> suggestions;
        for (const auto& s : dictionary)
        {
            // 长度差太大直接跳过
            if (std::abs((int)s.size() - (int)t.content.size()) > 1) continue;
            if (levenshtein(s, t.content) == 1)
            {
                suggestions.insert(s);
            }
        }
        if (!suggestions.empty())
        {
            res.emplace(t, suggestions);
        }
    }
    return res;
}


/* Helper methods */

#include "utils.cpp"
