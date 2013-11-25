 #pragma once

#include "triangulation_primitives.h"
#include <boost/optional/optional.hpp>
#include <boost/optional.hpp>
namespace cg {

    template <class T>
    struct cell {
        cell() {
            vertexes.push_back(vertex_ptr<T>(new vertex_t<T>(true)));
        }

        bool contains_point(point_2t<T> const & p) {
            for (int i = 0; i < vertexes.size(); i++) {
                if (vertexes[i]->point == p) {
                    return true;
                }
            }
            return false;
        }

        boost::optional<edge_ptr<T> > find_edge(point_2t<T> const & p) {
            boost::optional<edge_ptr<T> > ans;
            for (int i = 0; i < faces.size(); i++) {
                edge_ptr<T> e = faces[i]->edge;
                for (int j = 0; j < 3; j++) {
                    if (cg::orientation(e->begin()->point, p, e->end()->point) == CG_COLLINEAR) {
                        ans = e;
                        return ans;
                    }
                    e = e->next_edge;
                }
            }
            return ans;
        }

        face_ptr<T> & find_face(point_2t<T> const & p) {
            for (int i = 0; i < faces.size(); i++) {
                if (faces[i]->check_inside(p)) {
                    return faces[i];
                }
            }
        }


        void init_cell() {
            face_ptr<T> face1(new face_t<T>());

            edge_ptr<T> e1(new edge_t<T> (face1, vertexes[0]));
            edge_ptr<T> e2(new edge_t<T> (face1, vertexes[1]));
            edge_ptr<T> e3(new edge_t<T> (face1, vertexes[2]));
            e1->next_edge = e2;
            e2->next_edge = e3;
            e3->next_edge = e1;
            face1->edge = e1;

            face_ptr<T> face2(new face_t<T>());

            edge_ptr<T> e4(new edge_t<T> (face1, vertexes[0]));
            edge_ptr<T> e5(new edge_t<T> (face1, vertexes[2]));
            edge_ptr<T> e6(new edge_t<T> (face1, vertexes[1]));
            e4->next_edge = e5;
            e5->next_edge = e6;
            e6->next_edge = e4;
            face2->edge = e4;

            //set twins
            e1->twin = e4;
            e4->twin = e1;
            e2->twin = e6;
            e6->twin = e2;
            e3->twin = e5;
            e5->twin = e3;

            faces.push_back(face1);
            faces.push_back(face2);
        }

        void add_point( point_2t<T> const & p) {
            if (contains_point(p)) return;
            vertex_ptr<T> v (new vertex_t<T>(p));
            vertexes.push_back(v);
            if (vertexes.size() <= 2) {
                return;
            }
            if (vertexes.size() == 3) {
                init_cell();
                return;
            }

            //внутри фэйса(добавить 3 ребра)
            auto face = find_face(p);
            std::cout << "localize in" << " ";
            face->print();
            auto it = std::find(faces.begin(), faces.end(), face);
            faces.erase(it);
            edge_ptr<T> e = face->edge;
            edge_ptr<T> old_e[3];
            old_e[0]= face->edge;
            old_e[1] = face->edge->next_edge;
            old_e[2] = face->edge->next_edge->next_edge;

            vertex_ptr<T> old_v[3];
            old_v[0]=  old_e[0]->begin();
            old_v[1] = old_e[1]->begin();
            old_v[2] = old_e[2]->begin();


            for (int i = 0; i < 3; i++) {
                face_ptr<T> new_face(new face_t<T>());
                edge_ptr<T> e1(new edge_t<T>(new_face, old_v[i]));
                edge_ptr<T> e2(new edge_t<T>(new_face, old_v[(i + 1) % 3]));
                e->face = new_face;
                e->opp_vertex = v;
                e->next_edge = e1;
                e1->next_edge = e2;
                e2->next_edge = e;

                new_face->edge = e;
                faces.push_back(new_face);
                ////e -> next
                e = ((i == 0) ? old_e[1] : old_e[2]);
                //debug
                new_face->print();
                //debug
             }
             //set twins
             for (int i = 0; i < 3; i++) {
                for(int j = i + 1; j < 3; j++) {
                    auto e1 = old_e[i];
                    auto e2 = old_e[j];
                        for (int k = 0; k < 3; k++) {
                            for (int l = 0; l < 3;l++) {
                                if (*e1 == *e2) {
                                    e1->twin = e2;
                                    e2->twin = e1;
                                }
                                e2 = e2->next_edge;
                            }
                            e1 = e1->next_edge;
                        }
                }
            }

             for (int i = 0; i < 3; i++) {
                fix_edge(old_e[i]);
             }

        }


