#include <Buffer.h>
#include <FastMath.h>


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
        for (compteur = 1 ; compteur <= longX ; compteur++) {
            SetPoint(Coord2D(x,y), (c1*w1)+(c2*w2));
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
        for (compteur = 1 ; compteur <= longY ; compteur++) {
            SetPoint(Coord2D(x,y), (c1*w1)+(c2*w2));
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
    scanLineComputer.Init();
    scanLineComputer.Compute(p1, p2, p3);
    for(int compteur = scanLineComputer.ymin ; compteur <= scanLineComputer.ymax ; compteur++)
    {
        Color cc1, cc2;
        cc1 = c1*scanLineComputer.leftweight.data[compteur].data[0]+c2*scanLineComputer.leftweight.data[compteur].data[1]+c3*scanLineComputer.leftweight.data[compteur].data[2];
        cc2 = c1*scanLineComputer.rightweight.data[compteur].data[0]+c2*scanLineComputer.rightweight.data[compteur].data[1]+c3*scanLineComputer.rightweight.data[compteur].data[2];
        Coord2D left = Coord2D(scanLineComputer.left.data[compteur], compteur);
        Coord2D right = Coord2D(scanLineComputer.right.data[compteur], compteur);
        DrawLine(left, right, cc1, cc2);
    }
}

void Buffer::DrawPhongTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3,
		const Coord3D posi1, const Coord3D posi2, const Coord3D posi3,
		const Coord3D normal1, const Coord3D normal2, const Coord3D normal3,
		const AmbientLight & ambientLight, const PointLight & pointLight)
{
    scanLineComputer.Init();
    scanLineComputer.Compute(p1, p2, p3);
    for(int compteurY = scanLineComputer.ymin ; compteurY <= scanLineComputer.ymax ; compteurY++)
    {
        Coord3D n, p, n1, n2, n3, q1, q2, q3;
        Color c, cc, cc1, cc2, cc3;
        cc1 = c1*scanLineComputer.leftweight.data[compteurY].data[0]+c2*scanLineComputer.leftweight.data[compteurY].data[1]+c3*scanLineComputer.leftweight.data[compteurY].data[2];
        cc2 = c1*scanLineComputer.rightweight.data[compteurY].data[0]+c2*scanLineComputer.rightweight.data[compteurY].data[1]+c3*scanLineComputer.rightweight.data[compteurY].data[2];

        q1 = posi1*scanLineComputer.leftweight.data[compteurY].data[0]+posi2*scanLineComputer.leftweight.data[compteurY].data[1]+posi3*scanLineComputer.leftweight.data[compteurY].data[2];
        q2 = posi1*scanLineComputer.rightweight.data[compteurY].data[0]+posi2*scanLineComputer.rightweight.data[compteurY].data[1]+posi3*scanLineComputer.rightweight.data[compteurY].data[2];

        n1 = normal1*scanLineComputer.leftweight.data[compteurY].data[0]+normal2*scanLineComputer.leftweight.data[compteurY].data[1]+normal3*scanLineComputer.leftweight.data[compteurY].data[2];
        n2 = normal1*scanLineComputer.rightweight.data[compteurY].data[0]+normal2*scanLineComputer.rightweight.data[compteurY].data[1]+normal3*scanLineComputer.rightweight.data[compteurY].data[2];

        //cc1 = cc1 * (ambientLight.ambientColor + pointLight.GetColor(q1, n1));
        //cc2 = cc2 * (ambientLight.ambientColor + pointLight.GetColor(q2, n2));

        int leftX = scanLineComputer.left.data[compteurY];
        int rightX = scanLineComputer.right.data[compteurY];

        for (int compteurX = leftX ; compteurX <= rightX ; compteurX++)
        {
            double poids = 0.5;
            if (leftX != rightX)
                poids = 1 - (double)(compteurX-leftX)/(double)(rightX-leftX);

            n3 = n1*poids + n2*(1-poids);

            q3 = q1* poids + q2*(1-poids);

            cc3 = cc1* poids + cc2*(1-poids);

            Color color = cc3 * (ambientLight.ambientColor + pointLight.GetColor(q3, n3));


            SetPoint(Coord2D(compteurX, compteurY), color);
        }
    }
}

