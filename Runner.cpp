#ifndef RUNNER_CPP
#define RUNNER_CPP

#include <cstdlib>
#include "Vector.cpp"
using namespace std;


template <class T>
class Runner {
public:
    // Name: Default Constructor
    // Precondition: None
    // Postcondition: Initiates state/environment
  Runner(Vector<T>*, Vector<T>*);
    
    // Name: mainMenu
    // Desc: Main Menu
    // Precondition: Existing Vectors
    // Postcondition: Handles various menu commands
  int mainMenu(){
    int choice;
    cout << "Choose an option" << endl;
    cout << "1. Display Vectors" << endl;
    cout << "2. Vector comparison (<)" << endl;
    cout << "3. Vector comparison (==)" << endl;
    cout << "4. Vector addition" << endl;
    cout << "5. Vector multiplication" << endl;
    cout << "6. Exit" << endl;
    cin >> choice;

    if (choice == 1){
      cout << "Vector1: ";
      m_vector1.Display();
      cout << "Vector2: ";
      m_vector2.Display();
      return choice;
    }

    else if (choice == 2){
      Vector<char>* resultVec = m_vector1 < m_vector2;
      cout << "Vector1 < Vector2: ";
      resultVec->Display(); 
      delete resultVec;
      return choice;
    }

    else if (choice == 3){
      Vector<char>* resultVec = m_vector1 == m_vector2;
      cout << "Vector1 == Vector2: ";
      resultVec->Display();
      delete resultVec;
      return choice;
    }

    else if(choice == 4){
      Vector<T>* resultVec = m_vector1 + m_vector2;
      cout << "Vector1 + Vector2: ";
      resultVec->Display();
      delete resultVec;
      return choice;
    }

    else if (choice == 5){
      Vector<T>* resultVec = m_vector1 * m_vector2;
      cout << "Vector1 * Vector2: ";
      resultVec->Display();
      delete resultVec;
      return choice;
    }
      
private:
    Vector<T> m_vector1;
    Vector<T> m_vector2;
};


template<class T>
Runner<T>::Runner(Vector<T>* vector1, Vector<T>* vector2){
  int choice;
  m_vector1 = vector1;
  m_vector2 = vector2;
  do{
    choice = mainMenu();
  }
  while(choice != 9);
}






#endif /* Runner_h */


