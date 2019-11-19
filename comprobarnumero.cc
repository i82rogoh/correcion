#include <ctime>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;


bool comprobarnumero(string numero){

    int i;

    for ( i = 0; i < numero.size(); i++)
    {
        if(isdigit(numero[i])){

        }
        else
        {
            return false;
        }
        
    }

    return true;
}

