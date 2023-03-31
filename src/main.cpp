#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include "onnxruntime/core/session/onnxruntime_cxx_api.h"
#include "onnxruntime/core/session/onnxruntime_c_api.h"
#include "util.h"
#include "detector.h"
#include <map>
#include "logs.h"
#include "nlohmann/json.hpp"
#include "BYTETracker.h"


//#include "json.hpp" Ubuntu 18.04


using json = nlohmann::json;

void print(const json& js){
  std::cout << "Model was initialized." << "\n\n";
  std::cout << "configurate model: " << "\n\n";
  for (auto it = js.begin(); it != js.end(); ++it)
      std::cout << it.key() << " : " << it.value() << "\n";
};


void bytetrack_update(const std::vector<Detection>& res, std::vector<Object>& obj, const int& class_id ){
      for (size_t i = 0; i < res.size(); i++){
          try
            {
              if (res[i].classId != class_id){ continue; }
              obj[i].label = res[i].classId;
              obj[i].rect.x = res[i].box.x;
              obj[i].rect.y = res[i].box.y;
              obj[i].rect.height = res[i].box.height;
              obj[i].rect.width = res[i].box.width;
              obj[i].prob = res[i].conf;
            }
          catch(const std::exception& e)
            {
              std::cerr << e.what() << '\n';
            }        
      }

};



int main(int argc, char* argv[])
{
    std::ifstream f("opt.json");
    json cnf = json::parse(f);
    print(cnf);

    std::map<int, std::vector<int>> object_id_list;
    const std::vector<std::string> classNames = util::loadNames(cnf["classNamesPath"]);
    const int class_id = cnf["class_id"];
    
    YOLODetector detector {nullptr};
    cv::Mat frame;
    std::vector<Detection> result;

    detector = YOLODetector(cnf["modelpath"], cnf["cuda"], cv::Size(cnf["hw"], cnf["hw"]));

    std::vector <double> avg;
    cv::VideoCapture source(argv[1]);
    std::chrono::time_point<std::chrono::high_resolution_clock>prev_frame_time(std::chrono::high_resolution_clock::now());
    std::chrono::time_point<std::chrono::high_resolution_clock>new_frame_time;
    int frame_width  =  source.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height =  source.get(cv::CAP_PROP_FRAME_HEIGHT);
    int fpsvideo = source.get(cv::CAP_PROP_FPS);


    cv::namedWindow("Camera", cv::WINDOW_NORMAL);
    BYTETracker tracker(fpsvideo, 30);

    while (source.isOpened()) {
        source >> frame;
        if (frame.empty())
        {
          break;
        }
        
        std::vector<Object> obj;
        result = detector.detect(frame, cnf["confThreshold"], cnf["iouThreshold"]);
        const int num = result.size();
        obj.resize(num);
        bytetrack_update(result, obj, class_id);
        std::vector<STrack> output_stracks = tracker.update(obj);

      for (size_t i = 0; i < output_stracks.size(); i++){
          std::vector<float> tlwh = output_stracks[i].tlwh;
          cv::Scalar __color = tracker.get_color(output_stracks[i].track_id);
          cv::putText(frame, std::to_string(output_stracks[i].track_id), cv::Point(tlwh[0], tlwh[1] - 10), cv::FONT_ITALIC, 0.75, __color, 2);
          cv::rectangle(frame, cv::Rect(tlwh[0], tlwh[1], tlwh[2], tlwh[3]), __color, 2);    
      }


        cv::imwrite("demo.jpg", frame);
        new_frame_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration1(new_frame_time - prev_frame_time);
        double fps = 1/duration1.count();
        
        avg.push_back(fps);


        std::cout <<"FPS: " << fps <<  std::endl;
        prev_frame_time = new_frame_time;

        cv::imshow("Camera", frame);
        if (cv::waitKey(1) == 27) {
          break;
        }


}


    double average = std::accumulate(avg.begin(), avg.end(), 0.0)/avg.size();
    std::cout << "AVG FPS: "<< average << std::endl;

    cv::destroyAllWindows();
    return 0;
}
