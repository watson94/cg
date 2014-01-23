
#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include <cg/visualization/viewer_adapter.h>
#include <cg/visualization/draw_util.h>

#include <cg/io/point.h>

#include <cg/primitives/point.h>
#include <cg/operations/visibility_graph.h>
#include <cg/operations/shortest_path.h>
#include <cg/operations/rasterization.h>

using cg::point_2f;
using cg::point_2;
using cg::contour_2;

struct visibility_graph_viewer : cg::visualization::viewer_adapter
{
   visibility_graph_viewer() :
       in_building(false),
     seg(cg::point_2(0, 0),  cg::point_2(100, 100))
   {};

   void draw_rectangle (cg::point_2 const & a, cg::visualization::drawer_type & drawer) const{
       drawer.draw_line(a, cg::point_2(a.x, a.y + 1));
       drawer.draw_line(a, cg::point_2(a.x + 1, a.y));
       drawer.draw_line(cg::point_2(a.x + 1, a.y + 1), cg::point_2(a.x + 1, a.y));
       drawer.draw_line(cg::point_2(a.x + 1, a.y + 1), cg::point_2(a.x, a.y + 1));
   }

   void draw(cg::visualization::drawer_type & drawer) const
   {
      std::cout << "Im here 1" << std::endl;
      drawer.set_color(Qt::green);
      for (auto x : ans) {
        draw_rectangle(x, drawer);
      }
      drawer.set_color(Qt::white);
      drawer.draw_line(seg[0], seg[1]);

   }

   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "Rasterization of segment" << cg::visualization::endl;
   }

   bool on_press(const point_2f & p)
   {
       seg[(in_building ? 0 : 1)] = p;
       in_building ^= 1;
       ans.clear();
   }

   bool on_key(int key)
   {
      switch (key)
      {
        case Qt::Key_Space:
            cg::rasterization(seg, std::back_inserter(ans));
        break;
        default : return false;
      }
      return true;
   }
private:
   cg::segment_2 seg;
   std::vector<point_2> ans;
   bool in_building;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   visibility_graph_viewer viewer;
   cg::visualization::run_viewer(&viewer, "Visibility graph of points and obstacles");
}


