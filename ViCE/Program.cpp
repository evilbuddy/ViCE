#include <iostream>
#include <cstring>
#include <codecvt>
#include <Windows.h>
#include <chrono>
#include <ctime>

// image (OpenCV)
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

const char* getChar(unsigned char grayScale)
{
    if (grayScale >= 240)
        return "$";
    else if (grayScale >= 220)
        return "@";
    else if (grayScale >= 200)
        return "B";
    else if (grayScale >= 175)
        return "%";
    else if (grayScale >= 150)
        return "8";
    else if (grayScale >= 125)
        return "o";
    else if (grayScale >= 100)
        return "p";
    else if (grayScale >= 80)
        return "L";
    else if (grayScale >= 55)
        return "{";
    else if (grayScale >= 40)
        return "!";
    else if (grayScale >= 25)
        return "^";
    else if (grayScale >= 10)
        return ".";
    else
        return " ";
}

std::string wstringToString(std::wstring wstr) {
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    std::string str = converter.to_bytes(wstr);
    return str;
}

std::string ExePath() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    std::wstring wpath = std::wstring(buffer).substr(0, pos);
    std::string path = wstringToString(wpath);
    return path;
}

int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 3)
    {
        std::cout << "Usage: ViCE <video>";
        return -1;
    }

	std::string video = argv[1];

	cv::VideoCapture capture(video);

    cv::Mat frame;
    std::chrono::system_clock::time_point lastFrame = std::chrono::system_clock::now();
    std::string frameASCII;
    std::string rowASCII;
    cv::Vec3b bgr;
    unsigned char grayScale;
    int frameNbr = 0;
    bool doSkip = false;
    double frameCnt = capture.get(cv::CAP_PROP_FRAME_COUNT);
    double FPS = capture.get(cv::CAP_PROP_FPS);

    if (video.substr(1, 1) != ":")
    {
        video = ExePath() + video;
    }

	while (capture.read(frame))
	{
        frameNbr++;
        cv::resize(frame, frame, cv::Size(120, 45));
        frameASCII = "";

        for (int row = 0; row < frame.rows; row++)
        {
            rowASCII = "";

            for (int col = 0; col < frame.cols; col++)
            {
                bgr = frame.at<cv::Vec3b>(row, col);
                grayScale = (bgr[2] * .21) + (bgr[1] * .72) + (bgr[0] * .07);

                rowASCII += getChar(grayScale);
            }

            frameASCII += rowASCII + "\n";
        }

        system("cls");
        std::cout << frameASCII;
        std::cout << frameNbr << "/" << frameCnt << " @ " << (std::chrono::system_clock::now() - lastFrame).count() / 60000 << "/" << FPS << std::endl;

        lastFrame = std::chrono::system_clock::now();
	}
    
    capture.release();
}