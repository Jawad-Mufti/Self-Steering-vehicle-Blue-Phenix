
 * Copyright (C) 2020  Christian Berger
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// Include the single-file, header-only middleware libcluon to create high-performance microservices
#include "cluon-complete.hpp"
// Include the OpenDLV Standard Message Set that contains messages that are usually exchanged for automotive or robotic applications
#include "opendlv-standard-message-set.hpp"
#define CLUON_TIME_HPP
#include <chrono>
// Include the GUI and image processing header files from OpenCV
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<string>
#include <iostream>
#include <ctime>
#include <cstddef>
#include <cstdint>
#include <atomic>
#include <cv.h>

using namespace cv;
using namespace std;
float cordinateYellowX;
 float cordinateYellowY;
 float cordinateBlueX;
 float cordinateBlueY;
  int tstampz;



  const float RIGHT_TURN{(float)-0.2908};
    const float RIGHT_TURN_new{(float)-0.1259535};

    const float MINOR_RIGHT_TURN2{(float)-0.15};
      const float MINOR_RIGHT_TURN{(float)-0.0749791};
      const float LEFT_TURN{(float)0.2908};
      const float MINOR_LEFT_TURN{(float)0.1908};
            const float MINOR_LEFT_TURNEX{(float)0.06298564};

      const float MINOR_LEFT_TURN2{(float)0.1208};
      const float MINOR_LEFT_TURN3{(float)0.05088};




 //std::cout << env.sampleTimeStamp().seconds() << "." << env.sampleTimeStamp().microseconds() << std::endl;
   //int ts = env.sampleTimeStamp().seconds()+"."+ env.sampleTimeStamp().microseconds();
