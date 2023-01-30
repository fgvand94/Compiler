#include "node.h"
#include <string>
#include <array>
#include <vector>
using namespace std;


Node::Node(std::string typePeram, std::string valuePeram, std::array<int,2> parentNodePeram)
{
	type = typePeram;
	value = valuePeram;
	parentNode = parentNodePeram;
}

void Node::setType(std::string typePeram) 
{
	type = typePeram;
}

void Node::setValue(std::string valuePeram) 
{
	value = valuePeram;
}
 
void Node::setChildNode(std::array<int,2> childNodePeram) 
{
	std::array childEnd = {0, 1};
	childNodes.pop_back();
	childNodes.push_back(childNodePeram);
	childNodes.push_back(childEnd);
}

void Node::setParentNode(int parentNodeDepthPeram, int parentNodeBredthPeram) 
{
	parentNode[0] = parentNodeDepthPeram;
	parentNode[1] = parentNodeBredthPeram;
}

void Node::incrementChild()
{
	lastTraversedChild ++;
}

int Node::getLastChild()
{
	return lastTraversedChild;
}

std::string Node::getType() {
	return type;
}

std::string Node::getValue() {
	return value;
}

std::array<int,2> Node::getChildNode(int num) {
	return childNodes.at(num);
}

std::array<int,2> Node::getParentNode() {
	return parentNode;
}