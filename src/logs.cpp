#include <iostream>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <fstream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include "logs.h"

std::string getCurrentDateTime(std::string s){
  time_t now = time(0);
  struct tm tstruct;
  char  buf[80];
  tstruct = *localtime(&now);
  if(s=="now")
      strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
  else if(s=="date")
      strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
  return std::string(buf);
};

void Logger(std::string logMsg, std::string filePath, int& cnt, cv::Mat& imgsrc){
    std::ostringstream filenamestream;
    std::string now = getCurrentDateTime("now");
    std::ofstream ofs(filePath.c_str(), std::ios_base::out | std::ios_base::app );
    filenamestream << "tmp/" << now << "_" << cnt << ".jpg";
    cv::imwrite(filenamestream.str(), imgsrc);
    ofs << now << "\t" << logMsg + "\n";
    ofs.close();



};
