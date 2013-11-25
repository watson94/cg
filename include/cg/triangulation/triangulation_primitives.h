#include <cg/primitives/point.h>
#include <algorithm>
#include <cg/operations/orientation.h>
#include <cg/primitives/triangle.h>
#include <cg/primitives/segment.h>
#include <cg/io/segment.h>
#include <set>
#include <map>
#include <memory>
#include <boost/optional.hpp>
#include <exception>
#include <cg/operations/has_intersection/segment_segment.h>


namespace cg {
    template<class T> struct vertex_t;
    template<class T> struct edge_t;
    template<class T> struct face_t;


    template <class T>
    using vertex_ptr = std::shared_ptr<vertex_t<T> > ;
    template <class T>
    using edge_ptr = std::shared_ptr<edge_t<T> > ;
    template <class T>
    using face_ptr = std::shared_ptr<face_t<T> > ;


    template <class T>
    struct vertex_t  {

        vertex_t (bool _is_inf) {
            is_inf = _is_inf;
        }

        vertex_t (point_2t<T> const  & _point)   {
            point = _point;
            is_inf = false;
        }

        point_2t<T> & to_point() {
            return point;
        }



        void print() {
            if (is_inf) {
                std:: cout << "Infinity" << std::endl;
            } else {
                std::cout << point.x << " " << point.y << std::endl;
            }
        }

        bool is_inf;
        point_2t<T> point;
    };

    template <class T>
    struct edge_t {


        edge_t(face_ptr<T>  & _face, vertex_ptr<T>  & _opp_vertex) {
            face = _face;
            opp_vertex = _opp_vertex;
        }

        void print() {
            std::cout << "v1 : ";
            begin()->print();
            std::cout << "v2 : ";
            end()->print();
        }


        vertex_ptr<T> & begin() {
            return next_edge->opp_vertex;
        }

        vertex_ptr<T> & end() {
            return next_edge->next_edge->opp_vertex;
        }
        bool operator == (edge_t<T> & e2) {
            return (((begin() == e2.begin()) && ((end() == e2.end()))) ||
                     ((begin() == e2.end()) && ((end() == e2.begin()))) );
        }


        edge_ptr<T> twin, next_edge;
        vertex_ptr<T> opp_vertex; //Opposite vertex
        face_ptr<T> face;
    };

    template <class T>
    struct face_t  {
        face_t() {

        }

        void print() {
            std::cout << "This is face" << std::endl;
            edge->begin()->print() ;
            edge->end()->print();
            edge->opp_vertex->print();
        }

        bool check_inside(point_2t<T> const & p) {

            auto v1 = edge->opp_vertex;
            auto v2 = edge->next_edge->opp_vertex;
            auto v3 = edge->next_edge->next_edge->opp_vertex;

            auto p1 = v1->point;
            auto p2 = v2->point;
            auto p3 = v3->point;

            if (v1->is_inf) {
                return (cg::orientation(p2, p3, p) != CG_RIGHT);
            }

            if (v2->is_inf) {
                return (cg::orientation(p3, p1, p) != CG_RIGHT);
            }
            if (v3->is_inf) {
                return (cg::orientation(p1, p2, p) != CG_RIGHT);
            }

            return (cg::orientation(p1, p2, p) == cg::orientation(p2, p3, p) &&
                    cg::orientation(p1, p2, p) == cg::orientation(p3, p1, p));
        }

        bool check_inside_circumcircle(vertex_ptr<T> const & v) {
            if (v->is_inf) {
                return false;
            }
            auto v1 = edge->opp_vertex;
            auto v2 = edge->next_edge->opp_vertex;
            auto v3 = edge->next_edge->next_edge->opp_vertex;

            auto p = v->point;
            auto p1 = v1->point;
            auto p2 = v2->point;
            auto p3 = v3->point;
            if (v1->is_inf) {
                return (cg::orientation(p2, p3, p) != CG_RIGHT);
            }

            if (v2->is_inf) {
                return (cg::orientation(p3, p1, p) != CG_RIGHT);
            }
            if (v3->is_inf) {
                return (cg::orientation(p1, p2, p) != CG_RIGHT);
            }
            return check_inside_circumcircle(p1, p2, p3, v->point);
        }

        bool check_inside_circumcircle(point_2t<T> a, point_2t<T> b, point_2t<T> c, point_2t<T> d) {
           double a11 = a.x - d.x, a12 = a.y - d.y, a13 = (a.x * a.x - d.x * d.x) + (a.y * a.y - d.y * d.y);
           double a21 = b.x - d.x, a22 = b.y - d.y, a23 = (b.x * b.x - d.x * d.x) + (b.y * b.y - d.y * d.y);
           double a31 = c.x - d.x, a32 = c.y - d.y, a33 = (c.x * c.x - d.x * d.x) + (c.y * c.y - d.y * d.y);
           return (a11 * (a22 * a33 - a23 * a32) - a12 * (a21 * a33 - a23 * a31) + a13 * (a21 * a32 - a22 * a31)) > 0;
        }

        edge_ptr<T> edge;
    };

}
