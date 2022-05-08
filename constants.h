#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QColor>
#include <vector>

#define DEBUG 0

extern unsigned long long cellSizeX,
                          cellSizeY,
                          mapSizeX,
                          mapSizeY,
                          depth;

extern const QColor MaskaRoadColor,
             MaskaSpaceColor,
             MaskaSelectedCarColor,
             MaskaDestinationColor;

extern const unsigned int CarColorSIZE;
extern const QColor CarColor[20];

typedef unsigned short mapType;

// Fun constants
extern std::vector<unsigned long long> points;

// End of fun constants

#endif // CONSTANTS_H
