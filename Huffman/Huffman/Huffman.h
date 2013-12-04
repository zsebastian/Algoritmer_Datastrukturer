#pragma once

#include "Tree.h"

#include <vector>
#include <string>

class Huffman
{
public:
	/* When creating a huffman, pass in a string of the 
		text you want to encode. On construction the object
		will then encode the string */
	Huffman(std::string);

	/* Return the huffman tree of the compression */
	const Tree* const getTree() const;

	/* return the compressed bytes of the text */
	const std::vector<bool>& getCompressed() const;

	std::string deCompress();
	std::string serialize();
	void deserialize(std::string&);

private:
	void encode(std::string&);

	std::vector<bool> m_Compressed;
	std::unique_ptr<Tree> m_Tree;
};