#include "iostream"
#include "warcraft.h"
#include "cstdio"

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int t;
    std::cin >> t;
    while (t--)
    {
        init();
        game();
    }
    return 0;
}