/*
 * Node.h
 *
 *  Created on: 28-aug.-2013
 *      Author: lieven2
 */

#ifndef NODE_H_
#define NODE_H_
#include <stdint.h>
#include "Erc.h"
#define NodeNull (Node*)0
class Node {
public:
	Node();
	virtual ~Node();
	Erc addNext(Node* next);
	Erc addChild(Node* child);
	Erc remove();
        Node* parent();
         Node* next();
         Node* child();
         Node* follow();
         void type(uint32_t id);
         uint32_t type();
         Node* followNode();
private:
	Node* _next;
	Node* _prev;
	Node* _child;
	Node* _parent;
	uint32_t _type;
};

#endif /* NODE_H_ */
