#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>    
using namespace std;

//Data structure representing a buy/sell interval
struct interval {
	int product;
	int buyDay;
	int sellDay;
	int profit;
	interval() {

	}

	interval(int newProduct, int newBuyDay, int newSellDay, int newProfit) {
		product = newProduct;
		buyDay = newBuyDay;
		sellDay = newSellDay;
		profit = newProfit;
	}
};
//This function intializes p which is a map from [interval indecies of the intervals]  -> [A pair holding the interval
void initializeP(unordered_map<int, pair<interval,int>>& p, int intervalIndex, vector<interval> &intervals, int c) {
	if(intervalIndex == 0)
	{
		return;
	}

	for(int i = intervalIndex - 1; i >= 0; i--) {
		interval intervalToCalculatePFor = intervals[intervalIndex];
		interval currentInterval = intervals[i];
		//If the sell day comes 2 days before the buy day
		if(currentInterval.sellDay  < intervalToCalculatePFor.buyDay - c)
		{
			pair<interval, int> newPair(currentInterval, i);
			p[intervalIndex] = newPair;
			return;
		}

	}
}

int getClosestIntervalIndex(int intervalIndex, unordered_map<int, pair<interval, int>>& p) {
	if (p.find(intervalIndex) == p.end())
	{
		return -1;
	}



	return p.find(intervalIndex)->second.second;
}

int  opt(int intervalIndex, vector<interval> &intervals, unordered_map<int,int>& memTable, unordered_map<int, pair<interval, int>>& p) {
	if(intervalIndex < 0)
	{
		return 0;
	}

	if(memTable.find(intervalIndex) != memTable.end() )
	{
		return memTable[intervalIndex];
	}
	else
	{ 
		//The optimal profit is equal to the maximum between:
		
		//The profit we can make at this current index in the optimal solution + the optimal profit we can make at the 
		//closest previous index that does not correspond to an interval that overlaps with the interval at the current index or: 
		
		//The profit we can make at just the previous index
		int maximum = max(intervals[intervalIndex].profit + opt(getClosestIntervalIndex(intervalIndex, p), intervals, memTable, p), opt(intervalIndex - 1, intervals, memTable, p));
		memTable[intervalIndex] = maximum;
		return maximum;
	}

}

void findSolution(int j, unordered_map<int, int>& memTable, vector<interval>& intervals, unordered_map<int, pair<interval, int>>& p, vector<interval> &output) {
	if (j == -1)
	{
		return;
	}
	else
	{
		interval& currentInterval = intervals[j];
		if (intervals[j].profit + memTable[getClosestIntervalIndex(j, p)] >= memTable[j - 1])
		{
			output.push_back(currentInterval);
			findSolution(getClosestIntervalIndex(j, p), memTable, intervals, p, output);
		}
		else {
			findSolution(j-1, memTable, intervals, p, output);
		}
	}
}

bool comparisonFunction(interval& left, interval& right) {
	return left.sellDay < right.sellDay;
}
int main() {
	// c represents the cool down period in days between seling and buying another stock
	int c;
	cin >> c;
	//Map from interval indecies to a pair containing the previous interval index and the interval at that previous index
	unordered_map<int, pair<interval, int>> p;
	
	vector<interval> intervals;
	unordered_map<int, int> memTable;
	vector<interval> output;

	//Example matrix of m products and n days to buy and sell products
	 int arr[5][7] = { {2, 9, 8, 4, 5, 0, 7},
	 	              {6, 7, 3, 9, 1, 0, 8},
	 	              {1, 7, 9, 6, 4, 9, 11},
	 	              {7, 8, 3, 1, 8, 5, 2},
	 	              {1, 8, 4, 0, 9, 2, 1}};
	 //This for loop assembles the vector of all valid intervals that are profitable in the above matrix
	for (int i = 0; i < 5; i++) {
		interval temp;
		for (int j = 0; j < 7; j++) {
			for(int k = j; k < 7; k++) {
			    temp.buyDay = j +1;
				temp.sellDay = k +1;
				temp.profit = arr[i][k] - arr[i][j];
				temp.product = i + 1;
				if(temp.profit > 0) {
					intervals.push_back(temp);
				}
			}
		}
	}

	//sort(intervals.begin(), intervals.end(), comparisonFunction);
	for (int i = 0; i < intervals.size(); i++) {
		initializeP(p, i, intervals, c);
	}
	int maxProfit = opt(intervals.size() - 1, intervals, memTable, p);
	findSolution(intervals.size() - 1, memTable, intervals, p, output);

	for (int i = output.size()-1; i >= 0; i--) {
		if(i!=0)
			cout << "(" << output[i].product << ", " << output[i].buyDay << ", " << output[i].sellDay << "), ";
		else
			cout << "(" << output[i].product << ", " << output[i].buyDay << ", " << output[i].sellDay << ")";
	}
}