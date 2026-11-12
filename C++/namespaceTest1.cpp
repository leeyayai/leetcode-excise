

#include <iostream>
#include <algorithm>   // std::swap 在这个头文件
using namespace std;

class Demo
{
public:
    // 类自己的 swap 成员函数，和 std::swap 同名
    void swap()
    {
        cout << "✅ 调用：Demo类自己的 swap() 成员函数\n";
    }

    void test()
    {
        int a = 1, b = 2;
        cout << "\n----- 情况1：直接写 swap() -----\n";
        swap();   // 【重点】优先找本类成员 Demo::swap，遮蔽了 std::swap
        // swap(a, b); // ❌ 编译报错！Demo::swap 是无参版本，不接受两个int

        cout << "\n----- 情况2：std::swap 强制指定名字空间 -----\n";
        std::swap(a, b);  // 强制去std名字空间找两参数版本
        cout << "a=" << a << ", b=" << b << "\n";
    }
};

// 再演示一层：全局函数 遮蔽 using 进来的 std 符号
void swap(int x, int y)
{
    cout << "\n✅ 调用：全局的 swap(int, int)，遮蔽 std::swap\n";
}

int main()
{
    Demo d;
    d.test();

    int m = 10, n = 20;
    cout << "\n----- 情况3：main里面直接调用swap(m,n) -----\n";
    swap(m, n);        // 优先找到【全局swap】，而不是 std::swap
    cout << "\n----- 情况4：强制std::swap绕过全局 -----\n";
    std::swap(m, n);
    cout << "m=" << m << ", n=" << n << "\n";

    return 0;
}








