#include<bits/stdc++.h>
#include <string>
#include <sstream>
#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<windows.h>
using namespace std;

ofstream file;
void title();

class Register {
	private:
		string name;
		string address;
		string id;
		string email;
		string password;
		string repeat_password;
		int date;
		int exp_date;

	public:
		void choice() {

			cout << "\n\n\t\t    *****************************************************";
			cout << "\n\n\t\t                  E-RECURTIMENT SYSTEM";
			cout << "\n\n\t\t    *****************************************************";
			int c;
			cout<<"\n\n\t\t\t1- Login "<<endl;
			cout<<"\t\t\t2- SignUp "<<endl;
			cout<<"\n\n\t\t\t\t\t";
			cin>>c;
			if(c==1) {
				sign_in();
			}
			if(c==2) {
				sign_up();
			} else {
				cout<<"\nselect correct nmbr ";
			}

		}
		void sign_up() {

			fstream ip;
			ip.open("registration.txt",ios::app);

			if (!ip.is_open()) {
				cout<<"could not open file\n";
				return;
			}

			cout<<"\n\n\t\t\t\tEnter id: ";
			cout<<"\n\n\t\t\t\t\t";
			cin>>id;
			cout<<"\n\n\t\t\t\tEnter email: ";
			cout<<"\n\n\t\t\t\t\t";
			cin>>email;
Z:
			cout<<"\n\n\t\t\t\tEnter password: ";
			cout<<"\n\n\t\t\t\t\t";
			cin>>password;
			cout<<"\n\n\t\t\t\tRepeat password: ";
			cout<<"\n\n\t\t\t\t\t";
			cin>>repeat_password;
			if(password!=repeat_password) {
				cout<<"\n\n\t\t\tpassword and re_password are not same: ";
				goto Z;
			}

			ip<<id;
			ip<<',';
			ip<<password;
			ip<<',';
			ip<<email;
			ip<<'\n';
			ip.close();

			Sleep(100);
			system("cls");

			int c;
			cout<<"\n\n\t\t\t1- Login "<<endl;
			cout<<"\t\t\t2- SignUp "<<endl;
			cout<<"\n\n\t\t\t\t\t";
			cin>>c;
			if(c==1) {
				sign_in();
			} else if(c==2) {
				exit(1);
			}

		}

		void sign_in() {

			ifstream fs("registration.txt");
			string temp,temp1, temp2;
			int ch;
			cout<<"\n\n\t\t\t\tEnter id: ";
			cin>>id;
			cout<<"\n\n\t\t\t\tEnter password: ";
			cin>>password;


			while(fs.good() && (id!=temp && password!=temp1)) {
				getline(fs,temp,',');
				getline(fs,temp1,',');
				getline(fs,temp2,'\n');
			}

			if(id==temp&&password==temp1 ) {
				cout<<"\n\n\t\t\t\tlogin successfull\n";
				cout<<"\n\n\t\t\t\tloding";
				fs.close();

				for(int i=0 ; i<=5; i++) {
					Sleep(500);
					cout<<".";
				}

				cout<<"\n\n\t\t\tpress any key to continue...";
				getch();
				return;
			} else {
				cout<<"\nIncorrect Password!\nSystem is Shutting Down!... ";
				exit(0);
			}
		}
};

class Node {
	public:
		string ID, Name, Occupation, Skill, Experience;
		Node *left;
		Node *right;
		int height;

		Node(string id,string name,string occupation,string skill,string experience) {
			ID = id;
			Name = name;
			Occupation = occupation;
			Skill = skill;
			Experience = experience;
			left = NULL;
			right = NULL;
			height = 1;
		}
};

class view {
	public:
		void title();
		void welcome();
		void menu(Node*);
		void ex_it();
};


int height(Node *N) {
	if (N == NULL)
		return 0;
	return N->height;
}

int max(int a, int b) {
	return (a > b)? a : b;
}

Node *rightRotate(Node *y) {
	Node *x = y->left;
	Node *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left),
	                height(y->right)) + 1;
	x->height = max(height(x->left),
	                height(x->right)) + 1;

	return x;
}

