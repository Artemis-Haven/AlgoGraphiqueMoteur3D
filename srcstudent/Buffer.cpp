#include <Buffer.h>
#include <FastMath.h>

//Dessine une ligne suivant l'algortihme de Bresenham
void Buffer::DrawLine(const Coord2D p1, const Coord2D p2, const Color c1,
		const Color c2)
{
    int x = p1.x;
    int y = p1.y;
    int longX = p2.x - p1.x;
    int longY = p2.y - p1.y;
    int critere, const1, const2, incX, incY, compteur;
    double w1 = 1;
    double w2 = 1 - w1;
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
            double depth = (p1.depth*w1)+(p2.depth*w2);
            SetPoint(Coord2D(x,y, depth), (c1*w1)+(c2*w2));
            if (critere > 0) {
                y += incY;
                critere += const1;
            } else {
                critere += const2;
            }
            x += incX;
            w1 = (double)(longX - compteur)/(double)(longX);
            w2 = 1 - w1;
        }
    } else {
        const1 = 2 * (longX - longY);
        const2 = 2 * longX;
        critere = const2 - longY;
        for (compteur = 0 ; compteur <= longY ; compteur++) {
            double depth = (p1.depth*w1)+(p2.depth*w2);
            SetPoint(Coord2D(x, y, depth), (c1*w1)+(c2*w2));
            if (critere > 0) {
                x += incX;
                critere += const1;
            } else {
                critere += const2;
            }
            y += incY;
            w1 = (double)(longY - compteur)/(double)(longY);
            w2 = 1 - w1;
        }
    }
}

void Buffer::DrawFilledTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3)
{
    //Initialisation du ScanLine
    scanLineComputer.Init();
    scanLineComputer.Compute(p1, p2, p3);
    //On parcours ensuite verticalement chacun des points du ScanLine pour pouvoir en tracer les lignes
    for(int compteur = scanLineComputer.ymin ; compteur <= scanLineComputer.ymax ; compteur++)
    {
        Color leftColor, rightColor;
        leftColor = c1*scanLineComputer.leftweight.data[compteur].data[0]+c2*scanLineComputer.leftweight.data[compteur].data[1]+c3*scanLineComputer.leftweight.data[compteur].data[2];
        rightColor = c1*scanLineComputer.rightweight.data[compteur].data[0]+c2*scanLineComputer.rightweight.data[compteur].data[1]+c3*scanLineComputer.rightweight.data[compteur].data[2];

        double depthLeft = p1.depth*scanLineComputer.leftweight.data[compteur].data[0]+p2.depth*scanLineComputer.leftweight.data[compteur].data[1]+p3.depth*scanLineComputer.leftweight.data[compteur].data[2];
        double depthRight = p1.depth*scanLineComputer.rightweight.data[compteur].data[0]+p2.depth*scanLineComputer.rightweight.data[compteur].data[1]+p3.depth*scanLineComputer.rightweight.data[compteur].data[2];

        Coord2D leftPoint = Coord2D(scanLineComputer.left.data[compteur], compteur, depthLeft);
        Coord2D rightPoint = Coord2D(scanLineComputer.right.data[compteur], compteur, depthRight);
        DrawLine(leftPoint, rightPoint, leftColor, rightColor);
    }
}

void Buffer::DrawPhongTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3,
		const Coord3D posi1, const Coord3D posi2, const Coord3D posi3,
		const Coord3D normal1, const Coord3D normal2, const Coord3D normal3,
		const AmbientLight & ambientLight, const PointLight & pointLight)
{
    //Initialisation du ScanLine
    scanLineComputer.Init();
    scanLineComputer.Compute(p1, p2, p3);
    //On parcours ensuite verticalement chacun des points du ScanLine pour pouvoir en tracer les lignes
    for(int compteurY = scanLineComputer.ymin ; compteurY <= scanLineComputer.ymax ; compteurY++)
    {
        Coord3D normal, point, leftNormal, rightNormal, leftPoint, rightPoint;
        Color leftColor, rightColor;
        leftColor = c1*scanLineComputer.leftweight.data[compteurY].data[0]+c2*scanLineComputer.leftweight.data[compteurY].data[1]+c3*scanLineComputer.leftweight.data[compteurY].data[2];
        rightColor = c1*scanLineComputer.rightweight.data[compteurY].data[0]+c2*scanLineComputer.rightweight.data[compteurY].data[1]+c3*scanLineComputer.rightweight.data[compteurY].data[2];

        leftPoint = posi1*scanLineComputer.leftweight.data[compteurY].data[0]+posi2*scanLineComputer.leftweight.data[compteurY].data[1]+posi3*scanLineComputer.leftweight.data[compteurY].data[2];
        rightPoint = posi1*scanLineComputer.rightweight.data[compteurY].data[0]+posi2*scanLineComputer.rightweight.data[compteurY].data[1]+posi3*scanLineComputer.rightweight.data[compteurY].data[2];

        leftNormal = normal1*scanLineComputer.leftweight.data[compteurY].data[0]+normal2*scanLineComputer.leftweight.data[compteurY].data[1]+normal3*scanLineComputer.leftweight.data[compteurY].data[2];
        rightNormal = normal1*scanLineComputer.rightweight.data[compteurY].data[0]+normal2*scanLineComputer.rightweight.data[compteurY].data[1]+normal3*scanLineComputer.rightweight.data[compteurY].data[2];

        double depthLeft = p1.depth*scanLineComputer.leftweight.data[compteurY].data[0]+p2.depth*scanLineComputer.leftweight.data[compteurY].data[1]+p3.depth*scanLineComputer.leftweight.data[compteurY].data[2];
        double depthRight = p1.depth*scanLineComputer.rightweight.data[compteurY].data[0]+p2.depth*scanLineComputer.rightweight.data[compteurY].data[1]+p3.depth*scanLineComputer.rightweight.data[compteurY].data[2];

        int leftX = scanLineComputer.left.data[compteurY];
        int rightX = scanLineComputer.right.data[compteurY];
        //On parcours ensuite horizontalement chacun des points de la ligne
        for (int compteurX = leftX ; compteurX <= rightX ; compteurX++)
        {
            double poids = 0.5;
            if (leftX != rightX)
                poids = 1 - (double)(compteurX-leftX)/(double)(rightX-leftX);

            normal = leftNormal*poids + rightNormal*(1-poids);
            point = leftPoint* poids + rightPoint*(1-poids);
            double depth = depthLeft*poids + depthRight*(1-poids);

            Color color = (leftColor*poids + rightColor*(1-poids))* (ambientLight.ambientColor + pointLight.GetColor(point, normal));
            //Après interpolation des couleurs obtenu grâce aux normales en chaque point, on peut "déssiner" le point
            SetPoint(Coord2D(compteurX, compteurY, depth), color);
        }
    }
}

