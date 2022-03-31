//
//  main.cpp
//  facade pattern
//
//  Created by AK on 29/12/2021.
//

#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>

using namespace std;

class ResizeVideo {
public:
  string initialise() const {
    return "Resize Video module initialised\n";
  }
  string resize() const {
    return "Resizing video\n";
  }
};

class ApplyFilter {
public:
  string initialise() const {
    return "ApplyFilter Video module initialised\n";
  }
  string apply() const {
    return "Applying filter to video\n";
  }
};

class VideoConversionPipeline {
public:
  VideoConversionPipeline(ResizeVideo* resize_video = nullptr,
                          ApplyFilter* apply_filter = nullptr)
  {
    resize_video_ = resize_video ? : new ResizeVideo;
    apply_filter_ = apply_filter ? : new ApplyFilter;
  }
  ~VideoConversionPipeline()
  {
    delete resize_video_;
    delete apply_filter_;
  }
  
  string execute() {
    string log = "Initialise system\n";
    log += resize_video_->initialise();
    log += apply_filter_->initialise();
    log += "Executing pipeline..\n";
    log += resize_video_->resize();
    log += apply_filter_->apply();
    return log;
  }
  
protected:
  ResizeVideo* resize_video_;
  ApplyFilter* apply_filter_;
};

void runner(VideoConversionPipeline* pipeline) {
  cout << pipeline->execute();
}

int main(int argc, const char * argv[]) {
  ResizeVideo* resize_video(new ResizeVideo);
  ApplyFilter* apply_filter(new ApplyFilter);
  auto pipeline = make_unique<VideoConversionPipeline>(resize_video, apply_filter);
  runner(pipeline.get());
  return 0;
}
