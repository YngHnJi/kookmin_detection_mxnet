#include <iostream>
#include <string>
#include <fstream>
#include "opencv2/opencv.hpp"
#include "RetinaFace.h"
#include <io.h>

#define FEATURE_VECTOR_SIZE 15

std::vector<std::string> get_files_inDirectory(const std::string& _path, const std::string& _filter){
	
	std::string searching_dir = _path + "*.*";
	
	std::vector<std::string> return_;
	int cnt = 0;

	struct _finddata_t fd;
	intptr_t handle;
	if ((handle = _findfirst(searching_dir.c_str(), &fd)) == -1L)

		std::cout << "No file in directory!" << std::endl;

	do {
		//std::cout << fd.name << std::endl;
		return_.push_back(fd.name);
		cnt += 1;
	} while (_findnext(handle, &fd) == 0);

	_findclose(handle);

	return return_;
}


int main(void)
{
	std::cout << "OpenCV version : " << CV_VERSION << std::endl;

	//std::string model_path("D:\\Yhji\\Suprema_frvt11\\trained_model\\R50.onnx");
	//std::string model_path("D:\\Yhji\\Suprema_frvt11\\trained_model\\model-mxnet_210113.onnx");

	std::string base_path("D:\\Yhji\\Suprema_frvt11\\data\\ftvt_images\\");
	std::string output_dir("D:\\Yhji\\Suprema_frvt11\\data\\retina_debug_detection\\");
	std::string file_filter(".ppm");


	std::vector<std::string> file_list = get_files_inDirectory(base_path, file_filter);
	file_list.erase(file_list.begin(), file_list.begin() + 2);
	

	std::cout << "Debugging" << std::endl;

	RetinaFace RetinaFace;
	RetinaFace.LoadModel();

	std::vector<Bbox> result;

	//for (const std::string file : file_list)
	for (std::string file : file_list)
	{
		std::string image_path = base_path + file;
		cv::Mat img = cv::imread(image_path);

		if (img.empty())
		{
			std::cout << "Could not read the image: " << file << ": ";
			continue;
		}
		//std::cout << "===> Data loaded" << std::endl;
		std::cout << "Processing image: " << file << " -->";

		//std::cout << "Model Loaded" << std::endl;

		//RetinaFace.RunModel(img);
		//cv::Mat detected_result = RetinaFace.RunModel_debug(img);
		result = RetinaFace.RunModel_debug(img);

		std::cout << result[0].score << "  |  ";
		std::cout << result[0].ppoint[0] << " ";
		std::cout << result[0].ppoint[1] << " ";
		std::cout << result[0].ppoint[2] << " ";
		std::cout << result[0].ppoint[3] << " ";
		std::cout << result[0].ppoint[4] << " ";
		std::cout << result[0].ppoint[5] << " ";
		std::cout << result[0].ppoint[6] << " ";
		std::cout << result[0].ppoint[7] << " ";
		std::cout << result[0].ppoint[8] << " ";
		std::cout << result[0].ppoint[9] << " ";

		//std::cout << "Debug" << std::endl;

		////cv::cvtColor(org_img, org_img, cv::COLOR_BGR2RGB);
		//char name[256];
		//cv::Scalar color(255,0,0);
		//sprintf_s(name, "%.2f", result[0].score);

		//cv::putText(img, name, cv::Point(result[0].x1, result[0].y1), cv::FONT_HERSHEY_COMPLEX, 0.7, color, 2);
		////cv::Rect box(rect.face_box.x - rect.face_box.w / 2, rect.face_box.y - rect.face_box.h / 2, rect.face_box.w, rect.face_box.h);
		//cv::Rect box(result[0].x1, result[0].y1, result[0].x2-result[0].x1, result[0].y2 - result[0].y1);
		////cv::rectangle(img, box, color, 2, cv::LINE_8, 0);
		//cv::rectangle(img, box, cv::Scalar(255, 0, 0), 2, cv::LINE_8, 0);
		//for (int k = 0; k < 5; k++) {
		//	cv::Point2f key_point = cv::Point2f(result[0].ppoint[2*k], result[0].ppoint[2 * k + 1]);
		//	if (k % 3 == 0)
		//		cv::circle(img, key_point, 3, cv::Scalar(0, 255, 0), -1);
		//	else if (k % 3 == 1)
		//		cv::circle(img, key_point, 3, cv::Scalar(255, 0, 255), -1);
		//	else
		//		cv::circle(img, key_point, 3, cv::Scalar(0, 255, 255), -1);
		//}

		//cv::imshow("result", img);
		//cv::waitKey(0);

		std::cout << " Debug" << std::endl;

		//file.replace(file.end() - 4, file.end(), ".png");
		//std::string output_file = output_dir + "detected_" + file;

		//cv::imwrite(output_file, detected_result);
		//std::cout << "saved" << std::endl;
	}

	std::cout << "Done" << std::endl;

	return 0;
}


