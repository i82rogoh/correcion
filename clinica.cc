#include <iostream>
#include <string>
#include <cstdlib> 
#include "clinica.h"
#include <cstdio>
#include "comprobarnumero.cc"
#include "comprobarFecha.cc"
#include "comprobarHora.cc"
#include "calcularEdad.cc"



void Clinica::addPaciente(){

    string dni, nombre, apellidos, direccion, direccionpostal,cedad,cnumerotelefono,tipopaciente,fechanacimiento;
    int edad=-8,numerotelefono=-3,opcion;
    bool comprobacion=true,comprobacion2=true;

    Paciente p("");

    cout << "Intoduce DNI del nuevo Paciente: ";
    cin >> dni;
    p.setDNI(dni);
    list <Paciente>::iterator i;
    for (i = listapacientes_.begin(); i != listapacientes_.end(); ++i) {

		if ((*i).getDNI()==p.getDNI()){
            cout << "El paciente ya existe...";
            return;
        }
    }
       
    cout << "Introduce solo el nombre del nuevo Paciente: ";
    cin >> nombre;
    cin.ignore();
    p.setNombre(nombre);
    cout << "Introduce los apellidos del nuevo Paciente: ";
    getline(cin,apellidos);
    p.setApellidos(apellidos);
    cout <<"Introduce la fecha de nacimiento del nuevo Paciente (dd/mm/yyyy): ";
    getline(cin,fechanacimiento);
    while (comprobacion){
        if(comprobarFecha(fechanacimiento)){
            p.setFechanacimiento(fechanacimiento);
            comprobacion=false;
        }
        else{
            cout << "Formato de Fecha erroneo. Formato correcto: dd/mm/yyyy\n";
            cin >> fechanacimiento;
        }
    }
    
    cout << "Introduce el numero de telefono del nuevo Paciente: ";
    cin >> cnumerotelefono;
    while (comprobacion2)
    {
        if(comprobarnumero(cnumerotelefono)){
            numerotelefono=stoi(cnumerotelefono);
            p.setNumerotelefono(numerotelefono);
            comprobacion2=false;
        }
        else
        {
            cout << "Introduzca un numero valido: ";
            cin >> cnumerotelefono;
        }
        
    }
    cout << "Que tipo de paciente es: " << "1. Sanidad Publica" <<" 2. Sanidad Privada\n";
    cin>>opcion;
    switch (opcion){
        case 1:
            tipopaciente="Sanidad Publica";
            p.setTipopaciente(tipopaciente);
            break;
    
        case 2:
            tipopaciente="Sanidad Privada";
            p.setTipopaciente(tipopaciente);
            break;
    }
    cin.ignore();
    cout << "Introduce la dirección del nuevo Paciente: ";
    getline(cin,direccion);
    p.setDireccion(direccion);
    cout << "Introduce la dirección postal del Nuevo Paciente: ";
    cin >> direccionpostal;
    p.setDireccionPostal(direccionpostal);

    listapacientes_.push_back(p);


    Historial h(p);

    string nombrefichero;
    string a="";
    nombrefichero="Historial de " + p.getDNI() + ".txt";

    ofstream fich(nombrefichero.c_str());

    fich << a;

    fich.close();

    string nombrefichero2;
    nombrefichero2="Citas de " + p.getDNI() + ".txt";

    ofstream fich2(nombrefichero2.c_str());

    fich2 << a;

    fich2.close();

    string nombrefichero3;
    nombrefichero3="Tratamientos de " + p.getDNI() + ".txt";

    ofstream fich3(nombrefichero3.c_str());

    fich3 << a;

    fich3.close();

   
}

