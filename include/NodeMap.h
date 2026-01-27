// NodeMap.h
#ifndef NODE_MAP_H // include guard
#define NODE_MAP_H
#include <string>
#include <memory>
#include "Map.h"
#include "MoveType.h"

using namespace std;

namespace soko
{
    /**
     * A class to represent a node in a graph of maps.
     * This class is used by the solver to find the shortest path to a solution
     */
    class NodeMap
    {
        private:
            NodeMap* parent;
            unique_ptr<Map> map;
            MoveType move;
        public:
            /**
             * Construct a node given a parent node and a move to perform
             * @param aParent parent of the node to create
             * @param move to perform
             */
            NodeMap(NodeMap& aParent, MoveType m);

            /**
             * Construct a node given an input map. Parent node is set to null
             * in this case
             * @param m
             */
            NodeMap(const Map& m);

            /**
             * Create a copy a node of an existing node
             */
            NodeMap(const NodeMap& n);

            /**
             * two nodes are equaled if and only if the two maps are equaled
             */
            bool operator==(const NodeMap& n2) const;

            /**
             * Compute a hash for a node base on the corresponding map
             */
            size_t getHash() const { return map->getHash(); };

            /**
             * Get sequence of moves associated to current node, ie compute path
             * from start node to this node
             */
            string getMoveSeq();

            /**
             * Indicate if the game is won at this node
             */
            bool isWin() { return map->isWin(); };

            /**
             * Return true if the map cannot be solved anymore
             */
            bool mapLocked() { return map->mapLocked(); };
    };

    struct NodeMapHasher {
        size_t operator()(const shared_ptr<NodeMap>& n) const
        {
            return n->getHash();
        }
        size_t operator()(const NodeMap& n) const
        {
            return n.getHash();
        }
    };

    struct NodeMapKeyEqual{
        bool operator()( const shared_ptr<NodeMap>& n1, const shared_ptr<NodeMap>& n2) const
        {
            return (*n1)==(*n2);
        }
    };
}

#endif /* NODE_MAP_H */
