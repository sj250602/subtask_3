#include <opencv2/opencv.hpp>
#include <iostream>
#include <bits/stdc++.h>
#include <sys/time.h>

using namespace cv;
using namespace std;

vector<Point2f> pts_src;
vector<Point2f> pts_dst;
vector<double> ans_vec;
Rect box;



//float metric_cal( float f, float g){
	//return abs(f-g);
//}

long gettime(){
	struct timeval start;
	gettimeofday(&start, NULL);
return start.tv_sec*1000000 + start.tv_usec;
}

//long myruntime(){
	//return final-initial;
//}

//struct triplet{
//	int x, double y, double z;
//}




void getcontoursarea(Mat image,Mat image2,Mat image3){
	int queue = 0,dynamic = 0,total = 0; 
	for (int i = 0; i <image.size().height; i++) {
		for (int j = 0; j<image.size().width; j++) {
			total += 1;
			if (abs(image.at<uchar>(i, j)-image2.at<uchar>(i,j))>22) {
				queue += 1;
			}
			if (abs(image.at<uchar>(i, j)-image3.at<uchar>(i,j))>10) {
				dynamic += 1;
			}
		}
	}
	ans_vec.push_back((double) queue / (double)(image.size().height*image.size().width));
	ans_vec.push_back((double) dynamic / (double)(image.size().height*image.size().width));
}


Mat crop_frame(Mat im_src)
{
	Mat im_out; 
	Mat h = findHomography(pts_src, pts_dst);
	warpPerspective(im_src, im_out, h, im_src.size());
	Mat crop = im_out(box);
    	return crop;
}


void framesdifference(int k, vector<pair<int, pair<double,double>>> &st, VideoCapture cap, Mat &emptyframe){
	Mat prev_image = emptyframe;

	int frame_num = 0;
	int fps_3 = -1;
	double frames= cap.get(CAP_PROP_FRAME_COUNT);
	
	while (fps_3<frames)
	{
		fps_3++;
		Mat curr_frame,gray_prev,gray_emp,crop_emp,crop_curr,crop_prev,gray_curr;
		bool bSuccess = cap.read(curr_frame);
		if(fps_3%k==1){
			frame_num++;
			// read a new frame from video
			//Breaking the while loop at the end of the video
			if (bSuccess == false)
  			{
  				//cout << "runtime is" + to_string(total_runtime) << endl;
   				cout << "Found the end of the video" << endl;
   				break;
  			}
  			
  			cvtColor(emptyframe,gray_emp,COLOR_BGR2GRAY);
  			crop_emp = crop_frame(gray_emp);
  			
  			cvtColor (prev_image , gray_prev, COLOR_BGR2GRAY);
  			crop_prev = crop_frame(gray_prev);
  			
  			cvtColor (curr_frame, gray_curr, COLOR_BGR2GRAY);
			crop_curr = crop_frame(gray_curr);
	
		
			getcontoursarea(crop_curr,crop_emp,crop_prev);
			
			pair<int,pair<double,double>> store;
			store.first = fps_3;
			store.second.first = ans_vec[0];
			store.second.second = ans_vec[1];
			st.push_back(store);
			
			//store_coor<< frame_num <<","<< ans_vec[0] <<"," << ans_vec[1]<< endl;
			ans_vec.clear();
		
			prev_image = curr_frame;
		
			
	  		//wait for for 10 ms until any key is pressed.  
	  		//If the 'Esc' key is pressed, break the while loop.
	  		//If the any other key is pressed, continue the loop 
	  		//If any key is not pressed withing 10 ms, continue the loop
	  		if (waitKey(40) == 27)
	  		{
	   			cout << "Esc key is pressed by user. Stopping the video" << endl;
	   			break;
	  		}
	 	}
	}
}
int main(int argc, char* argv[])
{
	pts_dst.push_back(Point2f(472, 52));
	pts_dst.push_back(Point2f(472,830));
	pts_dst.push_back(Point2f(800, 830));
	pts_dst.push_back(Point2f(800, 52));

	pts_src.push_back(Point2f(969,233));
	pts_src.push_back(Point2f(614,974));
	pts_src.push_back(Point2f(1406,995));
	pts_src.push_back(Point2f(1254,230));

	box.width=(410);
	box.height=(1000);
	box.x=(430);
	box.y=(32);
	
	String str1;
	cout<<"Enter the path of empty frame:";
	cin>>str1;
	Mat emptyframe = imread(str1);
	
	
	String str;
	cout<<"Enter the path of video:";
	cin>>str;
	//open the video file for reading
	VideoCapture cap(str); 
	
	
	// if not success, exit program
	if (cap.isOpened() == false)  
	{
		cout << "Cannot open the video file" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	//get the frames rate of the video
	
	double frames= cap.get(CAP_PROP_FRAME_COUNT);
	cout <<"No of frames="<< frames << "\n";
	
	double fps = cap.get(CAP_PROP_FPS); 
	cout << "Frames per seconds : " << fps << endl;
 	
 	String window_name = "Traffic_Density";
 	
 	int differenceofframes;
 	cout<<"Enter the number of frames you want to skip:";
 	cin>>differenceofframes;
 	//ofstream store_coor;
	long initial = gettime();
	vector<pair<int,pair<double,double>>> myvector;
	framesdifference(differenceofframes, myvector, cap, emptyframe);
	long final = gettime();
	long total_runtime = final-initial;
	cout << "Runtime is " << to_string(total_runtime) <<endl;
	ofstream store_coor;	
	string m = to_string(differenceofframes) + ".txt";
	store_coor.open(m);
	for (auto k: myvector){
	store_coor<< k.first << "	" << k.second.first << "	"<<k.second.second << endl;
	}	
	//store_coor.open(store_data);
 	//namedWindow(window_name, WINDOW_NORMAL); //create a window
 	//cout<<"Your video is processed successfully now you plot the curve\n";  	
 	store_coor.close();
	return 0;
}
