#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <cstring>
#include <string>
#include <set>
#include <iterator>
//#include <fmt>




using namespace std;


/*
 *
 * a grid of numbers which represent trees
 * count the number of trees on the edges.
 * count the number of trees visible not on the edges
 * a tree is visible if it is taller than every other tree
 * in it's row and column
 *
 * this is sounding very similar to 2020/day_eleven (which is currently unsolved)
 *
 * approch. each number is a Point. the point's height is its value.
 * the points x,y are its column, row. the point should need know nothing
 * about itself nor its neighbors, but if it did, something else would tell
 * the point about that.
 * Points can be compared to each other. Point A > Point B if A.height > B.height
 * A == B if A.height = B.height
 *
 * the points are a Grid which itself if comprised of Rows and Columns
 * each Row is a vector of Points. each Column is a vector of Points
 *
 *
 *
 * 
 */

/* sample input
30373
25512
65332
33549
35390
*/

//make this a template class

class Point {

    public:
        int x() const { return _x; }
        int y() const { return _y; }
        const int height() const { return _height; }

        bool operator<(const Point& p) const {
            return _height < p._height;
        }

        bool operator>(const Point& p) const {
            return _height > p._height;
        }
        
        bool operator==(const Point& p) const {
            return (_x==p._x && _y==p._y &&_height==p._height);
        }

        friend ostream& operator<<(ostream &os, const Point& p) {
            return os << "(" << p._x << "," << p._y << "," << p._height << ")";
        };


        Point() : _x(0), _y(0), _height(0) {}

        Point(int x, int y, int height) {
            _height = height;
            _x = x;
            _y = y;
        }

        

    private:
        int _x = 0;
        int _y = 0;
        int _height = 0;

    
};

//a vector<Point> can be reclassed as a line
class Line {
    public:

        enum Direction {LEFT, RIGHT, UP, DOWN};

                
        vector<Point>::const_iterator begin() const { return _points.begin(); }
        vector<Point>::const_iterator end() const { return _points.end(); }

        int length() { return _points.size(); }

        const Point& operator[](int num) {
            return _points[num-1];
        }

        Point highest_in_direction_from_point(const Point& p, Direction dir) {

            Point rtn = p;
            switch (dir) {
                case UP:
                    for (int i = p.y(); i >= 0; i--) {
                        if (_points[i].height() >= p.height())
                            rtn = _points[i];                        
                    }
                    break;
                    
                case LEFT:
                    for (int i = p.x(); i >= 0; i--) {
                        if (_points[i].height() >= p.height())
                            rtn = _points[i];
                    }
                    break;

                case DOWN:
                    for (int i = p.y(); i <= _points.size(); i++) {
                        if (_points[i].height() >= p.height())
                            rtn = _points[i];                        
                    }
                    break;
                    
                case RIGHT:
                    for (int i = p.x(); i <= _points.size(); i++) {                        
                        if (_points[i].height() >= p.height())
                            rtn = _points[i];                        
                    }
                    break;
            }

            return rtn;
        };

        friend ostream& operator<<(ostream &os, const Line& ell) {
            return os << "line number: " << ell._num;
        };

        void add_point(Point p) { _points.push_back(p); }

        //void push_back(Point p) { add_point(p); }

        void add_point(int x, int y) { _points.push_back(Point{x,y,0}); }

        Line() : _points{0}, _num(0) {};
        
        Line(vector<Point> points) : _points(points) {};

        //this is essentially the copy constructor
        //Line(Line line) {
            ////not implemented
            ////iterate over line.points adding to _points
        //}

        Line(int line_num) : _points{0}, _num(line_num) {};

        Line(int line_num, size_t num_points) : _points{num_points}, _num(line_num) {};

        Point get_point(int num) { return _points[num-1]; }

        Point max_point() const {
            return *max_element(_points.begin(), _points.end());
        };

        void show_points() {
            for (auto& p : _points) { cout << p; }
            cout << endl;
        };

        void show_point_vals() {
            for (auto& p : _points) { cout << p.height(); }
            cout << endl;
        };

        

    private:
        vector<Point> _points{0};
        int _num = 0;

    
};

//ostream& operator<<(ostream& os, const Point& p) {
    //return os << "(" << p._x << "," << p._y << "," << p._height << ")";
//}

//make this so it can take a vector<Type> thing
class Grid {

    public:

        const int num_points() { return points.length(); };

