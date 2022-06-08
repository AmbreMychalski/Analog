/*************************************************************************
                           Main  -  description
                             -------------------
    début                : 14/01
    copyright            : (C) 2022 par JOSEPH, MYCHALSKI
    e-mail               : matheo.joseph@insa-lyon.fr   ambre.mychalski@insa-lyon.fr
*************************************************************************/

//---------- Réalisation du main (fichier main.cpp) ----------------

//---------------------------------------------------------------- INCLUDE
#include "Lecture.h"
#include "StatLog.h"
//-------------------------------------------------------- Include système

using namespace std;

#include <iostream>
#include <cstring>

//-------------------------------------------------------------- Fonctions

// Mode d'emploi :
// Fonction renvoyant faux si le log en paramètre contient une des extensions interdites par l'option -e.
bool checkType(Log &log)
{
   
    string refusedExtension[6] = { ".js", ".jpg",
                              ".css", ".png", ".gif",".ico" };
 

    for(int i=0; i<sizeof(refusedExtension)/sizeof(string);i++)
    {
        // Cherche la sous-string dans la string
        size_t pos = log.request.find(refusedExtension[i]);
        if (pos != std::string::npos)
        {
            return false;
        }
    }
    return true;
}
//----- Fin de la Fonction

// Mode d'emploi :
// Fonction renvoyant faux si le log en paramètre a un status d'erreur c'est à dire non compris entre 200 et 400 exclu  .
bool checkStatus(Log &log)
{   
    if(log.status>= 200 && log.status<400)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//----- Fin de la Fonction

// Mode d'emploi :
// Fonction mettant en int l'heure contenue dans une chaîne de caractère 
// dans des variables passées en paramètres
void strToHour(string & hour, int & heure, int & minute, int & seconde)
{
    string temp;
    temp=hour.substr(0,hour.find(':'));
    heure=atoi(temp.c_str());
    if(hour.size()<=2)
    {
        minute=0;
        seconde=0;
    }
    else
    {
        hour.erase(0,hour.find(':')+1);
        temp=hour.substr(0,hour.find(':'));
        minute=atoi(temp.c_str());
        if(hour.size()<=5)
        {
            seconde=0;
        }
        else
        {
            hour.erase(0,hour.find(':')+1);
            temp=hour.substr(0,hour.find(':'));
            seconde=atoi(temp.c_str());
        }
    }
}
//----- Fin de la Fonction

// Mode d'emploi :
// Fonction renvoyant faux si le log en paramètre contient une heure non contenue 
// dans [h,h+1[ de l'option -t.
bool checkTime(const Log & l, const int heureT, const int minuteT, const int secondeT )
{
    int heureLog;
    int minuteLog;
    int secondeLog;

    // enlève la date du log (dateHour)
    string hourLog (l.dateHour);
    hourLog=hourLog.substr(0,hourLog.find('+'));
    hourLog.erase(0,hourLog.find(':')+1);
    // met l'heure dans les variables heureLog, minuteLog et secondeLog
    strToHour(hourLog, heureLog, minuteLog, secondeLog);

    if((heureLog==heureT && minuteLog>=minuteT)||(heureLog==heureT+1 && minuteLog<minuteT)||(heureLog==heureT && minuteLog== minuteT && secondeLog>=secondeT) || (heureLog==heureT+1 && minuteLog==minuteT && secondeLog<secondeT))
    {
        return true;
    }
    return false;
}
//----- Fin de la Fonction

// Mode d'emploi :
// Supprime d'une string principale une string secondaire si elle est présente.
void eraseSubStr(string & mainStr, const string & toErase)
{
   
    // Cherche la sousstring dans la string
    size_t pos = mainStr.find(toErase);
    if (pos != std::string::npos)
    {
        // Si la sousstring est trouvé
        mainStr.erase(pos, toErase.length());
    }
}
//----- Fin de la Fonction


//------------------------------------------------------------------- Main

int main(int argc, char *argv[])
{
    int i =0;
    bool optionE = false;
    bool optionT = false;
    bool optionG = false;
    string fileNameGraph;

    bool logValid;

    string referer;
    string target;
    Log logLu;
    StatLog analog;

    int heureT;
    int minuteT;
    int secondeT;
    string hourT;

    //Vérifie qu'il y ai au moins un argument
    if(argc<=1)
    {
        cerr<<"Nom du fichier .log manquant"<<endl;
        exit(1);
    }
    string fileName(argv[argc-1]);
    
    //Boucle de lecture des paramètre du main
    while (i<argc-1)
    {
        // Active l'option -g
        if(strcmp(argv[i],"-g")==0)
        {
            optionG = true;
            i++;

            if(i==argc-1 && strcmp(argv[i], "-e")!=0 && strcmp(argv[i], "-t")!=0)
            {
                cerr<<"Argument manquant à l'option -g"<<endl;
                exit(1);
            }

            fileNameGraph= string(argv[i]);
        }

        // Active l'option -e
        if(strcmp(argv[i],"-e")==0)
        {
            optionE = true;
        }

        // Active l'option -t
        if(strcmp(argv[i],"-t")==0)
        {
            i++;
            if(i==argc-1 && strcmp(argv[i], "-g")!=0 && strcmp(argv[i], "-e")!=0)
            {
                cerr<<"Argument manquant à l'option -t"<<endl;
                exit(1);
            }

            optionT = true;
            hourT=string(argv[i]);
            strToHour(hourT, heureT, minuteT, secondeT);
        }

        i++;
    }

    Lecture l (fileName);

    //Tant qu'il a des lignes à lire
    while(l.ReadLine())
    {
        logValid = true ;
        logLu=l.GetLog();
        target = logLu.request;
        eraseSubStr(target,"GET ");
        eraseSubStr(target," HTTP/1.1");

        referer = logLu.referer;
        eraseSubStr(referer,"http://intranet-if.insa-lyon.fr");

        logValid = checkStatus(logLu);

        if(optionE && logValid)
        {
            logValid = checkType(logLu);
        }
        if(optionT && logValid)
        {
            logValid = checkTime(logLu, heureT, minuteT, secondeT);
        }
        if(logValid)
        {
            analog.AddLog(target, referer);
        }
    }
    
    if(optionG)
    {
        analog.MakeGraph(fileNameGraph);
    } 

    analog.PrintStats();
    return 0;
}
//----- Fin du main
