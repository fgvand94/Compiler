// #include "node.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.cpp"
// #include "node.cpp"
using namespace std;

Program test;
int level = 1;
std::string subB;


bool isPunctuator(char ch)					//check if the given character is a punctuator or not
{

    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
        ch == '&' || ch == '|')
        {
            return true;
        }
    return false;
}

bool validIdentifier(std::string str)						//check if the given identifier is valid or not
{
    if (str.at(0) == '0' || str.at(0) == '1' || str.at(0) == '2' ||
        str.at(0) == '3' || str.at(0) == '4' || str.at(0) == '5' ||
        str.at(0) == '6' || str.at(0) == '7' || str.at(0) == '8' ||
        str.at(0) == '9' || isPunctuator(str.at(0)) == true)
        {
            return false;
        }									//if first character of string is a digit or a special character, identifier is not valid
    int i,len = str.length();
    if (len == 1)
    {
        return true;
    }										//if length is one, validation is already completed, hence return true
    else
    {
    for (i = 1 ; i < len ; i++)						//identifier cannot contain special characters
    {
        if (isPunctuator(str.at(i)) == true)
        {
            return false;
        }
    }
    }
    return true;
}

bool isOperator(char ch)							//check if the given character is an operator or not
{
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=' || ch == '|' || ch == '&')
    {
       return true;
    }
    return false;
}

bool isKeyword(std::string str)						//check if the given substring is a keyword or not
{
    if (str == "if" || str == "else" ||
        str == "while" || str == "do" ||
        str == "break" ||  str == "continue"
        || str == "int" || str == "double"
        || str == "float" || str == "return"
        || str == "char" || str == "case"
        || str == "long" || str == "short"
        || str == "typedef" || str == "switch"
        || str == "unsigned" || str == "void"
        || str == "static" || str == "struct"
        || str == "sizeof" || str =="long"
        || str == "volatile" || str == "typedef"
        || str == "enum" || str == "const"
        || str == "union" || str == "extern"
        || str =="bool" || str == "string")
        {
            return true;
        }
    else
    {
       return false;
    }
}

bool isNumber(std::string str)							//check if the given substring is a number or not
{
    int i, len = str.length(),numOfDecimal = 0;
    if (len == 0)
    {
        return false;
    }
    for (i = 0 ; i < len ; i++)
    {
        if (numOfDecimal > 1 && str.at(i) == '.')
        {
            return false;
        } else if (numOfDecimal <= 1)
        {
            numOfDecimal++;
        }
        if (str.at(i) != '0' && str.at(i) != '1' && str.at(i) != '2' &&
             str.at(i) != '3' && str.at(i) != '4' && str.at(i) != '5' &&
             str.at(i) != '6' && str.at(i) != '7' && str.at(i) != '8' &&
             str.at(i) != '9' || (str.at(i) == '-' && i > 0))
            {
                return false;
            }
    }
    return true;
}

std::string subString(std::string realStr, int l, int r)				//extract the required substring from the main string
{
    int i;
    int j = 0;

    std::string sub;
 
    for (i = l; i < r; i++)
    {
        sub.insert(j, 1, realStr.at(i));
        j++;
    }

    return sub;
}

//Sets child node of the parent of the node that's being created
void setChildNode(int level, std::array<int,2> parentNode)
{
    int childNodeBredth = test.tree.at(level).size() -1;
    std::array<int,2> childNode = {level, childNodeBredth};
    test.tree.at(parentNode[0]).at(parentNode[1]).setChildNode(childNode);
}

//Creates a new Node instance
void createNode(std::string type, std::string value, std::array<int,2> parentNode, int level)
{
    cout << "\n" << "createNode" << parentNode[0] << parentNode[1];
    Node treeNode(type, value, parentNode);
     
    if (test.tree.size() <= level) 
    {
        test.tree.push_back({});
    } 
    test.tree.at(level).push_back(treeNode);
    setChildNode(level, parentNode);
    
}

//Creates the parent node array to be set in createNode 
std::array<int,2> parentNode(int a, int b)
{
    std::array<int,2> parentNode = {a, b};
    return parentNode;
}

//Holds a createNode call for variable name until assignment is confirmed. 
void wasDetermining()
{
    createNode("Assignment", subB, parentNode(level -1, test.tree.at(level -1).size()-1), level);
}


