#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>
using namespace std;

template <typename V> 
class TableEntry {
    public:
      
	    // miembros públicos
	string key;
	V value;

	TableEntry(string key, V value){
		
	this->key = key;
	this->value = value;

	}

	
	TableEntry(string key){

		this->key = key;
	}
	
	TableEntry(){

		this->key = ""; 
	}

	friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2){

		if(te1.key == te2.key){
			return true;
		}else{
		       	return false;
		}


	}

	friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2){

		if(te1.key!=te2.key){
			return true;
		}else{
			return false;
		}	
	
	}

	friend ostream& operator<<(ostream &out, const TableEntry<V> &te){
		
	out << te.key <<"->" << te.value;

	return out;

	}	
		


};

#endif
