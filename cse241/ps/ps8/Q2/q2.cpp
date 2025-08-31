#include <iostream>
#include <cstdlib>

namespace  
{         
    int lev = 0;

    void f(int throw_level)
    {
        ++lev;
        std::cout << "lev == " << lev << std::endl;

        if (lev == throw_level)
        {
            throw lev;
        }

        if (lev < 10)
        {
            f(throw_level);  
        }

        --lev;  
        std::cout << "Returning from level " << lev + 1 << std::endl;
    }
}

int main()
{
    int throw_level;
    
    std::cout << "Enter level to throw exception (1-10): ";
    std::cin >> throw_level;
    
    if (throw_level < 1 || throw_level > 10)
    {
        std::cout << "Level must be between 1 and 10." << std::endl;
        return 1;
    }
    
    try
    {
        std::cout << "Starting recursive function calls..." << std::endl;
        f(throw_level);
        std::cout << "No exception was thrown." << std::endl;
    }
    catch (int level)
    {
        std::cout << "Caught exception at level " << level << std::endl;
    }
    
    std::cout << "Program completed successfully." << std::endl;
    return 0;
}