        //maybe these should be map<int, set<Point>>
        map<int, Line> rows;
        map<int, Line> cols;
        Line points;

        
        Grid() {
            rows[1] = Line {0};
            cols[1] = Line {0};
            points = Line {0};           
        }

        Grid(int num_rows, int num_cols) {

            //populate the points
            for (int x = 1; x <= num_cols; x++) {
                
                for (int y = 1; y <= num_rows; y++) {
                    points.add_point(Point {x,y,0});
                }
            }

            
            //populate the rows
            for (int y = 1; y <= num_rows; y++){
                Line ell {num_rows};
                for (int x = 1; x <= num_cols; x++) {
                    ell.add_point(Point{x,y,0});
                }

                rows[y] = ell;
            }
            
            //populate the columns
            for (int x = 1; x <= num_cols; x++) {
                Line ell {num_rows};
                for (int y = 1; y <= num_rows; y++) {
                    ell.add_point(Point{x,y,0});
                }
                cols[x] = ell;
            }
            
        }

        void add_point(Point p) {            
            cols[p.x()].add_point(p);
            rows[p.y()].add_point(p);
            points.add_point(p);
            
        };

        bool contains(const Point& p) const {
            for (auto _p : points) {
                if (_p == p) {
                    return true; 
                }
            }

            //for (const vector<Point>::iterator it = points.begin(); it != points.end(); it++) {
                //if (*it == p)
                    //return true;
            //}
            
            return false;
        };
        
        Line get_line(int num) {
            //not implemented
            return Line{0};
        }

        
        
        Point get_point(const int x, const int y) {

            //for e (auto& p : points) {
                //cout << "looking at point: " << p << endl;
                //if (p.x() == x && p.y() == y)
                    //return p;
            //}

            //return Point{0,0,0};
            Line p = rows[x];
            return p[y-1];

            //return rows[x].[y];
            
        };

        Line get_row(int num) {
            return rows[num];
        };

        Line get_col(int num) {
            return cols[num];
            
        };

        //tallest in row
        Point max_in_row(int num) {
            //Point max = *max_element(rows[num].begin(), rows[num].end());
            //return max;
            Line row = rows[num];
            return row.max_point();
            
            
        }


        Point max_in_col(int num) {
            //Point max = *max_element(cols[num].begin(), cols[num].end());
            //return max;

            return cols[num].max_point();
            
            
        }

        //the tallest point or points of the grid
        Point get_max_points() {
            //not implemented
            vector<Point> max_rows {};

            return Point{0,0,0};
            
            
        };

        Grid get_visible_points() {
            Grid g;

            //for (const auto& [row_num, row] : g.rows) {
                //cout << "row number: " << row_num << endl;
                //Point max_in_row = row.max_point();
                ////Point max_in_col = g.max_col(max_in_row.y());
            //}

            this->_add_boundry_lines(g);

            
            //loop over the rows (or columns) skipping the first
            //and last number in each
            Point p;
            for (size_t r = 2; r < rows.size(); r++) {
                
                Line& ell = rows[r];
                //cout << "Checking row " << r << endl;

                for (int i = 2; i <= ell.length()-1; i++) {
                    p = ell[i];
                    //cout << "  checking point " << p << endl;
                    Line& col = cols[p.x()];

                    Point highest_right = ell.highest_in_direction_from_point(p, Line::Direction::RIGHT);
                    Point highest_left = ell.highest_in_direction_from_point(p, Line::Direction::LEFT);
                    Point highest_up = col.highest_in_direction_from_point(p, Line::Direction::UP);
                    Point highest_down = col.highest_in_direction_from_point(p, Line::Direction::DOWN);

                    
                    

                    if (
                        (p == ell.highest_in_direction_from_point(p, Line::Direction::RIGHT))
                        ||
                        (p == ell.highest_in_direction_from_point(p, Line::Direction::LEFT))
                        ||
                        (p == col.highest_in_direction_from_point(p, Line::Direction::UP))
                        ||
                        (p == col.highest_in_direction_from_point(p, Line::Direction::DOWN))
                    ) {
                        cout << "Point " << p << " is visible" << endl;
                        cout << "    highest right " << highest_right << endl;
                        cout << "    highest left  " << highest_left << endl;
                        cout << "    highest up    " << highest_up << endl;
                        cout << "    highest down  " << highest_down << endl;
                        
                        g.add_point(p);
                    }

                    

                    if (p.y() == 2 && p.height() == 3) {
                        break;
                    }
                    
                    
                    
                    //Point max_in_row = ell.max_point();
                    
                    //Point max_in_col = this->max_in_col(max_in_row.y());

                    //if (max_in_row > max_in_col) {
                        //if (!g.contains(max_in_row))
                            //g.add_point(max_in_row);
                    //}
                    //else {
                        //if (!g.contains(max_in_col))
                        //g.add_point(max_in_row);
                    //}
                }

                if (p.y() == 2 && p.height() == 3) {
                    break;
                }
            }
                        

            return g;
        };

