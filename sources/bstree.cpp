#include <iostream>
#include "bstree.hpp"
#include <fstream>

using namespace std;
using namespace BSTree;

Node::Node(int val) : data(val), left(nullptr), right(nullptr) {}

Tree::Tree() : root(nullptr) {}

Tree::Tree(initializer_list<int> list) : root(nullptr) {
	for (auto p = list.begin(); p != list.end(); p++)
                add(*p);
}

Tree::Tree(const Tree& tree) : root(nullptr) {
	appropriation(tree.root);
}

void Tree::appropriation(Node *m_root) {
        add(m_root->data);
        if (m_root->left != nullptr)
                appropriation(m_root->left);
        if (m_root->right != nullptr)
                appropriation(m_root->right);
}

bool Tree::check() const {
	if (root == nullptr)
		return false;
	else
		return true;
}

void Tree::add(int m_data, Node *&m_root) {
        if (m_root == nullptr)
                m_root = new Node{m_data};
        if (m_data < m_root->data) {
                if (m_root->left != nullptr)
                        add(m_data, m_root->left);
                else
                        m_root->left = new Node{m_data};
        }
        if (m_data > m_root->data) {
                if (m_root->right != nullptr)
                        add(m_data, m_root->right);
                else
                        m_root->right = new Node{m_data};
        }
}

void Tree::clear(Node *&m_root) {
        if (m_root != nullptr) {
                clear(m_root->left);
                clear(m_root->right);
                delete m_root;
                m_root = nullptr;
        }
}

void Tree::add(int m_data) {
        add(m_data, root);
}

void Tree::detour() {
	cout << "Enter order code (0-2)" << endl;
	cout << "0. In" << endl;
	cout << "1. Pre" << endl;
	cout << "2. Post" << endl;
	int code;
	cin >> code;
	switch (code) {
		case in :
			transversal();
			cout << endl;
			break;
		case pre :
			straight();
			cout << endl;
			break;
		case post :
			reverse();
			cout << endl;
			break;
	}

}

void Tree::print(Node *m_root, int space) const {
        if (m_root == nullptr)
                return;
        int count = 1;
        space += count;
        print(m_root->right, space);
        cout << endl;
        for (int i = count; i < space; i++)
                cout << "   ";
        cout << "--" << m_root->data << endl;
        print(m_root->left, space);
}

void Tree::print() const {
	print(root, 0);
}

void Tree::transversal(Node *m_root) const {
	if (m_root->left != nullptr)
		transversal(m_root->left);
	cout << m_root->data << " ";
	if (m_root->right != nullptr)
		transversal(m_root->right);
}

void Tree::transversal() const {
	transversal(root);
}

void Tree::straight(Node *m_root) const {
	cout << m_root->data << " ";
	if (m_root->left != nullptr)
		straight(m_root->left);
	if (m_root->right != nullptr)
		straight(m_root->right);
}

void Tree::straight() const {
	straight(root);
}

void Tree::reverse(Node *m_root) const {
	if (m_root->left != nullptr)
		reverse(m_root->left);
  	if (m_root->right != nullptr)
		reverse(m_root->right);
  	cout << m_root->data << " ";
}

void Tree::reverse() const {
	reverse(root);
}

bool Tree::compare(int m_item, Node *&m_root) const {
	if (m_root == nullptr)
		return false;
	if (m_item == m_root->data)
		return true;
	if (m_item < m_root->data) {
		if (m_root->left != nullptr)
			return compare(m_item, m_root->left);
		else
			return false;
	} else {
		if (m_root->right != nullptr)
			return compare(m_item, m_root->right);
		else
			return false;
	}
}

bool Tree::compare(int m_item) {
	compare (m_item, root);
}

void Tree::deleting(int m_item, Node *&m_root) {
    	if (m_item == m_root->data) {
        	Node *tmp;
        	if (m_root->right == nullptr)
            		tmp = m_root->left;
        	else {
            		Node *ptr = m_root->right;
            		if (ptr->left == nullptr) {
                		ptr->left = m_root->left;
                		tmp = ptr;
            		} else {
                		Node *pmin = ptr->left;
                		while (pmin->left != nullptr) {
                    			ptr  = pmin;
                    			pmin = ptr->left;
                		}
                		ptr->left = pmin->right;
                		pmin->left = m_root->left;
                		pmin->right = m_root->right;
                		tmp = pmin;
            		}
        	}
        delete m_root;
	m_root = tmp;
    	} else if (m_item < m_root->data)
        		deleting(m_item, m_root->left);
    		else
        		deleting(m_item, m_root->right);
}

void Tree::deleting(int m_item) {
	deleting(m_item, root);
}

void Tree::saving(Node *m_root, int space, string m_address) const {
	ofstream fout(m_address, ios_base::app);
        if (m_root == nullptr)
                return;
        int count = 1;
        space += count;
        saving(m_root->right, space, m_address);
        fout << endl;
        for (int i = count; i < space; i++)
                fout << "   ";
        fout << "--" << m_root->data << endl;
        saving(m_root->left, space, m_address);
	fout.close();
}

void Tree::saving() const {
	string address;
	cout << "Введите путь к файлу: ";
	cin >> address;
	ifstream file;
	file.open(address);
	if (!file.is_open())
		cerr << "Этот файл не существует" << endl;
	else {
		file.seekg(0, ios::end);
		if (file.tellg() == 0) {
			file.close();
                	saving(root, 0, address);
		}
		else {
			cout << "Файл уже существует, перезаписать?:" << endl;
			string exit;
			cin >> exit;
			if ((exit == "y") || (exit == "yes")) {
				file.close();
				ofstream file(address, ios_base::out | ios_base::trunc);
				file.close();
				saving(root, 0, address);
			}
			else
				return;
		}
	}
}

void Tree::loading(string address) {
	ifstream fin(address);
    	string stree;
    	getline (fin, stree);
    	int count = 0;
    	for (int i=0; i< stree.length(); i++) {
        	if (stree[i] == ' ')
			count++;
    	}
    	fin.close();
    	fin.open(address);
    	for (int i = 0; i <= count; i++) {
        	fin >> stree;
        	add(atoi(stree.data()));
    	}
	fin.close();
}

void Tree::loading() {
        string address;
        cout << "Введите путь к файлу ";
        cin >> address;
        ifstream file;
        file.open(address);
        if (!file.is_open())
                cerr << "Этот файл не существует" << endl;
        else {
        	file.close();
                loading(address);
	}
}

void Tree::auxiliary_fun(ostream& stream, Node *m_root, int space) {
        if (m_root == nullptr)
                return;
        int count = 1;
        space += count;
        auxiliary_fun(stream, m_root->right, space);
        cout << endl;
        for (int i = count; i < space; i++)
                stream << "   ";
        stream << "--" << m_root->data << endl;
        auxiliary_fun(stream, m_root->left, space);
}

auto Tree::operator=(const Tree& tree) -> Tree& {
        Node *ptr  = nullptr;
        try {
                ptr->left = new Node(*tree.root->left);
                ptr->right = new Node(*tree.root->right);
        }
        catch(...) {
                delete ptr;
                throw;
        }
        this->root->data = tree.root->data;
        swap(root->left, ptr->left);
        swap(root->right, ptr->right);
        delete ptr;
        return *this;
}

Tree::~Tree() {
        clear(root);
}
