#include "map.hpp"

void readRoster(map<Student,list<string>>&, string);
void printRoster(map<Student,list<string>>&);

int main(int argc,char *argv[]){
   if (argc <= 1){ 
      std::cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" 
      << std::endl;
      exit(1);
   }
    
    // reading in all students in each courses

    map<Student,list<string>> courses;
    for(int i = 1; i < argc - 1; ++i){
        map<Student,list<string>> temp;
        cout << "\n\n" << argv[i] << "\n";  
        readRoster(courses,argv[i]);

        readRoster(temp,argv[i]);
        printRoster(temp);
    }


    // reading in dropouts
    map<Student,list<string>> dropouts;
    readRoster(dropouts, argv[argc-1]); 

    //outputting all dropouts
    cout << "\n\n" << "Dropouts: " << std::endl;
    printRoster(dropouts);
    readRoster(courses,argv[argc-1]);

    std::cout << "\n\n" << "All Students sorted" << std::endl;
    printRoster(courses);

    std::cout << "\n\n" << "Dropout removed" << std::endl;
    for(auto dropout = dropouts.cbegin(); dropout != dropouts.cend(); ++dropout){
        courses.erase(dropout->first);
    }
    printRoster(courses);

}

void readRoster(map<Student,list<string>>&courses, string fileName){
    std::ifstream file(fileName);
    string first,last;
    string courseName = fileName.substr(0,fileName.find('.'));

    while(file >> first >> last){
        Student user(first,last);
        std::list<string> userCourses;
        userCourses.push_back(courseName);
        auto located = std::find_if(courses.begin(),courses.end(),
            [&first,&last](const std::pair<Student,list<string>>&pair){return (first == pair.first.getFirst() && last == pair.first.getLast());}
        );
        if(located != courses.end()){
            located->second.push_back(" ");
            located->second.push_back(courseName);
        }else{
            courses.insert(make_pair(user,userCourses));
        }
    }
}

void printRoster(map<Student,list<string>>&courses){
    for(auto it = courses.cbegin(); it != courses.cend();++it){
        it->first.print();
        for(auto className = it->second.cbegin(); className != it->second.cend(); ++className){
            std::cout << *className;
        }
        std::cout << std::endl;
    }
}