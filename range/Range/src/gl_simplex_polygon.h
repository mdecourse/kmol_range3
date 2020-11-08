/*********************************************************************
 *  AUTHOR: Tomas Soltys                                             *
 *  FILE:   gl_simplex_polygon.h                                     *
 *  GROUP:  Range                                                    *
 *  TYPE:   header file (*.h)                                        *
 *  DATE:   7-th August 2015                                         *
 *                                                                   *
 *  DESCRIPTION: OpenGL simplex polygon class declaration            *
 *********************************************************************/

#ifndef GL_SIMPLEX_POLYGON_H
#define GL_SIMPLEX_POLYGON_H

#include "gl_simplex.h"

class GLSimplexPolygon : public GLSimplex
{

    protected:

        //! Thickness.
        double thickness;

    private:

        //! Internal initialization function.
        void _init(const GLSimplexPolygon *pGlPolygon = nullptr );

    public:

        //! Constructor.
        explicit GLSimplexPolygon(GLWidget *glWidget, const std::vector<RR3Vector> &nodes, double thickness = 0.0);

        //! Copy constructor.
        GLSimplexPolygon(const GLSimplexPolygon &glPolygon);

        //! Destructor.
        ~GLSimplexPolygon();

        //! Assignment operator.
        GLSimplexPolygon &operator =(const GLSimplexPolygon &glPolygon);

    protected:

        //! Initialize scene.
        void initialize(void);

        //! Finalize scene.
        void finalize(void);

        //! Draw scene.
        void draw(void);

        //! Draw normal.
        void drawNormal(const std::vector<RNode> &nodes1,
                        const std::vector<RNode> &nodes2,
                        bool volumeElement,
                        bool useTexture);

        //! Draw wired.
        void drawWired(const std::vector<RNode> &nodes1,
                       const std::vector<RNode> &nodes2,
                       bool volumeElement,
                       bool useTexture);

        //! Draw nodes.
        void drawNodes(const std::vector<RNode> &nodes1,
                       const std::vector<RNode> &nodes2,
                       bool volumeElement);

};

#endif // GL_SIMPLEX_POLYGON_H
