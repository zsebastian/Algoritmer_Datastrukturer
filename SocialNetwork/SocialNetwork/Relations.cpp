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
	{}

	std::vector<node::ptr_t> node::list_friends()
	{
		std::vector<node::ptr_t> current_level, next_level;

		std::vector<node::ptr_t> friends; 
		std::set<node::ptr_t> visited; 

		current_level.push_back(shared_from_this());
		visited.insert(shared_from_this());
		bool enemy_is_friend = false;

		while(!current_level.empty())
		{
			for (auto& node : current_level)
			{
				for(auto& enemy : node->enemies_)
				{
					if (visited.count(enemy) == 0)
					{
						if(enemy_is_friend
							&& std::find(friends.begin(), friends.end(),
								enemy) == friends.end())
						{
							friends.push_back(enemy);
						}
						visited.insert(enemy);
						next_level.push_back(enemy);
					}
				}
			}
			enemy_is_friend = !enemy_is_friend;
			current_level = std::move(next_level);
		}

		return std::move(friends);
	}

	const std::string& node::name()
	{
		return name_;
	}
}