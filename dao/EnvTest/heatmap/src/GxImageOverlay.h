#ifndef GX_IMAGE_OVERLAY_H
#define GX_IMAGE_OVERLAY_H

#include "GxAnnotationNode.h"

#include <osg/Texture2D>
#include <osg/Geometry>
#include "dckjgzgis_export.h"

class DCKJGZGIS_EXPORT GxImageOverlay : public GxAnnotationNode
{
public:
	GxImageOverlay();
	~GxImageOverlay();

	void setBounds(double xmin, double ymin, double xmax, double ymax);

	void setImage(osg::Image *);

private:
	//osg::ref_ptr<osg::Vec3Array> m_rpVertices;	// ���е㣨�������꣩
	osg::ref_ptr<osg::Vec2Array> m_rpTexCoords;	// ��������
	osg::ref_ptr<osg::Geometry> m_rpGeometry;
	osg::ref_ptr<osg::Texture2D> m_rpTexture;
};

#endif // !GX_IMAGE_OVERLAY_H
