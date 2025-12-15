#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        int nelem;           // Número de elementos
        BSNode<T> *root;     // Nodo raíz

        // --- MÉTODOS PRIVADOS RECURSIVOS ---

        // Búsqueda recursiva
        BSNode<T>* search(BSNode<T>* n, T e) const {
            if (n == nullptr) {
                throw std::runtime_error("Element not found!");
            }
            if (n->elem < e) {
                return search(n->right, e);
            } else if (n->elem > e) {
                return search(n->left, e);
            } else {
                return n; // Encontrado
            }
        }

        // Inserción recursiva
        BSNode<T>* insert(BSNode<T>* n, T e) {
            if (n == nullptr) {
                return new BSNode<T>(e);
            }
            if (n->elem == e) {
                throw std::runtime_error("Duplicate element!");
            }
            if (n->elem > e) {
                n->left = insert(n->left, e);
            } else {
                n->right = insert(n->right, e);
            }
            return n;
        }

        // Recorrido Inorden recursivo
        void print_inorder(std::ostream &out, BSNode<T>* n) const {
            if (n != nullptr) {
                print_inorder(out, n->left);
                out << n->elem << " "; // Imprimimos el elemento y un espacio
                print_inorder(out, n->right);
            }
        }

        // Eliminar recursivo
        BSNode<T>* remove(BSNode<T>* n, T e) {
            if (n == nullptr) {
                throw std::runtime_error("Element not found!");
            }

            if (n->elem < e) {
                n->right = remove(n->right, e);
            } else if (n->elem > e) {
                n->left = remove(n->left, e);
            } else {
                // Nodo encontrado
                if (n->left != nullptr && n->right != nullptr) {
                    // Caso 3: Dos hijos. Reemplazo por MAX del subárbol IZQUIERDO
                    n->elem = max(n->left);
                    n->left = remove_max(n->left);
                } else {
                    // Caso 1 y 2: 0 o 1 hijo
                    BSNode<T>* aux = (n->left != nullptr) ? n->left : n->right;
                    delete n;
                    return aux;
                }
            }
            return n;
        }

        // Devuelve el valor máximo del subárbol (el nodo más a la derecha)
        T max(BSNode<T>* n) const {
            if (n == nullptr) {
                throw std::runtime_error("Empty subtree");
            }
            if (n->right != nullptr) {
                return max(n->right);
            } else {
                return n->elem;
            }
        }

        // Elimina el nodo con el valor máximo del subárbol
        BSNode<T>* remove_max(BSNode<T>* n) {
            if (n->right == nullptr) {
                // Este es el nodo máximo, lo eliminamos y devolvemos su hijo izquierdo (si tiene)
                BSNode<T>* leftChild = n->left;
                delete n;
                return leftChild;
            }
            // Seguimos buscando a la derecha
            n->right = remove_max(n->right);
            return n;
        }

        // Borrado en cascada (para el destructor)
        void delete_cascade(BSNode<T>* n) {
            if (n != nullptr) {
                delete_cascade(n->left);
                delete_cascade(n->right);
                delete n;
            }
        }

    public:
        // --- MÉTODOS PÚBLICOS ---

        // Constructor
        BSTree() {
            nelem = 0;
            root = nullptr;
        }

        // Destructor
        ~BSTree() {
            delete_cascade(root);
        }

        // Tamaño
        int size() const {
            return nelem;
        }

        // Búsqueda (Lanzadera)
        T search(T e) const {
            return search(root, e)->elem;
        }

        // Operador []
        T operator[](T e) const {
            return search(e);
        }

        // Inserción (Lanzadera)
        void insert(T e) {
            root = insert(root, e);
            nelem++;
        }

        // Impresión (Sobrecarga <<)
        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
            bst.print_inorder(out, bst.root);
            return out;
        }

        // Eliminación (Lanzadera)
        void remove(T e) {
            root = remove(root, e);
            nelem--;
        }
};

#endif
