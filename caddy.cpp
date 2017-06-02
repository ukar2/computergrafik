#include "caddy.h"


Caddy::Caddy()
{
    this->counter = 0;
}

Name Caddy::getName()
{
    switch (counter) {
    case 0:
        planet = Name::Sun;
        break;
    case 1:
        planet = Name::Mercury;
        break;
    case 2:
        planet = Name::Venus;
        break;
    case 3:
        planet = Name::Earth;
        break;
    case 4:
        planet = Name::Moon;
        break;
    case 5:
        planet = Name::Mars;
        break;
    case 6:
        planet = Name::Phobos;
        break;
    case 7:
        planet = Name::Deimos;
        break;
    case 8:
        planet = Name::Jupiter;
        break;
    case 9:
        planet = Name::Saturn;
        break;
    case 10:
        planet = Name::Uranus;
        break;
    case 11:
        planet = Name::Neptune;
        break;
    default:
        break;
    }

    counter++;

    return planet;

}


int Caddy::getSize()
{
    Name size = Name::Size;

    return (int)size;
}
