#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>

template <class T>
class Container{
private:
    unsigned int size;
    unsigned int capacity;
    T* buffer;
    void  reserve();// Riserva la capacita' corretta adattando al numero di elementi
public:

    class iterator{
        friend class Container<T>;
    private:
        T* punt;
        iterator(T*);
    public:
        bool operator == (const iterator&) const;
        bool operator != (const iterator&) const;

        T& operator * ();
        T* operator ->();

        iterator& operator ++();
        iterator operator ++(int);
        iterator& operator --();
        iterator operator --(int);
        iterator &operator +(unsigned int);
        iterator &operator -(unsigned int);
        iterator &operator +=(unsigned int);
        iterator &operator -=(unsigned int);
    };

    class const_iterator{
        friend class Container<T>;
    private:
        const T* cpunt;
        const_iterator(T*);
    public:
        bool operator==(const const_iterator&) const;
        bool operator!= (const const_iterator&) const;
        const T& operator* ()const;
        const T* operator->()const;
        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator --();
        const_iterator operator --(int);
        const_iterator &operator +(unsigned int);
        const_iterator &operator -(unsigned int);
        const_iterator &operator +=(unsigned int);
        const_iterator &operator -=(unsigned int);
    };
     Container(unsigned int=2);
     Container(const T&,unsigned int=2);
     Container(const Container<T>&);
    ~Container();
     //Rule of three
    Container<T> & operator= (const Container<T> &);
    T& operator[](unsigned int);

    bool operator==(const Container<T>&) const;
    unsigned int getSize() const;// Numero di elementi presenti nel Container
    unsigned int getCapacity()const;// Capacita' del Container
    void clear();// Pulisce il Container
    bool isEmpty()const;

    T& front();//Ritorna il primo elemento del Qootnainer
    T& back();//Ritorna l'ultimo elemento del Container

    void push_back(const T&);
    void pop_back();

    void erase(unsigned int =0);//Cancellazione singola
    void erase (unsigned int, unsigned int);//Cancellazione multipla
    void erase(T);//Cancellazione in base all'elemento passato

    T& at(unsigned int);
    //iteratori
    iterator begin()const;//Iteratore iniziale
    iterator end()const;//Iteratore Finale
    //const_iterator
    const_iterator cbegin()const;//Iteratore costante iniziale
    const_iterator cend()const;//Iteratore costante finale
    void print_all()const;

};


/*Definizione ed implementazione sullo stesso file perche' e' template. */

template <typename T>
Container<T>::Container(unsigned int s)
    :size(0), capacity(s),
    buffer( new T[s]){
}
template  <typename T>
Container<T>::Container( const T& t,unsigned int s):
    size(0), capacity(s),    buffer(new T[s]){

    for(int i=0; i<capacity; i++)
        buffer[i]=t;
}
template<typename T>
Container<T>::Container(const Container<T>& a)
    : size(a.size),
      capacity(a.capacity),buffer(new T[a.capacity]){
    for(unsigned int i=0; i<size; i++)
        buffer[i]=a.buffer[i];
}
template<typename T>
Container<T>::~Container<T>(){
    if(buffer) delete[] buffer;
}

template <typename T>
Container<T>& Container<T>::operator=(const Container<T>& t){
    if(this!= &t){
        delete[] buffer;
        size=t.size;
        capacity=t.capacity;
        buffer= new T[capacity];
        for(unsigned int i=0; i<size; i++)
            buffer[i]=t.buffer[i];
    }

    return *this;
}

template<typename T>
T& Container<T>::operator[](unsigned int index){
    return buffer[index];
}

template<class T>
bool Container<T>::operator==(const Container<T> & t) const
{
    bool uguale=t.size== size && t.capacity== capacity;
    for (auto it= cbegin(), it2= t.cbegin(); it!=cend() && uguale; ++it, ++it2) {
        if(*it!=*it2)uguale=false;
    }
    return uguale;
}

template <typename T>
unsigned int Container<T>::getSize()const{
    return size;
}

template <typename T>
unsigned int Container<T>::getCapacity()const{
    return capacity;
}
template <typename T>
void Container<T>::clear(){
    delete [] buffer;
    buffer= new T[2];
    capacity=2;
    size=0;
}
template <typename T>
bool Container<T>::isEmpty()const {
    return size==0;
}
template <typename T>
T& Container<T>::front(){
    return buffer[0];
}


template< typename T>
T& Container<T>::back(){
    return buffer[size-1];
}
template  <typename T>
void Container<T>::reserve(){
    //Raddoppia la capacita' del Container
    unsigned int newCapacity= capacity*2;
    T* newBuffer= new T[newCapacity];

    for(unsigned int i=0; i<size; i++){
        newBuffer[i]= buffer[i];
    }

    capacity= newCapacity;
    delete [] buffer;
    buffer=newBuffer;
}
template<typename T>
void Container<T>::push_back(const T& t){
    if (!(size<capacity))
        reserve();
    buffer[size++]=t;

}