void Clinica::getPacientes(){

    list <Paciente>::iterator it;

    for ( it = listapacientes_.begin(); it!= listapacientes_.end(); it++)
    {
        cout <<"DNI: "<< it -> getDNI() << " Nombre: " <<it ->getNombre() <<" Apellidos: "<< it -> getApellidos() << " Edad: " <<it ->getEdad() << " Fecha Nacimiento: "<< it->getFechanacimiento() << " Numero Telefono: "<< it -> getNumerotelefono() << " Tipo de paciente: "<< it -> getTipopaciente() << " Dirección: "<< it -> getDireccion() << " Direccion Postal: " <<it ->getDireccionPostal() << "\n"<<"\n";
    }
    
}

void Clinica::guardaPacientes(){

	list<Paciente>::iterator i;

	ofstream fich;

    fich.open("pacientes.txt");

	for (i = listapacientes_.begin(); i != listapacientes_.end(); ++i){
        
		fich << (*i).getDNI() << ',' << (*i).getNombre() << ',' << (*i).getApellidos() << ',' << (*i).getNumerotelefono() << ',' << (*i).getFechanacimiento() << ',' << (*i).getTipopaciente() << ',' << (*i).getDireccion() << ',' << (*i).getDireccionPostal() <<  "\n";
	}

	fich.close();
}

void Clinica::cargaPacientes(){

	listapacientes_.clear();
	string dni, nombre, apellidos, direccion, direccionpostal,cedad,cnumerotelefono,tipopaciente;
	int edad, numerotelefono;
    string fechanacimiento;

	Paciente p("");

	ifstream fich("pacientes.txt");

	while(getline(fich, dni,',')){
		getline(fich, nombre,',');
		getline(fich, apellidos,',');
        getline(fich, cnumerotelefono,',');
        getline(fich, fechanacimiento,',');
        getline(fich, tipopaciente,',');
		getline(fich, direccion,',');
		getline(fich, direccionpostal,'\n');
        numerotelefono=stoi(cnumerotelefono);

        edad=calcularEdad(fechanacimiento);

		p.setDNI(dni);
		p.setNombre(nombre);
		p.setApellidos(apellidos);
        p.setNumerotelefono(numerotelefono);
        p.setEdad(edad);
        p.setFechanacimiento(fechanacimiento);
        p.setTipopaciente(tipopaciente);
		p.setDireccion(direccion);
        p.setDireccionPostal(direccionpostal);

		listapacientes_.push_back(p);

	}

	fich.close();
}

Paciente & Clinica::getPaciente(){
    pacientesrepetidos_.clear();
    string nombre, apellidos;
    Paciente J("");
    cout << "Introduce el nombre: ";
    cin >> nombre;
    J.setNombre(nombre);
    cout << "Introduce los apellidos: ";
    cin.ignore();
    getline(cin, apellidos);
    J.setApellidos(apellidos);
    int c=0;

    list <Paciente>::iterator it;

    for (it=listapacientes_.begin(); it!=listapacientes_.end(); it++){

        if ((*it).getNombre()==J.getNombre() and (*it).getApellidos()==J.getApellidos()){

            cout << "Paciente Encontrado"<<"\n";

            //Mostrar sus cosas. Dos funciones, una como esta para todas las otras, y otra que sea solo para mostrar datos de un paciente.

            c++;

            cout <<c<<". "<<"DNI: "<< it -> getDNI() << " Nombre: " <<it ->getNombre() <<" Apellidos: "<< it -> getApellidos()<<" Fecha Nacimiento: "<<it -> getFechanacimiento() << " Edad: " <<it ->getEdad() <<  " Numero Telefono: "<< it -> getNumerotelefono() << " Tipo de paciente: "<< it -> getTipopaciente() << " Dirección: "<< it -> getDireccion() << " Direccion Postal: " <<it ->getDireccionPostal() << "\n\n";

            (*it).setIdentificador(c);
            
            pacientesrepetidos_.push_back(*it);

        }

    }

    if (c==1){

        list<Paciente>::iterator j;
        for ( j = pacientesrepetidos_.begin(); j != pacientesrepetidos_.end(); j++)
        {
            return (*j);
        }
        
    }

    if (c>1){
        int opcion;
        cout << "Que paciente es el buscado: ";
        cin >> opcion;
        list<Paciente>::iterator j;
        for ( j = pacientesrepetidos_.begin(); j != pacientesrepetidos_.end(); j++){
            if ((*j).getIdentificador()==opcion)
            {
                return (*j);
            }
            
            
        }


    }
    cout << "Paciente no encontrado";
}

