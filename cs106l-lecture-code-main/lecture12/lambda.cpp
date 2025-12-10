#include <string>
#include <iostream>

template <typename It, typename Pred>
It my_find_if(It begin, It end, Pred pred)
{
    for (auto it = begin; it != end; it++)
        if (pred(*it))
            return it;
    return end;
}

int main()
{
    std::string corlys = "Lord of the tides";
    auto it = my_find_if(corlys.begin(), corlys.end(),
        [](auto c) {
            c = toupper(c);
            return c == 'A' || c == 'E' ||
                   c == 'I' || c == 'O' || c == 'U';
    });
    std::cout << *it << std::endl;
}