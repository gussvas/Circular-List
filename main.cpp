//
//  main.cpp
//  12. Tarea Lista Circular
//
//  Created by Alex Vasquez on 10/9/19.
//  Copyright © 2019 Alex Vasquez. All rights reserved.
//

#include <iostream>
 
using namespace std;
 
template <typename T>
class Nodo {
public:
    T valor;
    Nodo<T>* siguiente = nullptr;
};
 
template <typename T>
class Circular {
public:
    Circular() {
    }
 
    ~Circular(){
        auto actual = cabeza;
        if (esCircular()){
        while(actual->siguiente != cabeza) {
            auto temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        }
        else
            while(actual) {
                auto temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
    }
    
    void makeCircular(){
        auto actual = cabeza;
        while (actual->siguiente != nullptr){
            actual = actual->siguiente;
        }
        actual->siguiente = cabeza;
    }
    
    bool esCircular(){
        auto actual = cabeza;
        for (int i = 0; i<tamano() - 1; ++i){
            actual = actual -> siguiente;
        }
        if (actual->siguiente == cabeza){
            return true;
        }
        else
            return false;
    }
 
    void agregarInicio(T valor) {
        auto siguienteNodo = new Nodo<T>;
        siguienteNodo->valor = valor;
        siguienteNodo->siguiente = cabeza;
 
        cabeza = siguienteNodo;
        
        if(esCircular()){
            auto actual = cabeza;
            while (actual->siguiente != cabeza){
                actual = actual->siguiente;
            }
            actual->siguiente = cabeza;
        }
    }
 
    void agregarFin(T valor) {
        if(esVacia()) {
            cabeza = new Nodo<T>;
            cabeza->valor = valor;
            return;
        }
 
        auto actual = cabeza;
        auto nuevoNodo = new Nodo<T>;
        nuevoNodo->valor = valor;
        
        if(!esCircular()){
        while(actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
        }
        else if (esCircular()){
            while (actual->siguiente != cabeza){
                actual = actual->siguiente;
            }
            actual -> siguiente = nuevoNodo;
            nuevoNodo -> siguiente = cabeza;
        }
    }
 
    void agregar(T valor, int posicion) {
        if(esVacia()) {
            cabeza = new Nodo<T>;
            cabeza->valor = valor;
            return;
        }
 
 
        if(posicion <= 0) {
            agregarInicio(valor);
            return;
        }
 
        if(posicion >= tamano()) {
            agregarFin(valor);
            return;
        }
 
        auto actual = cabeza;
        for (int i = 0; i <posicion-1; ++i){
            actual = actual->siguiente;
        }
        auto nuevoNodo = new Nodo<T>;
        nuevoNodo->valor = valor;
        nuevoNodo -> siguiente = actual -> siguiente;
        actual->siguiente = nuevoNodo;
    }
 
    bool esVacia() {
        return !cabeza;
    }
 
    T sacarInicio() {
        if(esVacia()) {
            return T();
        }
 
        auto viejaCabeza = cabeza;
        auto resultado = viejaCabeza->valor;
        if (esCircular()){
            auto actual = cabeza;
            while (actual->siguiente != cabeza){
                actual -> siguiente;
            }
            cabeza = viejaCabeza -> siguiente;
            actual->siguiente = cabeza;
            delete viejaCabeza;
        }
        else
        cabeza = viejaCabeza->siguiente;
        delete viejaCabeza;
        return resultado;
        
    }
 
    T sacarFin() {
        if(esVacia()) {
            return T();
        }
 
        if(!cabeza->siguiente) {
            auto viejaCabeza = cabeza;
            cabeza = nullptr;
            auto valor = cabeza->valor;
            delete viejaCabeza;
            return valor;
        }
 
        auto actual = cabeza;
        while(actual->siguiente->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        auto penultimo = actual;
 
        auto ultimo = penultimo->siguiente;
        if (esCircular()){
            penultimo -> siguiente = cabeza;
        }
        else{
            penultimo->siguiente = nullptr;}
 
        auto valor = ultimo->valor;
        delete ultimo;
        return valor;
    }
 
    T sacar(int posicion) {
        if(esVacia()) {
            return T();
        }
 
        if(posicion == 0) {
            return sacarInicio();
        }
 
        auto actual = cabeza;
        for (int i = 0; i<posicion-1; ++i){
            actual = actual->siguiente;
        }
        auto nodoViejo = actual->siguiente;
        auto valor = nodoViejo->valor;
        actual->siguiente = nodoViejo->siguiente;
        delete nodoViejo;
        return valor;
    }
 
    int tamano() {
        int cuenta = 0;
        auto actual = cabeza;
        while(actual) {
            if (actual->siguiente == cabeza){
                cuenta++;
                break;
            }
            cuenta++;
            actual = actual->siguiente;
        }
        return cuenta;
    }
 
    void imprimir() {
       auto actual = cabeza;
        if (esCircular()){
            while (actual->siguiente != cabeza){
                cout << actual->valor << endl;
                actual = actual->siguiente;
            }
            cout << actual->valor << endl;
        }
        else
            while (actual){
                cout << actual->valor << endl;
                actual = actual->siguiente;
            }
    }
 
 
private:
 
    Nodo<T>* cabeza = nullptr;
};

 
int main()
{
    Circular<float> lista;
    lista.agregarInicio(10.0);
    lista.agregarInicio(20.0);
    lista.agregarFin(30.0);
    lista.agregar(40.0, 1);
    lista.agregarInicio(400);
    lista.sacarInicio();
    lista.agregarFin(50.0);
    
    lista.imprimir(); // NO CIRCULAR
    cout << lista.esCircular() << endl;
    
    lista.makeCircular();
    lista.agregarFin(250);
    lista.sacar(4);
    lista.agregar(550, 4);

    lista.imprimir(); // CIRCULAR
    cout << lista.esCircular() << endl;


    return 0;
}



