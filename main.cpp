#include "Engine/Engine.hpp"
#include "Catalog/Catalog.hpp"
#include "GUI/GUI.hpp"

int main()
{
    Catalog catalog;
    Engine engine(catalog);
    GUI gui(catalog, engine);
    gui.run();
    return 0;
}
