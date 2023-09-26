#include <iostream>
#include <string>
#include <vector> //list type object
#include <fstream> //read/write files
#include <cstring> //access to stoi function
//#include <map> //access to dictionary. not needed
#include <utility> //access to tuple like pair
#include <algorithm> //access to min function

using namespace std;


//make this a template function
//template <typename T>
//T& print(const T&) {
    ////#include <iostream>
    //return std::cout << T << std::endl; //expected primary-expression before <<???
//}

class File {
    public:
        string name = "";
        int size = 0;
        File(string input_line) {
            parse_line(input_line);
        }

        File(pair<string, string> &file_thing) {
            name = file_thing.second;
            size = stoi(file_thing.first);
        }

    private:
        void parse_line(string input_line) {
            int sep_idx = input_line.find(' ');
            size = stoi(input_line.substr(0, sep_idx));
            name = input_line.substr(sep_idx+1, input_line.length());
        };
};



class Directory {
    public:
        string name = "";
        vector<Directory> sub_dirs; //refactor for this later because it matches flattened_dirs() syntax// { return _sub_dirs; };
        vector<File> files;
        Directory* parent() { return _parent_dir; };

        void set_parent(Directory p) { _parent_dir = &p; };

        bool operator ==(Directory& rhs) { return get_size() == rhs.get_size(); }

        bool operator <(Directory& rhs) {
            return get_size() < rhs.get_size();
        }

        bool operator >(Directory& rhs) {
            return get_size() > rhs.get_size();
        }

        ostream& operator<<(const Directory&);

        vector<Directory> flattened_dirs() {

            vector<Directory> flat{};
            
            return _flattened_dirs(flat);
        };

        void show_subdirs(bool recurse=false) {
            _show_subdirs(recurse, "");
            return;
            cout << "  showing subdirectories" << endl;
            for (auto& d : sub_dirs) {
                cout << "   directory name: " << d.name << ". size: " << get_size() << endl;
                d.show_subdirs();
                
                

                if (_parent_dir != NULL)
                    cout << ". parent: " << _parent_dir->name << endl;
                else
                    cout << ". parent: NONE" << endl;
            }
                
                
        };

        void show_files() {
            cout << "  showing files  " << endl;
            for (auto& f : files)
                cout << "   file name name: " << f.name << ". size: " << f.size << endl;
            
        };

        Directory* move_to(const string dir_name) {
            //cout << "moving to new directory" << endl;
            //cout << "requested directory is |" << dir_name << "|" << endl;
            //cout << "current directory is " << name << endl;

            //if (_parent_dir != NULL) {
                //cout << "is this the parent dir name? " << _parent_dir->name << endl;
            //}

            if (dir_name == "..") {
                //cout << "returning parent" << endl;
                return _parent_dir;
            }

            
            for (auto& d : sub_dirs) {
                //cout << "comparing directory " << d.name << " to requested directory " << dir_name << endl;
                if (d.name == dir_name) {
                    //cout << "name match. returning " << &d << endl;
                    //cout << "parent: " << d.parent().name << "||" << endl;
                    return &d;
                }
            }

            cout << "returning last" << endl;
            return new Directory("last", NULL);
        };

      
        void add(Directory dir) {
            //cout << "adding to sub directories" << endl;
            //cout << "sub_dirs size :"  << sub_dirs.size() << endl;
            sub_dirs.push_back(dir);
            //cout << "sub_dirs new size :"  << sub_dirs.size() << endl;
        };

        void add(File f) {
            files.push_back(f);
        };

        int get_size() {
            int size = 0;

            for (auto d : sub_dirs) {
                size += d.get_size();
            }

            for (auto f : files) {
                //cout << "  " << f.name << endl; 
                size += f.size;
            }

            return size;
        };

        int get_file_size() {
            int size = 0;
            for (const auto& f : files)
                size += f.size;
            return size;
        }


        Directory() :
            name(""),
            sub_dirs(),
            _parent_dir()
            //_DIRECTORY_SIZE_LIMIT(100000)
            {};


        //copy constructor
        //Directory(const Directory& d):
            //name(d.name),
            //sub_dirs(d.sub_dirs),
            //_parent_dir(d._parent_dir)
            //{ cout << "copying" << endl; };
                
        Directory(string dir_name) :
            name(dir_name),
            sub_dirs(),
            _parent_dir()
            //_DIRECTORY_SIZE_LIMIT(100000)
            {};

