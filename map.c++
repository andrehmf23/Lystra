#include "map.h"

map::map(/* args */)
{
}

map::~map()
{
}

string setCursor(int x, int y) {
    return "\033[" + to_string(y) + ";" + to_string(x) + "H";
}

string setColor(int x) {
    return "\033[" + to_string(x) + "m";
}

string selected(bool selected) {
    if (selected) {
        return setColor(47) + setColor(30);
    } else {
        return setColor(0);
    }
}
