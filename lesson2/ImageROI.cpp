#include <assert.h>
#include <opencv2/opencv.hpp>
#include <regex>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>

using namespace cv;
using namespace std;

typedef struct ArgsROI
{
	char src[PATH_MAX];
	char mask[PATH_MAX];
} ArgsROI;

int main(int argc, char **argv)
{

	char ch = '\0';
	ArgsROI argsROI;
	memset(&argsROI, 0, sizeof(ArgsROI));

	while ((ch = getopt(argc, argv, "s:m:h")) != -1)
	{
		switch (ch)
		{
		case 's':
			strcpy(argsROI.src, optarg);
			break;
		case 'm':
			strcpy(argsROI.mask, optarg);
			break;
		case 'h':
			printf("usage: %s -s path/to/source/image -m path/to/mask/image\n", argv[0]);
			break;
		case '?':
			printf("Unknown option: %c\n", (char)optopt);
			break;
		default:
			printf("help: %s -h\n", argv[0]);
		}
	}

	if (strlen(argsROI.src) && strlen(argsROI.mask))
	{
		Mat srcImage = imread(argsROI.src);
		Mat maskImage = imread(argsROI.mask);

		assert(srcImage.data != NULL);
		assert(maskImage.data != NULL);

		Mat imageROI = srcImage(Rect(srcImage.rows / 10, srcImage.cols / 10, maskImage.cols, maskImage.rows));

		Mat mask = imread(argsROI.mask, 0);

		maskImage.copyTo(imageROI, mask);

		namedWindow("利用ROI实现图像叠加示例");
		imshow("利用ROI实现图像叠加示例", srcImage);
		waitKey(0);
	}

	return EXIT_SUCCESS;
}
