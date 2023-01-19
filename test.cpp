#include "test.h"
#include <QDebug>

#include "library/supernote/include/SnDataLoad.h"
#include "library/supernote/include/sndataoperationfile.h"
#include "library/docx/include/docx.hpp"
Test::Test()
{


}

int Test::getTotalPage(const string &filePath)
{
    SnDataOperationFile opt;
  return opt.fetchTotalPageNumOfNote(filePath);

}

void Test::getData(vector<vector<RattaPoint> > &data,const string& path,const int& page)
{
    SnDataLoad dataLoad;
    vector<TrailContainer> trailsContainer;
    dataLoad.fetchNotePathFromFile(trailsContainer,path,page);

   size_t endsite = trailsContainer.size();
   for (size_t i = 0; i < endsite; i++) {

       if (trailsContainer.at(i).layer == 0
           && trailsContainer.at(i).penType != MARK_PEN
           && trailsContainer.at(i).penType != MARK_PEN_RECT_CAP_ROUND_JOIN
           && trailsContainer.at(i).penType != SEPARATION_ELLIPSE_LINE
           && trailsContainer.at(i).m_copy != SELECTED_TRAIL_SEPARATION
           && trailsContainer.at(i).m_copy != ERASE_TRAIL_AREA
           && trailsContainer.at(i).m_copy != ERASE_TRAIL_TRAIL
           && trailsContainer.at(i).m_copy != ERASE_TRAIL_LINE
           && trailsContainer.at(i).m_copy != ERASE_TRAIL_ALL
           && trailsContainer.at(i).m_copy != SET_AS_TITLE
           && trailsContainer.at(i).m_copy != SET_AS_LINK
           && trailsContainer.at(i).m_copy != SELECTED_TITLES_DELETE
           && trailsContainer.at(i).m_copy != SELECTED_LINKS_DELETE
           && trailsContainer.at(i).m_copy != SELECTED_TITLESANDLINKS_DELETE
           && trailsContainer.at(i).m_points.size() > 0
           && trailsContainer.at(i).m_trailStatus >= NORMAL_STATUS) {
           std::vector<RattaPoint> recognPoints;
           mappingTrailPoints2imageSize(trailsContainer.at(i), SCREEN_VERT_WID, SCREEN_VERT_HEI, recognPoints);//坐标系

           for (std::vector<RattaPoint>::iterator iter = recognPoints.begin(); iter != recognPoints.end();) {
               if (iter->x > (1404 - 1) || iter->y > (1872 - 1)) {//去除屏幕外的采样点，屏幕外采样点不参与识别20221212
                   iter = recognPoints.erase(iter);
               } else {
                   iter++;
               }
           }

           size_t recognPointsSize = recognPoints.size();
           if (recognPointsSize == 0) {

               continue;
           } else if (recognPointsSize < 3) {
               RattaPoint p = recognPoints.back();
               while (recognPointsSize < 3) {
                   recognPoints.push_back(p);
                   ++recognPointsSize;
               }
               cout<< "trail Point Num less than 3.";
           }
           data.push_back(recognPoints);
       } else {

           continue;
       }
   }
}

void Test::run(const string &filePath)
{
    int totalPage=getTotalPage(filePath);
    qDebug()<<"totalPage:"<<totalPage;


    for(auto i=1;i<=totalPage;++i){
        vector< vector<RattaPoint>> data;
       getData(data,filePath,i);
       qDebug()<<"data size:"<<data.size();
    }
}

void Test::exportDocx(const string &text, const string &exportPath)
{

    docx::Document doc(exportPath);
        doc.open();

        docx::Paragraph p = doc.paragraphs();
        docx::Run r = p.runs();
        if (r.has_next()) {
            p.append_paragraph(text);
        } else {
            p.add_run(text);
        }
        doc.save();
}

void Test::exportTxt(const string &content, const string &exportPath)
{

}