        Directory(string dir_name, Directory* parent) :
            name(dir_name),
            sub_dirs(),
            _parent_dir(parent)
            //_DIRECTORY_SIZE_LIMIT(100000)
            {};


        /*this huge brick of code is where I learned about copy constructors and
         * assignment overloading
         * for this class, overloading and writing my own copy constructor (which
         * maybe I should do just to know how to do it) isn't strictly necessary
         */
        //Directory& operator=(const Directory& d) {

            //cout << "assignmenting" << endl;
            //string stuff = "   name: " + name + ". sub directories: " + to_string(sub_dirs.size());    
            //if (_parent_dir != NULL) {
                //stuff += ". parent name: " + _parent_dir->name;
            //}
            //else {
                //stuff += ". parent name: NONE";
            //}    

            //cout << stuff << endl;
            
            //cout << "   rhs parent name: " << d._parent_dir->name << endl;
            //cout << "   rhs address: " << &d << endl;
            //cout << "   rhs parent address: " << d._parent_dir << endl;
            //cout << "   lhs address: " << this << endl;

            //if (this == &d) {
                //return *this;
            //}
            //name = d.name;
            //sub_dirs = d.sub_dirs;
            //_parent_dir = d._parent_dir;
            
            
            //cout << "post assignment" << endl;
            //stuff = "   name: " + name + ". sub directories: " + to_string(sub_dirs.size());
            //if (_parent_dir != NULL) {
                //stuff += ". parent name: " + _parent_dir->name;
            //}
            //else {
                //stuff += ". parent name: NONE";
            //}
            
            //cout << stuff << endl;

            //cout << "   rhs parent name: " << d._parent_dir->name << endl;
            //cout << "   rhs address: " << &d << endl;
            //cout << "   rhs parent address: " << d._parent_dir << endl;
            //cout << "   lhs address: " << this << endl;

            
            
            //return *this;
            
        //};


    private:
        Directory* _parent_dir;
        const static int _DIRECTORY_SIZE_LIMIT = 100000;

        vector<Directory> _flattened_dirs(vector<Directory>& rtn){

            for (auto& d : sub_dirs) {
                rtn.push_back(d);

                rtn = d._flattened_dirs(rtn);
                
            }

            return rtn;

        
            
        };

        void _show_subdirs(bool recurse=false, string padding="") {
            padding += ' ';
            for (auto d : sub_dirs) {
                cout << padding << "directory: " << d.name << endl;

                if (recurse)
                    d._show_subdirs(recurse, padding);
                
                

                //if (_parent_dir != NULL)
                    //cout << ". parent: " << _parent_dir->name << endl;
                //else
                    //cout << ". parent: NONE" << endl;
            }
                
                
        };
    
};



/*
    To begin, find all of the directories with a total size of at most 100000,
*  then calculate the sum of their total sizes.
* In the example above, these directories are a and e;
*  the sum of their total sizes is 95437 (94853 + 584).
* (As in this example, this process can count files more than once!)

    sample input file
        $ cd /
        $ ls
        dir a
        14848514 b.txt
        8504156 c.dat
        dir d
        $ cd a
        $ ls
        dir e
        29116 f
        2557 g
        62596 h.lst
        $ cd e
        $ ls
        584 i
        $ cd ..
        $ cd ..
        $ cd d
        $ ls
        4060174 j
        8033020 d.log
        5626152 d.ext
        7214296 k
*
* it would fun to do this by adapting stroustrup's calculator

*/

ostream& operator<<(ostream& os, Directory& d) {
    //return os << "Badge: " << eg.badge << ". Value: " << eg.badge_val;

    string parent_name = d.parent() == NULL ? "/" : d.parent()->name;
    return os << "name: " << d.name <<
                               ". size : " << d.get_size()
                               << ". parent: " << parent_name;

                
}

void parse_line(const string input_line, pair<string, string> &line_info) {

    int sep_idx = -1;
    //this is a command
    if (input_line[0] == '$') {
        string sub_line = input_line.substr(2, input_line.length());
        sep_idx = sub_line.find(' ');

        line_info.first = sub_line.substr(0, sep_idx);
        line_info.second = sub_line.substr(sep_idx+1, sub_line.length());
    }

    //this is a non-command
    else {
        sep_idx = input_line.find(' ');
        line_info.first = input_line.substr(0, sep_idx);
        line_info.second = input_line.substr(sep_idx+1, input_line.length());
    }
    
    
};


