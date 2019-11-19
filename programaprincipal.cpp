#include <fstream>
#include <list>
#include "clinica.h"
#include <iostream>

using namespace std;
int main(){
    Clinica m;
	int opcion=0;
	m.cargaPacientes();
	m.cargaCitas();
	m.cargaTratamientos();
	//Dividir los switch en paciente, citas, tratamientos e historial. Formato para fecha.
	string respuesta;
	cout << "\nOpciones a elegir: \n\n" << "1. Añadir Paciente " << "2. Mostrar Pacientes " << "3. modificar Paciente " <<" 4. Buscar un paciente por nombre y apellidos"<< " 5. Escribir en el historial " << "6. Ver Historial" << " 7. Añadir Cita " << "8.Ver Citas de un Paciente " << "9.Ver citas del dia " << "10.Modificar Citas" << " 11. Eliminar Citas" << "12. Añadir Tratamiento " << "13. Ver Tratamientos de un paciente " << "14. Eliminar un tratamiento\n";

	cin >> opcion;

	while (opcion !=15){

		switch(opcion){

			case 1: m.addPaciente(); 
					m.guardaPacientes();
					m.cargaPacientes();
					break;

			case 2: m.getPacientes();
					break;

			case 3: m.modificarPaciente();
					m.guardaPacientes();
					break;
			case 4: m.getPaciente2();
					break;
			case 5: m.addHistorial();
					break;
			case 6: m.getHistorial();
					break;
			case 7: m.addCita();
					m.guardaCitas();
					m.cargaCitas();
					break;
			case 8: m.citasPaciente();
					break;
			case 9: m.citasDia();
					break;
			case 10: m.modificarCitas();
					m.guardaCitas();
					m.cargaCitas();
					break;
			case 11: m.eliminarCitas();
					 m.guardaCitas();
					 m.cargaCitas();
					 break;
			case 12: m.addTratamiento();
					 m.guardaTratamientos();
					 m.cargaTratamientos();
					 break;
			case 13: m.tratamientosPaciente();
					 break;
			case 14: m.eliminarTratamiento();
					 m.guardaTratamientos();
					 m.cargaTratamientos();
					 break;
		}
        cout << "\n¿Quiere Continuar?(Si/No) ";
		cin >> respuesta;
		if (respuesta == "Si" or respuesta=="SI" or respuesta == "si" or respuesta=="sI"){
			cout << "\nOpciones a elegir: \n\n" << "1. Añadir Paciente " << "2. Mostrar Pacientes " << "3. modificar Paciente " <<" 4. Buscar un paciente por nombre y apellidos"<< " 5. Escribir en el historial " << "6. Ver Historial" << " 7. Añadir Cita " << "8.Ver Citas de un Paciente " << "9.Ver citas del dia " << "10.Modificar Citas" << " 11. Eliminar Citas" << "12. Añadir Tratamiento " << "13. Ver Tratamientos de un paciente " << "14. Eliminar un tratamiento\n";
			cin >> opcion;
		}
		else{
			//m.guardaPacientes();
			opcion=15;
		}
				   
	}
			
}