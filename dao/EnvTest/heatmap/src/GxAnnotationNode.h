#ifndef GX_ANNOTATION_NODE_H
#define GX_ANNOTATION_NODE_H

#include <osg/Group>

/**
* @class GxAnnotationNode
* @brief ���ڵ����
* @note
* @author k00026
**/
class GxAnnotationNode : public osg::Group
{
public:
	GxAnnotationNode();
	~GxAnnotationNode();

	/**
	* @brief ���ñ��ڵ������
	* @param visible [in] �Ƿ�ɼ�
	*/
	virtual void setVisible(bool visible);
};

#endif // !GX_ANNOTATION_NODE_H
