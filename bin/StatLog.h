/*************************************************************************
                           StatLog  -  description
                             -------------------
    début                : 14/01
    copyright            : (C) 2022 par JOSEPH, MYCHALSKI
    e-mail               : matheo.jospeh@insa-lyon.fr   ambre.mychalski@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe StatLog (fichier StatLog.h) ----------------
#if ! defined ( StatLog_H )
#define StatLog_H

using namespace std;
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe StatLog :
// Gère les demandes liées au fichier de LOG. 
// Gère le stockage des LOG, les statistiques et les graphes liés aux demandes de l'utilisateur.
//
//------------------------------------------------------------------------

class StatLog 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void AddLog ( string target, string referer );
    // Mode d'emploi :
    // Ajoute un log à mapLog

    void MakeGraph ( string fileName );
    // Mode d'emploi :
    // Crée et rempli le fichier .dot avec les informations de l'attribut mapLog

    void PrintStats ( );
    // Mode d'emploi :
    // Affiche dans le terminal le top 10 des cibles les plus populaires

    int GetIndex (vector<string>& v, string name);
    // Mode d'emploi :
    // Renvoie l'index d'une string donnée, dans un vecteur de string

//-------------------------------------------- Constructeurs - destructeur
    StatLog ( );
    // Mode d'emploi :
    // Construit l'objet StatLog

    virtual ~StatLog ( );
    // Mode d'emploi :
    // Détruit l'objet StatLog appelant

protected:
//----------------------------------------------------- Attributs protégés

map < string , pair <map < string , int >, int >> mapLog;

};

#endif // StatLog_H

