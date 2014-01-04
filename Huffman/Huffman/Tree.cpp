#include "Tree.h"

Tree::Tree(int weight, char c)
	:m_Weight(weight)
	,m_Char(c)
{}

Tree::Tree(Tree* t1, Tree* t2)
	:m_Weight(!t1 || !t2 ? 0 : t1->m_Weight + t2->m_Weight)
	,m_Left(!t1 || !t2 ? nullptr : (t1->m_Weight > t2->m_Weight ? t1 : t2))
	,m_Right(!t1 || !t2 ? nullptr : (t1->m_Weight <= t2->m_Weight ? t1 : t2))
	,m_Char(0)
{}

int Tree::getWeight() const
{
	return m_Weight;
}

void Tree::printTree(std::ostream& stream) const
{
	std::string bitString;
	printTree(bitString, stream);
}

void Tree::printTree(std::string& bitString, std::ostream& stream) const
{
 	if (m_Char != 0)
	{
		stream << bitString << ":" << m_Char << std::endl; 
	}
	if (m_Right != nullptr)
	{
		std::string bitStringR(bitString);
		bitStringR.push_back('0');
		m_Right->printTree(bitStringR, stream);
		bitStringR.pop_back();
	}
	if (m_Left != nullptr)
	{
		std::string bitStringL(bitString);
		bitStringL.push_back('1');
		m_Left->printTree(bitStringL, stream);
		bitStringL.pop_back();
	}
}

void Tree::getEncodings(std::map<char, std::vector<bool>>& val, std::vector<bool> bitString)
{
	if (m_Char != 0)
	{
		val[m_Char] = bitString;
	}
	if (m_Right != nullptr)
	{
		std::vector<bool> bitStringR(bitString);
		bitStringR.push_back(false);
		m_Right->getEncodings(val, bitStringR);
	}
	if (m_Left != nullptr)
	{
		std::vector<bool> bitStringL(bitString);
		bitStringL.push_back(true);
		m_Left->getEncodings(val, bitStringL);
	}
}

std::map<char, std::vector<bool>> Tree::getEncodings()
{
	std::map<char, std::vector<bool>> encodings;
	std::vector<bool> temp;
	getEncodings(encodings, temp);
	return encodings;
}