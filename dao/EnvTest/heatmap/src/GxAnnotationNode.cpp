#include "GxAnnotationNode.h"

GxAnnotationNode::GxAnnotationNode()
{
}


GxAnnotationNode::~GxAnnotationNode()
{
}

void GxAnnotationNode::setVisible(bool bVisible)
{
	setNodeMask(bVisible);
}
