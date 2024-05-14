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

// audio (winmmm)
#include <Mmsystem.h>
#include <mciapi.h>
#pragma comment(lib, "Winmm.lib")

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
    LPSTR buffer;
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string fullpath(buffer);
    std::string::size_type pos = fullpath.find_last_of("\\/");
    std::string path = fullpath.substr(0, pos);
    return path;
}

bool fileExists (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 4)
    {
        std::cout << "Usage: ViCE <video> (frameskip/auto)";
        return -1;
    }

	std::string video = argv[1];
    int customFrameSkip = 0;
    double frameSkipMultiplier = 0.1;

    if(argc == 3)
    {
        std::string arg = argv[2];

        if(arg == "auto")
        {
            customFrameSkip = -1;
        }
        else if(arg.substr(0, 1) == "*")
        {
            customFrameSkip = -1;
            frameSkipMultiplier = std::stod(arg.substr(1, arg.length()));
        }
        else if(arg.substr(0, 1) == "/")
        {
            customFrameSkip = -1;
            frameSkipMultiplier = 1 / std::stod(arg.substr(1, arg.length()));
        }
        else
        {
            customFrameSkip = std::stoi(arg);
        }
    }

	cv::VideoCapture capture(video);

    cv::Mat frame;
    std::chrono::system_clock::time_point lastFrame = std::chrono::system_clock::now();
    std::string frameASCII;
    std::string rowASCII;
    cv::Vec3b bgr;
    unsigned char grayScale;
    int frameNbr = 0;
    int framesToSkip = 0;
    int skippedFrames = 0;
    double frameCnt = capture.get(cv::CAP_PROP_FRAME_COUNT);
    double FPS = capture.get(cv::CAP_PROP_FPS);

    if (video.substr(1, 1) != ":")
    {
        video = ExePath() + video;
    }
    
    std::string audio = video.substr(0, video.find_last_of(".")) + ".mp3";

    if(fileExists(audio))
    {
        mciSendString(("open \"" + audio + "\" type mpegvideo alias mp3").c_str(), NULL, 0, NULL);
        mciSendString("play mp3", NULL, 0, NULL);
    }

	while (capture.read(frame))
	{
        if(framesToSkip > 0)
        {
            if(skippedFrames == framesToSkip)
            {
                frameNbr += framesToSkip;
                skippedFrames = 0;
                framesToSkip = 0;
            }
            else
            {
                skippedFrames += 1;
                continue;
            }
        }

        if(customFrameSkip < 0 && (std::chrono::system_clock::now() - lastFrame).count() / 60000 != FPS)
        {
            framesToSkip = (FPS - (std::chrono::system_clock::now() - lastFrame).count() / 60000) * frameSkipMultiplier;
        }
        else
        {
            framesToSkip = customFrameSkip;
        }

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
        std::cout << frameNbr << "/" << frameCnt << " @ " << (std::chrono::system_clock::now() - lastFrame).count() / 60000 << "/" << FPS << " (" << framesToSkip << ")" << "\n";

        lastFrame = std::chrono::system_clock::now();
	}
    
    capture.release();
}