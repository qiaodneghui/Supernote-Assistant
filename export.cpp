#include "export.h"

#include "library/docx/include/docx.hpp"
#include "library/supernote/include/SnDataLoad.h"
#include "library/supernote/include/sndataoperationfile.h"

Export::Export(QObject* parent) : QObject{parent} { qDebug("Export(QObject *parent)"); }

QString Export::appKey() const {
    qDebug("appKey()");
    return mAppKey;
}

QString Export::hmacKey() const {
    qDebug("hmacKey()");
    return mHmacKey;
}

QString Export::pageRange() const {
    qDebug("pageRange()");
    return mPageRange;
}

QString Export::notePath() const {
    qDebug("notePath()");
    return mNotePath;
}

void Export::setAppKey(const QString& appKey) {
    qDebug() << "setAppKey()  appKey:" << appKey;
    mAppKey = appKey;
    emit appKeyChanged();
}

void Export::setHmacKey(const QString& hmacKey) {
    qDebug() << "setHmacKey()  hmacKey:" << hmacKey;
    mHmacKey = hmacKey;
    emit hmacKeyChanged();
}

void Export::setPageRange(const QString& pageRange) {
    qDebug() << "setPageRange()  pageRange:" << pageRange;
    mPageRange = pageRange;
    emit pageRangeChanged();
}

void Export::setNotePath(const QString& notePath) {
    qDebug() << "setNotePath()  notePath:" << notePath;
    mNotePath = notePath;
    emit notePathChanged();
}

int Export::getTotalPage() {
    qDebug() << "getTotalPage()";
    SnDataOperationFile opt;
    mTotalPage = opt.fetchTotalPageNumOfNote(mNotePath.toStdString());
    qDebug() << "mTotalPage:" << mTotalPage;
    return mTotalPage;
}

void Export::startExport(const int& type) {
    qDebug() << "startExport()  type:" << type;

    // 1.获取要导出的页码
    vector<int> pages;
    bool ret = parsePage(pages);
    if (!ret) {
        return;
    }
    vector<vector<RattaPoint>> pageData;
    for (const auto& page : pages) {
        pageData.clear();
        getData(pageData, page);

        // 构造识别数据

        // 网络请求

        // 从信号槽中得到当前页识别结果并保存到map中

        // 遍历map 将数据写入文件
    }
}

void Export::getData(vector<vector<RattaPoint>>& data, const int& page) {
    SnDataLoad dataLoad;
    vector<TrailContainer> trailsContainer;
    dataLoad.fetchNotePathFromFile(trailsContainer, mNotePath.toStdString(), page);

    size_t endsite = trailsContainer.size();
    for (size_t i = 0; i < endsite; i++) {
        if (trailsContainer.at(i).layer == 0 && trailsContainer.at(i).penType != MARK_PEN &&
            trailsContainer.at(i).penType != MARK_PEN_RECT_CAP_ROUND_JOIN &&
            trailsContainer.at(i).penType != SEPARATION_ELLIPSE_LINE &&
            trailsContainer.at(i).m_copy != SELECTED_TRAIL_SEPARATION &&
            trailsContainer.at(i).m_copy != ERASE_TRAIL_AREA && trailsContainer.at(i).m_copy != ERASE_TRAIL_TRAIL &&
            trailsContainer.at(i).m_copy != ERASE_TRAIL_LINE && trailsContainer.at(i).m_copy != ERASE_TRAIL_ALL &&
            trailsContainer.at(i).m_copy != SET_AS_TITLE && trailsContainer.at(i).m_copy != SET_AS_LINK &&
            trailsContainer.at(i).m_copy != SELECTED_TITLES_DELETE &&
            trailsContainer.at(i).m_copy != SELECTED_LINKS_DELETE &&
            trailsContainer.at(i).m_copy != SELECTED_TITLESANDLINKS_DELETE &&
            trailsContainer.at(i).m_points.size() > 0 && trailsContainer.at(i).m_trailStatus >= NORMAL_STATUS) {
            std::vector<RattaPoint> recognPoints;
            mappingTrailPoints2imageSize(trailsContainer.at(i), SCREEN_VERT_WID, SCREEN_VERT_HEI,
                                         recognPoints);  // 坐标系

            for (std::vector<RattaPoint>::iterator iter = recognPoints.begin(); iter != recognPoints.end();) {
                if (iter->x > (1404 - 1) ||
                    iter->y > (1872 - 1)) {  // 去除屏幕外的采样点，屏幕外采样点不参与识别20221212
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
                cout << "trail Point Num less than 3.";
            }
            data.push_back(recognPoints);
        } else {
            continue;
        }
    }
}

bool Export::parsePage(vector<int>& pageData) { return true; }
