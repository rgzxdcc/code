#include "GxImageOverlay.h"

#include <osgDB/ReadFile>
#include <GxGeoUtil.h>
#include <osg/BlendFunc>
#include <QDebug>
#include <GxMapManager.h>
#include <osg/PrimitiveSet>

GxImageOverlay::GxImageOverlay()
{
	// 组成点数组
	osg::ref_ptr<osg::Vec3Array> m_rpVertices = new osg::Vec3Array;
	osg::Vec3d worldPos, worldMin, worldMax;
	GxGeoUtil::degreeLLH2XYZ(osg::Vec3d(100, 28, 100), worldMin);
	m_rpVertices->push_back(worldMin);
	GxGeoUtil::degreeLLH2XYZ(osg::Vec3d(110, 28, 100), worldPos);
	m_rpVertices->push_back(worldPos);
	GxGeoUtil::degreeLLH2XYZ(osg::Vec3d(110, 32, 100), worldMax);
	m_rpVertices->push_back(worldMax);
	GxGeoUtil::degreeLLH2XYZ(osg::Vec3d(100, 32, 100), worldPos);
	m_rpVertices->push_back(worldPos);
	

	m_rpTexCoords = new osg::Vec2Array;
	/*m_rpTexCoords->push_back(osg::Vec2(0.0f, 0.0f));
	m_rpTexCoords->push_back(osg::Vec2(1.0f, 0.0f));
	m_rpTexCoords->push_back(osg::Vec2(1.0f, 1.0f));
	m_rpTexCoords->push_back(osg::Vec2(0.0f, 1.0f));*/

	m_rpTexCoords->push_back(osg::Vec2(0.0f, 1.0f));
	m_rpTexCoords->push_back(osg::Vec2(1.0f, 1.0f));
	m_rpTexCoords->push_back(osg::Vec2(1.0f, 0.0f));
	m_rpTexCoords->push_back(osg::Vec2(0.0f, 0.0f));

	//osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
	//normals->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

	m_rpGeometry = new osg::Geometry;
	m_rpGeometry->setDataVariance(Object::DYNAMIC);       // 动态渲染
	m_rpGeometry->setUseDisplayList(false);               // 关闭用户显示列表
	m_rpGeometry->setUseVertexBufferObjects(true);        // 开启用户顶点缓冲项
	m_rpGeometry->setVertexArray(m_rpVertices.get());
	//m_rpGeometry->setNormalArray(normals.get());
	//m_rpGeometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
	m_rpGeometry->setTexCoordArray(0, m_rpTexCoords.get());
	//m_rpGeometry->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
	
	//m_rpGeometry->getOrCreateStateSet()->setRenderingHint(
	//	osg::StateSet::TRANSPARENT_BIN);
	//
	osg::ref_ptr<osg::PrimitiveSet> rpPrimitiveSet1 = new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, m_rpVertices->size());
	m_rpGeometry->addPrimitiveSet(rpPrimitiveSet1);
	
	osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
	blendFunc->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_rpTexture = new osg::Texture2D;
	m_rpTexture->setResizeNonPowerOfTwoHint(false);
	osg::ref_ptr<osg::Image> image =
		osgDB::readImageFile("image/04.png");
	m_rpTexture->setImage(image.get());
	m_rpTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	m_rpTexture->setWrap(osg::Texture::WRAP_R, osg::Texture::REPEAT);
	m_rpTexture->setUnRefImageDataAfterApply(true);

	/*osg::ref_ptr<osg::Geode> root = new osg::Geode;
	root->addDrawable(m_rpGeometry.get());
	root->getOrCreateStateSet()->setAttributeAndModes(blendFunc);
	root->getOrCreateStateSet()->setTextureAttributeAndModes(
		0, m_rpTexture.get());
	root->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	root->getOrCreateStateSet()->setRenderBinMode(osg::StateSet::OVERRIDE_RENDERBIN_DETAILS);*/

	//osg::Vec4Array *pColorArray = new osg::Vec4Array;
	//pColorArray->push_back(osg::Vec4(0.0, 1.0, 0.0, 0.0));
	//m_rpGeometry->setColorArray(pColorArray, osg::Array::Binding::BIND_OVERALL);
	
	m_rpGeometry->getOrCreateStateSet()->setAttributeAndModes(blendFunc);
	m_rpGeometry->getOrCreateStateSet()->setTextureAttributeAndModes(0, m_rpTexture.get());
	m_rpGeometry->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	m_rpGeometry->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	m_rpGeometry->getOrCreateStateSet()->setRenderBinMode(osg::StateSet::OVERRIDE_RENDERBIN_DETAILS);

	this->addChild(m_rpGeometry);

	//GxMapManager::instace()->targetLayer()->addChild(this);
}


GxImageOverlay::~GxImageOverlay()
{
}

void GxImageOverlay::setBounds(double xmin, double ymin, double xmax, double ymax)
{
	osg::Vec3Array *rpVertices = dynamic_cast<osg::Vec3Array *>(m_rpGeometry->getVertexArray());
	rpVertices->clear();
	osg::Vec3d worldPos;
	GxGeoUtil::degreeLLH2XYZ(osg::Vec3d(xmin, ymin, 100), worldPos);
	rpVertices->push_back(worldPos);
	GxGeoUtil::degreeLLH2XYZ(osg::Vec3d(xmax, ymin, 100), worldPos);
	rpVertices->push_back(worldPos);
	GxGeoUtil::degreeLLH2XYZ(osg::Vec3d(xmax, ymax, 100), worldPos);
	rpVertices->push_back(worldPos);
	GxGeoUtil::degreeLLH2XYZ(osg::Vec3d(xmin, ymax, 100), worldPos);
	rpVertices->push_back(worldPos);

	osg::DrawArrays *rpDrawArrays = dynamic_cast<osg::DrawArrays *>(m_rpGeometry->getPrimitiveSet(0));
	rpDrawArrays->setCount(rpVertices->size());

	rpVertices->dirty();
	rpDrawArrays->dirty();
	//m_rpTexCoords->dirty();
	m_rpGeometry->dirtyBound();
	//this->dirtyBound();
	//m_rpGeometry->getOrCreateStateSet()->removeAssociatedTextureModes(0, m_rpTexture.get());
	//m_rpGeometry->getOrCreateStateSet()->setTextureAttributeAndModes(0, m_rpTexture.get());
}

void GxImageOverlay::setImage(osg::Image *pImage)
{
	m_rpTexture->setImage(pImage);
}
