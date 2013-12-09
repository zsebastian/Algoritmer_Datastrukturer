#pragma once

#include <memory>
#include <string>
#include <map>
#include <vector>
#include <iostream>

class Tree 
{
public:
	Tree(int weight, char c);
	Tree(Tree* t1, Tree* t2);

	int getWeight() const;
	void printTree(std::ostream& stream = std::cout) const;
	std::map<char, std::vector<bool>> getEncodings();

	Tree* getLeft() const { return m_Left.get(); }; 
	Tree* getRight() const { return m_Right.get(); }; 
	void setLeft(Tree* left)  { m_Left = std::unique_ptr<Tree>(left); }; 
	void setRight(Tree* right) { m_Right = std::unique_ptr<Tree>(right); }; 
	char getChar() const { return m_Char; }
	void setChar(char chr) { m_Char = chr; }
private:
	void getEncodings(std::map<char, std::vector<bool>>& val, std::vector<bool> bitString); 
	void printTree(std::string& bitString, std::ostream& stream) const;
	std::unique_ptr<Tree> m_Left;
	std::unique_ptr<Tree> m_Right;
	int m_Weight;
	char m_Char;
};