#include <Renderer.h>
#include <Panel3D.h>
#include <Engine.h>

void Renderer::DrawFilaire()
{
	for(int i = 0 ; i < drawable->faces.size ; i++) {
        Face face = drawable->faces.data[i];
        Color c1, c2, c3;
        if(drawable->colorOnFace)
        {
            c1 = drawable->faceColors.data[face.index1];
            c2 = drawable->faceColors.data[face.index2];
            c3 = drawable->faceColors.data[face.index3];
        }
        else
        {
            c1 = drawable->pointColors.data[face.index1];
            c2 = drawable->pointColors.data[face.index2];
            c3 = drawable->pointColors.data[face.index3];
        }
        Coord2D p1 = renderable.points2D.data[face.index1];
        Coord2D p3 = renderable.points2D.data[face.index3];
        Coord2D p2 = renderable.points2D.data[face.index2];
	    buffer->DrawLine(p1, p2, c1, c2);
	    buffer->DrawLine(p2, p3, c2, c3);
	    buffer->DrawLine(p1, p3, c1, c3);
	}
}
void Renderer::DrawFilaireCache()
{

}
void Renderer::DrawFacePleine()
{
	// compléter ici
}

void Renderer::DrawLambert()
{
	// compléter ici
}
void Renderer::DrawGouraud()
{
	// compléter ici
}
void Renderer::DrawPhong()
{
	// compléter ici
}
