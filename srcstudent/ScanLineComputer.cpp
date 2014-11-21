
#include <ScanLineComputer.h>
#include <Buffer.h>
#include <FastMath.h>
#include <limits.h>



void ScanLineComputer::AddEdge(const Coord2D p1, const Coord2D p2,
															 const int index1, const int index2)
{
	// on utitlise la méthode de Bresenheim pour calculer les points du segment [p1,p2] et on les ajoute via la méthode AddPoint

    int x = p1.x;
    int y = p1.y;
    int longX = p2.x - p1.x;
    int longY = p2.y - p1.y;
    int critere, const1, const2, incX, incY, compteur;
    if (longX >= 0) {
        incX = 1;
    } else {
        incX = -1;
        longX = -longX;
    }
    if (longY >= 0) {
        incY = 1;
    } else {
        incY = -1;
        longY = -longY;
    }
    if (longY < longX) {
        const1 = 2 * (longY - longX);
        const2 = 2 * longY;
        critere = const2 - longX;
        for (compteur = 0 ; compteur <= longX ; compteur++) {
            try{
                if((y >= 0)&&(y < height))
                    AddPoint(x, y, p1, p2, index1, index2);
            }
            catch(...)
            {
                std::cerr << "x : " << x << " y : " << y << std::endl;
            }
            if (critere > 0) {
                y += incY;
                critere += const1;
            } else {
                critere += const2;
            }
            x += incX;
        }
    } else {
        const1 = 2 * (longX - longY);
        const2 = 2 * longX;
        critere = const2 - longY;
        for (compteur = 0 ; compteur <= longY ; compteur++) {
            try{
                if((y >= 0)&&(y < height))
                    AddPoint(x, y, p1, p2, index1, index2);
            }
            catch(...)
            {
                std::cerr << "x : " << x << " y : " << y << std::endl;
            }
            if (critere > 0) {
                x += incX;
                critere += const1;
            } else {
                critere += const2;
            }
            y += incY;
        }
    }
}


