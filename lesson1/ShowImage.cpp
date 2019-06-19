#include <assert.h>
#include <opencv2/opencv.hpp>
#include <regex>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>

using namespace cv;
using namespace std;

const char *parse_filename(const char *path);
int show_image(const char *path);

int main(int argc, char **argv)
{

	char ch = '\0';
	int ret = 0;

	while ((ch = getopt(argc, argv, "s:h")) != -1)
	{
		switch (ch)
		{
		case 's':
			ret = show_image(optarg);
			printf("show_image: %s, returned: %d\n", optarg, ret);
			break;
		case 'h':
			printf("usage: %s -s path/to/image\n", argv[0]);
			break;
		case '?':
			printf("Unknown option: %c\n", (char)optopt);
			break;
		default:
			printf("help: %s -h\n", argv[0]);
		}
	}
	return EXIT_SUCCESS;
}

int show_image(const char *path)
{
	assert(path != NULL);
	const char *filename = parse_filename(path);
	assert(filename != NULL);

	printf("filename: %s\n", filename);
	Mat image = imread(path, 1);
	if (!image.data)
	{
		printf("No image data \n");
		delete filename;
		return EXIT_FAILURE;
	}
	namedWindow(filename, WINDOW_AUTOSIZE);
	imshow(filename, image);
	waitKey(0);
	delete filename;
	return EXIT_SUCCESS;
}

const char *parse_filename(const char *path)
{
	smatch results;
	regex r(".+/(.+)$");
	string file(path);
	char *filename = new char[PATH_MAX];

	if (regex_search(file, results, r))
		cout << results.str(1) << endl;

	strcpy(filename, results.str(1).c_str());
	return filename;
}