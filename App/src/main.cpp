#include <iostream>
#include "Document.h"
#include <glm/glm.hpp>

int main()
{
    Document doc
    {
        "Sam",
        std::time(nullptr),
        "Delivering cargos",
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor"
                " incididunt ut labore et dolore magna aliqua.\nUt enim ad minim veniam, quis nostrud"
                " exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat."
    };

    doc.print(std::cout);
    
    glm::vec3 v = { 0, 2, 3 };

    return 0;
}
