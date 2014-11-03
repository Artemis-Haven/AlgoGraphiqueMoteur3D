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
	for(int i = 0 ; i < drawable->faces.size ; i++) {
        if(effectiveDrawable->faceVisibles.data[i])
        {
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
}
void Renderer::DrawFacePleine()
{
	for(int i = 0 ; i < effectiveDrawable->sortedVisibleFaces.size; i++) {
        FaceDepthAccessor depth = effectiveDrawable->sortedVisibleFaces.data[i];
        Face face = drawable->faces.data[depth.index];
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
        buffer->DrawFilledTriangle(p1, p2, p3, c1, c2, c3);
	}
}

void Renderer::DrawLambert()
{
    //Ilumination a faire
    for(int i = 0 ; i < effectiveDrawable->sortedVisibleFaces.size; i++) {
        FaceDepthAccessor depth = effectiveDrawable->sortedVisibleFaces.data[i];
        Face face = drawable->faces.data[depth.index];
        Color c1, c2, c3;
        Color ambient = ambientLight.ambientColor;
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
        c1 = c1*(ambient+pointLight.GetColor(effectiveDrawable->points.data[face.index1], effectiveDrawable->faceNormals.data[depth.index]));
        c2 = c2*(ambient+pointLight.GetColor(effectiveDrawable->points.data[face.index2], effectiveDrawable->faceNormals.data[depth.index]));
        c3 = c3*(ambient+pointLight.GetColor(effectiveDrawable->points.data[face.index3], effectiveDrawable->faceNormals.data[depth.index]));

        Coord2D p1 = renderable.points2D.data[face.index1];
        Coord2D p3 = renderable.points2D.data[face.index3];
        Coord2D p2 = renderable.points2D.data[face.index2];
        buffer->DrawFilledTriangle(p1, p2, p3, c1, c2, c3);
    }
}
void Renderer::DrawGouraud()
{
    //Ilumination a faire
    for(int i = 0 ; i < effectiveDrawable->sortedVisibleFaces.size; i++) {
        FaceDepthAccessor depth = effectiveDrawable->sortedVisibleFaces.data[i];
        Face face = drawable->faces.data[depth.index];
        Color c1, c2, c3;
        Color ambient = ambientLight.ambientColor;
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
        c1 = c1*(ambient+pointLight.GetColor(effectiveDrawable->points.data[face.index1], effectiveDrawable->pointNormals.data[face.index1]));
        c2 = c2*(ambient+pointLight.GetColor(effectiveDrawable->points.data[face.index2], effectiveDrawable->pointNormals.data[face.index2]));
        c3 = c3*(ambient+pointLight.GetColor(effectiveDrawable->points.data[face.index3], effectiveDrawable->pointNormals.data[face.index3]));

        Coord2D p1 = renderable.points2D.data[face.index1];
        Coord2D p3 = renderable.points2D.data[face.index3];
        Coord2D p2 = renderable.points2D.data[face.index2];
        buffer->DrawFilledTriangle(p1, p2, p3, c1, c2, c3);
    }
}
void Renderer::DrawPhong()
{
    //Ilumination a faire
    for(int i = 0 ; i < effectiveDrawable->sortedVisibleFaces.size; i++) {
        FaceDepthAccessor depth = effectiveDrawable->sortedVisibleFaces.data[i];
        Face face = drawable->faces.data[depth.index];
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
        buffer->DrawFilledTriangle(p1, p2, p3, c1, c2, c3);
    }
}
