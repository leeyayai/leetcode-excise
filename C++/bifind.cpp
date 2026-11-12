
#include <iostream> // 输入输出的库
#include <vector>
using namespace std;  // 省去每次写 std::，刷题常用


class Solution{


//  vector<int> 动态、可变长、连续下标访问 `[i]`
//  `vector<vector<int>>& matrix` 对应 Java `ArrayList<ArrayList<Integer>>`，就是二维动态数组
// Java 所有对象传参本质是**值传递（传对象地址副本）**，没有 `&` 引用语法。
// Java：`void func(ArrayList<Integer> list)` 传进去也是同一个对象，可以改里面元素；
// C++ 如果你不写 `&`，它是实打实复制整个数组，数据量大的时候超时。
public:

    // 传引用 &：不拷贝，直接操作原数组，速度快
    void func(vector<int>& nums) {
        nums[0] = 999; // 修改会影响外面传入的原vector
    }

    // 没有&：值传递，会完整拷贝一份新vector，大数组很慢
    void func(vector<int> nums) {
        nums[0] = 999; // 只改拷贝出来的副本，外面原来的不变
    }


    // 闭区间 [left, right] lower_bound，返回第一个 >= target 的下标
    int lower_bound(vector<int>& nums,int target){  // 传引用 &：不拷贝，直接操作原数组，速度快
        int left=0,right=(int)nums.size()-1;
        while(left<=right){
            int mid=left+(right-left)/2; // 防止溢出的中点计算，面试官要考的点
            if (nums[mid]<target) {
                left=mid+1;
            }else {
                right=mid-1;
            }
        }
        return left;
    }

    int lower_bound2(vector<int>& nums,int target){
        int left=0,right=(int)nums.size();
        while (left<right) {
            int mid=left+(right-left)/2;
            if (nums[mid]<target) {
                left=mid+1;
            }else {
                right=mid-1;
            }
        }
        return right;
    }

    bool searchMatrix(vector<vector<int>>& matrix,int target){
        int m =(int)matrix.size();
        int n =(int)matrix[0].size();
        int left=0,right=m*n-1;
        while (left<right) {
            int mid=left+(right-left)/2;
            if (matrix[mid/m][mid%n]<target) {
                left=mid+1;
            }else {
                right=mid-1;
            }
        }
        if (left>=m*n) {
            return false;
        }
        return matrix[left/m][left%n]==target;
    } 

    vector<int> searchMatrix(vector<int>& nums,int target){
        int start=lower_bound(nums,target);
        if (start==(int)nums.size()||nums[start]!=target) {
            return {-1,-1};
        }
        int end=lower_bound(nums,target+1)-1;
        return {start,end};
    }

    int findMin(vector<int>& nums){
        int left=-1;
        int right=(int)nums.size()-1;
        while (left+1<right) {
            int mid=left+(right-left)/2;
            if (nums[mid]<nums.back()) {   
                // nums.back() nums的最后一个元素，java等价写法//  `nums[nums.length-1]`
                // python 等价写法nums[-1]
                right=mid;
            }else {
                left=mid;
            }
        }
        return right;
    }

    int lower(vector<int>& nums,int L,int R,int target){
        int left=L,right=R;
        while (left<=right) {
            int mid=left+(right-left)/2;
            if (nums[mid]<target) {
                left=mid+1;
            }else {
                right=mid-1;
            }
        }
        return left;
    }

    int search(vector<int>& nums,int target){
        int n=(int)nums.size();
        int i = findMin(nums);
        // int pos;  //  int pos=-1; // 正确写法,可以只声明不赋值，但是习惯还是先声明再使用
        int pos=-1;
        // C++ 局部内置基础类型（int、long 等），声明的时候允许不初始化；它只是「有一块内存、里面是随机垃圾值」，编译器不会强制要求你给初值。
        // Java 局部变量强制要求初始化，这是语言规则差异。
        // java:
        // int pos;
        // System.out.println(pos); // 直接编译报错！
        // python:没有 “只声明不赋值” 这个语法！`pos = xxx` 才是绑定变量；
        // python:没有赋值语句，变量根本不存在，和 C++/Java 不是一套内存模型。
        // int pos   # 直接语法报错
        // pos       # 直接报NameError
        if (target>nums.back()) {
            pos=lower(nums,0,i-1,target);  // 直接引用了，在python里是会报错的，要加self，
            // 在python里是直接import 类.方法 as 别名，然后用的
        }else {
            pos=lower(nums,i,n-1,target);
        }
        if (pos<n && nums[pos]==target) {
            return pos;
        }
        return -1;
    }


};

int main(){
    Solution sol;
    vector<int> arr ={1,2,3,4,5};
    cout<<sol.lower_bound(arr,2)<<endl;
    return 0;
}











