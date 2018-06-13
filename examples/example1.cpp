#include <iostream>
#include "bstree.hpp"

using namespace std;
using namespace BSTree;

void Menu(Tree *tree) {
        string ex;
        while ((ex != "y") && (ex != "yes")) {
               cout << "Выберите одну из операций:" << endl
		<< "1. Вывести дерево на экран" << endl
		<< "2. Вывести список узлов дерева" << endl
		<< "3. Добавить узел в дерево" << endl
		<< "4. Удалить узел из дерева" << endl
		<< "5. Сохранить дерево в файл" << endl
		<< "6. Загрузить дерево из файла" << endl
		<< "7. Проверить наличие узла" << endl
		<< "8. Завершить работу программы" << endl;
                int oper;
                cin >> oper;
                switch(oper) {
                        case 1:
                                if (tree->check())
                                        tree->print();
                                else
                                        cout << "Дерево пусто" << endl;
                                break;
                        case 2:
                                if (tree->check()) {
                                        cout << "a. transversal" << endl;
                                        cout << "b. straight" << endl;
                                        cout << "c. reverse" << endl;
                                        char option;
                                        cin >> option;
                                        switch (option) {
                                                case 'a':
                                                        tree->transversal();
                                                        cout << endl;
                                                        break;
                                                case 'b':
                                                        tree->straight();
                                                        cout << endl;
                                                        break;
                                                case 'c':
                                                        tree->reverse();
                                                        cout << endl;
                                                        break;
                                        }
                                }
                                else
                                        cout << "Дерево пусто" << endl;
                                break;
                        case 3:
                                cout << "Введите значение для нового узла: ";
                                int item;
                                cin >> item;
                                if (tree->compare(item))
                                        cout << "Узел уже существует в дереве" << endl;
                                else
                                        tree->add(item);
                                break;
                        case 4:
                                cout << "Введите узел для удаления";
                                int nodee;
                                cin >> nodee;
                                if (!tree->compare(nodee))
                                        cout << "Узел не найден в дереве" << endl;
                                else {
                                        tree->deleting(nodee);
                                        cout << "Узел успешно удален из дерева" << endl;
                                }
                                break;
                        case 5:
                                if (tree->check())
                                        tree->saving();
                                else
                                        cout << "Дерево пусто" << endl;
                                break;
                        case 6:
                                tree->loading();
                                break;
                        case 7:
                                if (tree->check()) {
                                        cout << "Введите значение для поиска: ";
                                        int val;
                                        cin >> val;
                                        if (tree->compare(val))
                                                cout << "Узел найден" << endl;
                                        else
                                                cout << "Узел не найден" << endl;
                                } else
                                        cout << "Дерево пусто" << endl;

                                break;
                        case 8:
                                cout << "Вы уверены?" << endl;
                                cin >> ex;
                                if ((ex == "y") || (ex =="yes"))
                                        cout << "До свидания!" << endl;
                                break;
                        default:
                                cerr << "Ошибка" << endl;
                  }
        }
}

int main(int argc, char *argv[]) {
        Tree *tree = new Tree;
        for (int i = 1; i < argc; i++)
                tree->add(atoi(argv[i]));
        Menu(tree);
        delete tree;
        return 0;
}
