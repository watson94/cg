#pragma once

#include <cg/primitives/contour.h>
#include <cg/primitives/rectangle.h>
#include <cg/primitives/segment.h>
#include "orientation.h"

namespace cg
{
   // c is ccw contour
    template <class OutIter>
    void rasterization(segment_2 seg, OutIter out) {

        seg = segment_2(min(seg), max(seg));
        if (seg[0].x == seg[1].x && (seg[0].x == (int) seg[0].x)) {
            for (int i = (int) seg[0].y ; i < seg[1].y; i++) {
                (*out++) = point_2((int)seg[0].x, i);
                (*out++) = point_2((int)seg[0].x - 1, i);
            }
            return;
        }
        double dx = 1;
        double dy = (seg[1].y >= seg[0].y ? 1 : -1);

        cg::point_2 cur_rect =  point_2((int)seg[0].x, (int)seg[0].y);

        cg::orientation_t to_x = (dy > 0 ? CG_LEFT : CG_RIGHT);

        point_2 check_point = (dy > 0 ? point_2(cur_rect.x + 1, cur_rect.y + 1) : point_2(cur_rect.x + 1, cur_rect.y));
        while (1/*ch.x < seg[1].x || dy * (cur_rect.y) < dy * seg[1].y*/) {
            (*out++) = cur_rect;
            if (check_point.x >= seg[1].x && dy * check_point.y >= dy * seg[1].y) {
                break;
            }
            if (cg::orientation(seg[0], seg[1],  check_point) == CG_COLLINEAR) {
                std::cout  << "Debug" << std::endl;
                cur_rect.x += dx;
                check_point.x += dx;
                cur_rect.y += dy;
                check_point.y += dy;
            } else
            if (cg::orientation(seg[0], seg[1],  check_point) == to_x) {
                cur_rect.x += dx;
                check_point.x += dx;
            } else {
                cur_rect.y += dy;
                check_point.y += dy;
            }
        }

    }
}
