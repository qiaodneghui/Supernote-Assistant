/*
 * Author : Asa
 * Time : 2019.7.19
*/

#ifndef SNDATALOAD_H
#define SNDATALOAD_H

#include <string>
#include "config.h"


    class SnDataLoad {

    public:

        SnDataLoad();
        SNFILE_RETURN_CODE fetchNotePathFromFile( std::vector<TrailContainer> &trailsContainer, std::string sNotePath, int iPage);
    };
#endif // SNDATALOAD_H
