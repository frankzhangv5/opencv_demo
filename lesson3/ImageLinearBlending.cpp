#include <assert.h>
#include <opencv2/opencv.hpp>
#include <regex>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>

using namespace cv;
using namespace std;

typedef struct ArgsLinearBlending
{
	char src1[PATH_MAX];
	double alpha;
	char src2[PATH_MAX];
	double beta;
	double gamma;
} ArgsLinearBlending;

/**
 * @usage: ./ImageLinearBlending -s ../images/snowman.png -a 0.6 -t ../images/christmas_tree.png -b 0.4
 */
int main(int argc, char **argv)
{

	char ch = '\0';
	ArgsLinearBlending argsLinearBlending;
	memset(&argsLinearBlending, 0, sizeof(ArgsLinearBlending));

	while ((ch = getopt(argc, argv, "s:a:t:b:g::h")) != -1)
	{
		switch (ch)
		{
		case 's':
			strcpy(argsLinearBlending.src1, optarg);
			break;
		case 'a':
			argsLinearBlending.alpha = atof(optarg);
			break;
		case 't':
			strcpy(argsLinearBlending.src2, optarg);
			break;
		case 'b':
			argsLinearBlending.beta = atof(optarg);
			break;
		case 'g':
			argsLinearBlending.gamma = atof(optarg);
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

	if (strlen(argsLinearBlending.src1) && strlen(argsLinearBlending.src2))
	{
		Mat srcImage1, srcImage2, dstImage;

		srcImage1 = imread(argsLinearBlending.src1);
		srcImage2 = imread(argsLinearBlending.src2);

		assert(srcImage1.data != NULL);
		assert(srcImage2.data != NULL);

		addWeighted(srcImage1, argsLinearBlending.alpha, srcImage2, argsLinearBlending.beta, argsLinearBlending.gamma, dstImage);

		namedWindow("线性混合示例窗口【原图】", 1);
		imshow("线性混合示例窗口【原图】", srcImage1);

		namedWindow("线性混合示例窗口【效果图】", 1);
		imshow("线性混合示例窗口【效果图】", dstImage);

		waitKey(0);
	}

	return EXIT_SUCCESS;
}
