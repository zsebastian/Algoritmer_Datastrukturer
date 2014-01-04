#include "Huffman.h"
#include <queue>
#include <array>

Huffman::Huffman(std::string str)
{
	encode(str);
}

const Tree* const Huffman::getTree() const
{
	return m_Tree.get();
}

/*
const std::vector<bool>& Huffman::getCompressed() const
{
	return m_Compressed;
}
*/
void Huffman::encode(std::string& str)
{
	std::array<int, 256U> charCount;
	std::fill(charCount.begin(), charCount.end(), 0);
	m_Tree.reset();

	struct priocomp
	{
		bool operator() (const std::pair<int, Tree*>& lhs, const std::pair<int, Tree*>& rhs) const
		{
			return (lhs.first > rhs.first );
		}
	};

	std::priority_queue<std::pair<int, Tree*>, std::vector<std::pair<int, Tree*>>, priocomp> treeQ;
	
	for (auto chr : str)
	{
		charCount[chr]++;
	}

	for (auto count = charCount.begin(); count != charCount.end(); ++count)
	{
		char chr = std::distance(charCount.begin(), count);
		if (*count != 0)
			treeQ.emplace(*count, new Tree(*count, chr));
	}

	while (!treeQ.empty())
	{
	
		Tree* lhs = treeQ.top().second;
		treeQ.pop();
		if (treeQ.empty())
		{
			m_Tree = std::unique_ptr<Tree>(lhs);
			break;
		}

		Tree* rhs = treeQ.top().second;
		treeQ.pop();
		Tree* newTree = new Tree(lhs, rhs);

		treeQ.emplace(newTree->getWeight(), newTree);
	}


	/*auto encoding = m_Tree->getEncodings();
	m_Compressed.clear();
	
	for (auto chr: str)
	{
		m_Compressed.insert(m_Compressed.end(), encoding[chr].begin(), encoding[chr].end());	
	}*/

}
/*
std::string Huffman::deCompress()
{
	Tree* current = m_Tree.get(); 
	std::string ret; 
	for(auto iter = m_Compressed.begin(); iter != m_Compressed.end();)
	{
		if(current->getChar() != 0) 
		{
			ret.push_back(current->getChar());
			current = m_Tree.get();
		}
		else if(*iter == true)
		{
			++iter;
			current = current->getLeft();
		}
		else
		{
			++iter;
			current = current->getRight();
		}
	}

	if(current->getChar() != 0) 
	{
		ret.push_back(current->getChar());
		current = m_Tree.get();
	}

	return ret; 
}

std::string Huffman::serialize()
{
	std::ostringstream ss;
	m_Tree->printTree(ss);
	std::string treeRep = ss.str();
	treeRep += ';';

	std::string compRep;
	int b = 0;
	unsigned char chr = 0;

	for (auto bit : m_Compressed)
	{
		chr |= (bit << (b % 8));
		++b;
		if (b % 8 == 0)
		{
			compRep.push_back(chr);
			chr = 0;
		}
	}
	compRep.push_back(chr);
	return treeRep + std::to_string(m_Compressed.size()) + " " + compRep;
}

void Huffman::deserialize(std::string& str)
{
	std::string bitString;
	m_Tree = std::unique_ptr<Tree>(new Tree(nullptr, nullptr));
	m_Compressed.clear();

	auto chr = str.begin();
	auto end = str.end();
	for (; chr != end; chr++)
	{
		if (*chr != ':' && *chr != ';')
			bitString += *chr;
		else if (*chr == ':')
		{
			char nodeChr = *(++chr);
			Tree* current = m_Tree.get();
			for (auto bit : bitString)
			{
				if (bit == '1')
				{
					if (!current->getLeft())
						current->setLeft(new Tree(0, 0));
					current = current->getLeft();
				}
				else if (bit == '0')
				{
					if (!current->getRight())
						current->setRight(new Tree(0, 0));
					current = current->getRight();
				}
			}
			current->setChar(nodeChr);
			if (chr != end) ++chr;
			bitString = std::string();
		}
		else if (*chr == ';')
			break;
	}

	int size = 0;
	if (chr != end)
	{
		++chr;
		std::string sizeStr;
		for (; chr != end; chr++)
		{
			sizeStr.push_back(*chr);
			if (*chr == ' ')
				break;

		}
		size = atoi(sizeStr.c_str());
	}

	if (chr != end)
	{
		++chr;
		for (; chr != end; chr++)
		{
			for (int i = 0; i < 8; ++i)
			{
				unsigned char mask = 1 << i;
				unsigned char masked = (static_cast<unsigned char>(*chr) & mask);

				m_Compressed.push_back(masked != 0);
			}
		}
		m_Compressed.resize(size);
	}
}*/