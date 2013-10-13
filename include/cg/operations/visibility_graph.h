#pragma once

#include <cg/primitives/contour.h>
#include <cg/primitives/segment.h>
#include <cg/operations/has_intersection/segment_segment.h>
#include <cg/operations/orientation.h>
#include "orientation.h"

namespace cg
{

   template <class Scalar>
   bool check_intersection(point_2t<Scalar> p, point_2t<Scalar> q,const  std::vector<contour_2t<Scalar> > & obstacles) {
       segment_2t<Scalar> seg1(p, q);
       for (const contour_2t<Scalar> & contour : obstacles) {
           for (size_t i = 0; i < contour.size(); i++) {
               segment_2t<Scalar> seg2;
               if (i != (contour.size() - 1)) {
                   seg2 = segment_2t<Scalar>(contour[i], contour[i + 1]);
               } else {
                   seg2 = segment_2t<Scalar>(contour[i], contour[0]);
               }
               if ( (seg1[0] != seg2[0]) && (seg1[0] != seg2[1]) && (seg1[1] != seg2[0]) && (seg1[1] != seg2[1]) && (has_intersection(seg1, seg2))) {
                   std::cout << "return true" << std::endl;
                   return true;
               }
           }

       }
       return false;
   }

   template <class Scalar>
   bool check_inside_polygon(const point_2t<Scalar> & p, const point_2t<Scalar> & q, const point_2t<Scalar> & prev,const point_2t<Scalar> &  next) {
       if (orientation(prev, p, next) != CG_LEFT) {
           return  ((orientation(prev, p, q) != CG_RIGHT) && (orientation(p, next, q) != CG_RIGHT));
       } else {
           return  ((orientation(prev, p, q) != CG_RIGHT) || (orientation(p, next, q) != CG_RIGHT));
       }
   }

   template <class Scalar, class BidIter, class OutIter>
   void get_visibility(BidIter it, const contour_2t<Scalar> * start_contour, const std::vector<contour_2t<Scalar> > & obstacles, OutIter out) {
       for (const contour_2t<Scalar> & contour : obstacles) {
           for (const point_2t<Scalar> & point : contour) {
               bool is_ok = true;
               point_2t<Scalar> prev = (it == start_contour->begin() ? *(start_contour->end() - 1) : *(it - 1));
               point_2t<Scalar> next = (it == (start_contour->end() - 1) ? *(start_contour->begin()) : *(it + 1));
               if (&contour != start_contour) {
                    if (check_intersection(*it, point, obstacles)) {
                        is_ok = false;
                    }
               } else {
                   if ((prev != point) && (next != point) && (check_inside_polygon(*it, point, prev,  next))) {
                        is_ok = false;
                   }
               }
               if (is_ok) {
                   std::cout << "Im Adding" << std::endl;
                   *(out++) = segment_2t<Scalar>(*(it), point);
               }
           }
       }
   }

   template <class Scalar, class OutIter>
   void get_endpoints_visibility(const point_2t<Scalar> & start, const std::vector<contour_2t<Scalar> > & obstacles, OutIter out) {
       for (const contour_2t<Scalar> & contour : obstacles) {
           for (const point_2t<Scalar> & point : contour) {
                bool is_ok = true;
                if (check_intersection(start, point, obstacles)) {
                    is_ok = false;
                }
                if (is_ok) {
                    std::cout << "Im Adding endpoints" << std::endl;
                    *(out++) = segment_2t<Scalar>(start, point);
                    *(out++) = segment_2t<Scalar>(point, start);
                }
           }

       }
   }

   template <class Scalar, class OutIter>
   void get_visibility(const point_2t<Scalar> & start,const point_2t<Scalar> & end, const std::vector<contour_2t<Scalar> > & obstacles, OutIter out) {
       if (!check_intersection(start, end, obstacles)) {
           *(out++) = segment_2(start, end);
       }
       std::vector<segment_2t<Scalar>> my_ans;
       get_endpoints_visibility(start, obstacles, std::back_inserter(my_ans));
       get_endpoints_visibility(end, obstacles, std::back_inserter(my_ans));


       for (const contour_2t<Scalar> & contour : obstacles) {
           for (auto it = contour.begin(); it != contour.end(); it++) {
               get_visibility(it, &contour, obstacles, std::back_inserter(my_ans));
           }
       }

       for (const segment_2t<Scalar> & seg : my_ans) {
           contour_2t<Scalar> c1(std::vector<point_2t<Scalar> >());
           contour_2t<Scalar> c2(std::vector<point_2t<Scalar> >());
           typename cg::contour_2t<Scalar>::const_iterator tmp;
           typename cg::contour_2t<Scalar>::const_iterator i1;
           typename cg::contour_2t<Scalar>::const_iterator i2;
           bool is_ok = true;
            for (const contour_2t<Scalar> & contour : obstacles) {
                for (auto it = contour.begin(); it != contour.end(); it++) {
                    if (*it == seg[0]) {
                        if (contour.size() > 2) {
                            point_2t<Scalar> prev = (it == contour.begin() ? *(contour.end() - 1) : *(it - 1));
                            point_2t<Scalar> next = (it == (contour.end() - 1) ? *(contour.begin()) : *(it + 1));
                            if (cg::orientation(seg[1], *it, prev) == cg::orientation(next, *it, seg[1])) {
                             is_ok = false;
                            }
                        }
                    }
                    if (*it == seg[1]) {
                        if (contour.size() > 2) {
                            point_2t<Scalar> prev = (it == contour.begin() ? *(contour.end() - 1) : *(it - 1));
                            point_2t<Scalar> next = (it == (contour.end() - 1) ? *(contour.begin()) : *(it + 1));
                            if (cg::orientation(seg[0], *it, prev) == cg::orientation(next, *it, seg[0])) {
                             is_ok = false;
                            }
                        }
                    }
                }
            }
            if (is_ok) {
                *(out++) = seg;
            }
       }


   }

}
