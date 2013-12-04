#pragma once
#include <vector>
#include <memory>
#include <set>
#include <string>

namespace relations
{
	class node : public std::enable_shared_from_this<node>
	{
	private:
		struct detail
		{
			struct this_is_private {};
		};

	public: 
		typedef std::shared_ptr<node> ptr_t;
		std::vector<node::ptr_t> list_friends();
		void add_enemy(node::ptr_t);

		static node::ptr_t make(std::string);
		node(std::string, detail::this_is_private&);
		const std::string& name();
	private: 
		std::string name_;
		std::set<node::ptr_t> enemies_; 
	};
}