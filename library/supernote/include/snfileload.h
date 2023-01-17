#ifndef SNFILELOAD_H
#define SNFILELOAD_H
#include <string>
#include "snpagefeaturemodule.h"
#include "snfileindexmodule.h"
using namespace std;



class SnFileLoad {
   private:

      std::string filePath = "";

   public:

       SnFileLoad();

       bool init_fileload(std::string strPath);

       /**
        * @brief fetchIndex fetch data of index module
        * @param paraCite cite of index module which be fetching
        * @param nIndex index in a module of the same type
        * @return view file sndatafile_global.h
        */
       SNFILE_RETURN_CODE fetchIndex(SnFileIndexModule &snFileIndexModule);

       /**
        * @brief fetchPageFeature fetch data of page feature module
        * @param paraCite cite of file feature module which be fetching
        * @param iPage Target page number
        * @return view file sndatafile_global.h
        */
       SNFILE_RETURN_CODE fetchPageFeature(SnPageFeatureModule &snPageFeatureModule, int iPage, PageFeatureReadFlag &pageFeatureReadFlag);


   };

#endif // SNFILELOAD_H
