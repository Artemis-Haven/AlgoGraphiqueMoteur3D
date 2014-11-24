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
            c1 = drawable->faceColors.data[i];
            c2 = c1;
            c3 = c1;
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
                c1 = drawable->faceColors.data[i];
                c2 = c1;
                c3 = c1;
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
            c1 = drawable->faceColors.data[depth.index];
            c2 = c1;
            c3 = c1;
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
    for(int i = 0 ; i < effectiveDrawable->sortedVisibleFaces.size; i++)
    {
        FaceDepthAccessor depth = effectiveDrawable->sortedVisibleFaces.data[i];
        Face face = drawable->faces.data[depth.index];
        Color c1, c2, c3;
        Color ambient = ambientLight.ambientColor;
        if(drawable->colorOnFace)
        {
            c1 = drawable->faceColors.data[depth.index];
            c2 = c1;
            c3 = c1;
        }
        else
        {
            c1 = drawable->pointColors.data[face.index1];
            c2 = drawable->pointColors.data[face.index2];
            c3 = drawable->pointColors.data[face.index3];
        }

        Coord3D position = effectiveDrawable->points.data[face.index1]*0.33+effectiveDrawable->points.data[face.index2]*0.33+effectiveDrawable->points.data[face.index3]*0.33;

        Color lightColor = (ambient+pointLight.GetColor(position, effectiveDrawable->faceNormals.data[depth.index]));

        c1 = c1*lightColor;
        c2 = c2*lightColor;
        c3 = c3*lightColor;

        Coord2D p1 = renderable.points2D.data[face.index1];
        Coord2D p3 = renderable.points2D.data[face.index3];
        Coord2D p2 = renderable.points2D.data[face.index2];
        buffer->DrawFilledTriangle(p1, p2, p3, c1, c2, c3);
    }
}
void Renderer::DrawGouraud()
{
    for(int i = 0 ; i < effectiveDrawable->sortedVisibleFaces.size; i++) {
        FaceDepthAccessor depth = effectiveDrawable->sortedVisibleFaces.data[i];
        Face face = drawable->faces.data[depth.index];
        Color c1, c2, c3;
        Color ambient = ambientLight.ambientColor;
        if(drawable->colorOnFace)
        {
            c1 = drawable->faceColors.data[depth.index];
            c2 = c1;
            c3 = c1;
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
        Coord2D p2 = renderable.points2D.data[face.index2];
        Coord2D p3 = renderable.points2D.data[face.index3];
        buffer->DrawFilledTriangle(p1, p2, p3, c1, c2, c3);
    }
}
void Renderer::DrawPhong()
{
    for(int i = 0 ; i < effectiveDrawable->sortedVisibleFaces.size; i++) {
        FaceDepthAccessor depth = effectiveDrawable->sortedVisibleFaces.data[i];
        Face face = drawable->faces.data[depth.index];
        Color c1, c2, c3;
        if(drawable->colorOnFace)
        {
            c1 = drawable->faceColors.data[depth.index];
            c2 = c1;
            c3 = c1;
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

        Coord3D q1 = effectiveDrawable->points.data[face.index1];
        Coord3D q2 = effectiveDrawable->points.data[face.index2];
        Coord3D q3 = effectiveDrawable->points.data[face.index3];

        Coord3D n1 = effectiveDrawable->pointNormals.data[face.index1];
        Coord3D n2 = effectiveDrawable->pointNormals.data[face.index2];
        Coord3D n3 = effectiveDrawable->pointNormals.data[face.index3];

        buffer->DrawPhongTriangle(p1, p2, p3,
                                   c1, c2, c3,
                                   q1, q2, q3,
                                   n1, n2, n3,
                                   ambientLight, pointLight);
    }
}
