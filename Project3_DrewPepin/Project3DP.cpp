#include <Python.h>
#include <iostream>
#include <iomanip>
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

void CallProcedure(string pName)
{
    char* procname = new char[pName.length() + 1];
    std::strcpy(procname, pName.c_str());

    Py_Initialize();
    PyObject* my_module = PyImport_ImportModule("PythonFile");
    PyErr_Print();
    PyObject* my_function = PyObject_GetAttrString(my_module, procname);
    PyObject* my_result = PyObject_CallObject(my_function, NULL);
    Py_Finalize();

    delete[] procname;
}



int callIntFunc(string proc, string param)
{
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());

    char* paramval = new char[param.length() + 1];
    std::strcpy(paramval, param.c_str());


    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    // Build the name object
    pName = PyUnicode_FromString((char*)"PythonFile");
    // Load the module object
    pModule = PyImport_Import(pName);
    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference 
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc))
    {
        pValue = Py_BuildValue("(z)", paramval);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else
    {
        PyErr_Print();
    }
    //printf("Result is %d\n", _PyLong_AsInt(presult));
    Py_DECREF(pValue);
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    // Finish the Python Interpreter
    Py_Finalize();

    // clean 
    delete[] procname;
    delete[] paramval;


    return _PyLong_AsInt(presult);
}



int callIntFunc(string proc, int param)
{
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());

    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    // Build the name object
    pName = PyUnicode_FromString((char*)"PythonFile");
    // Load the module object
    pModule = PyImport_Import(pName);
    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference 
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc))
    {
        pValue = Py_BuildValue("(i)", param);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else
    {
        PyErr_Print();
    }
    //printf("Result is %d\n", _PyLong_AsInt(presult));
    Py_DECREF(pValue);
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    // Finish the Python Interpreter
    Py_Finalize();

    // clean 
    delete[] procname;

    return _PyLong_AsInt(presult);
}



void Menu() {

    //variables
    int menuLoop = 0;
    int wordCount = 0;
    int itemQuantity = 0;
    //string for user search term                           
    string searchTerm;
    //string for item from frequency file                                                      
    string itemName;
    ifstream fileInput;

    while (menuLoop != 4) {

        //getting user input
        std::cout << "[1] Calculate the number of times each item appears" << std::endl;
        std::cout << "[2] Calculate the frequency of a specific item" << std::endl;
        std::cout << "[3] Create a histogram based on the number of appearances of each item" << std::endl;
        std::cout << "[4] Quit" << std::endl;

        std::cin >> menuLoop;

        //validating user input
        while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please input a valid selection: ";
            std::cin >> menuLoop;
        }


        //switch statement for user input
        switch (menuLoop) {


            //calculate / print the number of times each item appears
        case 1:
            system("CLS");
            //call python function CountAll                                         
            CallProcedure("CountAll");
            std::cout << std::endl;
            break;

            //calculate / print the number of times a specific item appears
        case 2:
            //clear
            system("CLS");
            std::cout << "What item would you like to search for?" << std::endl;
            std::cin >> searchTerm;

            //call Python function CountInstances with user search term
            wordCount = callIntFunc("CountInstances", searchTerm);

            //print found word count
            std::cout << std::endl << searchTerm << " : " << wordCount << std::endl << std::endl;

            break;

            //print a histogram based on how many times each item appears
        case 3:
            system("CLS");
            //call CollectData                                        
            CallProcedure("CollectData");

            fileInput.open("frequency.dat");

            fileInput >> itemName;
            fileInput >> itemQuantity;

            //for each line in the file, print a histogram, then break
            while (!fileInput.fail()) {
                //set text color to the default white

                //print item name
                std::cout << std::setw(14) << std::left << itemName << std::setw(6);

                //print itemQuantity number of stars
                for (int i = 0; i < itemQuantity; i++) {

                    //print green stars in line.
                    std::cout << std::right << "*";
                }

                std::cout << std::endl;
                fileInput >> itemName;
                fileInput >> itemQuantity;
            }

            //close frequency.dat
            fileInput.close();
            break;
            //quit the program.
        case 4:
            return;

            //default case
        default:
            std::cout << "Please input a valid selection.";
            std::cout << std::endl;
            break;
        }
    }
}

//main - call menu function
void main()
{
    //Draw the user menu.
    Menu();

}