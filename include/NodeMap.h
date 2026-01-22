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
     * A class to represent a node (only use for the solver)
     */
    class NodeMap
    {
        private:
            shared_ptr<NodeMap> parent;
            unique_ptr<Map> map;
            MoveType move;
        public:
            NodeMap(shared_ptr<NodeMap> parent, MoveType m);
            NodeMap(const Map& m);
            bool operator==(const NodeMap& n2);
            size_t getHash() const { return map->getHash(); };
            string getMoveSeq();
    };

    struct NodeMapHasher {
        size_t operator()(const NodeMap& n) const
        {
            return n.getHash();
        }
    };
}

#endif /* NODE_MAP_H */
