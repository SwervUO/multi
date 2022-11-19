//Copyright © 2022 Charles Kerr. All rights reserved.

#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <cstdlib>

#include "multi.hpp"
#include "strutil.hpp"
#include "argument.hpp"

using namespace std::string_literals ;
//================================================================================================
//  Useage:
//      multi flag[,flag] entrydirectory
//
//  Where flag is one of:
//      --housing= housing file name (assumed to be in the same location as entrydirectory)
//      --uop= multicollection.uop file path
//      --mul= idxfilepath,mulfilepath
//      --extract extract the data from the mul/uop file
//      --create create the requested file
//
//================================================================================================

int main(int argc, const char * argv[]) {
    auto exitcode = EXIT_SUCCESS;
    try {
        auto arg = argument_t(argc,argv) ;
        if (arg.paths.size() <2){
            std::cout <<"Insufficent paramaters.\n";
            std::cout <<"Usage:\n";
            std::cout <<"\tmulti flag csvdirectory uoppath \n";
            std::cout <<"\t\tWhere flag is --extract or --create\n";
            std::cout <<"\t\tOptionally one may include a flag: --housing=housingname\n";
            std::cout <<"\t\twhich will use that file name in the cvsdirectory for the housing.bin\n";
            std::cout <<"Or\n";
            std::cout <<"\tmulti flag csvdirectory idxpath mulpath\n";
            std::cout <<"\t\tWhere flag is --extract or --create\n";
        }
        else {
            if (!std::filesystem::exists(arg.paths[0])){
                try{
                    std::filesystem::create_directories(arg.paths[0]);
                }
                catch(...){
                    throw std::runtime_error("Unable to create: "s+arg.paths[0].string());
                }
            }
            auto housepath = std::filesystem::path("housing.bin");
            auto extract = true ;
            for (const auto &[flag,value]:arg.flags){
                if (flag == "house"){
                    housepath = std::filesystem::path(value) ;
                }
                else if (flag == "create"){
                    extract = false ;
                }
                else if (flag == "extract"){
                    extract = true ;
                }
            }
            if (extract) {
                auto multistorage = multistorage_t() ;
                if (arg.paths.size() >2) {
                    multistorage = multistorage_t(arg.paths[2],arg.paths[1]);
                }
                else {
                    multistorage = multistorage_t(arg.paths[1]);
                }
                auto maxid = multistorage.maxid() ;
                for (std::uint32_t j=0 ; j < maxid+1;j++){
                    auto multi = multistorage[j] ;
                    if (!multi.empty()){
                        auto filename = arg.paths[0]/std::filesystem::path( strutil::format("%.4u.csv",j) );
                        auto output = std::ofstream(filename.string());
                        if (!output.is_open()) {
                            throw std::runtime_error("Unable to create: "s +filename.string() );
                        }
                        multi.description(output);
                    }
                }
                if (multistorage.uop()){
                    auto filename = arg.paths[0] / housepath ;
                    multistorage.saveHousing(filename );
                }
                
            }
            else {
                if (arg.paths.size()>2) {
                    // This is a mul
                    multistorage_t::saveMUL(arg.paths[0], arg.paths[2], arg.paths[1]);
                }
                else {
                    multistorage_t::saveUOP(arg.paths[0], arg.paths[1],housepath);
                }
            }
        }
    }
    catch(const std::exception &e){
        std::cerr<<e.what()<<std::endl;
        exitcode = EXIT_FAILURE;
    }
   return exitcode;
}
