#include <Renderer.h>
#include <Panel3D.h>
#include <Engine.h>

void Renderer::DrawFilaire()
{
    // clear buffer ?
	for(int i = 0 ; i < drawable->faces.size ; i++) {
        Face face = drawable->faces.data[i];
        Coord3D p1 = drawable->points.data[face.index1];
        Coord3D p2 = drawable->points.data[face.index2];
        Coord3D p3 = drawable->points.data[face.index3];
        Color c1 = drawable->pointColors.data[face.index1];
        Color c2 = drawable->pointColors.data[face.index2];
        Color c3 = drawable->pointColors.data[face.index3];
	    buffer->DrawLine(Coord2D(p1.x, p1.y), Coord2D(p2.x, p2.y), c1, c2);
	    buffer->DrawLine(Coord2D(p1.x, p1.y), Coord2D(p3.x, p3.y), c1, c3);
	    buffer->DrawLine(Coord2D(p2.x, p2.y), Coord2D(p3.x, p3.y), c2, c3);
	}
}
void Renderer::DrawFilaireCache()
{
	// compléter ici
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
