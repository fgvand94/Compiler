#include <string>
#include <vector>
#include <array>
using namespace std;


class Node 
{

private:
	//Member variables. 
	std::array<int,2> initialChild = {0,1};
	std::string type;
	std::string value;
	vector<std::array<int,2>> childNodes = {initialChild};
	std::array<int,2> parentNode;
	int lastTraversedChild = 0;


public:
	//Constructor
	Node();
	Node(std::string typePeram, std::string valuePeram, std::array<int,2> parentNodePeram);

	//Set member variables
	void setType(std::string typePeram);
	void setValue(std::string valuePeram);
	void setChildNode(std::array<int,2> childNodePeram);
	void setParentNode(int parentNodeDepthPeram, int parentNodeBredthPeram);
	void incrementChild();

	//Get member variables
	std::string getType();
	std::string getValue();
	std::array<int,2> getChildNode(int num);
	std::array<int,2> getParentNode();
	int getLastChild();


};