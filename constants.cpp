#include <constants.h>

unsigned long long cellSizeX = 30,
                         cellSizeY = 30,
                         mapSizeX = 10,
                         mapSizeY = 10,
                         depth = 20;

const QColor MaskaRoadColor(Qt::green),
             MaskaSpaceColor(Qt::white),
             MaskaSelectedCarColor(Qt::red),
             MaskaDestinationColor(Qt::cyan);

const unsigned int CarColorSIZE = 20;
const QColor CarColor[20] = {QColor(255,0,5),QColor(0,125,53),QColor(0,39,141),QColor(0,142,194),QColor(100,53,0),QColor(255,154,0),QColor(203,1,129),QColor(255,218,0),QColor(159,159,159),QColor(255,174,201),QColor(0,127,154),QColor(118,218,234),QColor(127,127,127),QColor(255,0,255),QColor(255,255,128),QColor(128,128,255),QColor(128,0,255),QColor(243,71,35),QColor(128,64,64),QColor(157,145,1)};

// Fun constants
std::vector<unsigned long long> points(0,0);
// End of fun constants
