#include <iostream>

using namespace std;

namespace BSTree {
        struct Node {
                int data;
                Node *left;
                Node *right;
                Node(int val);
        };
	enum traversal_order {pre, in, post};
        class Tree {
                Node *root;
                void add(int m_data, Node *&m_root);
                void print(Node *m_root, int space) const;
                void clear(Node *&m_root);
                void transversal(Node *m_root) const;
                void straight(Node *m_root) const;
                void reverse(Node *m_root) const;
                bool compare(int m_item, Node *&m_root) const;
                void deleting(int m_item, Node *&m_root);
                void saving(Node *m_root, int space, string m_address) const;
		void appropriation(Node *m_root);
		void auxiliary_fun(ostream& stream, Node *m_root, int space);
         public:
                Tree();
        	Tree(initializer_list<int> list);
        	Tree(const Tree& tree);
                bool check() const;
                void print() const;
                void add(int m_data);
                void transversal() const;
                void straight() const;
                void reverse() const;
                bool compare(int m_item);
                void deleting(int m_item);
                void saving() const;
                void loading(string m_address);
                void loading();
		void detour();
		auto operator=(const Tree&) -> Tree&;
        	auto friend operator<<(ostream& stream, Tree& tree) -> ostream& {
            		tree.auxiliary_fun (stream, tree.root, 0);
            		return stream;
        	}
		~Tree();
        };
}
