#pragma once

#include <cg/primitives/contour.h>
#include <cg/operations/distance.h>
#include "orientation.h"
#include <cg/io/vector.h>


namespace cg
{
    //distance from point to point
    double distance(point_2 const & p, point_2 const & q) {
        return (sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y)));
    }

   // distance from point to segment
    double distance(point_2 const & p, point_2 const &  q, point_2 const & x) {
        std::cout<< "Distance between : " << p << q << x << std::endl;
        double length = distance(p, q);
        vector_2 v1 = x - p;
        vector_2 v2 = x - q;
        vector_2 v3 = q - p;
        double scalar = ((v1 * v3) / length);
        std::cout << "Scalar" << scalar << std::endl;
        if ((scalar > length) || (scalar < 0)) {
//          std::cout << " To vertex: " << std::min(distance(x, q), distance(x, p)) << std::endl;
            return std::min(distance(x, q), distance(x, p));
        } else {
//          std::cout << "Vectors: " << v1 << " " << v2 << " " << v3 << std::endl;
//          std::cout << " To segment: "  << abs(v1 ^ v3) / distance(x, q) << std::endl;
//          std::cout << "Multiplication: " << abs(v1 ^ v3) << abs(v2 ^ v3) << abs(v1 ^ v2) << std::endl ;
            return abs(v1 ^ v3) / length;
        }
    }  

}
