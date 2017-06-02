#ifndef CADDY_H
#define CADDY_H

#include <QObject>


enum Name{
    Sun,
    Mercury,
    Venus,
    Earth,
    Mars,
    Jupiter,
    Saturn,
    Uranus,
    Neptune,
    Moon,
    Phobos,
    Deimos,
    Size = 12
};


class Caddy
{
public:
    Caddy();

    int getSize();
    Name getName();

    Name planet;
    int counter;

};

#endif // CADDY_H
