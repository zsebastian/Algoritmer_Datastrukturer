#include "Relations.h"
#include <utility>
#include <deque>

namespace relations
{
	node::ptr_t node::make(std::string name)
	{
		return std::make_shared<node>(std::move(name), detail::this_is_private());
	}

	void node::add_enemy(node::ptr_t n)
	{
		enemies_.insert(n);
	}

	node::node(std::string name, detail::this_is_private&)
		:name_(std::move(name))
	{
	}

	std::vector<node::ptr_t> node::list_friends()
	{
		std::deque<node::ptr_t> children;  
		std::vector<node::ptr_t> friends; 
		std::set<node::ptr_t> visited; 

		children.push_back(shared_from_this());
		bool enemy_is_friend = false;

		while(!children.empty())
		{
			auto child = children.front;
			children.pop_front;
			for(auto& enemy : child->enemies_)
			{
				if(enemy_is_friend
					&& std::find(friends.begin(), friends.end(),
						enemy) == friends.end())
				{
					friends.push_back(enemy);
				}
				if(visited.count(enemy) == 0)
				{
					visited.insert(child);
					children.push_back(enemy);
				}
			}
			enemy_is_friend = !enemy_is_friend;
		}

		return std::move(friends);
	}

	const std::string& node::name()
	{
		return name_;
	}
}