void Clinica::getPaciente2(){
    pacientesrepetidos_.clear();
    string nombre, apellidos;
    Paciente J("");
    cout << "Introduce el nombre: ";
    cin >> nombre;
    J.setNombre(nombre);
    cout << "Introduce los apellidos: ";
    cin.ignore();
    getline(cin, apellidos);
    J.setApellidos(apellidos);
    int c=0;

    list <Paciente>::iterator it;

    for (it=listapacientes_.begin(); it!=listapacientes_.end(); it++){

        if ((*it).getNombre()==J.getNombre() and (*it).getApellidos()==J.getApellidos()){

            cout << "Paciente Encontrado"<<"\n";

            //Mostrar sus cosas. Dos funciones, una como esta para todas las otras, y otra que sea solo para mostrar datos de un paciente.

            c++;

            cout <<c<<". "<<"DNI: "<< it -> getDNI() << " Nombre: " <<it ->getNombre() <<" Apellidos: "<< it -> getApellidos()<<"\n";

            (*it).setIdentificador(c);
            
            pacientesrepetidos_.push_back(*it);

        }

    }

    if (c==1){

        list<Paciente>::iterator j;
        for ( j = pacientesrepetidos_.begin(); j != pacientesrepetidos_.end(); j++)
        {
            cout <<"DNI: "<< j -> getDNI() << " Nombre: " << j ->getNombre() <<" Apellidos: "<< j -> getApellidos()<<" Fecha Nacimiento: "<<j -> getFechanacimiento() << " Edad: " <<j ->getEdad() <<  " Numero Telefono: "<< j -> getNumerotelefono() << " Tipo de paciente: "<< j -> getTipopaciente() << " Dirección: "<< j -> getDireccion() << " Direccion Postal: " <<j ->getDireccionPostal() << "\n";
        }
        
    }

    if (c>1){
        int opcion;
        cout << "Que paciente es el buscado: ";
        cin >> opcion;
        list<Paciente>::iterator j;
        for ( j = pacientesrepetidos_.begin(); j != pacientesrepetidos_.end(); j++){
            if ((*j).getIdentificador()==opcion)
            {
                cout <<"DNI: "<< j -> getDNI() << " Nombre: " << j ->getNombre() <<" Apellidos: "<< j -> getApellidos()<<" Fecha Nacimiento: "<<j -> getFechanacimiento() << " Edad: " <<j ->getEdad() <<  " Numero Telefono: "<< j -> getNumerotelefono() << " Tipo de paciente: "<< j -> getTipopaciente() << " Dirección: "<< j -> getDireccion() << " Direccion Postal: " <<j ->getDireccionPostal() << "\n";
            }
            
        }

    }
    cout << "Paciente no encontrado";
}

