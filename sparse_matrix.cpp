#include <iostream>
#include <cassert>
using namespace std;

// Sparse Matrix Project
// By Baher Alabbar 
// 22/02/2025

struct Node {
    Node* next { };
    Node* prev { };
    int value;
    int idx;

    Node(int value, int idx): value(value), idx(idx) {}
};

class ArrayLinkedList {
    private:
    Node* head {};
    Node* tail {};
    int length;
    public:
    ArrayLinkedList(int length): length(length) {}

    // link
    // O(1) Time, O(1) Space
    void link(Node* prev, Node* next) {
        if (prev) {
            prev->next = next;
        }
        if (next) {
            next->prev = prev;
        }
    }


    // setter
    // O(n) Time, O(1) Space
    void set_value(int value, int idx) {
        assert(idx < length && idx >= 0);
        Node* new_node {new Node(value, idx)};

        if (!head) {
            head = tail = new_node;
            return;
        }

        Node* cur;
        for(cur=head; cur; cur=cur->next) {
            if (cur->idx == idx) {
                cur->value = value;
                break;
            } else if (cur->idx > idx) {
                link(cur->prev, new_node);
                link(new_node, cur);

                // new head
                if (!new_node->prev) {
                    head=new_node;
                }
                break;
            }
        }

        // new tail
        if (!cur) {
            link(tail, new_node);
            tail = new_node;
        }
    }

    // getter
    // O(n) Time, O(1) Space
    int get_value(int idx) {
        assert(idx < length && idx >= 0);
        
        for (Node* cur=head; cur && cur->idx<=idx; cur=cur->next) {
            if (cur->idx == idx) {
                return cur->value;
            }
        }

        // default value
        return 0;
    }

    // print array
    // O(n) Time, O(1) Space
    void print_array() {
        int cur_idx = 0;
        for (Node* cur=head; cur_idx<length; ++cur_idx) {
            if (cur && (cur->idx == cur_idx)) {
                cout << cur->value << " ";
                cur=cur->next;
            } else {
                cout << "0" << " ";
            }
        }
        cout << "\n";
    }

    // O(n) Time, O(1) Space
    void print_array_nonzero() {
        for(Node* cur=head; cur; cur=cur->next) {
            cout << cur->value << " ";
        }
        cout << "\n";
    }

    // add arrays
    // O(n^2) Time, O(1) Space
    void add(ArrayLinkedList &list2) {
        assert(list2.length == length);

        for (int idx=0; idx < length; ++idx) {
            int to_add = list2.get_value(idx);
            if (to_add != 0) {
                to_add += get_value(idx);
                set_value(to_add, idx);
            }
        }
    }
};

struct SparseNode {
    SparseNode* next { };
    SparseNode* prev { };
    ArrayLinkedList* list;
    int arr_idx;

    SparseNode(int arr_idx, ArrayLinkedList *list) {
        this->arr_idx = arr_idx;
        this->list = list;
    }
};

class SparseMatrix {
    private:
    int rows_num;
    int cols_num;
    SparseNode* head { };
    SparseNode* tail { };

    public:
    SparseMatrix(int rows_num, int cols_num): rows_num(rows_num), cols_num(cols_num) {}

    // O(1) Time, O(1) Space
    void link(SparseNode* prev, SparseNode* next) {
        if (prev) {
            prev->next = next;
        }
        if (next) {
            next->prev = prev;
        }
    }

    // O(n^2) Time, O(1) Space
    void set_value(int value, int row, int col) {
        assert(row > -1 && row < rows_num);
        assert(col > -1 && col < cols_num);

        ArrayLinkedList* new_row = new ArrayLinkedList(cols_num);
        new_row->set_value(value, col);
        SparseNode* snode {new SparseNode(row, new_row)};

        if (!head) {
            head = tail = snode;
        }

        
        SparseNode* cur;
        for(cur=head; cur; cur=cur->next) {
            if (cur->arr_idx == row) {
                cur->list->set_value(value, col);
                break;
            } else if (cur->arr_idx > row) {
                link(cur->prev, snode);
                link(snode, cur);

                // new head
                if (!snode->prev) {
                    head=snode;
                }
                break;
            }
        }

        // new tail
        if (!cur) {
            link(tail, snode);
            tail = snode;
        }
        
    }

    // get value
    // O(n^2) Time, O(1) Space
    int get_value(int row, int col) {
        assert(row > -1 && row < rows_num);
        assert(col > -1 && col < cols_num);
        
        for (SparseNode* cur=head; cur && cur->arr_idx<=row; cur=cur->next) {
            if (cur->arr_idx == row) {
                return cur->list->get_value(col);
            }
        }

        // default value
        return 0;
    }