int32_t main(int32_t argc, char **argv) {
    int32_t retCode{1};



    // Parse the command line parameters as we require the user to specify some mandatory information on startup.
    auto commandlineArguments = cluon::getCommandlineArguments(argc, argv);
    if ( (0 == commandlineArguments.count("cid")) ||
         (0 == commandlineArguments.count("name")) ||
         (0 == commandlineArguments.count("width")) ||
         (0 == commandlineArguments.count("height")) ) {
        std::cerr << argv[0] << " attaches to a shared memory area containing an ARGB image." << std::endl;
        std::cerr << "Usage:   " << argv[0] << " --cid=<OD4 session> --name=<name of shared memory area> [--verbose]" << std::endl;
        std::cerr << "         --cid:    CID of the OD4Session to send and receive messages" << std::endl;
        std::cerr << "         --name:   name of the shared memory area to attach" << std::endl;
        std::cerr << "         --width:  width of the frame" << std::endl;
        std::cerr << "         --height: height of the frame" << std::endl;
        std::cerr << "Example: " << argv[0] << " --cid=253 --name=img --width=640 --height=480 --verbose" << std::endl;
    }
    else {
        // Extract the values from the command line parameters
        const std::string NAME{commandlineArguments["name"]};
        const uint32_t WIDTH{static_cast<uint32_t>(std::stoi(commandlineArguments["width"]))};
        const uint32_t HEIGHT{static_cast<uint32_t>(std::stoi(commandlineArguments["height"]))};
        const bool VERBOSE{commandlineArguments.count("verbose") != 0};


        // Attach to the shared memory.
        std::unique_ptr<cluon::SharedMemory> sharedMemory{new cluon::SharedMemory{NAME}};
        if (sharedMemory && sharedMemory->valid()) {
            std::clog << argv[0] << ": Attached to shared memory '" << sharedMemory->name() << " (" << sharedMemory->size() << " bytes)." << std::endl;

            // Interface to a running OpenDaVINCI session where network messages are exchanged.
            // The instance od4 allows you to send and receive messages.
            cluon::OD4Session od4{static_cast<uint16_t>(std::stoi(commandlineArguments["cid"]))};
           opendlv::proxy::GroundSteeringRequest gsr;
            std::mutex gsrMutex;
            auto onGroundSteeringRequest = [&gsr, &gsrMutex](cluon::data::Envelope &&env){

                // The envelope data structure provide further details, such as sampleTimePoint as shown in this test case:
                // https://github.com/chrberger/libcluon/blob/master/libcluon/testsuites/TestEnvelopeConverter.cpp#L31-L40
                 std::lock_guard<std::mutex> lck(gsrMutex);
                 gsr = cluon::extractMessage<opendlv::proxy::GroundSteeringRequest>(std::move(env));




               /// std::cout << "lambda: groundSteering = " << gsr.groundSteering() << std::endl;

   tstampz = env.sampleTimeStamp().seconds();


                              // std::cout << env.sampleTimeStamp().seconds() << std::endl;
         // std::stringstream ss;
           

                  };

            od4.dataTrigger(opendlv::proxy::GroundSteeringRequest::ID(), onGroundSteeringRequest);


            // Endless loop; end the program by pressing Ctrl-C.
            while (od4.isRunning()) {}
         
 if(( ctArea2>400 ) && (cordinateYellowX<400)){
 
// gsr.groundSteering(MINOR_LEFT_TURN3);
//                                   od4.send(steerReq);
    std::tresult =  MINOR_LEFT_TURN3;
 
 }
             
 if((ctArea2>400) && (cordinateYellowX<500)){
  
    //  gsr.groundSteering(LEFT_TURN);

    //     od4.send(steerReq);

 tresult =  LEFT_TURN;

 //  std::cout << tresult << endl;
 //std::cout << "our left steeering = " << gsr.groundSteering() << std::endl;

 
 }
             
              if ((ctArea2>300)&&(cordinateYellowX<380)){
              tresult =  MINOR_LEFT_TURNEX;
               

    //  if((ctArea2>300 && ctArea2<400) && (cordinateYellowX>250 && cordinateYellowX<400)){
//   //  gsr.groundSteering(LEFT_TURN);
//   //                                  od4.send(steerReq);
//                                    tresult =  LEFT_TURN;
//                                  //  std::cout << tresult << endl;
//                                     //std::cout << "our left steeering = " << gsr.groundSteering() << std::endl;
//  }
   
   
// MINOR_LEFT_TURN3           
               
               
              } 
             
             
              imshow( "imgColorSpace",contourImage );
///std::cout << s << std::endl;
                cluon::data::TimeStamp before;
               cluon::data::TimeStamp timeNow{cluon::time::now()};
                //int64_t microTime= cluon::time::toMicroseconds(timeNow);
             

  int vTime = cluon::time::toMicroseconds(timeStampInfo.second);

  // The current time can ge queried as follows:
    before = cluon::time::now();
             
             
             
             
             // Just wait a little for this example.
   using namespace std::literals::chrono_literals;
        
    // Now, we initialize "after" directly on creation.
// int i = cluon::time:: toMicroseconds (before);  
    
std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
   

   
     
             


int date = now->tm_year + 1900;
 // std::cout << date <<"\n" ;
  int month = (now->tm_mon + 1);
  int day = now->tm_mday ;
  int hour = (now->tm_hour +1);
  int minutes = now->tm_min ;
int seconds = now->tm_sec; 


 //string str1= to_string(i); 
             
            // here we are converting numbers to strings in order to display them on the screen.
 string strDate= to_string(date);  
 string strMonth= to_string(month);  
 string strday= to_string(day);  
  string strHour= to_string(hour);  
  string strMinutes= to_string(minutes); 
  string strSeconds= to_string(seconds); 
  string v = to_string(vTime);
 
  
//////////////////////////////////////////////////////////////////////////////////////////////////////
string result = "j";
//"time now "+strDate+"-"+strMonth+"-"+strday+"T"+strHour+":"+strMinutes+":" +strSeconds+"ts "+v+";... Jawad Mofti";
cv::putText(img, //target image
           result, //text
          cv::Point(500, 50), //top-left position
            cv::FONT_HERSHEY_PLAIN,
              1.0,
               CV_RGB(255, 233, 255), //font color
               2);

                // TODO: Do something with the frame.
                // Example: Draw a red rectangle and display image




std::cout <<" wanna print this ; "<< tstampz<< " ; "<< tresult <<std::endl;

<< v << " sample time stamp ; "




//cvPutText (img, text, cvPoint(200,400), font, cvScalar(255,255,0));

                cv::rectangle(img, cv::Point(50, 50), cv::Point(100, 100), cv::Scalar(0,0,255));

                // If you want to access the latest received ground steering, don't forget to lock
//the mutex:
                {
                    std::lock_guard<std::mutex> lck(gsrMutex);
                    //the main grs
                    //std::cout << "main: groundSteering = " << gsr.groundSteering() << std::endl;
                }

                // Display image on your screen.
                if (VERBOSE) {
                    cv::imshow(sharedMemory->name().c_str(), img);
                    cv::waitKey(1);
                }
            }
        }
        retCode = 0;
    }
    return retCode;
}
