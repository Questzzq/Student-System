#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <windows.h>
using namespace std;

typedef struct node {
	int  Number;       // 学号
	char Name[20];     // 姓名
	char Sex;          // 性别 M or F
	int  Grade;        // 年级
	int  Class;        // 班级
	char Birth[20];    // 生日
	char Dorm[10];     // 宿舍
	char Address[20];  // 籍贯
	struct node *next;
}node, *LinkList;

void Print(const node* &point);
LinkList Creat_list();               // 创建
void Menu(node* head);               // 菜单
void Add(node* head);                // 增加
void Search(node* head);             // 搜索
void Delete(node* head);             // 删除
void Sort(node* head);               // 排序
void Clear(node *head);              // 清理

void Clear(node* head) {
    node *p = head;
    while(p) {
        node *q = p->next;
        delete p;
        p = q;
    }
}

node* Creat_list() {
    node *head = new node;
    head->next = NULL;
    return head;
}

void Menu_error(node* head) {     // 错误处理
    cout << "Input Button_num error" << endl;
    Menu(head);
}
int Student_num = 0;
int Button_num;

void Menu(node* head) {
	int Button_num;
	cout << "输入数字选择功能" << endl;
	cout << "1: 增加\n" << "2: 搜寻" << endl;
	cout << "3: 删除\n" << "4: 排序" << endl;
	cout << "5: 返回菜单" << endl;
	cin >> Button_num;
	switch(Button_num) {
        case 1:  Add(head);
        case 2:  Search(head);
        case 3:  Delete(head);
        case 4:  Sort(head);
        case 5:  Menu(head);
        default: Menu_error(head);
	}
}

void Print(const node* point) {
    cout << "学号为" << point->Number << "的学生信息如下:" << endl;
    cout << "姓名： " << point->Name << endl;
    cout << "性别： " << point->Sex << endl;
    cout << point->Grade << "年" << point->Class << "班" << endl;
    cout << "生日： " << point->Birth << endl;
    cout << "宿舍： " << point->Dorm << endl;
    cout << "籍贯： " << point->Address << endl;
}

void Display(const node* head) {
    cout << "学生表信息如下:" << endl;
    node *p = head->next;
    while(p != NULL) {
        Print(p);
        p = p->next;
    }
}

void Add(node* head) {
	cout << "请输入要插入的信息" << endl;
	node *q = new node;
	cout << "学号" << endl; cin >> q->Number;
	cout << "姓名" << endl; cin >> q->Name;
	cout << "性别" << endl; cin >> q->Sex;
	cout << "年级" << endl; cin >> q->Grade;
	cout << "班级" << endl; cin >> q->Class;
	cout << "生日" << endl; cin >> q->Birth;
	cout << "宿舍" << endl; cin >> q->Dorm;
	cout << "籍贯" << endl; cin >> q->Address;
	q->next = head->next;
	head->next = q;
	cout << "增加成功" << endl;
	Student_num++;
	cout << "Student_num = " << Student_num << endl;
	Menu(head);
}

void Search(node * head) {
    cout << "请输入要查找的学生姓名: ";
	char Search_name[20];
	cin >> Search_name;
	cout << "Search_name is " << Search_name << endl;
	node *Pointer = new node;
	Pointer = head->next;
	int flag = 0;
	while (Pointer != NULL) {
		if (!strcmp(Pointer->Name, Search_name)) {
            Print(Pointer);
			flag = 1;
			break;
		}
		Pointer = Pointer->next;
	}
	if (flag != 1) cout << "查无此人" << endl;
	Menu(head);
}

void Delete(node* head) {
    if(!Student_num) {
        cout << "学生表为空" << endl;
        Menu(head);
    }
    cout << "请要删除的输入学号: ";
	int Delete_num;
	cin >> Delete_num;
	node *Pointer = new node;
	node *Pre_point = new node;   //相对位置：Pre_point--->Point
	Pointer = head;
	while (Pointer->Number != Delete_num && Pointer->next != NULL) {
		Pre_point = Pointer;
		Pointer = Pointer->next;
	}
	if(Delete_num == Pointer->Number) {
        Pre_point->next = Pointer->next;
        delete Pointer;
        cout << "删除成功" << endl;
        Student_num--;
	} else {
        cout << "学生表中无学号为" << Delete_num << "的学生" << endl;
	}
    Menu(head);
}

void Swap(node* &node_1, node* &node_2) {
    node *tmp = new node;
    tmp = node_1;
    node_1 = node_2;
    node_2 = tmp;
}

node* Insert_sort_list(node *head){
    LinkList first;  // 指向无序子链表的第一个元素
    LinkList t;      // 保存无序元素的第一个元素，将其插入到有序元素中
    node* p = new node;      // 辅助
    LinkList q;      // 辅助
    LinkList h;      // 指向有序元素的第一个个元素

    /*
    先将链表拆分成一个有序的和一个无序的
    即第一个数据默认有序，剩下的默认无序
    */
    h = head->next;
    first = h->next;
    h->next = NULL;

    while(first != NULL) {
        for (t = first, q = h; ((q != NULL) && (q->Number < t->Number)); p = q, q = q->next);
        first = first->next; //向后移动

        if (q == h)//是要将插入的元素插入到头结点指向的位置，也就是最小的元素
        {
            head->next = t;
            t->next = h;
            h = head->next;//此处很重要，h只有一个作用就是要指向有序元素的第一个元素位置
        }
        else
        {  //插入的值是在有序元素第一个元素的后面
            p->next = t;//p保存插入元素的前一个元素的位置
            t->next = q;//q保存插入元素的后一个元素的位置
        }
    }
    return head;  //最后返回头指针即可，排序完成
}

void Sort(node* head) {
    system("cls");
    if(!Student_num) {
        cout << "学生表为空" << endl;
        Menu(head);
    }
	cout << "正在排序中" << endl;
	Sleep(3000);        // 暂停3s
	Insert_sort_list(head);
    Display(head);
	Menu(head);
}

int main() {
    node *head = Creat_list();
	Menu(head);
	return 0;
}
