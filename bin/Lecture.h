/*************************************************************************
                           Lecture  -  description
                             -------------------
    début                : 14/01
    copyright            : (C) 2022 par JOSEPH, MYCHALSKI
    e-mail               : matheo.joseph@insa-lyon.fr   ambre.mychalski@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe LECTURE> (fichier LECTURE.h) ----------------
#if ! defined ( LECTURE_H )
#define LECTURE_H
using namespace std;
#include <string>
#include <fstream>

//--------------------------------------------------- Interfaces utilisées
//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types
typedef struct   {
	 string iPAdresse ; 
	 string userLogName ;
     string userName;
     string dateHour;
     string request;
     int status;
     string dataAmount;
     string referer;
     string idClientBrowser;	 
	} Log;
//------------------------------------------------------------------------
// Rôle de la classe <LECTURE>
// Cette classe permet la lecture ligne par ligne d'un journal de LOG. A chaque lecture de ligne elle crée
// un LOG avec la ligne lue est actualise son attribut Log.
//------------------------------------------------------------------------
class Lecture 
{
//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Méthodes publiques
    bool ReadLine ();
    // Mode d'emploi :
    // Lis la prochaine ligne du journal de LOG, et actualise l'attribut LOG
    // Renvoie faux si il n'y plus de ligne à lire, et vrai sinon.

    const Log GetLog ()const;
    // Mode d'emploi :
    // Getter de l'atribut Log.


//-------------------------------------------- Constructeurs - destructeur
    Lecture ( string & fileName );
    // Mode d'emploi (constructeur) :
    // fileName correpond au nom du fichier du journal de LOG

    virtual ~Lecture ( );
    // Mode d'emploi :
    // Détruit l'objet Lecture appelant la méthode.


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
Log logAct;
ifstream stream;

};

#endif // Lecture_H