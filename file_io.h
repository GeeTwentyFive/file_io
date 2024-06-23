#ifndef _FILE_IO_H
#define _FILE_IO_H



#include <dirent.h>



static
FILE
*file;



static
inline
int
ReadFile
(

	const
	char
	*target_name,

	char
	*out,

	int
	out_size,

	int
	*out_target_size

) {

	file = fopen(target_name, "r");

	if (file == NULL)
		return -1;

	fseek(file, 0, SEEK_END);
	int
	target_file_size
	= ftell(file);
	fseek(file, 0, SEEK_SET);

	if (target_file_size > out_size) {

		fclose(file);
		return -2;

	}

	fread(out, 1, target_file_size, file);
	if (out_target_size != NULL)
		*out_target_size = target_file_size;

	fclose(file);

	return 0;

}



static
inline
int
WriteFile
(

	const
	char
	*target_name,

	char
	*out,

	int
	out_size

) {

	file = fopen(target_name, "w");

	if (file == NULL)
		return -1;

	fwrite(out, 1, out_size, file);

	fclose(file);

	return 0;

}



static
inline
int
EnumFiles
(

	const
	char
	*target_name,

	char
	(**out_names)[256]

) {

	static
	DIR
	*target_dir;
	target_dir = opendir(target_name);
	if (target_dir == 0) {
		perror(0);
		return -1;
	}

	int
	names_size
	= 256*256;
	char
	(*names)[256]
	= malloc(names_size);

	int
	count;
	struct
	dirent
	*target_content;
	target_content = readdir(target_dir); // .
	target_content = readdir(target_dir); // ..
	for (
		count = 0;

		(target_content = readdir(target_dir)) != 0;

		count++
	) {

		if (count == names_size/256)
			names = realloc(
				names,
				(names_size = names_size*2)
			);

		strcpy(names[count], target_content->d_name);

	}

	closedir(target_dir);

	*out_names = names;
	return count;

}

static
inline
void
EnumFiles_Free
(

	char
	(*target)[256]

) { free(target); }



#endif