void Clinica::modificarPaciente(){  
    int opcion;

    Paciente* J = &getPaciente();
    
    cout << "Que quieres modificar: 1. Dni, 2. Nombre, 3. Apellidos, 4. Fecha de nacimiento, 5. Numero de Telefono, 6. Tipo de Paciente, 7. Direccion, 8. Direccion Postal";

    cin >> opcion;

    switch(opcion){

        case 1:{

            string dni;
            cout << "Introduce el nuevo Dni: ";
            cin >> dni;
            
            J -> setDNI(dni);
            break;
        }

        case 2:{

            string nombre;
            cout << "Introduce el nuevo nombre: ";
            cin.ignore();
            getline(cin,nombre);
            
            J -> setNombre(nombre);
            break;
        }

        case 3:{

            string apellidos;
            cout << "Introduce los nuevos apellidos: ";
            cin.ignore();
            getline(cin,apellidos);
            
            J -> setApellidos(apellidos);
            break;
        }
        case 4:{
            string fechanacimiento;
            bool comprobacion=true;
            cout <<"Introduce la nueva fecha de nacimiento del Paciente: ";
            cin >> fechanacimiento;
            while (comprobacion){
                if(comprobarFecha(fechanacimiento)){
                    J ->setFechanacimiento(fechanacimiento);
                    comprobacion=false;
                }
                else{
                    cout << "Formato de Fecha erroneo. Formato correcto: dd/mm/yyyy\n";
                    cin >> fechanacimiento;
                }
            }
        }
        
        case 5:{
            string cnumerotelefono;
            bool comprobacion2=true;
            int numerotelefono;
            cout << "Introduce el  nuevo numero de telefono del Paciente: ";
            cin >> cnumerotelefono;
            while (comprobacion2){
                if(comprobarnumero(cnumerotelefono)){
                    numerotelefono=stoi(cnumerotelefono);
                    J->setNumerotelefono(numerotelefono);
                    comprobacion2=false;
                }
                else{
                    cout << "Introduzca un numero valido: ";
                    cin >> cnumerotelefono;
                }
        
            }
        }


        case 6:{

            string tipopaciente;
            int opcion;
            cout << "Que tipo de Paciente es: 1. Sanidad Publica 2. Sanidad Privada ";
            cin >> opcion;
            switch (opcion)
            {
            case 1:
                tipopaciente="Sanidad Publica";
                break;
            
            case 2:
                tipopaciente="Sanidad Privada";
                break;
            }
            
            J -> setTipopaciente(tipopaciente);
            break;
        }

        case 7:{

            string direccion;
            cout << "Introduce la nueva dirección: ";
            cin.ignore();
            getline(cin, direccion);
            
            J -> setDireccion(direccion);
            break;
        }

        case 8:{

            string direccionpostal;
            cout << "Introduce la nueva direccion postal: ";
            cin.ignore();
            getline(cin,direccionpostal);
            
            J -> setDireccionPostal(direccionpostal);
            break;
        }
    }

}

void  Clinica::addHistorial(){

    list<Historial>::iterator i;

    Paciente *p=&getPaciente();
    Historial h(*p);
    h.setFecha();
    string observaciones,prueba;
    cout << "Observaciones del paciente:";
    cin.ignore();
    getline(cin, observaciones);
    h.setObservaciones(observaciones);
    string nombrefichero;
    nombrefichero="Historial de " + p -> getDNI() +".txt";

    fstream fich(nombrefichero,ios::app);

	fich << h.getFecha() << ": " << h.getObservaciones() << "\n";
    
    fich.close();


}

void Clinica::getHistorial(){

    Paciente *p=&getPaciente();
    Historial h(*p);
    string nombrefichero;
    nombrefichero="Historial de " + p -> getDNI() +".txt";
    fstream fich(nombrefichero);
    string fecha,observaciones;

    while(getline(fich, fecha,' ')){
        getline(fich, observaciones,'\n');

        cout << fecha << " " << observaciones<< "\n";
    }
    
}

void Clinica::addCita(){

    Paciente *p= &getPaciente();
    bool comprobacion=true, comprobacion2=true;
    Citas c(*p);
    string fecha, motivo, hora;

    cout << "Introduce la fecha de la cita: ";
    cin >> fecha;
    while (comprobacion){
        if (comprobarFecha(fecha)){
            c.setFecha(fecha);
            comprobacion=false;
        }
        else{
            cout << "Formato de fecha incorrecto. Formato correcto: dd/mm/yyyy\n";
            cin >> fecha;
        } 
    }

    cout <<"Introduce la hora de la cita: ";
    cin >> hora;
    while (comprobacion2){
        if (comprobarHora(hora)){
            c.setHora(hora);
            comprobacion2=false;
        }
        else{
            cout << "Formato de hora incorrecto. Formato correcto: hh:mm";
            cin >> hora;
        } 
    }

    cout << "Introduce el motivo de la cita: ";
    cin.ignore();
    getline(cin,motivo);
    c.setMotivo(motivo);

    listacitas_.push_back(c);


}

