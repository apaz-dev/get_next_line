## Function Prototype

```C
char *get_next_line(int fd);
```

## Why Static is Perfect for This Job

- **Efficiency**: We don't need to re-read the entire file for each line.
- **Simplicity**: The static variable handles the state management for us.
- **Memory Management**: We can allocate memory once and reuse it, rather than allocating new memory for each function call.

---

> [!CAUTION]
> ⚠️ **Just use my code as a last alternative and try to find out what my code does and why I do it, don't copy my code without understanding anything. =)**

## Detailed Function Overview

### The Main Function: `get_next_line`

This is the heart of the solution. It reads a line from the file descriptor, updates the buffer, and returns the line.

```c
char	*get_next_line(int fd)
{
	static char	*text;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	text = read_fd(fd, text);
	if (text == NULL)
		return (NULL);
	line = get_first_line(text);
	text = fill_text(text);
	return (line);
}
```

- **Parameters**: File descriptor `fd`.
- **Returns**: The next line, or `NULL` on error or when the file ends.
  
The function works as follows:

1. **Error Handling**: If the file descriptor is invalid, or if there's an issue with `BUFFER_SIZE` or the read call, it returns `NULL`.
2. **Reading the File**: It calls the `read_fd` function to read data into the static `text`.
3. **Line Extraction**: Using `get_first_line`, it extracts the next line from the buffer.
4. **Buffer Update**: The remaining data in the buffer is adjusted by `fill_text` to account for the extracted line.
5. **Return**: Finally, it returns the extracted line.

---

### Reading from the File: `read_fd`

The `read_fd` function reads from the file into the buffer in chunks, appending data to a result string.

```c
char	*read_fd(int fd, char *fd_content)
{
	int		byte_read;
	char	*buff_tmp;

	buff_tmp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff_tmp)
		return (NULL);
	buff_tmp[0] = '\0';
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buff_tmp, BUFFER_SIZE);
		if (byte_read >= 1)
		{
			buff_tmp[byte_read] = '\0';
			fd_content = ft_strjoin(fd_content, buff_tmp);
		}
	}
	free(buff_tmp);
	if (byte_read < 0)
	{
		free(fd_content);
		return (NULL);
	}
	return (fd_content);
}
```

- **Parameters**: The file descriptor `fd` and the current `fd_content` buffer.
- **Returns**: The updated buffer with data read from the file.

This function works as follows:

1. **Reading Loop**: It allocates space for a temporary `buff_tmp` of size `BUFFER_SIZE` and reads data from the file into this buffer.
2. **Byte Read Check**: If `byte_read` is -1, indicating an error during reading, the code will never add the text to the `fd_content` and when it exits the while it will free `buff_tmp` & `fd_content` and return null.
3. **Appending Data**: I use strjoin to put together in `fd_content` what is in `buff_tmp` which will be the content of the fd but with the total buffer size.

---

### Extracting a Line: `get_first_line`

This function extracts a single line from the buffer, ensuring it stops at the newline character.

```c
char	*get_first_line(char *text)
{
	char	*left;
	char	*line;

	left = ft_strchr(text, '\n');
	if (!left)
	{
		if (ft_strlen(text) >= 1)
		{
			left = ft_strchr(text, '\0');
			if (!left)
				return (NULL);
		}
		else
			return (NULL);
	}
	line = ft_substr(text, 0, (ft_strlen(text) - ft_strlen(left)) + 1);
	return (line);
}
}
```

- **Parameters**: The buffer containing the file data.
- **Returns**: The extracted line.

How it works:

1. **Empty Check**: If the buffer is empty, it returns `NULL`.
2. **Left of first line**: With the help of ft_strchr I search for the first line break and store what is left after the line break
3. **First Line**: With ft_substr I copy from position `0` to the position up to the `\n` position. 

---

### Updating the Buffer: `fill_text`

After a line is extracted, `fill_text` updates the buffer by removing the line we just read, keeping any remaining data.

```c
char	*fill_text(char *text)
{
	char	*left;
	char	*tmp;
	int		l;

	left = ft_strchr(text, '\n');
	if (!left)
	{
		free (text);
		return (NULL);
	}
	else
		l = ft_strlen(left);
	tmp = ft_substr(text, (ft_strlen(text) - ft_strlen(left)) + 1, l + 1);
	free(text);
	return (tmp);
}
```

- **Parameters**: The buffer containing the data after reading.
- **Returns**: The updated buffer, or `NULL` if there’s no remaining data.

How it works:

This function has the same logic as the previous one but instead of copying from position `0` it now copies from the position `\n` to the end of the text.

---

## Resources

- [Tests](https://github.com/WaRtr0/francinette-image)
