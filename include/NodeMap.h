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
            NodeMap* parent;
            unique_ptr<Map> map;
            MoveType move;
        public:
            NodeMap(NodeMap& aParent, MoveType m);
            NodeMap(const Map& m);
            NodeMap(const NodeMap& n);
            bool operator==(const NodeMap& n2) const;
            size_t getHash() const { return map->getHash(); };
            string getMoveSeq();
            bool isWin() { return map->isWin(); };
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
