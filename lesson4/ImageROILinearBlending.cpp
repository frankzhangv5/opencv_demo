#include <assert.h>
#include <opencv2/opencv.hpp>
#include <regex>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>

using namespace cv;
using namespace std;

typedef struct ArgsROILinearBlending
{
	char src[PATH_MAX];
	double alpha;
	char mask[PATH_MAX];
	double beta;
	double gamma;
} ArgsROILinearBlending;

/**
 * @usage: ./ImageROILinearBlending -s ../images/source.png -a 0.5 -m ../images/mask.png -b 0.5 -g 0.5
 */
int main(int argc, char **argv)
{

	char ch = '\0';
	ArgsROILinearBlending argsROILinearBlending;
	memset(&argsROILinearBlending, 0, sizeof(ArgsROILinearBlending));

	while ((ch = getopt(argc, argv, "s:a:m:b:g:h")) != -1)
	{
		switch (ch)
		{
		case 's':
			strcpy(argsROILinearBlending.src, optarg);
			break;
		case 'a':
			argsROILinearBlending.alpha = atof(optarg);
			break;
		case 'm':
			strcpy(argsROILinearBlending.mask, optarg);
			break;
		case 'b':
			argsROILinearBlending.beta = atof(optarg);
			break;
		case 'g':
			argsROILinearBlending.gamma = atof(optarg);
			break;
		case 'h':
			printf("usage: %s -s image1 -a alpha -t image2 -b beta -g gamma\n", argv[0]);
			break;
		case '?':
			printf("Unknown option: %c\n", (char)optopt);
			break;
		default:
			printf("help: %s -h\n", argv[0]);
		}
	}

	if (strlen(argsROILinearBlending.src) && strlen(argsROILinearBlending.mask))
	{
		Mat srcImage, maskImage, roiImage;

		srcImage = imread(argsROILinearBlending.src);
		maskImage = imread(argsROILinearBlending.mask);

		assert(srcImage.data != NULL);
		assert(maskImage.data != NULL);

		roiImage = srcImage(Rect(10, 10, maskImage.cols, maskImage.rows));

		addWeighted(roiImage, argsROILinearBlending.alpha, maskImage, argsROILinearBlending.beta, argsROILinearBlending.gamma, roiImage);

		namedWindow("区域线性图像混合示例窗口");
		imshow("区域线性图像混合示例窗口", srcImage);

		waitKey(0);
	}

	return EXIT_SUCCESS;
}