void Clinica::guardaCitas(){

    list<Paciente>::iterator i;


	for (i = listapacientes_.begin(); i != listapacientes_.end(); ++i){

        string nombrefichero = "Citas de " + (*i).getDNI() +".txt";
	    ofstream fich(nombrefichero);
        int c = 0;

        list <Citas>::iterator j;

        for (j = listacitas_.begin(); j!= listacitas_.end(); j++){   
            if (((*j).getPacientecita()).getDNI()==(*i).getDNI()){
                c++;
                fich << c << '.' << (*j).getHora() <<"," << (*j).getFecha() << ":" << (*j).getMotivo()<<'\n';
            }
        }
        fich.close();
		
	}

}

void Clinica::cargaCitas(){

    listacitas_.clear();

    list<Paciente>::iterator i;
	for (i = listapacientes_.begin(); i != listapacientes_.end(); ++i){

        string nombrefichero = "Citas de " + (*i).getDNI() +".txt";
	    fstream fich(nombrefichero);
        Citas c((*i));

        list <Citas>::iterator j;
        string fecha, motivo, identificador,hora;
        

        while(getline(fich, identificador,'.')){
            getline(fich, hora,',');
            getline(fich,fecha,':');
		    getline(fich, motivo,'\n');
            c.setIdentificador(identificador);
            c.setFecha(fecha);
            c.setHora(hora);
            c.setMotivo(motivo);

            listacitas_.push_back(c);
        }
    }
}

void Clinica::citasPaciente(){

    list<Citas>::iterator i;

    Paciente *p= &getPaciente();

    for (i = listacitas_.begin(); i != listacitas_.end(); ++i){

        if (((*i).getPacientecita()).getDNI()==(*p).getDNI()){

            cout << (*i).getFecha() <<" a las "<<(*i).getHora() << ": " << (*i).getMotivo()<<"\n";
        }
    }

}

void Clinica::citasDia(){

    Paciente x("");
    Historial h(x); //Para poder seleccionar la fecha del dia que se comprueba. no me deja incluir la funcion en los dos archivos...
    h.setFecha(); 

    list<Citas>::iterator i;

    for (i = listacitas_.begin(); i != listacitas_.end(); ++i){

        if ((*i).getFecha()==h.getFecha()){

            cout << ((*i).getPacientecita()).getDNI() <<((*i).getPacientecita()).getNombre()<< " " << ((*i).getPacientecita()).getApellidos()<<" a las "<< (*i).getHora() << ": " << (*i).getMotivo()<<"\n";
        }
    }
}

