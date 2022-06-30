/*
 * Node.cpp
 *
 *  Created on: 28-aug.-2013
 *      Author: lieven2
 */

#include "Node.h"
#include <Log.h>

Node::Node() {
    _next = _prev = _child = _parent = (Node*) 0;
}

Node::~Node() {
//	ASSERT(true);
    while (1);
}

Erc Node::addChild(Node* child) {
    if (_child == NodeNull) {
        _child = child;
        child->_parent = this;
        child->_prev = NodeNull;
    } else {
        Node *cursor = _child;
        while (cursor->_next != NodeNull) {
            cursor = cursor->_next;
        }
        cursor->_next = child;
        child->_prev = cursor;
        child->_parent = this;
    }
    return E_OK;
}

Erc Node::addNext(Node* next) {
    Node *cursor = this;
    while (cursor->_next != NodeNull) {
        cursor = cursor->_next;
    }
    cursor->_next = next;
    next->_prev = cursor;
    return E_OK;
}

/*
 * E_INVAL when children attached or no parent to attach next children
 */
Erc Node::remove() {
    if (_child != NodeNull)
        return E_INVAL;
    if (_prev == NodeNull) {
        if (_parent == NodeNull) {
            if (_next != NodeNull)
                return E_INVAL;
        } else {
            _parent->_child = _next;
        }
    } else {
        _prev->_next = _next;
    }

    return E_OK;
}

Node* Node::parent() {
    return _parent;
}

Node* Node::follow() {
    if (_child) return _child;
    if (_next) return _next;
    Node *parent = _parent;
    while (parent) {
        if (parent->_next) return _parent->_next;
        parent = parent->_parent;
    }
    return NodeNull;
}

Node* Node::next() {
    return _next;
}

Node* Node::child() {
    return _child;
}

void Node::type(uint32_t type) {
    _type = type;
}

uint32_t Node::type() {
    return _type;
}

Node* Node::followNode() {
    Node *p = this;
    if (p->child()) return p->child();
    if (p->next()) return p->next();
    while (true) {
        if (p->parent() == NodeNull) return NodeNull;
        if (p->parent()->next()) return p->parent()->next();
        p = p->parent();
    }
//    if (p->parent()) return NodeNull;
}
