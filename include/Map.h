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
            int nLines = 0;
            int nCol = 0;
            int nTarget = 0;
            int nBoxOnTarget = 0;
            vector<int> characterPos;
            vector<BlockType> map;
            string title;
            string otherMetadata;
            
            /**
             * Initialize map properties from input stream
             * @param inStream input stream
             */
            void init(istream& inStream);

        public:
            /**
             * Get number of lines and columns
             * @param istream input stream containing map to read
             * @return number of lines and columns as a vector
             */
            static vector<int> getNLineColMap(istream& inStream);

            /**
             * Get number of lines and columns
             * @param filePath path to the file containing the map to read from
             * @return number of lines and columns as a vector
             */
            static vector<int> getNLineColMap(string filePath);

            /**
             * Get number of lines in the map
             */
            int getNLines();

            /**
             * Get number of columns in a map
             */
            int getNCol();

            /**
             * Get number of target in a map
             */
            int getNTarget();

            /**
             * Get number of boxes on a target
             */
            int getNBoxOnTarget();

            /**
             * Get position of character (line, column)
             */
            vector<int> getCharacterPos();

            /**
             * Get title of the map
             */
            string getTitle();

            /**
             * Get metadata that has not been parsed by constructor
             */
            string getOtherMetadata();

            /**
             * Move character to the provided position
             * @param direction
             * @return MOVE_OK or MOVE_KO depending if the move can be performed
             */
            int move(MoveType direction);

            string toString();

            /**
             * display map in standard output
             */
            void show();

            /**
             * Tell if all the box are on a target
             * @return true if all boxes are on a target, false otherwise
             */
            bool isWin();

            /**
             * Save curent map to given file
             */
            void save(string filePath);
            void save(ofstream& fileToSave);
            
            /**
             * Change orientation of the map
             */
            void transpose();

            /**
             * Construct map from an input stream
             * @param inStream
             */
            Map(istream& inStream);

            /**
             * Construct map from an input file
             */
            Map(string filePath);
    };

    enum MoveStatus
    {
        MOVE_OK,
        MOVE_KO
    };
}

#endif /* MAP_H */
