/*************************************************************************
                           Lecture  -  description
                             -------------------
    début                : 14/01
    copyright            : (C) 2022 par JOSEPH, MYCHALSKI
    e-mail               : matheo.joseph@insa-lyon.fr   ambre.mychalski@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe LECTURE> (fichier LECTURE.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <cstring>
#include <stdlib.h>

//------------------------------------------------------ Include personnel
#include "Lecture.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

// Algorithme : aucun
bool Lecture::ReadLine ()
{   
    string temp;
    
        getline(stream,logAct.iPAdresse,' ');
        //Si il n'y a plus de ligne à lire
        if(logAct.iPAdresse.size()==0)
        {
            return false;
        }
        getline(stream,logAct.userLogName,' ');
        getline(stream,logAct.userName,' ');
        stream.get();
        getline(stream,logAct.dateHour,']');
        stream.get();
        stream.get();
        getline(stream,logAct.request,'"');
        stream.get();
        getline(stream,temp,' ');
        logAct.status=atoi( temp.c_str() );
        getline(stream,logAct.dataAmount,' ');
        stream.get();
        getline(stream,logAct.referer,'"');
        stream.get();
        stream.get();
        getline(stream, logAct.idClientBrowser, '"');
        getline(stream, temp, '\n'); 
        return true;
    
}//----- Fin de Méthode

// Algorithme : aucun
const Log Lecture::GetLog()const
{
    return logAct;
}//----- Fin de Méthode


//-------------------------------------------- Constructeurs - destructeur

// Algorithme : aucun
Lecture::Lecture ( string & fileName  )
{
    stream.open(fileName.c_str());

    if(!stream){
        cerr<<"Problème à l'ouverture du fichier .log"<<endl;
        exit(1);
    }

#ifdef MAP
    cout << "Appel au constructeur de Lecture" << endl;
#endif
}//----- Fin de Méthode

// Algorithme : aucun
Lecture::~Lecture ( )
{
#ifdef MAP
    cout << "Appel au destructeur de Lecture" << endl;
#endif
} //----- Fin de Méthode
