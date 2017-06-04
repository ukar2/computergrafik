#include "caddy.h"


Caddy::Caddy()
{
    this->counter = 0;
    this->orb_speed = 1.0f;
    this->rot_factor = 1.0f;
    this->orb_distance = 1.0f;
    this->axial_tilt = 1.0f;
}


Name Caddy::getNextName()
{
    switch (counter) {
    case 0:
        planet = Name::Sun;
        orb_speed = 1.0f;
        rot_factor = 1.0f;
        orb_distance = 0.0f;
        axial_tilt = 7.25f;
        break;
    case 1:
        planet = Name::Mercury;
        orb_speed = 0.75f;
        rot_factor = 1.54f;
        orb_distance = 7.0f;
        axial_tilt = 2.0f;
        break;
    case 2:
        planet = Name::Venus;
        orb_speed = 0.75f;
        rot_factor = 1.0f;
        orb_distance = 10.0f;
        axial_tilt = 67.0f;
        break;
    case 3:
        planet = Name::Earth;
        orb_speed = 0.5f;
        rot_factor = 0.0f;
        orb_distance = 15.0f;
        axial_tilt = 23.26f;
        break;
    case 4:
        planet = Name::Moon;
        orb_speed = 1.0f;
        rot_factor = 1.0f;
        orb_distance = 0.0f;
        axial_tilt = 1.0f;
        break;
    case 5:
        planet = Name::Mars;
        orb_speed = 1.0f;
        rot_factor = 1.0f;
        orb_distance = 25.0f;
        axial_tilt = 1.0f;
        break;
    case 6:
        planet = Name::Phobos;
        orb_speed = 1.0f;
        rot_factor = 1.0f;
        orb_distance = 0.0f;
        axial_tilt = 1.0f;
        break;
    case 7:
        planet = Name::Deimos;
        orb_speed = 1.0f;
        rot_factor = 1.0f;
        orb_distance = 0.0f;
        axial_tilt = 1.0f;
        break;
    case 8:
        planet = Name::Jupiter;
        orb_speed = 1.0f;
        rot_factor = 1.0f;
        orb_distance = 50.0f;
        axial_tilt = 1.0f;
        break;
    case 9:
        planet = Name::Saturn;
        orb_speed = 1.0f;
        rot_factor = 1.0f;
        orb_distance = 60.0f;
        axial_tilt = 1.0f;
        break;
    case 10:
        planet = Name::Uranus;
        orb_speed = 1.0f;
        rot_factor = 1.0f;
        orb_distance = 70.0f;
        axial_tilt = 1.0f;
        break;
    case 11:
        planet = Name::Neptune;
        orb_speed = 1.0f;
        rot_factor = 1.0f;
        orb_distance = 80.0f;
        axial_tilt = 1.0f;
        break;
    default:
        break;
    }

    counter++;

    return planet;

}

float Caddy::getOrbSpeed()
{
    return orb_speed;
}

float Caddy::getOrbDistance()
{
    return orb_distance;
}

float Caddy::getRotationFactor()
{
    return rot_factor;
}

float Caddy::getAxialTilt()
{
    return axial_tilt;
}

int Caddy::getSize()
{
    Name size = Name::Size;

    return (int)size;
}
