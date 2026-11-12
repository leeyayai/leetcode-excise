
// 写一个 Student 类，练习构造、．调用、new 与 delete、智能指针。

// 1. `std` 是**名字空间盒子**，`self` / `this` 是**对象实例**，根本不是一类东西；
// 2. `using namespace std;` = 打开这个盒子，里面名字可以不加前缀直接用；
// 3. 名字查找优先级：
    // 1. 先找**局部变量**
    // 2. 再找**本类的成员（成员函数 / 成员变量）**
    // 3. 再找**外层作用域**
    // 4. 再找被 `using namespace` 导入的名字空间（std）
// 4. 冲突的时候，写 `std::xxx` 就是强制指定去标准库盒子找；
// 5. 教学写 `using namespace std` 省事，正式项目谨慎使用，防止名字遮蔽（name hiding）。


#include <iostream>
#include <string>
using namespace std;

class Student{

private:
    int id;
    string name;

public:

    // 默认构造
    Student():id(0),name("未知"){
        cout<<"调用默认构造函数"<< name <<endl;
    }

    // 带参构造器（初始化列表，move优化）
    Student(int _id,string _name):id(_id),name(move(_name)){
        cout<<"调用带参构造函数 id=" << id << "," << name << "\n";
    }

    // 拷贝构造函数（c++独有语法）
    Student(const Student& other):id(other.id),name(other.name){
        cout<<"调用拷贝构造 id=" << id << "," << name << "\n";
    }

    ~Student(){
        cout<<"[析构] Student " << name << ",id=" << id << "\n";
    }

    void show(){
        cout << id << " " << name << endl;
    }


};

int main(){
    Student s1;                // 默认构造
    Student s2(1001, "张三");  // 带参构造
    Student s3 = s2;           // 触发拷贝构造
}








