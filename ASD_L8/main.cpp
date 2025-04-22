#include <vector>
#include <iostream>
#include <set>
#include <unordered_set>
#include <algorithm>

bool isCorrect(std::vector<bool> block)
{
	int minRed = block.size();
	int currRed = 0;
	if (std::all_of(block.begin(), block.end(), [](bool x) {return x; }))
	{
		return true;
	}
	for (int i = 0; i < block.size(); i++)
	{
		if (block[i])
		{
			++currRed;
		}
		else if (currRed != 0)
		{
			minRed = std::min(currRed, minRed);
			currRed = 0;
		}
	}
	if (currRed != 0) minRed = std::min(currRed, minRed);
	
	return minRed >= 3;
}

int task6(int ind,std::vector<bool> block, std::unordered_set<std::vector<bool>>& hash)
{
	if (block.size() == ind)
	{
		if (!hash.contains(block) && isCorrect(block))
		{
			hash.insert(block);
		}
		return 0;
	}

	int i1 = task6(ind + 1, block,hash);
	block[ind] = true;
	int i2 = task6(ind + 1, block,hash);
}

int main()
{
	std::vector<bool> t6(50);
	std::unordered_set<std::vector<bool>> cache;
	task6(0, t6, cache);
	t6[0] = true;
	task6(0, t6, cache);
	for (auto& x : cache)
	{
		for (auto y : x)
		{
			std::cout << y << " ";
		}
		std::cout << "\n";
	}
	std::cout << cache.size() << std::endl;
}