
// - `Student` 类（普通构造、带参构造、拷贝构造、析构）
// - 栈对象直接创建调用
// - `new / delete` 裸指针动态分配
// - `std::unique_ptr`、`std::shared_ptr` 智能指针演示
// - 打印日志看**构造、析构调用顺序**，方便理解内存生命周期

// 1. **栈对象**：`Student s(...)`，生命周期在作用域，离开 `{}` 自动调用析构，**不需要手动释放**。
// 2. **new / delete**：
//    - `new Student(...)`：在堆上分配内存 + 调用构造
//    - `delete ptr`：调用析构函数 + 释放堆内存
//    - 裸指针风险：忘记 delete → 内存泄漏；delete 后继续用 → 野指针
// 3. **unique_ptr**
//    - 独占所有权，不允许拷贝，只能 `std::move`
//    - 指针销毁时自动 delete，优先推荐
// 4. **shared_ptr**
//    - 引用计数，多个指针可以指向同一个对象
//    - 计数减到 0 时自动释放内存，会有一点点计数开销
// 5. 推荐写法：优先用 `make_unique` / `make_shared`，比直接 `new` 更安全。


#include <iostream>
#include <string>
// using namespace std;  不用这个的版本


#include <memory>  // unique_ptr, shared_ptr

class Student{

private:
    int id;
    std::string name;

public:
    // 1. 默认构造函数
    Student():id(0),name("未知"){
        std::cout<< "[默认构造] Student " << name << "\n";
    }

    // 2. 带参数构造函数
    Student(int _id,std::string _name):id(_id),name(std::move(_name)){
        std::cout << "[带参构造] Student " << name << ", id = " << id << "\n";
    }

    // 3. 拷贝构造函数
    Student(const Student& other):id(other.id),name(other.name){
        std::cout << "[拷贝构造] Student " << name << "\n";
    }

    // 4. 析构函数
    ~Student(){
        std::cout << "[析构函数] Student " << name << "\n";
    }

    // 成员方法
    void showInfo() const{
        std::cout << "==== 学生信息 ====\n";
        std::cout << "id: " << id << ", name: " << name << "\n\n";
    }
    
    void setName(const std::string& n){
        name=n;
    }

};

int main(){
    std::cout<<"===== 1. 栈上对象（自动管理，出作用域自动析构）=====\n";
    Student s1;
    Student s2(1001,"张三");
    Student s3=s2; // // 触发拷贝构造
    s2.showInfo();

    std::cout << "\n===== 2. new / delete 裸指针（手动管理内存，忘记delete会内存泄漏）=====\n";
    Student* pStu =new Student(1002,"李四");
    pStu->showInfo();  // 通过指针访问对象成员
    delete pStu;  // 必须手动释放，否则内存泄漏
    pStu=nullptr; // 置空，避免出现野指针

    std::cout << "\n===== 3. unique_ptr：独占式智能指针（所有权唯一，不能共享）=====\n";
    std::unique_ptr<Student> uPtr = std::make_unique<Student>(1003,"王五");
    uPtr->showInfo();
    // unique_ptr 不支持拷贝：std::unique_ptr<Student> uPtr2 = uPtr;  // 编译报错
    std::unique_ptr<Student> uPtr2 = std::move(uPtr); // 可以通过 move 转移所有权
    if (!uPtr) {
        std::cout << "uPtr 已经被移走，现在是空\n";
    }

    std::cout << "\n===== 4. shared_ptr：共享智能指针，引用计数管理 =====" << "\n";
    std::shared_ptr<Student> sh1=std::make_shared<Student>(1004,"赵六");
    sh1->showInfo();
    std::shared_ptr<Student> sh2=sh1; // 拷贝，引用计数+1，变为2
    std::cout<<"引用计数： "<<sh1.use_count()<<std::endl;

    std::cout << "\n==== main 函数即将结束，栈对象、智能指针自动析构 ====\n";
    return 0;

}

===== 1. 栈上对象（自动管理，出作用域自动析构）=====
[默认构造] Student 未知
[带参构造] Student 张三, id = 1001
[拷贝构造] Student 张三
==== 学生信息 ====
id: 1001, name: 张三


// ===== 2. new / delete 裸指针（手动管理内存，忘记delete会内存泄漏）=====
// [带参构造] Student 李四, id = 1002
// ==== 学生信息 ====
// id: 1002, name: 李四

// [析构函数] Student 李四   --  del 时结束了

// ===== 3. unique_ptr：独占式智能指针（所有权唯一，不能共享）=====
// [带参构造] Student 王五, id = 1003
// ==== 学生信息 ====
// id: 1003, name: 王五

// uPtr 已经被移走，现在是空

// ===== 4. shared_ptr：共享智能指针，引用计数管理 =====
// [带参构造] Student 赵六, id = 1004
// ==== 学生信息 ====
// id: 1004, name: 赵六

// 引用计数： 2

// ==== main 函数即将结束，栈对象、智能指针自动析构 ====
// [析构函数] Student 赵六
// [析构函数] Student 王五
// [析构函数] Student 张三
// [析构函数] Student 张三
// [析构函数] Student 未知







