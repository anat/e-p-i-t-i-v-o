#include "Huffman.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <string.h>


/* By AnaT (korcza_b) --- How to :
        Huffman  h;
        h.compress((uint8_t*)buffer, length);
        h.uncompress(h.getBuffer());
        write(1, h.getBuffer(), h.getSize());
 */

class Node;
std::list<Node*> allNodes;

#define SHOW_LOG_HUFFMAN 0

void            Huffman::compress(uint8_t* buffer, int size)
{
#ifdef SHOW_LOG_HUFFMAN
  //std::cout << "Huffman compress - originalSize: " << size;
#endif
    bitWriter.reset();
    allNodes.clear();
    leafNodes.clear();
    values.clear();
    for (int i = 0; i < size; i++)
    {
        std::map<uint8_t, int>::iterator it;
        it = values.find(buffer[i]);
        if (it == values.end())
            values[buffer[i]] = 1;
        else
            (*it).second++;
    }
    //showMap(values);
    this->createTree(values);
    uint8_t * outputBuffer = bitWriter.getBuffer();
    HuffmanFileHeader fh;
    fh.numberOfType = size;

    for (int i = 0; i < 256; i++)
    {
        std::map<uint8_t, int>::iterator it = values.find(i);
        if (it == values.end())
            fh.N[i] = 0;
        else
            fh.N[i] = it->second;
    }
    memcpy(outputBuffer, &fh, sizeof(fh));
    for (int i = 0; i < size; i++)
        this->getPath(leafNodes[buffer[i]]);
    #ifdef SHOW_LOG_HUFFMAN
    //std::cout << " compressedSize: " << bitWriter.getSize() << " rate: " << (bitWriter.getSize() * 100) / size << "/100" << std::endl;
#endif
    bitWriter.deallocate();
    delete allNodes.back();
}



void            Huffman::uncompress(uint8_t* buffer)
{
    #ifdef SHOW_LOG_HUFFMAN
  //std::cout << "Huffman uncompress " << std::endl;
    #endif
    allNodes.clear();
    leafNodes.clear();
    values.clear();
    HuffmanFileHeader* fh = (HuffmanFileHeader*)buffer;
    std::map<uint8_t, int> assoc;
    std::map<uint8_t, int>::iterator it;
    for (int i = 0; i < 256; i++)
        if (fh->N[i])
            assoc[i] = fh->N[i];

    //showMap(assoc);
    createTree(assoc);
    index = sizeof(HuffmanFileHeader);
    bitindex = -1;
    bitWriter.reset(fh->numberOfType);

    uint64_t currentByte = 0;
    while (currentByte < fh->numberOfType)
    {
        uint8_t c = this->getNextChar(allNodes.back(), buffer);
        bitWriter.addByte(c);
        currentByte++;
    }
    delete allNodes.back();
}


void            Huffman::createTree(std::map<uint8_t, int> & assoc)
{

    std::map<uint8_t, int>::iterator it = assoc.begin();
    std::map<uint8_t, int>::iterator end = assoc.end();

    std::multimap<int, uint8_t> reverseValues;
    while (it != end)
    {
        reverseValues.insert(std::pair<int, char>((*it).second, (*it).first));
        ++it;
    }
    std::multimap<int, uint8_t>::iterator itr = reverseValues.begin();
    std::multimap<int, uint8_t>::iterator endr = reverseValues.end();
    while (itr != endr)
    {
        Node * current = new Node();
        current->value = (*itr).second;
        current->n = (*itr).first;
        current->isLeaf = true;
        nodes.push(current);
        leafNodes[current->value] = current;
        ++itr;
    }
    while (!nodes.empty())
    {
        Node * zero = nodes.front();
        nodes.pop();

        Node* n;
        if ((n = this->getMinDaddy()))
        {
            // optimized case
            if (zero->n > n->n) 
            {
                new Node(zero, n);
                continue;
            }
            // unoptimized case (rare)
            if (nodes.empty())
            {
              new Node(zero, n);
              continue;
            }
         }
        Node * one = nodes.front();
        nodes.pop();
        new Node(zero, one);
    }

    while (Huffman::getMinDaddy())
    {
        Node* n = this->getMinDaddy();
        n->hasDaddy = true;
        Node* n2;
        if ((n2 = this->getMinDaddy()))
        {
            new Node(n2, n);
        }
    }
    //showTree(allNodes.back(), 0);
}


Node*            Huffman::getMinDaddy()
{
    std::list<Node*>::iterator it = allNodes.begin();
    std::list<Node*>::iterator end = allNodes.end();
    int i = std::numeric_limits<int>::max();
    Node* n = NULL;
    while (it != end)
    {
        if (!(*it)->hasDaddy)
            if ((*it)->n < i)
            {
            n = (*it);
            i = n->n;
        }
        ++it;
    }
    return n;
}

void            Huffman::getPath(Node * current)
{
    if (current->parent != NULL)
    {
        getPath(current->parent);
        if (current->parent->one == current)
            bitWriter.addBit(true); // 1
        else
            bitWriter.addBit(false);// 0
    }
}

uint8_t         Huffman::getNextChar(Node * current, uint8_t * data)
{
    if (!current->isLeaf)
    {
        bitindex++;
        if (bitindex == 8)
        {
            index++;
            bitindex ^= bitindex;
        }
        if (data[index] & (1 << bitindex))
            getNextChar(current->one, data);
        else
            getNextChar(current->zero, data);
    }
    else
        return current->value;
}


uint8_t*	Huffman::getBuffer()
{
    return bitWriter.getBuffer();
}

int     	Huffman::getSize()
{
    return bitWriter.getSize();
}



/** For debug **/
void showMap(std::map<uint8_t, int> myMap)
{
    return;
    std::map<uint8_t, int>::iterator it = myMap.begin();
    std::map<uint8_t, int>::iterator end = myMap.end();
    while (it != end)
    {
        std::cout <<  (*it).first << " - " << (*it).second << std::endl;
        ++it;
    }
}

/** For debug **/
void    showTree(Node* n, int i)
{
    //  return;
    if (n == NULL)
    {
        std::cout << "NULL" << std::endl;
        return;
    }
    for (int j = 0; j < i; j++)
        std::cout << "\t";
    if (n->value == 0)
    {
        std::cout << "-N-" << n->n << "-- " << (n->parent != NULL && n->parent->zero == n ? "0" : "1") << std::endl;
        //        for (int j = 0; j < i + 1; j++)
        //            std::cout << "\t";
        //        std::cout << "showZero" << std::endl;
        showTree(n->zero, i + 1);
        //        for (int j = 0; j < i + 1; j++)
        //            std::cout << "\t";
        //        std::cout << "showOne" << std::endl;
        showTree(n->one, i + 1);
    }
    else
        std::cout << "[" << n->value << "] (N=" << n->n << ") " << (n->parent != NULL && n->parent->zero == n ? "0" : "1") << std::endl;
}