        void show() {
            for(auto& row : rows) {
                row.second.show_points();
            }
        };

        void show_heights() {
            for(auto& row : rows) {
                row.second.show_point_vals();
            }
        };

        friend ostream& operator<<(ostream& os, const Grid& g) {
            string st = "rows: " + to_string(g.rows.size());
            st += ". cols: " + to_string(g.cols.size());
            return os << st;
        }

    private:
        //map<int, Point> _max_points
        void _add_boundry_lines(Grid& _g) {
            //first and last rows are always visible
            for (auto& p : rows[1])
                _g.add_point(p);

            for (auto& p : rows[rows.size()])
                _g.add_point(p);

            //first and last columns are always visible, but don't include points
            //from the first/last row            
            Line& ell = cols[1];
            for (int i = 2; i <= ell.length()-1; i++)
                _g.add_point(ell[i]);

            ell = cols[cols.size()];
            for (int i = 2; i <= ell.length()-1; i++)
                _g.add_point(ell[i]);
        
        };
        
};


int main() {

    //string input_file = "../Inputs/day_08";
    string input_file = "../Inputs/test_input_02";

    ifstream ist {input_file};
    string heights = "";



    Grid g;
    int row = 1;
    int h = 0;
    
    
    while (getline(ist, heights)) {
        int col = 1;
        for (size_t p = 0; p < heights.size(); p++) {
            h = heights[p] - '0'; //from
            g.add_point(Point{col, row, h});
            col++;
        }
        row++;
    }


    //cout << " points " << endl;
    //g.show();

    //cout << "\noriginal input" << endl;
    //g.show_heights();




    /*
    //find the highest point in each row. then find the maximum point in
    // that same column. if the first point is the tallest, it can be seen
    // if not, it says nothing about the other point
    // test for all points

    //a vector<Point> can be reclassed as a line
    //line has [] overloaded
    //vector<Point> abc = {Point{1,1,3}, Point{1,1,5}, Point(1,1,2)};
    //vector<Point> abc = g.get_row(4);
    //cout << "row abc. should be row 4 from Grid g" << endl;
    //for (auto& p : abc)
        //cout << p << endl;

    //Point max = *max_element(abc.begin(), abc.end());
    //cout << "max from row abc: " << max << endl;


    //Line two = g.get_row(4);
    //Point line_max = two.max_point();
    //cout << "max point from line: " << line_max << endl;

    //Point set_point = g.get_point(4,5);
    //cout << "exact point: " << set_point << endl;

    //Line four = g.get_line(4);
    //cout << "max point in line 4, using Lines: " << four.max_point() << endl;

    */

    

    
/*
 * //find visible points
    vector<Point> vis_points{0};
    Line visible_points{0};
    visible_points.show_points();

    visible_points.add_point(Point{1,1,5});
    visible_points.show_point_vals();

    for (auto& row : g.rows) {
        cout << "row number: " << row.first << endl;
        Point max_in_row = g.max_in_row(row.first);
        Point max_in_col = g.max_in_col(max_in_row.y());

        
        cout << "max in row " << row.first << ": " << max_in_row << endl;
        cout << "max in col " << max_in_row.y() << ": " << max_in_col << endl;
        cout << "max in col " << max_in_col.y() << ": " << max_in_col << endl;

        if (max_in_row > max_in_col) {
            vis_points.push_back(max_in_row);
            visible_points.add_point(max_in_row);
        }
        else {
            vis_points.push_back(max_in_col);
            visible_points.add_point(max_in_col);
        }


*/
 

    Grid visible_points = g.get_visible_points();

    cout << "visible points" << endl;
    visible_points.show();
    visible_points.show_heights();

    cout << "number of visible points: " << visible_points.num_points();
    
    
    
    
    
    return 0;
}
