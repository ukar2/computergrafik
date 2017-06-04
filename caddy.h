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
    float getOrbSpeed();
    float getOrbDistance();
    float getRotationFactor();
    float getAxialTilt();
    Name getNextName();

    Name planet;
    int counter;
    float orb_speed;
    float rot_factor;
    float orb_distance;
    float axial_tilt;

};

#endif // CADDY_H
