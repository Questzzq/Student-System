#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <windows.h>
using namespace std;

typedef struct node {
	int  Number;       // ѧ��
	char Name[20];     // ����
	char Sex;          // �Ա� M or F
	int  Grade;        // �꼶
	int  Class;        // �༶
	char Birth[20];    // ����
	char Dorm[10];     // ����
	char Address[20];  // ����
	struct node *next;
}node, *LinkList;

void Print(const node* &point);
LinkList Creat_list();               // ����
void Menu(node* head);               // �˵�
void Add(node* head);                // ����
void Search(node* head);             // ����
void Delete(node* head);             // ɾ��
void Sort(node* head);               // ����
void Clear(node *head);              // ����

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

void Menu_error(node* head) {     // ������
    cout << "Input Button_num error" << endl;
    Menu(head);
}
int Student_num = 0;
int Button_num;

void Menu(node* head) {
	int Button_num;
	cout << "��������ѡ����" << endl;
	cout << "1: ����\n" << "2: ��Ѱ" << endl;
	cout << "3: ɾ��\n" << "4: ����" << endl;
	cout << "5: ���ز˵�" << endl;
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
    cout << "ѧ��Ϊ" << point->Number << "��ѧ����Ϣ����:" << endl;
    cout << "������ " << point->Name << endl;
    cout << "�Ա� " << point->Sex << endl;
    cout << point->Grade << "��" << point->Class << "��" << endl;
    cout << "���գ� " << point->Birth << endl;
    cout << "���᣺ " << point->Dorm << endl;
    cout << "���᣺ " << point->Address << endl;
}

void Display(const node* head) {
    cout << "ѧ������Ϣ����:" << endl;
    node *p = head->next;
    while(p != NULL) {
        Print(p);
        p = p->next;
    }
}

void Add(node* head) {
	cout << "������Ҫ�������Ϣ" << endl;
	node *q = new node;
	cout << "ѧ��" << endl; cin >> q->Number;
	cout << "����" << endl; cin >> q->Name;
	cout << "�Ա�" << endl; cin >> q->Sex;
	cout << "�꼶" << endl; cin >> q->Grade;
	cout << "�༶" << endl; cin >> q->Class;
	cout << "����" << endl; cin >> q->Birth;
	cout << "����" << endl; cin >> q->Dorm;
	cout << "����" << endl; cin >> q->Address;
	q->next = head->next;
	head->next = q;
	cout << "���ӳɹ�" << endl;
	Student_num++;
	cout << "Student_num = " << Student_num << endl;
	Menu(head);
}

void Search(node * head) {
    cout << "������Ҫ���ҵ�ѧ������: ";
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
	if (flag != 1) cout << "���޴���" << endl;
	Menu(head);
}

void Delete(node* head) {
    if(!Student_num) {
        cout << "ѧ����Ϊ��" << endl;
        Menu(head);
    }
    cout << "��Ҫɾ��������ѧ��: ";
	int Delete_num;
	cin >> Delete_num;
	node *Pointer = new node;
	node *Pre_point = new node;   //���λ�ã�Pre_point--->Point
	Pointer = head;
	while (Pointer->Number != Delete_num && Pointer->next != NULL) {
		Pre_point = Pointer;
		Pointer = Pointer->next;
	}
	if(Delete_num == Pointer->Number) {
        Pre_point->next = Pointer->next;
        delete Pointer;
        cout << "ɾ���ɹ�" << endl;
        Student_num--;
	} else {
        cout << "ѧ��������ѧ��Ϊ" << Delete_num << "��ѧ��" << endl;
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
    LinkList first;  // ָ������������ĵ�һ��Ԫ��
    LinkList t;      // ��������Ԫ�صĵ�һ��Ԫ�أ�������뵽����Ԫ����
    node* p = new node;      // ����
    LinkList q;      // ����
    LinkList h;      // ָ������Ԫ�صĵ�һ����Ԫ��

    /*
    �Ƚ������ֳ�һ������ĺ�һ�������
    ����һ������Ĭ������ʣ�µ�Ĭ������
    */
    h = head->next;
    first = h->next;
    h->next = NULL;

    while(first != NULL) {
        for (t = first, q = h; ((q != NULL) && (q->Number < t->Number)); p = q, q = q->next);
        first = first->next; //����ƶ�

        if (q == h)//��Ҫ�������Ԫ�ز��뵽ͷ���ָ���λ�ã�Ҳ������С��Ԫ��
        {
            head->next = t;
            t->next = h;
            h = head->next;//�˴�����Ҫ��hֻ��һ�����þ���Ҫָ������Ԫ�صĵ�һ��Ԫ��λ��
        }
        else
        {  //�����ֵ��������Ԫ�ص�һ��Ԫ�صĺ���
            p->next = t;//p�������Ԫ�ص�ǰһ��Ԫ�ص�λ��
            t->next = q;//q�������Ԫ�صĺ�һ��Ԫ�ص�λ��
        }
    }
    return head;  //��󷵻�ͷָ�뼴�ɣ��������
}

void Sort(node* head) {
    system("cls");
    if(!Student_num) {
        cout << "ѧ����Ϊ��" << endl;
        Menu(head);
    }
	cout << "����������" << endl;
	Sleep(3000);        // ��ͣ3s
	Insert_sort_list(head);
    Display(head);
	Menu(head);
}

int main() {
    node *head = Creat_list();
	Menu(head);
	return 0;
}
