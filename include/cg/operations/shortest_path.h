#pragma once

#include <cg/primitives/contour.h>
#include <cg/primitives/segment.h>
#include <cg/operations/has_intersection/segment_segment.h>
#include <cg/operations/visibility_graph.h>
#include <cg/operations/distance.h>
#include "orientation.h"
#include <algorithm>

#include <map>
#include <cg/io/segment.h>

using namespace std;
namespace cg
{
    template <class Scalar, class OutIter>
    void shortest_path(const point_2t<Scalar> & start,const point_2t<Scalar> & finish, const std::vector<contour_2t<Scalar> > & obstacles, OutIter out) {
        std::vector<segment_2t<Scalar>> ans;
        cg::get_visibility(start, finish, obstacles, std::back_inserter(ans));


        const double max_dist = 10000000;

        std::map<point_2t<Scalar>, int> dist;

        std::map<point_2t<Scalar>, point_2t<Scalar>> prev;
        for (segment_2t<Scalar> & seg : ans) {
            dist[seg[0]] = max_dist;
            dist[seg[1]] = max_dist;
        }
        dist[start] = 0;

        int n = dist.size();
        for (int i = 0; i < n; i++) {
            for (segment_2t<Scalar> & seg : ans) {
                if ((dist[seg[0]] + distance(seg[0], seg[1])) < dist[seg[1]]) {
                    dist[seg[1]] = dist[seg[0]] + distance(seg[0], seg[1]);
                    prev[seg[1]] = seg[0];
                }
                if ((dist[seg[1]] + distance(seg[0], seg[1])) < dist[seg[0]]) {
                    dist[seg[0]] = dist[seg[1]] + distance(seg[0], seg[1]);
                    prev[seg[0]] = seg[1];
                }
            }
        }

        point_2t<Scalar> cur = finish;
        while (cur != start) {
            *out++ = segment_2t<Scalar>(cur, prev[cur]);
            cur = prev[cur];
        }

    }


}


