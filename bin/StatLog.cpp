/*************************************************************************
                           StatLog  -  description
                             -------------------
    début                : 14/01
    copyright            : (C) 2022 par JOSEPH, MYCHALSKI
    e-mail               : matheo.joseph@insa-lyon.fr   ambre.mychalski@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe STATLOG (fichier STATLOG.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "StatLog.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

// Algorithme : 
// Vérifie si la target est déja présente dans la map :
//    -Si oui, vérifie si le referer est déja présent dans la sous map de la target:
//          -Si oui, incrémente le nombre de hits.
//          -Si non, ajoute le referer à la sous map et met le nombre de hit de ce referer à 1
//    -Si non, ajoute la target à la map, puis ajoute le referer à la sous map de la target,
//      et met le nombre de hit de ce referer à 1
//  Puis incrémente la somme totale de hit de la target de 1.
void StatLog::AddLog ( string target, string referer )
{
    map < string , pair <map < string , int >, int >>::iterator itMapLog;
    map <string, int> mapLink;

    itMapLog = mapLog.find(target);
    if (itMapLog == mapLog.end())
    {        
        
        pair <map < string , int >, int > pairLink;

        mapLink[referer]=1;
        pairLink = make_pair(mapLink,1);
        mapLog[target]= pairLink;
    }
    else
    {
       
        map < string , int >::iterator itMapLink;
        itMapLink = itMapLog->second.first.find(referer);   // vérfie si le Referer existe

        if(itMapLink==itMapLog->second.first.end())     // si le Referer n'existe pas, on le crée
        {
            itMapLog->second.first[referer]=1;
        }
        else    // si le Referer existe, on incrémente les hits
        {
            itMapLink->second++;
        }
        itMapLog->second.second++; // incrémenter la somme
    }

}
//----- Fin de Méthode


// Algorithme : 
// Créer un vecteur de string
// Parcourt l'attribut mapLog
// Pour chaque target:
//      Vérifie si elle est présente dans le vecteur
//          -Si non alors ajoute la target au vecteur
//      Pour chaque referer de la target:
//          Vérifie si il est présent dans le vecteur
//              -Si non alors ajoute le referer au vecteur
//
// Parcours le vecteur puis nomme dans le fichier .dot chaque noeud par son index dans le vecteur
// et le label de chaque noeud prend la valeur du nom du referer ou de la target contenu dans le vecteur
//
// On reparcourt ensuite l'attribut mapLog afin d'identifier chaque lien entre les noeuds
void StatLog::MakeGraph ( string fileName )
{
    // Vérifie que le nom du fichier .dot est valide
    size_t pos = fileName.find(".dot");
    if (pos == std::string::npos)
    {
        // Si le nom du fichier ne contient pas d'extension .dot 
        cerr<<"Nom du fichier .dot non fourni"<<endl;
        exit(1);
    }

    map < string , pair <map < string , int >, int >> :: iterator itMapLog;
    map < string , int >:: iterator itMapLink;

    vector<string> v;
    vector<string>::iterator itV;

    ofstream os (fileName);

    for(itMapLog=mapLog.begin() ; itMapLog != mapLog.end() ; itMapLog++)
    {
        itV= find(v.begin(), v.end(), itMapLog->first);
        // Si le noeud n'est pas présent dans notre Vecteur de noeud : on l'ajoute
        if (itV == v.end())
        {     
           v.push_back(itMapLog->first);
        }

        for(itMapLink = itMapLog->second.first.begin() ; itMapLink !=itMapLog->second.first.end() ; itMapLink++ )
        {
            itV= find(v.begin(), v.end(), itMapLink->first);
            // Si le noeud n'est pas présent dans notre Vecteur de noeud : on l'ajoute
            if (itV == v.end())
            {     
                v.push_back(itMapLink->first);
            } 
        }
    }

    // Ajout des noeuds avec label sur le fichier .dot
    os<<"digraph {"<<endl;
    for(itV = v.begin() ; itV !=v.end() ; itV++ )
    {
        os<<(itV - v.begin())<<" [label="<<'"'<<*itV<<'"'<<"];"<<endl;
    }

    // Ajout des liens sur le fichier .dot
    for(itMapLog=mapLog.begin() ; itMapLog != mapLog.end() ; itMapLog++)
    {
        for(itMapLink = itMapLog->second.first.begin() ; itMapLink !=itMapLog->second.first.end() ; itMapLink++ )
        {
            os<<GetIndex(v,itMapLink->first);
            os<<" -> ";
            os<<GetIndex(v,itMapLog->first);
            os<<" [label="<<'"'<<itMapLink->second<<'"'<<"];"<<endl;
        }
    }
    os<<"}"<<endl;    
}
//----- Fin de Méthode

// Algorithme : aucun
void StatLog::PrintStats ( )
{
    // Création d'une nouvelle map dont la clef est le nombre de hits.
    multimap <int, string,greater<int>> mapTop10;

    multimap <int, string> :: iterator itmapTop10;
    multimap <int, string> :: const_iterator itPrint;

    map < string , pair <map < string , int >, int >> :: const_iterator itMapLog;

    // Ajout de toutes les targets et leurs nombre de hits associés dans mapTop10
    for(itMapLog=mapLog.begin() ; itMapLog != mapLog.end() ; itMapLog++)
    {
        mapTop10.insert( make_pair (itMapLog->second.second, itMapLog->first ) );
    }

    // Récupération des 10 premiers éléments de mapTop10
    if(mapTop10.size()>10){
        itmapTop10 = mapTop10.begin();
        advance(itmapTop10,10);

        mapTop10.erase(itmapTop10,mapTop10.end());
    }

    for(itPrint=mapTop10.begin() ; itPrint != mapTop10.end() ; itPrint++)
    {
        cout<<itPrint->second<<" ("<<itPrint->first<<" hits)"<<endl;
    }

}
//----- Fin de Méthode

// Algorithme : aucun
int StatLog::GetIndex(vector<string>& v, string name)
{
    vector<string>::iterator it = find(v.begin(), v.end(), name);
 
    // Si l'élément est trouvé
    if (it != v.end())
    {     
        // Calcul de l'index
        int index = it - v.begin();
        return index;
    }
    else {
        // Si l'élément n'est pas présent
        return -1;
    }
}
//----- Fin de Méthode

//-------------------------------------------- Constructeurs - destructeur
// Algorithme : aucun
StatLog::StatLog ()
{
    
#ifdef MAP
    cout << "Appel au constructeur de StatLog" << endl;
#endif
}
//----- Fin de Méthode

// Algorithme : aucun
StatLog::~StatLog ( )
{  
#ifdef MAP
    cout << "Appel au destructeur de StatLog" << endl;
#endif
} 
//----- Fin de Méthode