template<class T>
void Container<T>::pop_back()
{
    size>0 ? --size:0;
}
template <typename T>
void Container<T>::erase(unsigned int index){
    if(index>size-1) throw std::out_of_range("The index is out of range!");
    for(unsigned int i=index; i<size-1; i++ )
        buffer[i]= buffer[i+1];
    size--;

}

template <typename T>
void Container<T>::erase(unsigned int start, unsigned int end){
    if(start<0 || end<0||start >size-1 || end>size-1 || start> end ) throw std::out_of_range("Indexes are out of bounds");

    unsigned int i=start, j=1;

    for(; i<size; i++, j++)
        buffer[i]=buffer[end+j];

    size-=(end-start)+1;
}
template<class T>
void  Container<T>::erase(T which)
{
    unsigned int index=0U;
    for(auto it= begin() ; (*it)!= which && it!=end(); index++, ++it);

    return erase(index);
}
template <typename T>
T& Container<T>::at(unsigned int index){
    if(index<0 || index > size-1){
        throw std::out_of_range("The index is out of bound");

    }
    return buffer[index];
}

//*******************************ITERATOR********************************
template <typename T>
typename Container<T>::iterator Container<T>::begin()const{
    return iterator(buffer);
}

template <typename T>
typename Container<T>::iterator Container<T>::end()const{
    return iterator(buffer+(size));
}
template <typename T>
typename Container<T>::const_iterator Container<T>::cbegin()const{
    return const_iterator(buffer);
}
template <typename T>
typename Container<T>::const_iterator Container<T>::cend()const{
    return const_iterator(buffer+(size));
}
template <typename T>
void Container<T>::print_all() const {
    if(size==0) std::cout<<"Il Container e' vuoto"<<std::endl;
    for( unsigned int i=0; i< size; i++)
        std::cout<<buffer[i]<<" ";
    std::cout<<std::endl;
}
//*********************************   iterator   ********************************
template<class T>
Container<T>::iterator::iterator(T* t):punt(t){
}
template< typename T>
bool Container<T>::iterator::operator!=(const iterator& ite) const {
    return punt!=ite.punt;
}
template <typename T>
bool Container<T>::iterator::operator==(const iterator& ite)const{
    return punt==ite.punt;
}

template< typename T>
typename Container<T>::iterator& Container<T>::iterator::operator++() {
    if(punt) punt++;
    return *this;
}
template< typename T>
typename Container<T>::iterator Container<T>::iterator::operator++(int) {
    iterator aux=*this;
    if(punt) punt++;
    return aux;
}
template  <typename T>
T& Container<T>::iterator::operator*(){
    return *punt;
}

template  <typename T>
T* Container<T>::iterator::operator->(){
    return punt;
}
template <typename T>
typename Container<T>::iterator& Container<T>::iterator::operator --(){

    if(punt) punt--;
    return *this;
}

template <typename T>
typename Container<T>::iterator Container<T>::iterator::operator --(int){
    iterator aux(punt);
    if(punt) punt--;
    return aux;
}

template <typename T>
typename Container<T>::iterator& Container<T>::iterator::operator +(unsigned int i){
    if(punt) punt+=i;
    return *this;
}

template <typename T>
typename Container<T>::iterator& Container<T>::iterator::operator -(unsigned int i){
    if(punt) punt-=i;
    return *this;
}
template <typename T>
typename Container<T>::iterator& Container<T>::iterator::operator -=(unsigned int i){
    if(punt) punt-=i;
    return *this;
}

template <typename T>
typename Container<T>::iterator& Container<T>::iterator::operator +=(unsigned int i){
    if(punt) punt+=i;
    return *this;
}
//*******************************  const_iterator   *****************************
template<class T>
Container<T>::const_iterator::const_iterator(T * t):cpunt(t){
}
template< typename T>
bool Container<T>::const_iterator::operator!=(const const_iterator& ite) const {
    return cpunt!=ite.cpunt;
}
template <typename T>
bool Container<T>::const_iterator::operator==(const const_iterator& ite)const{
    return cpunt==ite.cpunt;
}

template< typename T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator++() {
    if(cpunt) cpunt++;
    return *this;
}
template< typename T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator++(int) {
    const_iterator aux=*this;
    if(cpunt) cpunt++;
    return aux;
}
template  <typename T>
const T& Container<T>::const_iterator::operator*()const{
    return *cpunt;
}

template  <typename T>
const T* Container<T>::const_iterator::operator->()const{
    return cpunt;
}
template <typename T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator --(){
    if(cpunt) cpunt--;
    return *this;
}

template <typename T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator --(int){
    const_iterator aux(cpunt);
    if(cpunt) cpunt--;
    return aux;
}

template <typename T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator +(unsigned int i){
    if(cpunt) cpunt+=i;
    return *this;
}

template <typename T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator -(unsigned int i){
    if(cpunt) cpunt-=i;
    return *this;
}
template <typename T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator -=(unsigned int i){
    if(cpunt) cpunt-=i;
    return *this;
}

template <typename T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator +=(unsigned int i){
    if(cpunt) cpunt+=i;
    return *this;
}

#endif /*Container MyDispensary*/

