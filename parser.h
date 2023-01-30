#include <string>
#include <vector>
#include "node.cpp"
using namespace std;


class Program
{

private:


public:
	//constructor

	Program();

	//Member variables
	std::array<int,2> parentNode = {0, 1};
	Node treeNode = Node("Start", "test", parentNode);
	vector<vector<Node>> tree{{treeNode}};
	bool end = false;

	//Prints tree in a breadth first fashion
	void printTree()
	{
		int i = 0;
		while (i < tree.size())
		{
			int j = 0;
			while (j < tree.at(i).size())
			{
				std::cout << tree.at(i).at(j).getValue() << ' '<<tree.at(i).at(j).getParentNode()[0] <<tree.at(i).at(j).getParentNode()[1]<<",";
				j++;
			}
			std::cout << "\n";
			i++;
		}
	}


	//Depth first search
	int depthFirst(int i, int j)
	{
		Node *currentTree = &tree.at(i).at(j);
					

		int lastChild = currentTree->getLastChild();
		int a = currentTree->getChildNode(lastChild)[0];
		int b = currentTree->getChildNode(lastChild)[1];
		std::array<int,2> parentNode = currentTree->getParentNode();

		cout << currentTree->getValue() <<"\n";

		if(a == 0 && b ==1 && parentNode[0] == 0 && parentNode[1] == 1) 
		{
			cout <<"end";
			return 0;
		}
		
		else if (a == 0 && b == 1)
		{
			cout <<"if"<<parentNode[0]<<parentNode[1];
			depthFirst(parentNode[0], parentNode[1]);
			return 0;	
		}
		currentTree->incrementChild();
		depthFirst(a, b);
		return 0;
		
	}

};