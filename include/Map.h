// Map.h
#ifndef MAP_H // include guard
#define MAP_H
#include "MoveType.h"
#include "BlockType.h"
#include <vector>
#include <string>

using namespace std;

namespace soko
{
    /**
     * An example class that does nothing
     */
    class Map
    {
        private:
            int nLines;
            int nCol;
            int nTarget;
            int nBoxOnTarget;
            vector<BlockType> map;
            string title;
        public:
            int getNLines();
            int getNCol();
            int move(MoveType direction);
            void show();
            bool isWin();
            void save(string filename);
            Map(string filename);
    };
}

#endif /* MAP_H */
