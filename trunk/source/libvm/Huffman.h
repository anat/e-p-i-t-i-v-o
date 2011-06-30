#include <map>
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <list>
#include <cstdio>
#include <stdint.h>

#define ALLOC_SIZE 1572864

struct          HuffmanFileHeader
{
    uint64_t numberOfType;  // Number of type in data
    uint32_t N[256];        // Number of occurence for each value of an uint8_t
};

class		Node
{
public:
    static std::list<Node*> allNodes;

    Node() : hasDaddy(false), zero(0), one(0), value(0), isLeaf(false) {
        Node::allNodes.push_back(this);}

    Node(Node* Zero, Node* One) : hasDaddy(false), zero(Zero), one(One), value(0), parent(NULL), isLeaf(false) {
        Node::allNodes.push_back(this);
        zero->hasDaddy = (one->hasDaddy = true);
        zero->parent = (one->parent = this);
        n = zero->n + one->n;}

    Node* zero;
    Node* one;
    Node* parent;
    uint8_t value;
    int n;
    bool isLeaf;
    bool hasDaddy;
};
std::list<Node*> Node::allNodes;



class           Byte
{
private:
    uint8_t * buffer;

    int rotating;
    int bufferSize;
    int realSize;
public:

    void allocateByte()
    {
        this->buffer = (uint8_t *)realloc(this->buffer, ++this->bufferSize);
        this->buffer[this->bufferSize - 1] = 0;
        rotating = 0;
    }

    void deallocate()
    {
         this->buffer = (uint8_t *)realloc(this->buffer, this->bufferSize);
    }

    void addByte(uint8_t value)
    {
        this->buffer[this->bufferSize++] = value;
    }

    void addBit(bool value)
    {
        if (rotating == 8)
        {
            rotating = 0;
            this->bufferSize++;
        }
        if (value)
            this->buffer[this->bufferSize - 1] |= value << rotating;
        rotating++;
    }

    uint8_t * getBuffer()
    {
        return buffer;
    }

    uint32_t getSize()
    {
        return bufferSize;
    }

    void reset(int size = 0)
    {
        if (size)
        {
            this->buffer = (uint8_t*)realloc(NULL, size);
            this->bufferSize = 0;
        }
        else
        {
            this->buffer = (uint8_t*)realloc(NULL, ALLOC_SIZE);
            this->bufferSize = sizeof(HuffmanFileHeader) + 1;
        }

        rotating = 0;
    }
};

class		Huffman
{
public:
    void        compress(uint8_t * buffer, int size);
    void        uncompress(uint8_t * buffer);
    uint8_t*    getBuffer();
    int         getSize();

private:
    Node*       getMinDaddy();
    void        createTree(std::map<uint8_t, int> & assoc);
    void        getPath(Node* current);
    uint8_t     getNextChar(Node* current, uint8_t* data);

    Byte bitWriter;
    int size;
    std::map<uint8_t, int> values;
    std::map<uint8_t, Node*> leafNodes;
    std::queue<Node*> nodes;
    uint8_t* buffer;
    int index;
    int bitindex;
};
