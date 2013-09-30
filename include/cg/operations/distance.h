#pragma once

#include <cg/primitives/contour.h>
#include <cg/primitives/segment.h>
#include <cg/operations/distance.h>
#include "orientation.h"
#include <cg/io/vector.h>


#include <boost/numeric/interval.hpp>
#include <gmpxx.h>


namespace cg
{
    typedef boost::numeric::interval_lib::unprotect<boost::numeric::interval<double> >::type interval;
    //
    template<class Scalar>
    Scalar vect_mul(vector_2t<Scalar> const & v1, vector_2t<Scalar> const & v2) {
        return v1.x * v2.y - v1.y * v2.x;
    }

    template <class Scalar>
    Scalar distance2(point_2t<Scalar> const & p, point_2t<Scalar> const & q) {
        return (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y);
    }

    bool exactly_smaller_distance(point_2 const & p, point_2 const & q, point_2 const & p1, point_2 const & q1) {
        double d1 = distance2(p, q);
        double d2 = distance2(p1, q1);
        double eps = (d1 + d2) * std::numeric_limits<double>::epsilon() * 16;
        if (abs(d1 - d2) <= eps)
            return d1 < d2;
        interval d1_in(abs(distance2<interval>(p, q)));
        interval d2_in(abs(distance2<interval>(p1, q1)));
        if (d1_in.lower() >= d2_in.upper())
            return false;
        if (d1_in.upper() < d2_in.lower())
            return true;
        mpq_class d1_mpq(abs(distance2<mpq_class>(p, q)));
        mpq_class d2_mpq(abs(distance2<mpq_class>(p1, q1)));
        return d1_mpq < d2_mpq;
    }

    //Determines what point closet to segment(exactly);
    bool exactly_closer_to_segment(point_2 const & p, point_2 const & q, segment_2 const & seg) {
        return (((exactly_smaller_distance(p, seg[0], q, seg[0])) && (exactly_smaller_distance(p, seg[0], q, seg[1]))) ||
               ((exactly_smaller_distance(p, seg[1], q, seg[0])) && (exactly_smaller_distance(p, seg[1], q, seg[1])))) ;
//        vector_2 v1 = seg[0] - p;
//        vector_2 v2 = seg[1] - p;

//        vector_2 v3 = seg[0] - q;
//        vector_2 v4 = seg[1] - q;
//        double m1 = abs(vect_mul(v1, v2));
//        double m2 = abs(vect_mul(v3, v4));
//        double eps = (m1 + m2) * std::numeric_limits<double>::epsilon() * 8;
//        if (abs(m1 - m2) <= eps)
//            return m1 < m2;
//        interval m1_in(abs(vect_mul<interval>((vector_2t<interval>)v1, (vector_2t<interval>)v2)));
//        interval m2_in(abs(vect_mul<interval>(v3, v4)));
//        if (m1_in.lower() >= m2_in.upper())
//            return false;
//        if (m1_in.upper() < m2_in.lower())
//            return true;

//        mpq_class m1_mpq(abs(vect_mul<mpq_class>(v1, v2)));
//        mpq_class m2_mpq(abs(vect_mul<mpq_class>(v1, v2)));
//        return m1_mpq < m2_mpq;
    }




    //distance from point to point
    double distance(point_2 const & p, point_2 const & q) {
        return (sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y)));
    }

    //square of distance from point to point


    //distance from point to segment
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