    // print matrix 
    // O(n^2) Time, O(1) Space
    void print_matrix() {
        int cur_idx = 0;
        for (SparseNode* cur=head; cur_idx<rows_num; ++cur_idx) {
            if (cur && (cur->arr_idx == cur_idx)) {
                cur->list->print_array();
                cur=cur->next;
            } else {
                for(int i = 0; i < cols_num; ++i) {
                    cout << "0" << " ";
                }
                cout << "\n";
            }
        }
        cout << "\n";
    }

    // print matrix nonzero
    // O(n^2) Time, O(1) Space
    void print_matrix_nonzero() {
        int cur_idx = 0;
        for (SparseNode* cur=head; cur_idx<rows_num; ++cur_idx) {
            if (cur && (cur->arr_idx == cur_idx)) {
                cur->list->print_array_nonzero();
                cur=cur->next;
            }
        }
        cout << "\n";
    }

    // add matrix
    // O(n^2) Time, O(1) Space
    void add(SparseMatrix &matrix2) {
        assert(matrix2.rows_num == rows_num);
        assert(matrix2.cols_num == cols_num);

        if (!matrix2.head) {
            return;
        } else if (!head) {
            head = matrix2.head;
            tail = matrix2.tail;
            return;
        }

        SparseNode* cur_row = head;
        SparseNode* cur_row_2 = matrix2.head;

        while (cur_row && cur_row_2) {
            if (cur_row->arr_idx == cur_row_2->arr_idx) {
                cur_row->list->add(*(cur_row_2->list));
                cur_row_2=cur_row_2->next;
            } else if (cur_row->arr_idx > cur_row_2->arr_idx) {
                link(cur_row->prev, cur_row_2);
                link(cur_row_2, cur_row);

                if (!cur_row_2->prev) {
                    head = cur_row_2;
                }
                cur_row_2=cur_row_2->next;
            } else {
                cur_row=cur_row->next;
            }
        }

        if (cur_row_2) {
            link(tail, cur_row_2);
            tail = matrix2.tail;
        }

    }

};

int main() {
    ArrayLinkedList list(10);
    list.set_value(5, 3);
    list.set_value(2, 2);
    list.set_value(7, 5);
    list.set_value(-1, 4);
    list.set_value(-2, 3);
    list.set_value(-2, 6);
    list.set_value(-2, 0);

    list.print_array_nonzero();
    list.print_array();

    ArrayLinkedList list2(10);
    list2.set_value(5, 3);
    list2.set_value(2, 2);
    list2.set_value(7, 5);
    list2.set_value(-1, 4);
    list2.set_value(-2, 3);
    list2.set_value(-2, 6);
    list2.set_value(-2, 0);
    list2.set_value(-9, 9);

    list2.print_array_nonzero();
    list2.print_array();

    list.add(list2);
    list.print_array_nonzero();
    list.print_array();

    cout << "\n";

    SparseMatrix slist(10, 10);
    slist.set_value(5, 3, 6);
    slist.set_value(5, 3, 9);
    slist.set_value(-1, 3, 6);
    slist.set_value(3, 3, 6);
    slist.set_value(3, 1, 2);
    slist.set_value(3, 2, 2);
    slist.set_value(3, 3, 2);
    slist.set_value(3, 4, 2);
    slist.set_value(3, 5, 2);
    slist.set_value(7, 8, 2);
    slist.print_matrix();
    slist.print_matrix_nonzero();
    // cout << slist.get_value(3, 9) << "\n";
    // cout << slist.get_value(8, 2) << "\n";
    // cout << slist.get_value(8, 3) << "\n";
    cout << "slist2: " << "\n";


    SparseMatrix slist2(10, 10);
    slist2.set_value(33, 0, 6);
    slist2.set_value(5, 3, 6);
    slist2.set_value(5, 3, 9);
    slist2.set_value(-1, 3, 6);
    slist2.set_value(3, 3, 6);
    slist2.set_value(3, 1, 2);
    slist2.set_value(3, 2, 2);
    slist2.set_value(3, 3, 2);
    slist2.set_value(3, 4, 2);
    slist2.set_value(3, 5, 2);
    slist2.set_value(7, 8, 2);
    slist2.set_value(19, 9, 2);

    slist.add(slist2);
    slist.print_matrix();
    slist.print_matrix_nonzero();

    return 0;
}