void Clinica::modificarCitas(){
    Paciente *p=&getPaciente();
    Citas c(*p);
    string sopcion, fecha, hora;
    int opcion;
    
    list<Citas>::iterator i;

    for (i = listacitas_.begin(); i != listacitas_.end(); ++i){

        if (((*i).getPacientecita()).getDNI() == (c.getPacientecita()).getDNI()){

            cout << (*i).getIdentificador() << ". " << (*i).getFecha()<< " a las "<< (*i).getHora() << ": " << (*i).getMotivo()<<"\n";
           
        }
    }
    cout << "¿Que cita quieres modificar?: ";
    cin >>sopcion;
    list<Citas>::iterator j;

    for (j = listacitas_.begin(); j != listacitas_.end(); ++j){

        if (((*j).getPacientecita()).getDNI() == (c.getPacientecita()).getDNI() and sopcion==(*j).getIdentificador()){

            cout << "Que quieres modificar: 1. Fecha, 2. Hora, 3. Motivo";
            cin >> opcion;

            switch (opcion)
            {
                case 1:{
                    bool comprobacion=true;
                    cout << "Introduce la nueva fecha de la cita: ";
                    cin >> fecha;
                    while (comprobacion){
                        if (comprobarFecha(fecha)){
                            j -> setFecha(fecha);
                            comprobacion=false;
                        }
                        else{
                            cout << "Formato de fecha incorrecto. Formato correcto: dd/mm/yyyy\n";
                            cin >> fecha;
                        } 
                    }
                    break;
                } 

                case 2:{
                    bool comprobacion2=true;
                    cout << "Introduce la nueva hora de la cita: ";
                    cin >> hora;
                    while (comprobacion2){
                        if (comprobarHora(hora)){
                            j -> setHora(hora);
                            comprobacion2=false;
                        }
                        else{
                            cout << "Formato de hora incorrecto. Formato correcto: hh:mm";
                            cin >> fecha;
                        } 
                    }
                    break;
                } 
                
                case 3:{
                    string motivo;
                    cout << "Introduce el nuevo motivo: ";
                    cin.ignore();
                    getline(cin, motivo);
                    j -> setMotivo(motivo);
                    break;
                }
            }
        }
    }
}

void Clinica::eliminarCitas(){
    Paciente *p=&getPaciente();
    Citas c(*p);
    string sopcion, fecha;
    int opcion;
    
    list<Citas>::iterator i;

    for (i = listacitas_.begin(); i != listacitas_.end(); ++i){

        if (((*i).getPacientecita()).getDNI() == (c.getPacientecita()).getDNI()){

            cout << (*i).getIdentificador() << ". " << (*i).getFecha()<<" a las "<<(*i).getHora() << ": " << (*i).getMotivo()<<"\n";
           
        }
    }

    cout << "¿Que cita quieres eliminar?: ";
    cin >>sopcion;
    list<Citas>::iterator j;
    int k;
    //Hay que hacerlo asi porque al estar recorriendo la lista y borrar un elemento se descuadra.
    j= listacitas_.begin();                                       
    for (k = 0; k < listacitas_.size() && j != listacitas_.end(); ++j){

        if (((*j).getPacientecita()).getDNI() == (c.getPacientecita()).getDNI() and sopcion==(*j).getIdentificador()){

            j=listacitas_.erase(j);
        }
    }

}

void Clinica::addTratamiento(){

    Paciente *p= &getPaciente();
    
    Tratamientos t(*p);
    string medicamentos, dosis, regularidad, fechainicio, fechafin;
    bool comprobacion=true, comprobacion2=true;
    
    cout << "Introduce el medicamento: ";
    cin.ignore();
    getline(cin,medicamentos);
    t.setMedicamentos(medicamentos);

    cout << "Introduce la dosis: ";
    getline(cin,dosis);
    t.setDosis(dosis);

    cout << "Introduce la regularidad: ";
    getline(cin,regularidad);
    t.setRegularidad(regularidad);

    cout << "Introduce la fecha de inicio: ";
    cin >> fechainicio;
    while (comprobacion){
        if (comprobarFecha(fechainicio)){
            t.setFechainicio(fechainicio);
            comprobacion=false;
        }
        else{
            cout << "Formato de fecha incorrecto. Formato correcto: dd/mm/yyyy\n";
            cin >> fechainicio;
        } 
    }
    cout << "Introduce la fecha final: ";
    cin >> fechafin;
    while (comprobacion2){
        if (comprobarFecha(fechafin)){
            t.setFechafinal(fechafin);
            comprobacion2=false;
        }
        else{
            cout << "Formato de fecha incorrecto. Formato correcto: dd/mm/yyyy\n";
            cin >> fechafin;
        } 
    }

    listatratamientos_.push_back(t);
}