void lex(std::string str)						//parse the expression
{   

    //Set key variables that allow the tokens to be passed to the parser with correct values at the right time
    std::string statementType = "Initial";
    std::string statementIdentifier;
    std::string numTemp  = "empty";
    std::string keyword;
    int reset = 0;
    int statementTopNum; 
    int left = 0, right = 0;
    int len = str.length();
    
    while (right < len && left <= right) {



        if (isPunctuator(str.at(right)) == false)			//if character is a digit or an alphabet
            {

                right++;
            }
        if (isPunctuator(str.at(right)) == true && left == right)		//if character is a punctuator
            {
            if (isOperator(str.at(right)) == true)
                {

                    //if I at somepoint try to make a c++ compiler I'll have to take into
                    //consideration the context of *
                    if (str.at(right) == '+' || str.at(right) == '-' || str.at(right) == '/' ||
                        str.at(right) == '*')
                    {

                        if (test.tree.size() <= level) 
                        {
                            test.tree.push_back({});
                        } 

                        //Plus could be concat. 
                        statementType = "Numeric Operator";

                        createNode("Numeric Operator", "Operator", parentNode(level -1, test.tree.at(level -1).size()-1),level);
                        createNode("numeric Operation", numTemp, parentNode(level, test.tree.at(level).size()-1), level + 1);
                        
                        level ++;
                        reset ++;

                        std::cout<< str.at(right) <<" IS AN OPERATOR\n";                        
                    }


                    if (str.at(right) == '=' && str.at(right + 1) == '=')
                    {

   
                    }
                    else if (str.at(right) == '=' && str.at(right - 1) == '=') 
                    {

                        if (test.tree.size() <= level) 
                        {
                            test.tree.push_back({});
                        }  

                        createNode("Comparison Op", "==", parentNode(level -2, test.tree.at(level -2).size() -1), level);
                        std::cout<< str.at(right) << str.at(right -1) <<" IS AN OPERATOR\n";                     
                    }
                    else if (str.at(right) == '=' && str.at(right + 1) !='=' && str.at(right -1) != '=')
                    {

                        createNode("Assignment", keyword + "Assignment", parentNode(statementTopNum -1, test.tree.at(statementTopNum -1).size()-1), statementTopNum);
                       
                        if (statementType == "Determining")
                        {
                            wasDetermining();

                        }
                        statementType = "Assignment"; 
                        std::cout<< str.at(right) <<" IS AN OPERATOR\n";                   
                    }

                } 
            else if (str.at(right) != ' ')
                {
                    std::cout << str.at(right) << " IS A PUNCTUATOR\n";
                    if (str.at(right) == ';')
                    {
                        if (numTemp !="empty")
                        {
                            if (test.tree.size() <= level)
                            {
                                test.tree.push_back({});
                            }

                            createNode("Numeric Operator", numTemp, parentNode(level -1, test.tree.at(level -1).size()-1), level);
                        }


                        level = level - reset;
                        reset = 0;
                        statementType = "Initial";
                        numTemp = "empty";
                    }

                    else if (str.at(right) == '{')
                    {
                        level = level + 1;
                    }

                    else if (str.at(right) == '(')
                    {
                        statementType = "Comparison";
                    }

                    else if (str.at(right) == '}')
                    {
                        level = level - 1;
                    }

                    else if (str.at(right) == ')')
                    {
                        statementType = "Initial";
                    }
                }
            right++;
            left = right;
            } else if (isPunctuator(str.at(right)) == true && left != right
                   || (right == len && left != right)) 			//check if parsed substring is a keyword or identifier or number
            {
              
            std::string sub = subString(str, left, right);   //extract substring
           
            if (isKeyword(sub) == true)
                        {
                            cout<< sub <<" IS A KEYWORD\n";

                            statementTopNum = level;

                            if (test.tree.size() <= level)
                            {
                                test.tree.push_back({});
                            }

                            level = level + 1;
                            reset = reset + 1;
                            statementType = "Determining";
                            keyword = sub;

                        }
            else if (isNumber(sub) == true)
                        {
                            cout<< sub <<" IS A NUMBER\n";
                            if (test.tree.size() <= level)
                            {
                                test.tree.push_back({});
                            }

                             if (statementType == "Comparison")
                             {

                                createNode("Comparison", sub, parentNode(level -2, test.tree.at(level-2).size()-1), level+1);
                             }

                             else
                             {
                                numTemp = sub;
                             }
                        }
            else if (validIdentifier(sub) == true
                     && isPunctuator(str.at(right - 1)) == false)
                     {
                         cout<< sub <<" IS A VALID IDENTIFIER\n";
                /*         if (statementType == "initial") 


                         {

                            statementType = "Assign";
                            if (test.tree.size() <= level)
                            {
                                test.tree.push_back({});
                            }
                            test.tree.at(level).push_back(statementType);
                            level = level + 1;
                            if (test.tree.size() <= level)
                            {
                                test.tree.push_back({});
                            }
                            test.tree.at(level).push_back(sub);
                         } */


                        if (test.tree.size() <= level)
                        {
                            test.tree.push_back({});
                        }

                        

                         if (statementType == "Comparison" || statementType == "Numeric Operator")
                         {
                            createNode(statementType, sub, parentNode(level , test.tree.at(level).size()-1), level+1);
                         }

                         else if (statementType == "Determining")
                         {
                            subB = sub;                     
                         }
                         else
                         {
                            createNode("Assignment", sub, parentNode(level -1, test.tree.at(level -1).size()-1), level);
                         }


                     }
            else if (validIdentifier(sub) == false
                     && isPunctuator(str.at(right - 1)) == false)
                     {
                         cout<< sub <<" IS NOT A VALID IDENTIFIER";
                     }

            left = right;
            }

    }
    test.depthFirst(0,0);
}