        void flip(edge_ptr<T> & edge) {
            auto twin = edge->twin;
            auto v1 = edge->begin();
            auto v2 = edge->end();
            auto v3 = edge->opp_vertex;
            auto v4 = twin->opp_vertex;
            auto face1 = edge->face;
            auto face2 = twin->face;
            //debug
            std::cout << "face1 before flip: ";
            face1->print();

            std::cout << "face2 before flip: ";
            face2->print();
            //debugOK
            auto e1 = edge->next_edge;
            auto e2 = edge->next_edge->next_edge;
            auto e3 = twin->next_edge;
            auto e4 = twin->next_edge->next_edge;
            //debug
            std::cout << "debug Edges" << std::endl;
            e1->print();
            e2->print();
            e3->print();
            e4->print();
            //debug


            //first face

            edge_ptr<T> new_edge(new edge_t<T>(face1, v1));
            e2->face = face1;
            e3->face = face1;

            e2->next_edge = e3;
            e3->next_edge = new_edge;

            e2->opp_vertex = v4;
            e3->opp_vertex = v3;
            new_edge->next_edge = e2;
            face1->edge = e2;

            std::cout << "first face after flip" << std::endl;
            face1->print();

            //second face
            edge_ptr<T> new_twin(new edge_t<T>(face2, v2));
            e1->face = face2;
            e4->face = face2;

            e1->next_edge = new_twin;
            new_twin->next_edge = e4;

            e1->opp_vertex = v4;
            e4->opp_vertex = v3;
            e4->next_edge = e1;
            face2->edge = e1;


            std::cout << "second face after flip" << std::endl;
            face2->print();

            //twins
            new_edge->twin = new_twin;
            new_twin->twin = new_edge;
        }

        void fix_edge(edge_ptr<T> & edge) {
            if (check_Delaunay_criteria(edge)) {
                std::cout << "Yes, I will flip now" << std::endl;
                edge_ptr<T> edge_to_fix[4];
                edge_to_fix[0] = edge->next_edge;
                edge_to_fix[1] = edge->next_edge->next_edge;
                edge_to_fix[2] = edge->twin->next_edge;
                edge_to_fix[3] = edge->twin->next_edge->next_edge;
                //4 to fix
                flip(edge);
                for (int i = 0; i < 4; i++) {
                    fix_edge(edge_to_fix[i]);
                }
            }
        }

        bool check_Delaunay_criteria(edge_ptr<T> & edge) {
            face_ptr<T> face1 = edge->face;
            face_ptr<T> face2 = edge->twin->face;
            vertex_ptr<T> v1 = edge->opp_vertex;
            vertex_ptr<T> v2 = edge->twin->opp_vertex;
            return (face1->check_inside_circumcircle(v2) || face2->check_inside_circumcircle(v1));
        }



        std::vector<triangle_2t<T> >  get_triangulation() { //toDo
            std::vector<triangle_2t <T> > ans;
            ans.push_back(triangle_2(point_2(0, 0), point_2(0, 0), point_2(0, 0)));
            for (int i = 0; i < faces.size(); i++) {
                if ((!faces[i]->edge->begin()->is_inf) && (!faces[i]->edge->end()->is_inf) && (!faces[i]->edge->opp_vertex->is_inf)) {
                    ans.push_back(triangle_2(faces[i]->edge->begin()->point, faces[i]->edge->end()->point, faces[i]->edge->opp_vertex->point));
                }
            }
            return ans;
        }

        std::vector<vertex_ptr <T> > vertexes;
        std::vector<face_ptr <T> > faces;
    };


}





