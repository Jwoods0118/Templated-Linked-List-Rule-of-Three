#ifndef VECTOR_CPP
#define VECTOR_CPP

#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

template <class T> 
struct Node {
public:
  Node(T value) {
    m_value = value;
    next = nullptr;
  }
  
  Node(T value, Node* _next) {
    m_value = value;
    next = _next;
  }
  
  T getValue() {
    return m_value;
  }
  
  Node<T>* getNextNode() {
    return next;
  }
  
  void setNextNode(Node<T>* newNode) {
    next = newNode;
  }
  
private:
  T m_value;
  Node<T>* next;
};


template <class T>
class Vector {
public:
  // Name: Default Constructor
  // Precondition: None (Must be templated)
  // Postcondition: Creates a vector using a linked list
  Vector(){
    m_head = nullptr;
  }
   
  // Name: Destructor
  // Desc: Frees memory
  // Precondition: Existing Vector
  // Postcondition: Destructs existing Vector
  ~Vector(){
    //Goes through each node and deletes/sets each m_head to nullptr
    Node<T>* curr = m_head;
    while (curr != nullptr){
      m_head = curr;
      curr = curr->getNextNode();
      delete m_head;
      m_head = nullptr;
    }
  }
  
  // Name: Copy Constructor
  // Desc: Copies an existing vector
  // Precondition: Existing Vector
  // Postcondition: Two identical vectors (in separate memory spaces)
  // Hint: Utilize overloaded [] operator
  Vector (Vector<T>* const& source){
    //Inserts using overloaded operator
    for( unsigned int i = 0; i < source->size(); i++){
      Insert(source->operator[](i));
    }
  }

  
  // Name: Overloaded Assignment operator
  // Desc: Assingns a vector
  // Precondition: Existing Vector
  // Postcondition: Assigns a vector
  // Hint: Utilize overloaded [] operator
  Vector<T>* operator=(Vector<T>* source){
    if(this != source){
      //Inserts/assigns by iterating
      for(int i = 0; i < source->Size(); i++){
      Insert(source->operator[](i));
      }
    }
    return this;
  } 
  
  // Name: Overloaded [] operator
  // Desc: to retrive use [indx]
  // Precondition: Existing Vector
  // Postcondition: Returns the value of the element at the given index
  T operator[](int indx){
    int count = 0;
    Node<T> *temp = m_head;
    //while loop to iterate through until index is found
    while(count != indx){
      temp = temp->getNextNode();
      count++;
    }
    //when index is found, return the value of the node at the given index
    return temp->getValue();
  } 
  // Name: Insert
  // Desc: insert a node to the end of the vector
  // Precondition: Existing Vector
  // Postcondition: A vector with the newly added value
  void Insert(T data){
    //if only one node
    if (m_head == nullptr){
      m_head = new Node<T>(data);
    }
    //multiple nodes
      Node<T> *curr = m_head;
      while (curr->getNextNode() != nullptr){
	curr = curr->getNextNode(); 
      }
      curr->setNextNode(new Node<T>(data));
  }
  

    
  // Name: SortedInsert
  // Desc: Inserts a node into the vector at it's correct position (sorted ascendingly)
  // Precondition: Existing Vector
  // Postcondition: sorted vector (low to high)
  void SortedInsert(T data){
    //if only one node
    if (m_head == nullptr){
      m_head = new Node<T>(data);
    }
    //multiple nodes
    Node<T> *curr = m_head;
    while (curr->getNextNode() != nullptr){
      curr = curr->getNextNode();
    }
    curr->setNextNode(new Node<T>(data));
  }

      
  // Name: Remove
  // Desc: removes a node from the vector
  // Precondition: Existing Vector
  // Postcondition: A vector that holds the results of the vectors added
  void Remove(int indx){
    int position = 0;
    Node<T> *curr = m_head;
    //iterate through until one position before
    while (position != indx - 1){
      curr = curr->next;
      position++; 
  }
    //need set temp as the node being remove, then set curr to node after temp to relink
    Node<T> *temp = curr->getNextNode();
    curr->setNextNode(temp->getNextNode());
    delete temp;
  }
  
  // Name: Overloaded + operator | Vector Addition
  // Desc: Adds two vectors and returns the result
  // Precondition: Existing Vector, vectors can be of different size
  // Postcondition: A vector that holds the results of the vectors added
  Vector<T>* operator+(Vector<T>& source){
    Vector<T>* resultVector = new Vector<T>();
    //when + is used, operator calculates and returns value
    for (int i = 0; i < Size(); i++){
      resultVector->Insert(operator[](i) + source[i]);
    }
    return resultVector; 
 } 
  // Name: Overloaded * operator | Vector Multiplication
  // Desc: Multiplys two vectors and returns the result
  // Precondition: Existing Vector, vectors can be of different size
  // Postcondition: returns a vector that holds the results of the vectors multiplied
  Vector<T>* operator*(Vector<T>& other){
    //When * is used, operator calculates and returns value
    Vector<T>* resultVector = new Vector<T>();
    for (int i = 0; i < Size(); i++){
      resultVector->Insert(operator[](i) * other[i]);
    }
    return resultVector;
  }
    
  // Name: Overloaded < operator | Vector Comparision
  // Desc: Compares two vectors [using the < operator] and returns the result
  // Precondition: Existing Vector -> vectors need to be of the same size
  // Postcondition: returns a vector that holds the boolean char (T or F) value of each node comparison
  Vector<char>* operator<(Vector<T>& other){
    Vector<char>* resultVector = new Vector<char>();
    //When < is used, operator compares and return a bool
    //iterate throught the linked list and compare nodes
    for (int i = 0; i < Size(); i++){
	if(operator[](i) < other[i]){
	  resultVector->Insert('T');
	}
	else{
	  resultVector->Insert('F');
	}
    }
    return resultVector;
  }
      
  // Name: Overloaded == operator | Vector Comparision
  // Desc: Compares two vectors [using the == operator] and returns the result
  // Precondition: Existing Vector, vectors need to be of the same size
  // Postcondition: returns a vector that holds the boolean char (T or F) value of each node comparison
  Vector<char>* operator==(Vector<T>& other){
    Vector<char>* resultVector = new Vector<char>();
    //when == is used, operator compares and returns a bool
    //iterate throught the linked list and compare nodes
    for (int i = 0; i < Size(); i++){
      if(operator[](i) == other[i]){
	resultVector->Insert('T');
      }
      else{
	resultVector->Insert('F');
      }
    }
    return resultVector;
  }
    
  // Name: Size
  // Desc: number of nodes in Vector
  // Precondition: Existing Vector
  // Postcondition: returns the size of the vector
  int Size(){
    int count = 0;
    Node<T> *curr = m_head;
    //iterate linked list and add one for each node, return total(count)
    while(curr != nullptr){
      count++;
      curr = curr->getNextNode();
    }
    return count;
  }
    
  // Name: Display
  // Desc: displays the contents of the vector
  // Precondition: Existing Vector
  // Postcondition: prints to console the contents of Vector
  void Display(){
      
  Node<T> *temp = m_head;
  //iterate linked list and print each node
  while(temp != nullptr){
    cout << temp->getValue() << " ";
    temp = temp->getNextNode();
  }
  cout << endl;
 }
  private:
    Node<T>* m_head;
};
