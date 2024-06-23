# ReadFile
```
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

)
```
### Returns:
```
-1 == Failed to open target file
-2 == Size of target file exceeds size of output buffer
```

# WriteFile
```
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

)
```
### Returns:
```
-1 == Failed to open target file
```

# EnumFiles
```
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

)
```
### Returns:
```
-1 == Failed to open target directory
else returns number of files in target directory (except "." && "..") && length of out_names output
```
**Call EnumFiles_Free() on `out_names` if you want to free dynamically allocated memory.**
