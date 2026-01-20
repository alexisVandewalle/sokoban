#include "SokoParser.h"
#include <iostream>
#include "BlockType.h"
#include <fstream>
#include <string>
#include <memory>
#include "exceptions.h"

using namespace std;
using namespace soko;

SokoParser::SokoParser(string inFilePath, string outDir, string mapSetTitle)
:mInFilePath(inFilePath), mOutDir(outDir), mMapSetTitle(mapSetTitle)
{
}

void SokoParser::parse(){
    ifstream inFile(mInFilePath);
    if (inFile.is_open()){
        string line;
        bool newSokoban(false);
        bool ignoreSection(true);
        int level(0);
        string findPattern{static_cast<char>(WALL)}; // there is at least one wall in each line of a sokoban
        // create directory to store maps
        system(("mkdir -p " + mOutDir).c_str());
        // define a pointer to a file storing the sokoban map
        unique_ptr<ofstream> outFile;
        while(getline(inFile, line)){
            // check if there is a character indicating a wall in the line
            if(line.find(findPattern)!=string::npos){
                // check wether it is the sstart of a new map
                if(ignoreSection){
                    level++;
                    string outFilePath(mOutDir + "/level" + to_string(level) + ".soko");
                    // write the map to a file
                    outFile = make_unique<ofstream>(outFilePath);
                    if(!outFile->is_open()){
                        throw FileWriteException(outFilePath);
                    }
                }
                (*outFile) << line << endl;
                ignoreSection = false;
            }else{
                // if the line before was part of a map
                if(!ignoreSection && outFile->is_open()){
                    (*outFile) << endl << "title:";
                    (*outFile) << mMapSetTitle << "/" << "level " << level << endl; 
                    outFile->close();
                }
                ignoreSection = true;
            }
        }
        // if output file has not been closed before, close it and write metadata
        if(outFile!=nullptr && outFile->is_open()){
            (*outFile) << endl << "title:";
            (*outFile) << mMapSetTitle << "/" << "level " << level << endl; 
            outFile->close();
        }
        inFile.close();
    }else{
        throw FileWriteException(mInFilePath); 
    }
}
