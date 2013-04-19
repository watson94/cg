#pragma once

#include <cg/operations/orientation.h>
#include <cg/primitives/contour.h>

namespace cg
{
   // c is convex contour ccw orientation
   inline bool convex_contains(contour_2 const & pol, point_2 const & p) {
       if (orientation(p, pol[0], pol[1]) == CG_RIGHT) return false;
       auto i = std::lower_bound(pol.begin() + 2, pol.end(), p, [&pol](const point_2 &p1, const point_2 &p2) {
           return (orientation(pol[0], p2, p1) == CG_RIGHT);
           }
       );
       if (i == pol.end()) {
           return false;
       }
       return (orientation(p, *i, *(i - 1)) != CG_LEFT);
   }

   // c is ordinary contour
   inline bool contains(contour_2 const & c, point_2 const & q);
}




