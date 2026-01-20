// SokoParser.h
#ifndef SOKO_PARSER_H // include guard
#define SOKO_PARSER_H
#include <string>

using namespace std;

namespace soko
{
    /**
     * A class to help parsing text files containing sokoban maps
     */
    class SokoParser
    {
        private:
            string mInFilePath;
            string mOutDir;
            string mMapSetTitle;
        public:

            /**
             * Construct SokoParser
             * @param inFilePath path to the input files containing all sokoban maps
             * @param outDir output directory (where to store all the maps)
             * @param mapSetTitle title of the set of maps
             */
            SokoParser(string inFilePath, string outDir, string mapSetTitle);

            /**
             * launch parsing of file containg sokoban maps
             */
            void parse();
    };
}

#endif /* SOKO_PARSER_H */