Node *leftRotate(Node *x) {
	Node *y = x->right;
	Node *T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(height(x->left),
	                height(x->right)) + 1;
	y->height = max(height(y->left),
	                height(y->right)) + 1;

	return y;
}

int getBalance(Node *N) {
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

Node* insert(Node* node,string id,string name,string occupation,string skill,string experience) {
	if (node == NULL) {
		Node* root = new Node(id,name,occupation,skill,experience);
		return root;
	}

	if ((skill <= node->Skill && !(experience > node->Experience)) || (skill <= node->Skill && !(experience < node->Experience)))
		node->left = insert(node->left,id,name,occupation,skill,experience);
	else if ((skill >= node->Skill && !(experience < node->Experience)) || (skill >= node->Skill && !(experience > node->Experience)))
		node->right = insert(node->right,id,name,occupation,skill,experience);

	node->height = 1 + max(height(node->left), height(node->right));

	int balance = getBalance(node);

	if (balance > 1 && skill <= node->left->Skill)
		return rightRotate(node);

	if (balance < -1 && skill >= node->right->Skill)
		return leftRotate(node);

	if (balance > 1 && skill >= node->left->Skill) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && skill <= node->right->Skill) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

Node * RR(Node *T) {

	T = leftRotate(T);
	return(T);
}

Node * LL(Node *T) {
	T = rightRotate(T);
	return(T);
}

Node * LR(Node *T) {

	T -> left = leftRotate(T->left);
	T = rightRotate(T);
	return(T);
}

Node * RL(Node *T) {
	T -> right = rightRotate(T->right);
	T = leftRotate(T);
	return(T);
}

int to_integer(string s1) {
	int num=0;
	for(int i=0,j=s1.size(); i<s1.size(); i++) {
		num+=(s1[--j]-'0')*pow(10,i);
	}
	return num;
}
string into_string(int num) {

	string res="";
	while(num>0) {
		res+=char(num%10 + 48);
		num/=10;
	}
	for(int i=0; i<res.length()/2; i++) {
		swap(res[i],res[res.length()-i-1]);
	}
	return res;
}

Node * Delete(Node *root,string x) {

	Node *p;

	if(root == NULL) {
		return NULL;
	} else if(x > root->Skill) {
		root -> right = Delete(root -> right,x);
		if(getBalance(root) == 2)
			if(getBalance(root -> left) >= 0)
				root = LL(root);
			else
				root = LR(root);
	} else if(x < root->Skill ) {
		root -> left = Delete(root->left,x);
		if(getBalance(root)==-2)
			if(getBalance(root->right)<=0)
				root=RR(root);
			else
				root=RL(root);
	} else {
		if(root -> right != NULL) {
			p = root -> right;

			while(p -> left != NULL)
				p = p -> left;

			root -> Skill = p->Skill;
			root->Experience = p->Experience;
			root->Occupation = p->Occupation;
			root->right = Delete(root ->right,p->Skill);

			if(getBalance(root) == 2)
				if(getBalance(root -> left) >= 0)
					root=LL(root);
				else
					root=LR(root);
		} else
			return(root->left);
	}
	root ->height = height(root);

	int num=to_integer(x);

	if(num!=0) {
		--num;
		string ans=into_string(num);
		x=ans;
		Delete(root,x);
	}

	return(root);
}

void search(Node* root,string skill,string exp,string occ) {
	if(root != NULL) {

		if(root->Skill>=skill && root->Experience>=exp && !(root->Occupation!=occ)) {
			file.open("Search data.txt",ios::app);
			file << "\n\t\tDetails of ID " << root->ID << " : \n";
			file << "\t\tName: " << root->Name << "\n";
			file << "\t\tOccupation: " << root->Occupation << "\n";
			file << "\t\tSkill: " << root->Skill << "\n";
			file << "\t\tExperience: " << root->Experience << "\n";
			file.close();
		}
		if(root->Skill>skill)
			search(root->left,skill,exp,occ);

		search(root->right,skill,exp,occ);
	}
}

void preorder(Node *temp) {
	if( temp != NULL) {
		cout << "Details of ID " << temp->ID << " : \n";
		cout << "Name: " << temp->Name << "\n";
		cout << "Occupation: " << temp->Occupation << "\n";
		cout << "Skill: " << temp->Skill << "\n";
		cout << "Experience: " << temp->Experience << "\n";
		cout<<endl<<endl;
		preorder(temp->left);
		preorder(temp->right);
	}
}

Node* read_record(Node* root) {
	fstream fin;
	vector<string> row;
	string line, word;
//	int count=0;

	for(int i=1; i<=2; i++) {
		string s1=into_string(i);
		string name = s1 +".csv";

		fin.open(name.c_str(), ios::in);
		while(!fin.eof()) {
			row.clear();

			getline(fin, line);
			stringstream s(line);

			while (getline(s, word, ',')) {
				row.push_back(word);
			}
	//		count++;
			root = insert(root,row[0],row[1],row[2],row[3],row[4]);
		}
		fin.close();
	}
//	cout<<endl<<count<<endl;

	return root;
}

void inorder(Node* root) {
	if(root==NULL)
		return;
	else {
		inorder(root->right);
		cout << "\n\t\tDetails of ID " << root->ID << " : \n";
		cout << "\t\tName: " << root->Name << "\n";
		cout << "\t\tOccupation: " << root->Occupation << "\n";
		cout << "\t\tSkill: " << root->Skill << "\n";
		cout << "\t\tExperience: " << root->Experience << "\n";
		cout<<endl<<endl;
		inorder(root->left);
	}
}

void display_top(queue<Node*> &q1) {
	int num;
	cout<<"\n\n\n\t\tEnter the No. of TOP Candidate whom you want to see : ";
	cin>>num;
	Sleep(100);
	system("cls");
	file<<"\n\n\n\t\t\t\tTOP "<<num<<" Candidates : \n\n\n";
	int count=0;
	while(!q1.empty()) {
		Node* temp=q1.front();
		file << "\n\t\tDetails of ID " << temp->ID << " : \n";
		file << "\t\tName: " << temp->Name << "\n";
		file << "\t\tOccupation: " << temp->Occupation << "\n";
		file << "\t\tSkill: " << temp->Skill << "\n";
		file << "\t\tExperience: " << temp->Experience << "\n";
		count++;
		q1.pop();
		if(count>=num) {
			cout << "\n\n\n\tData of TOP "<<num<<" Candidates is added into a text file name as 'Sort Data'.\n";
			return;
		}
	}

	cout << "\n\n\n\tData of TOP "<<count<<" Candidates is added into a text file name as 'Sort Data'.\n";
}

void sort(Node* root,queue<Node*>&q1) {
	if(root==NULL)
		return;
	else {
		sort(root->right,q1);
		q1.push(root);
		sort(root->left,q1);
	}
}

void searchbyskills(Node* root,string skill) {
	Node *temp= root;
	if(root != NULL) {

		if(temp->Skill==skill) {
			cout << "\n\t\tDetails of ID " << temp->ID << " : \n";
			cout << "\t\tName: " << temp->Name << "\n";
			cout << "\t\tOccupation: " << temp->Occupation << "\n";
			cout << "\t\tSkill: " << temp->Skill << "\n";
			cout << "\t\tExperience: " << temp->Experience << "\n";
		}
		if(temp->Skill>skill)
			searchbyskills(temp->left,skill);

		searchbyskills(temp->right,skill);
	}
}

void searchbyexperience(Node* root,string Experience) {
	queue<Node*> q;
	q.push(root);

	while(!q.empty()) {
		Node* tmp = q.front();
		if(tmp->Experience==Experience) {
			cout << "\n\t\tDetails of ID " << tmp->ID << " : \n";
			cout << "\t\tName: " << tmp->Name << "\n";
			cout << "\t\tOccupation: " << tmp->Occupation << "\n";
			cout << "\t\tSkill: " << tmp->Skill << "\n";
			cout << "\t\tExperience: " << tmp->Experience << "\n";
			return;
		}
		q.pop();
		if(tmp->left!=NULL)
			q.push(tmp->left);
		if(tmp->right!=NULL)
			q.push(tmp->right);
	}
}

void searchbyoccupation(Node* root,string occ) {
	queue<Node*> q;
	q.push(root);

	while(!q.empty()) {
		Node* tmp = q.front();
		if(!(tmp->Occupation!=occ)) {
			cout << "\n\t\tDetails of ID " << tmp->ID << " : \n";
			cout << "\t\tName: " << tmp->Name << "\n";
			cout << "\t\tOccupation: " << tmp->Occupation << "\n";
			cout << "\t\tSkill: " << tmp->Skill << "\n";
			cout << "\t\tExperience: " << tmp->Experience << "\n";
			return;
		}
		q.pop();
		if(tmp->left!=NULL)
			q.push(tmp->left);
		if(tmp->right!=NULL)
			q.push(tmp->right);
	}
}

void display(queue<Node*>&q1) {
	int num;
	cout<<"\n\n\n\t\tEnter the No. of TOP Candidate whom you want to see : ";
	cin>>num;
	Sleep(100);
	system("cls");
	file<<"\n\n\n\t\t\t\tTOP "<<num<<" Candidates : \n\n\n";
	int count=0;
	while(!q1.empty()) {
		Node* temp=q1.front();
		cout << "\n\t\tDetails of ID " << temp->ID << " : \n";
		cout << "\t\tName: " << temp->Name << "\n";
		cout << "\t\tOccupation: " << temp->Occupation << "\n";
		cout << "\t\tSkill: " << temp->Skill << "\n";
		cout << "\t\tExperience: " << temp->Experience << "\n";
		count++;
		q1.pop();
		if(count>=num) {
			cout << "\n\n\n\tData of TOP "<<num<<" Candidates is added into a text file name as 'Sort Data'.\n";
			return;
		}
	}
}

void add_record(Node* root) {
	string id,name,occ,skill,exp;
	int no;
	cout<<"\n\t\tENTER THE NO. OF RESUMES YOU WANT TO ADD : ";
	cin>>no;
	fstream fout;

	fout.open("2.csv", ios::out | ios::app);


	for (int i = 0; i < no; i++) {
		cout<<"\n\t\tEnter ID : ";
		cin>>id;
		cout<<"\n\t\tEnter NAME : ";
		cin>>name;
		cout<<"\n\t\tEnter OCCUPATION : ";
		cin>>occ;
		cout<<"\n\t\tEnter SKILLS : ";
		cin>>skill;
		cout<<"\n\t\tEnter EXPERIENCE : ";
		cin>>exp;
		fout << id << ","
		     << name << ","
		     << occ << ","
		     << skill << ","
		     << exp
		     << "\n";

		root=insert(root,id,name,occ,skill,exp);

	}
}


void gotoxy(int x, int y) {
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void view::welcome() {
	int l=54,n=40;

	system("Color 8e");

	Sleep(250);
	gotoxy(l,13);
	cout << "W",
	     l+=2;

	Sleep(250);
	gotoxy(l,13);
	cout << "E",
	     l+=2;

	Sleep(250);
	gotoxy(l,13);
	cout << "L",
	     l+=2;

	Sleep(250);
	gotoxy(l,13);
	cout << "C",
	     l+=2;

	Sleep(250);
	gotoxy(l,13);
	cout << "O",
	     l+=2;

	Sleep(250);
	gotoxy(l,13);
	cout << "M",
	     l+=2;

	Sleep(250);
	gotoxy(l,13);
	cout << "E",
	     l+=2;

	l=58;

	Sleep(250);
	gotoxy(l,16);
	cout << "T",
	     l+=2;

	Sleep(250);
	gotoxy(l,16);
	cout << "O",
	     l+=2;

	l=44;

	Sleep(250);
	gotoxy(l,19);
	cout << "E",
	     l+=2;

	Sleep(250);
	gotoxy(l,19);
	cout << "-",
	     l+=2;

	Sleep(250);
	gotoxy(l,19);
	cout << "R",
	     l+=2;

	Sleep(250);
	gotoxy(l,19);
	cout << "E",
	     l+=2;

	Sleep(250);
	gotoxy(l,19);
	cout << "C",
	     l+=2;

	Sleep(250);
	gotoxy(l,19);
	cout << "R",
	     l+=2;

	Sleep(250);
	gotoxy(l,19);
	cout << "U",
	     l+=2;

	Sleep(250);
	gotoxy(l,19);
	cout << "T",
	     l+=2;

	Sleep(250);
	gotoxy(l,19);
	cout << "I",
	     l+=2;

	Sleep(250);
	gotoxy(l,19);
	cout << "M",
	     l+=2;

	Sleep(250);
	gotoxy(l,19);
	cout << "E",
	     l+=2;

	Sleep(250);
	gotoxy(l,19);
	cout << "N",
	     l+=2;

	Sleep(250);
	gotoxy(l,19);
	cout << "T",
	     l+=4;

	Sleep(250);
	gotoxy(l,19);
	cout << "S",
	     l+=2;

	Sleep(250);
	gotoxy(l,19);
	cout << "Y",
	     l+=2;

	Sleep(250);
	gotoxy(l,19);
	cout << "S",
	     l+=2;

	Sleep(250);
	gotoxy(l,19);
	cout << "T",
	     l+=2;

	Sleep(250);
	gotoxy(l,19);
	cout << "E",
	     l+=2;

	Sleep(250);
	gotoxy(l,19);
	cout << "M",
	     l+=2;

	for(int m=0; m<50; m++) {
		Sleep(50);
		gotoxy(n,22);
		cout << "_",
		     n++;
	}

	Sleep(1000);

	system("Color E");

	Sleep(100);
	gotoxy(55,24);
	cout << "D";
	Sleep(100);
	gotoxy(56,24);
	cout << "E";
	Sleep(100);
	gotoxy(57,24);
	cout << "V";
	Sleep(100);
	gotoxy(58,24);
	cout << "E";
	Sleep(100);
	gotoxy(59,24);
	cout << "L";
	Sleep(100);
	gotoxy(60,24);
	cout << "O";
	Sleep(100);
	gotoxy(61,24);
	cout << "P";
	Sleep(100);
	gotoxy(62,24);
	cout << "E";
	Sleep(100);
	gotoxy(63,24);
	cout << "D";
	Sleep(100);
	gotoxy(65,24);
	cout << "B";
	Sleep(100);
	gotoxy(66,24);
	cout << "Y";
	Sleep(100);
	gotoxy(69,24);
	cout << ":";
	Sleep(200);
	gotoxy(72,25);
	cout << "20K-1043";
	Sleep(200);
	gotoxy(72,26);
	cout << "20K-1695";
	Sleep(200);
	gotoxy(72,27);
	cout << "20K-0128";

	Sleep(100);
	gotoxy(52,32);
	cout << "PRESS ANY KEY...";
}

void view::title() {
	cout << "\n\n\t\t    *****************************************************";
	cout << "\n\n\t\t                  E-RECURTIMENT SYSTEM";
	cout << "\n\n\t\t    *****************************************************";
}

void view::ex_it() {
	cout << "\n\n\n\t\t  THANKS FOR VISTING US";
	cout << "\n\n\n\t\t  PRESS ANY KEY TO TERMINATE PROGRAM...\n";
	exit(0);
}

void view::menu(Node* root) {
	root = read_record(root);
	title();

	char choice;
	int valid=1;

	do {
		cout << "\n\n\n\t\t   PRESS 1 FOR SEARCH w.r.t Skill & Experience";
		cout << "\n\n\n\t\t   PRESS 2 FOR PRINTING TOP Candidates";
		cout << "\n\n\n\t\t   PRESS 3 FOR DISPLAYING ALL THE DATA OF TOP Candidates";
		cout << "\n\n\n\t\t   PRESS 4 TO SEARCH w.r.t SKILLS";
		cout << "\n\n\n\t\t   PRESS 5 TO SEARCH w.r.t EXPERIENCE";
		cout << "\n\n\n\t\t   PRESS 6 TO SEARCH w.r.t DOMAIN";
		cout << "\n\n\n\t\t   PRESS 7 TO ADD RECORD";
		cout << "\n\n\n\t\t   PRESS 8 TO EXIT";
		cout<<endl<<endl<<endl<<endl;
		cout << "\n\n\t\t   CHOOSE FROM 1 TO 8 : ";
		cin >> choice;

		string skill, exp, occ, skill_sample, s;
		string read;
		int num;
		queue<Node*>q1;

		switch(choice) {

			case '1':
				Sleep(100);
				system("cls");
				view::title();
				cout<<"\n\n\n\t\tEnter the Min. Skills(on the scale of 1 to 10) : ";
				cin>>skill;
				cin.ignore();
				cout<<"\n\n\n\t\tEnter the Recommended Experience(in term of no. of years) : ";
				cin>>exp;
				cin.ignore();
				cout<<"\n\n\n\t\tEnter the occupation : ";
				getline(cin,occ);
				Sleep(100);
				system("cls");
				view::title();
				num=to_integer(skill);
				skill_sample=into_string(num-1);
				root = Delete(root,skill_sample);
				file.open("Search data.txt",ios::out);
				file.close();
				search(root,skill,exp,occ);
				cout << "\n\n\n\tData of Skills '>="<<skill<<"', Experience '>="<<exp<<"' are added into a text file name as 'Search Data'.\n";
				cout << "\n\n\t\t   Press Any Key To Go Back To Menu";
				system("pause>nul");
				system("cls");
				menu(root);
				break;

			case '2':
				Sleep(100);
				system("cls");
				view::title();
				sort(root,q1);
				file.open("Sort data.txt",ios::out);
				display_top(q1);
				file.close();
				cout << "\n\t\t   Press Any Key To Go Back To Menu";
				system("pause>nul");
				system("cls");
				menu(root);
				break;

			case '3':
				Sleep(100);
				system("cls");
				view::title();
				sort(root,q1);
				display(q1);
				cout << "\n\n\t\t   Press Any Key To Go Back To Menu";
				system("pause>nul");
				system("cls");
				menu(root);
				break;

			case '4':
				Sleep(100);
				system("cls");
				view::title();
				cout << "\n\n\t\tEnter skills (1-10): ";
				cin >> s;
				system("CLS");
				searchbyskills(root,s);
				cout << "\n\n\t\t   Press Any Key To Go Back To Menu";
				system("pause>nul");
				system("cls");
				menu(root);
				break;

			case '5':
				Sleep(100);
				system("cls");
				view::title();
				cout << "\n\n\t\tEnter experience: ";
				cin >> s;
				system("CLS");
				searchbyexperience(root,s);
				cout << "\n\n\t\t   Press Any Key To Go Back To Menu";
				system("pause>nul");
				system("cls");
				menu(root);
				break;

			case '6':
				Sleep(100);
				system("cls");
				view::title();
				cout << "\n\n\t\tEnter Domain: ";
				getchar();
				getline(cin,s);
				system("CLS");
				searchbyoccupation(root,s);
				cout << "\n\n\t\t   Press Any Key To Go Back To Menu";
				system("pause>nul");
				system("cls");
				menu(root);
				break;

			case '7':
				Sleep(100);
				system("cls");
				view::title();
				add_record(root);
				cout << "\n\n\t\t   Press Any Key To Go Back To Menu";
				system("pause>nul");
				system("cls");
				menu(root);
				break;

			case '8':
				Sleep(100);
				system("cls");
				view::ex_it();
				break;


			default:
				Sleep(100);
				system("cls");
				view::title();
				printf("\n\n\t\t* OPPS! YOU HAVE ENTERED INVALID CHARACTER");
				valid=0;
				break;
				getch();
		}
	} while(valid==0);
}

int main() {
	Node* root = NULL;

	view v;
	v.welcome();
	system("pause>nul");
	system("cls");
	system("Color 8e");
	Register obj;
	obj.choice();
	Sleep(100);
	system("cls");
	v.menu(root);
}
