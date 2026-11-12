


#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

class Solution{

public:
    // 爬楼梯
    int climbStairs(int n){
        if (n<=1) return 1;
        vector<int> dp(n+1,0);
        dp[0]=1;
        dp[1]=1;
        for(int i=2;i<=n;i++){
            dp[i]=dp[i-1]+dp[i-2];
        }
        return dp[n];
    }

    // 杨辉三角
    vector<vector<int>> generate(int numRows){
        vector<vector<int>> ans;
        ans.push_back({1});
        for(int i=1;i<numRows;++i){
            vector<int> temp;
            for(int j=0;j<=i;++j){
                if(j==0||j==i){
                    temp.push_back(1);
                }else {
                    temp.push_back(ans[i-1][j-1]+ans[i-1][j]);
                }
            }
            ans.push_back(temp);
        }
        return ans;
    }

    // 打家劫舍
    int rob(vector<int>& nums){
        int n=nums.size();
        if(n==1) return nums[0];
        vector<int> dp(n,0);
        dp[0]=nums[0];
        dp[1]=max(nums[0],nums[1]);
        for(int i=2;i<n;++i){
            dp[i]=max(dp[i-1],dp[i-2]+nums[i]);
        }
        return dp.back();
    }

    // 完全平方数
    int numSquares(int n){
        vector<int> dp(n+1);
        for (int i=0;i<n;++i) dp[i]=i;
        for (int i=1;i<=n;++i){
            int j=1;
            while (j*j<=i) {
                dp[i]=min(dp[i],dp[i-j*j]+1);
                j++;
            }
        }
        return dp[n];
    }

    // 零钱兑换（完全背包）
    int coinChange(vector<int>& coins,int amount){
        int INF=1e9;
        vector<int> dp(amount+1,INF);
        dp[0]=0;
        for(int c:coins){
            for(int j=c;j<=amount;++j){
                dp[j]=min(dp[j],dp[j-c]+1);
            }
        }
        return dp[amount]==INF?-1:dp[amount];
    }

    // 分割等和子集（01背包）
    bool canPartition(vector<int>& nums){
        int total=0;
        for(int x:nums) total+=x;
        if(total%2!=0) return false;
        int target=total/2;
        vector<bool> dp(target+1,false);
        dp[0]=true;

        for(int num:nums){
            for(int j=target;j>=num;--j){
                dp[j]=dp[j]||dp[j-num];
            }
        }
        return dp[target];
    }

};

    void print2D(const vector<vector<int>>& arr){
        for(auto &row:arr){
            for(int v:row){
                cout << v << " ";
            }
            cout << endl;
        }
    }

int main(){
    Solution sol;
    cout << "===== 1. climbStairs =====" << endl;
    cout << "n=5, expect 8, res=" << sol.climbStairs(5) << "\n\n";

    cout << "===== 2. generate 杨辉三角 =====" << endl;
    auto tri = sol.generate(5);
    print2D(tri);
    cout << endl;

    cout << "===== 3. rob 打家劫舍 =====" << endl;
    vector<int> rob_nums = {1,2,3,1};
    cout << "[1,2,3,1], expect 4, res=" << sol.rob(rob_nums) << "\n\n";

    cout << "===== 4. numSquares 完全平方数 =====" << endl;
    cout << "n=12, expect 3, res=" << sol.numSquares(12) << "\n";
    cout << "n=13, expect 2, res=" << sol.numSquares(13) << "\n\n";

    cout << "===== 5. coinChange 零钱兑换 =====" << endl;
    vector<int> coins = {1,2,5};
    int amount = 11;
    cout << "coins [1,2,5], amount=11, expect 3, res=" << sol.coinChange(coins, amount) << "\n\n";

    cout << "===== 6. canPartition 分割等和子集 =====" << endl;
    vector<int> part1 = {1,5,11,5};
    vector<int> part2 = {1,2,3,5};
    cout << "[1,5,11,5] expect true, res=" << boolalpha << sol.canPartition(part1) << "\n";
    cout << "[1,2,3,5] expect false, res=" << sol.canPartition(part2) << "\n";

    return 0;
}











