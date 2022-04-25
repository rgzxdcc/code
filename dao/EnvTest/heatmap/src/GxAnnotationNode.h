#ifndef GX_ANNOTATION_NODE_H
#define GX_ANNOTATION_NODE_H

#include <osg/Group>

/**
* @class GxAnnotationNode
* @brief 标绘节点基类
* @note
* @author k00026
**/
class GxAnnotationNode : public osg::Group
{
public:
	GxAnnotationNode();
	~GxAnnotationNode();

	/**
	* @brief 设置标绘节点的显隐
	* @param visible [in] 是否可见
	*/
	virtual void setVisible(bool visible);
};

#endif // !GX_ANNOTATION_NODE_H
