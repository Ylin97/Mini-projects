#include <iostream>
#include <string>
#include <vector>
#include "linklist.h"
#include "student.h"

bool cmpfunc(void *x, void *y);

int main()
{
    using namespace std;

    LinkList studs1;
    Student stud1("62221007", "zhangsan", "chongqingnananqu");
    studs1.addNode(stud1);
    // studs.traverse();
    // cout << endl;
    Student stud2("62221008", "xiaomei", "shanghai");
    studs1.addNode(stud2);
    // studs.traverse();
    // cout << endl;
    Student stud3("62221010", "xiaoming", "beijing");
    studs1.addNode(stud3, "tail");
    // studs.traverse();
    cout << endl;
    Student stud4("62221005", "wangwu", "changsha");
    studs1.addNode(stud4, 2);
    cout << "studs1当前链表长度: " << studs1.getSize() << endl;
    studs1.removeNode(3);
    // studs.traverse();
    cout << "studs1当前链表长度: " << studs1.getSize() << endl;
    Student stud5("62221011", "xiaoxiao", "shanghai");
    studs1.addNode(stud5);
    cout << "studs1当前链表长度: " << studs1.getSize() << endl;
    studs1.sort("id", true);
    // studs.traverse();
    vector<Student> search_vector = studs1.search("xiaoming");
    Student stud6("62221122", "caixukun", "xianggang");
    if (!search_vector.empty())
    {
        stud6 = search_vector[0];
        cout << "查找结果: \n";
        stud6.show();
    }
    else
    {
      
      cout << "未找到!" << endl;
    }
    studs1.removeNode("xiaoming", "name");
    LinkList studs2 = studs1;
    studs1.clean();
    cout << "studs2遍历结果:" << endl;
    studs2.traverse();
    cout << "studs1当前链表长度: " << studs1.getSize() << endl;
    cout << "studs2当前链表长度: " << studs2.getSize() << endl;
    studs1.addNode(stud6);
    cout << "studs1遍历结果:" << endl;
    studs1.traverse();
    cout << "studs1当前链表长度: " << studs1.getSize() << endl;
    LinkList studs3 = studs1 + studs2;
    cout << "studs3遍历结果:" << endl;
    studs3.sort();
    studs3.traverse();
    cout << "studs3当前链表长度: " << studs3.getSize() << endl; 
    return 0;
}

/*===========================================================
期待输出:

studs1当前链表长度: 4
studs1当前链表长度: 3
studs1当前链表长度: 4
查找结果:
***************************************

     ID: 62221010
   Name: xiaoming
Address: beijing

***************************************
studs2遍历结果:
***************************************

     ID: 62221011
   Name: xiaoxiao
Address: shanghai

***************************************
***************************************

     ID: 62221008
   Name: xiaomei
Address: shanghai

***************************************
***************************************

     ID: 62221005
   Name: wangwu
Address: changsha

***************************************
studs1当前链表长度: 0
studs2当前链表长度: 3
studs1遍历结果:
***************************************

     ID: 62221010
   Name: xiaoming
Address: beijing

***************************************
studs1当前链表长度: 1
studs3遍历结果:
***************************************

     ID: 62221005
   Name: wangwu
Address: changsha

***************************************
***************************************

     ID: 62221008
   Name: xiaomei
Address: shanghai

***************************************
***************************************

     ID: 62221010
   Name: xiaoming
Address: beijing

***************************************
***************************************

     ID: 62221011
   Name: xiaoxiao
Address: shanghai

***************************************
studs3当前链表长度: 4
===========================================================*/