void Clinica::guardaTratamientos(){

    list<Paciente>::iterator i;


	for (i = listapacientes_.begin(); i != listapacientes_.end(); ++i){

        string nombrefichero = "Tratamientos de " + (*i).getDNI() +".txt";
	    ofstream fich(nombrefichero);
        int c = 0;

        list <Tratamientos>::iterator j;

        for (j = listatratamientos_.begin(); j!= listatratamientos_.end(); j++){ 
            if (((*j).getPacientetratamiento()).getDNI()==(*i).getDNI()){
                c++;
                fich << c << '.' <<(*j).getMedicamentos() << "," << (*j).getDosis()<<','<<(*j).getRegularidad()<<','<<(*j).getFechainicio() << ',' << (*j).getFechafinal() <<'\n';
            }
        }
        fich.close();
		
	}

}

void Clinica::cargaTratamientos(){

    listatratamientos_.clear();

    list<Paciente>::iterator i;
	for (i = listapacientes_.begin(); i != listapacientes_.end(); ++i){

        string nombrefichero = "Tratamientos de " + (*i).getDNI() +".txt";
	    fstream fich(nombrefichero);
        Tratamientos t((*i));

        list <Tratamientos>::iterator j;
        string medicamentos, dosis, regularidad, fechainicio, fechafinal, identificador;
        

        while(getline(fich, identificador,'.')){
            getline(fich, medicamentos,',');
		    getline(fich, dosis,',');
            getline(fich, regularidad,',');
		    getline(fich, fechainicio,',');
            getline(fich, fechafinal,'\n');
            t.setIdentificador(identificador);
            t.setMedicamentos(medicamentos);
            t.setDosis(dosis);
            t.setRegularidad(regularidad);
            t.setFechainicio(fechainicio);
            t.setFechafinal(fechafinal);

            listatratamientos_.push_back(t);
        }
    }
}

void Clinica::tratamientosPaciente(){

    list<Tratamientos>::iterator i;

    Paciente *p= &getPaciente();

    for (i = listatratamientos_.begin(); i != listatratamientos_.end(); ++i){

        if (((*i).getPacientetratamiento()).getDNI()==(*p).getDNI()){

            cout <<"Medicamento: "<< (*i).getMedicamentos() << " Dosis: " << (*i).getDosis()<< " Regularidad: " << (*i).getRegularidad() << " Fecha Inicio: "<< (*i).getFechainicio()<< " Fecha Final: " << (*i).getFechafinal() <<"\n";
        }
    }

}


void Clinica::eliminarTratamiento(){
    Paciente *p=&getPaciente();
    Tratamientos t(*p);
    string sopcion, fecha;
    int opcion;
    
    list<Tratamientos>::iterator i;

    for (i = listatratamientos_.begin(); i != listatratamientos_.end(); ++i){

        if (((*i).getPacientetratamiento()).getDNI() == (t.getPacientetratamiento()).getDNI()){

            cout << (*i).getIdentificador() << ". " <<"Medicamento: "<< (*i).getMedicamentos() << " Dosis: " << (*i).getDosis()<< " Regularidad: " << (*i).getRegularidad() << " Fecha Inicio: "<< (*i).getFechainicio()<< " Fecha Final: " << (*i).getFechafinal() <<"\n";
           
        }
    }

    cout << "¿Que tratamiento quieres eliminar?: ";
    cin >>sopcion;
    list<Tratamientos>::iterator j;
    int k;
    
    j= listatratamientos_.begin();                                       
    for (k = 0; k < listatratamientos_.size() && j != listatratamientos_.end(); ++j){

        if (((*j).getPacientetratamiento()).getDNI() == (t.getPacientetratamiento()).getDNI() and sopcion==(*j).getIdentificador()){

            j=listatratamientos_.erase(j);
        }
    }

}
    
   




