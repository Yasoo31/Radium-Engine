#include <Core/Mesh/DCEL/Iterator/Vertex/VFIterator.hpp>

#include <Core/Mesh/DCEL/Vertex.hpp>
#include <Core/Mesh/DCEL/HalfEdge.hpp>
#include <Core/Mesh/DCEL/Face.hpp>

namespace Ra {
namespace Core {



/// CONSTRUCTOR
inline VFIterator::VFIterator( Vertex_ptr& v ) : VIterator< Face >( v ) { }



/// DESTRUCTOR
inline VFIterator::~VFIterator() { }



/// LIST


inline FaceList VFIterator::list() const
{
    FaceList L;
    HalfEdge_ptr h1 = m_v->HE();
    HalfEdge_ptr h2 = h1 != NULL ? h1->Twin() : NULL;
    Face_ptr f1 = h1->F();
    Face_ptr f2 = h2->F();
    do {
        if (h1 != NULL)
        {
            L.push_back(f1);
            if (f1 == f2) break;
            h1 = h1->Prev()->Twin();
            f1 = h1->F();
        }
        if (h2 != NULL)
        {
            L.push_back(f2);
            if (f1 == f2) break;
            h2 = h2->Next()->Twin();
            f2 = h2->F();
        }
    } while( h1 != NULL || h2 != NULL );
    return L;
}




/// OPERATOR
inline Face* VFIterator::operator->() const {
    return m_he->F().get();
}



} // namespace Core
} // namespace Ra