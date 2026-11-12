

#include <iostream>
using namespace std; 

// 本类有方法 A，std 里也有 A
void swap(int &a, int &b) {
    cout << "我是Student类里面自己写的swap\n";
}

// 本类 / 当前局部作用域的名字，优先级高于 using namespace 导入的名字。
class Test{
public:
    void swap() {
        cout << "类自己的swap\n";
    }
    void func() {
        swap();       // ✅ 优先调用 Test::swap()，本类成员
        std::swap(a,b);// 如果你想要标准库的swap，就手动写std::，强制指定盒子
    }
};

// C++ 的名字查找顺序（简化）：

// 1. 先找**局部变量**
// 2. 再找**本类的成员（成员函数 / 成员变量）**
// 3. 再找**外层作用域**
// 4. 再找被 `using namespace` 导入的名字空间（std）


int main() {
    int x=1,y=2;
    swap(x,y);   // 优先找到当前作用域这个swap，而不是std::swap
}











