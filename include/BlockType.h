// BlockType.h
#ifndef BLOCK_TYPE_H // include guard
#define BLOCK_TYPE_H

namespace soko
{
    enum BlockType
    {
        WALL = '#',
        FLOOR = ' ',
        TARGET = '.',
        BOX = '$',
        BOX_ON_TARGET = '*',
        CHARACTER = '@',
        CHARACTER_ON_TARGET = '+'
    };
}

#endif /* BLOCK_TYPE_H */
