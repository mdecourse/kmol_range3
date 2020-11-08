/*********************************************************************
 *  AUTHOR: Tomas Soltys                                             *
 *  FILE:   gl_entity_list.cpp                                       *
 *  GROUP:  Range                                                    *
 *  TYPE:   source file (*.cpp)                                      *
 *  DATE:   20-th March 2012                                         *
 *                                                                   *
 *  DESCRIPTION: OpenGL entity list class definition                 *
 *********************************************************************/

#include "gl_entity_list.h"

GLEntityList::GLEntityList()
    : GLList(GL_ENTITY_LIST_ITEM_N_LISTS)
{
    this->_init();
}

GLEntityList::GLEntityList(const GLEntityList &glEntityList)
    : GLList(glEntityList)
{
    this->_init(&glEntityList);
}

GLEntityList::~GLEntityList()
{
}

GLList &GLEntityList::operator =(const GLEntityList &glEntityList)
{
    this->GLList::operator =(glEntityList);
    this->_init(&glEntityList);
    return (*this);
}

void GLEntityList::_init(const GLEntityList *pGlEntityList)
{
    if (pGlEntityList)
    {

    }
}