//int main(void)
//{
//	std::cout << "OpenCV version : " << CV_VERSION << std::endl;
//
//	//std::string model_path("D:\\Yhji\\Suprema_frvt11\\trained_model\\R50.onnx");
//	//std::string model_path("D:\\Yhji\\Suprema_frvt11\\trained_model\\model-mxnet_210113.onnx");
//
//	std::string image_path("D:\\Yhji\\Suprema_frvt11\\data\\ftvt_images\\S001-03-t10_01.ppm");
//	cv::Mat img = cv::imread(image_path);
//
//	if (img.empty())
//	{
//		std::cout << "Could not read the image" << std::endl;
//		return 1;
//	}
//	std::cout << "===> Data loaded" << std::endl;
//
//	RetinaFace RetinaFace;
//	RetinaFace.LoadModel();
//	std::cout << "Model Loaded" << std::endl;
//
//	//RetinaFace.RunModel(img);
//	cv::Mat detected_result = RetinaFace.RunModel_debug(img);
//
//	cv::imshow("detected", detected_result);
//	cv::waitKey(0);
//
//
//	//std::cout << "===> Debugging" << std::endl;
//
//	std::cout <<  "Done" << std::endl;
//
//	return 0;
//}

//int main(void)
//{
//    std::cout << "OpenCV version : " << CV_VERSION << std::endl;
//
//    std::string model_path("D:\\Yhji\\Suprema_frvt11\\trained_model\\R50.onnx");
//    //std::string model_path("D:\\Yhji\\Suprema_frvt11\\trained_model\\model-mxnet_210113.onnx");
//
//    std::string image_path("D:\\Yhji\\Suprema_frvt11\\data\\ftvt_images\\S001-03-t10_01.ppm");
//    cv::Mat img = cv::imread(image_path);
//
//    if (img.empty())
//    {
//        std::cout << "Could not read the image" << std::endl;
//        return 1;
//    }
//    std::cout << "Data loaded" << std::endl;
//
//    cv::dnn::Net model = cv::dnn::readNetFromONNX(model_path);
//
//    cv::Scalar mean_mxnet_(0.0, 0.0, 0.0);
//    float alpha_mxnet_ = 1.0;
//    cv::Size size_detection(640, 640);
//    //cv::Size size_verification(112, 112);
//
//    cv::Mat inp = cv::dnn::blobFromImage(img, alpha_mxnet_, size_detection, mean_mxnet_, true);
//
//    model.setInput(inp);
//    cv::Mat result = model.forward();
//
//    //for(int i =0;i< result[0].rows;i++)
//    //    for(int j =0;j<result[0].cols;j++)
//    //std::cout << sizeof(((float *)result[0].data)[0])/sizeof(*((float*)result[0].data[0])) << std::endl;
//
//    std::cout << "Debugging" << std::endl;
//
//    
//    std::ofstream file2write;
//    file2write.open("C:\\Users\\user\\Documents\\Project\\Suprema_frvt\\detection\\debug\\model_output\\detection_output_S001-03-t10_01_cpp_ptr_access.txt");
//
//    if (!file2write.is_open()) {
//        std::cout << "file not opened" << std::endl;
//
//        return 0;
//    }
//    std::cout << "File opened successfully" << std::endl;
//
//    //int num_of_anchors = result.total() / FEATURE_VECTOR_SIZE;
//    int num_of_anchors = 16800;
//    int feature_index = 0;
//
//    std::vector<float> float_templ; float_templ.clear();
//    std::vector<std::vector<float>> vec2write; vec2write.clear();
//
//    ////for (int i = 0; i < num_of_anchors; i++) {
//    //for (int i = 0; i < 5; i++) {
//    //    std::cout << "Data index: " << i << std::endl;
//    //    for (int j = 0; j < FEATURE_VECTOR_SIZE; j++)
//    //    {
//    //        feature_index = (FEATURE_VECTOR_SIZE * i) + j;
//    //        //std::cout << result.at<float>(feature_index) << " ";
//
//    //        float_templ.push_back(result.at<float>(feature_index));
//    //        std::cout << result.at<float>(feature_index) << " ";
//    //        //file2write << result.at<float>(feature_index) << " ";
//    //    }
//    //    std::cout << "\n";
//    //    //file2write << "\n";
//    //    vec2write.push_back(float_templ);
//    //    float_templ.clear();
//    //}
//
//    
//    for(int i=0; i< num_of_anchors;i++){
//    //for (int i = 0; i < 5; i++) { // debug purpose
//        std::cout << "==> Data index: " << i << std::endl;
//        
//        float* current_row = (float*)result.data;
//        for (int j = 0; j < 15; j++)
//        {
//            //std::cout << current_row[15 * i + j] << " ";
//            file2write << current_row[15 * i + j] << " ";
//        }
//    }
//    
//    std::cout << "Done" << std::endl;
//    file2write.close();
//
//	return 0;
//}