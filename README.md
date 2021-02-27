

### Summary
the project is built using docker.
With the use of OpenCV , C++ and cluon to process video image frames from a rec. file that is supposed to be taken from a mounted camera on the car, which records the lane when the car is driving for the porpose of detecting the lane and the boundaries. these data will be prosess and used in my algorithm for the porpose of coming up with the right steering angles per frame to perform self-automation in steering..

### Prerequisites:

- This project is most likely to only work on linux operating systems or any simulation of a linux system.
- You need to install Docker for your platform
- You need to install docker-compose
 - You have a recording file (.rec) that could display a lane with boundaries of blue and yellow cones.
- Building and testing the software module for your laptop (replay mode)
- This template folder contains everything you need to compile and run a C++ software component that uses OpenCV for image processing. We are using Docker to build and run the resulting binary.
- use opendlv tool https://github.com/chalmers-revere/opendlv.


Step 1: Assuming that you have a folder ~/recordings, where you have at least one .rec file from your experiments with Kiwi.

Step 2: Clone this repository:

```cd $HOME
git clone git@github.com:Jawad-Mufti/Self-Steering-vehicle-Blue-Phenix.git
cd template/working_with_records/cpp-opencv/src
```
Step 3:
Now, you can start the h264 decoder and webapp for replaying as follows (the actual h264 decoder is built once during the first call):
``` docker-compose -f h264-decoder-viewer.yml up```

### Tools
* Docker

* cluon library (from chalmers)  more instructions to work with cluon and opendlv :  https://github.com/chalmers-revere/opendlv-device-ps3controller
* CMake 
* Git
* Visual Studio



### Addition of features
If a new feature is to be added on gitlab, the user will create a new branch to work on, to avoid merge conflicts in the master. The new features will be developed and tested until we feel they are safe to merge with the master.

### Fixing Bugs
The code will be run, tested and reviewed in feature branches in order to find any unexpected behavior. If any issues are found in the code we will notify the team for a discussion to take place. Then we will use the tools in Visual Studio to debug and discuss solutions in our upcoming meeting.




#### Author

*  Jawad Mofti
