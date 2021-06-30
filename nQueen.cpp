#include <iostream>
#include <ctime>
#include <unordered_set>
#include <utility>
#include <unistd.h>
using namespace std;

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

bool isSafe(unordered_set<pair<int, int>, pair_hash> &queenIndices, int row, int col)
{
	for(auto x : queenIndices)
	{
		//if(x.first == row)//no need to check for row
			//return false;
		
		if(x.second == col)
			return false;
			
		if((row - x.first) == (col - x.second))
			return false;
		
	}
	
	return true;
}

bool solveNQueenUtil(int n, unordered_set<pair<int, int>, pair_hash> &queenIndices, int row)//it can be row or col
{
	if(row >= n)
		return true;
	
	for(int i = 0; i < n; ++i)
	{
		if(isSafe(queenIndices, row, i) == true)
		{
			//board[row][i] = 1;
			queenIndices.insert({row, i});
			
			if(solveNQueenUtil(n, queenIndices, row + 1) == true)
				return true;
			
			queenIndices.erase({row, i});
			//board[row][i] = 0;
		}
	}
	
	return false;
}


void solveNQueen(int n)
{
	//vector<vector<int>> board(n, vector<int>(n, 0));
	unordered_set<pair<int, int>, pair_hash> queenIndices;
	
	if(solveNQueenUtil(n, queenIndices, 0) == false)
	{
		cout << "solution doesn't exitst\n";
		return ;
	}
	
	//cout << "The Board is : " << endl;
	//printBoard(board);
	//for(auto x : queenIndices)
		//cout << "(" << x.first+1 <<", "<< x.second+1 << ") " ;
	//cout << endl;
}

int main()
{
	int n;
	cout << "Enter number of queens : ";
	cin >> n;
	
	clock_t start, end;
	
	start = clock();
	solveNQueen(n);
	end = clock();
	
	//not using cout coz of it's double display reason, 4+e0.5 ....
	printf("Time Required : %lf\n", static_cast<double>(end-start)/CLOCKS_PER_SEC);
	
	return 0;
}
