#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "../../Practica1/PRA_2324_P1/ListLinked.h"  // Ajusta la ruta según tu proyecto

template <typename V>
class HashTable: public Dict<V> {

private:
    int n; // número de entradas
    int max; // capacidad de la tabla
    ListLinked<TableEntry<V>>* table; // array de punteros a listas

public:

    // Función hash
    int h(std::string key){
        int valor = 0;
        for (size_t i = 0; i < key.length(); i++){
            valor += int(key[i]);
        }
        return valor % max;
    }    

    // Constructor
    HashTable(int size){
        max = size;
        n = 0;
        table = new ListLinked<TableEntry<V>>[max];
        for(int i = 0; i < max; i++){
            table[i] = ListLinked<TableEntry<V>>();
        }
    }

    // Destructor
    ~HashTable(){
        delete[] table;
    }

    // Devuelve la capacidad
    int capacity() const {
        return max;
    }

    // Devuelve número de entradas
    int entries() override {
        return n;
    }

    // Insertar clave-valor
    void insert(std::string key, V value) override {
        if(key == "") 
            throw std::runtime_error("La clave no puede estar vacía.");

        int idx = h(key);

        for(int i = 0; i < table[idx].size(); i++){
            TableEntry<V> e = table[idx][i];
            if(e.key == key){
                throw std::runtime_error("Key '" + key + "' already exists!");
            }
        }

        table[idx].append(TableEntry<V>(key, value));
        n++;
    }

    // Buscar valor por clave
    V search(std::string key) override {
        int idx = h(key);

        for(int i = 0; i < table[idx].size(); i++){
            TableEntry<V> e = table[idx][i];
            if(e.key == key) return e.value;
        }

        throw std::runtime_error("Key '" + key + "' not found!");
    }

    // Eliminar clave
    V remove(std::string key) override {
        int idx = h(key);

        for(int i = 0; i < table[idx].size(); i++){
            TableEntry<V> e = table[idx][i];
            if(e.key == key){
                V val = e.value;
                table[idx].remove(i);
                n--;
                return val;
            }
        }

        throw std::runtime_error("Key '" + key + "' not found!");
    }

    // Operador []
    V operator[](std::string key){
        return search(key); // igual que search
    }

    // Impresión
    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
        out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]\n";
        out << "==============\n";
        for(int i = 0; i < th.max; i++){
            out << "== Cubeta " << i << " ==\n";
            out << "List => " << th.table[i] << "\n\n";
        }
        out << "==============\n";
        return out;
    }
};

#endif
