#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include <cg/visualization/viewer_adapter.h>
#include <cg/visualization/draw_util.h>

#include <cg/io/point.h>

#include <cg/primitives/point.h>
#include <cg/operations/visibility_graph.h>
#include <cg/operations/shortest_path.h>

using cg::point_2f;
using cg::point_2;
using cg::contour_2;

struct visibility_graph_viewer : cg::visualization::viewer_adapter
{
   visibility_graph_viewer() :
       cur(0),
       start(-250, 0),
       finish(250, 0),
       obstacles(std::vector<cg::contour_2>())
   {
       obstacles.push_back(cg::contour_2(std::vector<cg::point_2>()));
   }

   void draw(cg::visualization::drawer_type & drawer) const
   {
      std::cout << "Im here 1" << std::endl;
      drawer.set_color(Qt::red);
      drawer.draw_point(start, 4);
      drawer.draw_point(finish, 4);

      std::cout << "Im here 2" << std::endl;

      drawer.set_color(Qt::white);
      for (contour_2 const & polygon : obstacles) {
        for (point_2 const & p : polygon) {
            drawer.draw_point(p, 4);
        }
      }

      std::cout << "Im here 3" << std::endl;

      std::vector<cg::segment_2> ans;

      std::vector<cg::segment_2> shortest_path;
      //std::vector<cg::contour_2> obstacles;

      cg::get_visibility(start, finish, obstacles, std::back_inserter(ans));
      cg::shortest_path(start, finish, obstacles, std::back_inserter(shortest_path));

      drawer.set_color(Qt::green);
      for (const cg::segment_2 & seg : ans) {
          drawer.draw_line(seg[0], seg[1]);
      }

      drawer.set_color(Qt::green);
      for (const cg::segment_2 & seg : ans) {
          drawer.draw_line(seg[0], seg[1]);
      }


      drawer.set_color(Qt::red);
      for (contour_2 const & polygon : obstacles) {
          for (size_t i = 0; i < polygon.size() ; i++) {
              //std::cout << i << std::endl;
              if (i != (polygon.size() - 1)) {
                drawer.draw_line(polygon[i], polygon[i + 1]);
              } else {
                  drawer.draw_line(polygon[0], polygon[i]);
              }

          }

      }

      drawer.set_color(Qt::blue);
      for (const cg::segment_2 & seg : shortest_path) {
          drawer.draw_line(seg[0], seg[1]);
      }
   }

   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "algorithm of building visibility graph" << cg::visualization::endl;
      p.corner_stream() << "press mouse rbutton to add point" << cg::visualization::endl
                        << "press up/down key to change polygon" << cg::visualization::endl
                        << "press space key to add polygon" << cg::visualization::endl;

   }

   bool on_press(const point_2f & p)
   {
       obstacles[cur].add_point(p);
       return true;
   }

   bool on_key(int key)
   {
      switch (key)
      {
        case Qt::Key_Up :
            if (cur == obstacles.size() - 1) {
              cur = 0;
             } else {
              cur++;
            }
        break;

        case Qt::Key_Down :
            if (cur == 0) {
              cur = obstacles.size() - 1;
            } else {
              cur--;
            }
        break;
        case Qt::Key_Space:
            obstacles.push_back(contour_2(std::vector<cg::point_2>()));
            cur = obstacles.size() - 1;
            std::cout << cur << std::endl;
        break;
        default : return false;
      }
      return true;
   }
private:
   std::vector<cg::contour_2> obstacles;
   int cur;
   cg::point_2 start;
   cg::point_2 finish;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   visibility_graph_viewer viewer;
   cg::visualization::run_viewer(&viewer, "Visibility graph of points and obstacles");
}


