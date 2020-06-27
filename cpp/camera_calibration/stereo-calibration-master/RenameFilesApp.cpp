/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RenameFilesApp.cpp
 * Author: northlight
 *
 * Created on June 13, 2020, 6:37 PM
 */

#include <cstdlib>
#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS
#include <string>
#include <iostream>
#include <boost/program_options.hpp>
#include<stdio.h>     //for remove( ) and rename( )
using namespace std;
namespace po = boost::program_options;
namespace filesystem = boost::filesystem;


namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

struct AppOptions {
    string new_name;
    string path;
    string extension;
    };

 /*!parse an input data into an AppOptions instance */
void parseCommandLine(int argc, char **argv, AppOptions &options) {
    /*!first parameter always is the name of an application*/
    string app_name(argv[0]);

    // default values
    options.new_name = "new_name";
    options.new_name = "";
    options.extension = "";
   /*!OD == is great boost parser of input data; example == https://pastebin.com/yBmfCgvr */
    po::options_description desc("OPTIONS");
    desc.add_options()
            // help outputs all descriptions + parameters
            ("help,h", "Print this help messages")
    ////////////////////////////////////////////////////////////->required()
            ("new_name,n", po::value<string > (&options.new_name), "New name of files.")
            ("path,p", po::value<string > (&options.path), "If a path was not specified, it uses a current directory.")
     ("extension,e", po::value<string > (&options.extension), "Add an extension. Example: jpg, txt.");
     
    // dictionary of input parameters
    po::variables_map vm;

    try { // infill vm
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) {
            cout << "USAGE: " << app_name << " OPTIONS"
                    << endl << endl << desc;
            exit(EXIT_SUCCESS);
        }
        // can call some function before putting data in OD options
        po::notify(vm);
    }// if required option wasn't called
    catch (boost::program_options::required_option& e) {
        cerr << "ERROR: " << e.what() << endl << endl;
        cout << "USAGE: " << app_name << " OPTIONS"
                << endl << endl << desc;
        exit(EXIT_FAILURE);
    } catch (boost::program_options::error& e) {
        cerr << "ERROR: " << e.what() << endl << endl;
        cout << "USAGE: " << app_name << " OPTIONS"
                << endl << endl << desc;
        exit(EXIT_FAILURE);
    }
//
//    std::transform(options.algorithm_type.begin(),
//            options.algorithm_type.end(),
//            options.algorithm_type.begin(), ::toupper);

//    std::transform(options.output_type.begin(),
//            options.output_type.end(),
//            options.output_type.begin(), ::toupper);
//
//    if (options.algorithm_type.compare("DCM") &&
//            options.algorithm_type.compare("OCM")) {
//        cerr << "Unrecognized algorithm type (" << options.algorithm_type << ")" << endl;
//        exit(EXIT_FAILURE);
//    }
    // -1 if was not found, 0 if was found

}
struct path_leaf_string
{
    std::string operator()(const boost::filesystem::directory_entry& entry) const
    {
        return entry.path().leaf().string();
    }
};
 
void read_directory(std::string& name, vector<string> & v)
{
    
    if(name == "")
        name = filesystem::current_path().c_str();
    std::cout << name << " current path "<<std::endl; 
    boost::filesystem::path p(name);
    boost::filesystem::directory_iterator start(p);
    boost::filesystem::directory_iterator end;
    std::transform(start, end, std::back_inserter(v), path_leaf_string());

}

int main(int argc, char** argv) {
    AppOptions options;

    // infill options
    parseCommandLine(argc, argv, options);
    using namespace std;
    vector<string> vec;
    string path = options.path;
    string new_name = options.new_name;
    string extension = options.extension;
    read_directory(path, vec);
    cout << vec.size() << endl;
    
    for(int i{0}; i < vec.size(); i++)
    {
        
        string final_name =  string(filesystem::current_path().c_str()) +"/" + path + "/" + new_name + patch::to_string(i) + "." + extension;
        string old_name = string(filesystem::current_path().c_str()) +"/" + path + "/" + vec.at(i);
        cout << vec.at(i) << " old name."<<endl;
        rename(old_name.c_str(), final_name.c_str());
    }
    return 0;
}