int main() {

    const string input_file = "/home/wrowsers/CppStuff/AdventOfCode/2022/Inputs/day_07";
    //const string input_file = "/home/wrowsers/CppStuff/AdventOfCode/2022/Inputs/test_input";


    ifstream ist(input_file);

    Directory root{"/", NULL};
    Directory* current_dir = &root;
    
    string input_line = "";
    while(getline(ist, input_line)) {
        pair<string, string> line_info;
        parse_line(input_line, line_info);
        
        //cout << input_line << endl;
        if (line_info.first == "cd") {            
            //cout << "changing directory to " << line_info.second << endl;
            if (line_info.second == "/") {
                //special case for root directory. could have some logic to
                //create the directory if it doesn't exist or otherway not error
                
            }
            else {
                current_dir = current_dir->move_to(line_info.second);
                //cout << "successfully changed to directory " << current_dir->name << endl;                
            }
        }
        else if (line_info.first == "ls") {
            //cout << "listing directory contents of " << current_dir->name << endl;
        }
        else if (line_info.first == "dir") {
            //cout << "creating new directory " << line_info.second << " in directory " << current_dir->name << endl;
            //Directory new_dir{line_info.second};
            //new_dir.set_parent(current_dir);
            current_dir->add(Directory{line_info.second, current_dir});
            
        }
        else {
            //cout << "adding file " << line_info.second << " to directory " << current_dir->name << endl;
            
            current_dir->add(File{line_info});

        }
        
    }

    /*
    cout << "root directory size: " << root.get_size() << endl;
    root.show_subdirs(true);

    //cout << "root filtered size: " << root.get_filtered_size() << endl;

    for (auto& d : root.sub_dirs) {
        cout << "directory name: " << d.name;
        cout << ". size: " << d.get_size() << endl;
    }

    //cout << "filtered size: " << root.get_filtered_size() << endl;
    

    Directory a = *root.move_to("a");
    Directory e = *a.move_to("e");

    cout << "a's size: " << a.get_size() << endl;
    //cout << "a's filtered size: " << a.get_filtered_size() << endl;


    //cout << "e's size: " << e.get_size() << endl;
    //cout << "e's filtered size: " << e.get_filtered_size() << endl;

    //cout << endl << endl;

    //cout << "flatenned size: " << root.get_flattened_size(100000) << endl;
    *
    */

    /* BEGIN PART ONE*/
    int total_size = 0;
    int num_dirs = 0;
    const int DIRECTORY_SIZE_LIMIT = 100000;
    cout << "---BEGIN PART 01---" << endl;
    for (auto& d : root.flattened_dirs()) {
        if (d.get_size() <= DIRECTORY_SIZE_LIMIT) {
            cout << d << endl;
            total_size += d.get_size();
            num_dirs++;
        }
    }

    /* END PART ONE*/
        

    cout << "directories under limit: " << num_dirs << endl;
    cout << "total size: " << total_size << endl;
    cout << "---END PART 01---" << endl;


    /* BEGIN PART TWO*/

    const int MAX_SIZE_LIMIT = 70000000;
    const int UPDATE_SPACE = 30000000;

    /* find the smallest directory which when deleted will make the
     * available space more than the UPDATE_SPACE
     *
     */


    int free_space = MAX_SIZE_LIMIT - root.get_size();
    vector<Directory> candidates{};
    cout << "---BEGIN PART 02---" << endl;
    for (auto& d : root.flattened_dirs()) {
        
        if ((d.get_size() + free_space) >= UPDATE_SPACE) {
            candidates.push_back(d);
            cout << d << endl;
        }
    }

    //this works too, but seems a bit long for one line
    //for (vector<Directory>::iterator it = candidates.begin(); it < candidates.end(); it++) {
        //cout << *it << endl;
    //}
    

    vector<Directory>::iterator begin = candidates.begin();
    vector<Directory>::iterator end = candidates.end();
    Directory delete_me = *(min_element(begin, end));


    cout << endl << endl;
    cout << "free space: " << free_space << endl;
    cout << "directory found: " << delete_me << endl;
    
    cout << "---END PART 02---" << endl;
    

    return 0;
}
