#include <stdio.h>
#include <string.h>

static int GetFileName(const char *file_path,char *file_name, size_t file_name_size)
{
	char* dir_end = NULL;

	if ((file_path == NULL) || (file_name==NULL))
		return -1;

	dir_end = strrchr(file_path, '/');
	if (dir_end == NULL)
		return -1;

	(void)snprintf(file_name, file_name_size, "%s", dir_end + 1);

	return 0;
}

int main(int argc, char *argv[])
{
	char		buf[256];
	FILE		*fpIn;
	char		target[256];
	char		line[512];
	char		reliance[256];
	char		*src;
	char		*dst;
	char		*drv;
	char		*pth;

	if (argc != 2)
		goto error;

	if (GetFileName(argv[1], buf, 256) < 0)
		strcpy(buf, argv[1]);

	if ((fpIn = fopen(argv[1], "rb")) == NULL) {
		printf("Cannot open input file.\n");
		return 1;
	}

	strcpy(target, strtok(buf, "."));

	while (NULL != fgets(line, 510, fpIn)) {
		if (strstr(line, "CFILE") == NULL)
			continue;
		strtok(line, "\"");
		src = strtok(NULL, "\"");
		if (src == NULL)
			continue;
		dst = &buf[0];
		while (*src != 0) {
			if (*src == '\\') {
				*dst = '/';
				src++;
			} else {
				*dst = *src;
			}
			src++;
			dst++;
		}
		*dst = 0;
		drv = strtok(buf, ":");
		pth = strtok(NULL, ":");
		if (pth != NULL) {
			strcpy(reliance, "/cygdrive/");
			if (*drv < '`')
				reliance[10] = *drv + ('a' - 'A');
			else
				reliance[10] = *drv;
			reliance[11] = 0;
			strcat(reliance, pth);
		} else {
			strcpy(reliance, buf);
		}
		if (target[0] != 0) {
			printf("%s.o: %s ", target, reliance);
			target[0] = 0;
		} else {
			printf("\\\n");
			printf("\t%s ", reliance);
		}
	}
	printf("\n");
	fclose(fpIn);
	return 0;

error:
	printf("Parameter Error!\n\n");
	return -1;
}
