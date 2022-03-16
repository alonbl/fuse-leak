#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define FUSE_USE_VERSION 32

#include <fuse.h>
#include <stdio.h>
#include <string.h>

static
int
__fuse_getattr(
	const char *path, struct stat *stbuf,
	struct fuse_file_info *fi
) {
	fuse_log(FUSE_LOG_WARNING, "getattr '%s'\n", path);

	if (!strcmp(path, "/")) {
		stbuf->st_mode = S_IFDIR | 0777;;
		stbuf->st_nlink = 2;
		stbuf->st_size = 0;
	} else {
		stbuf->st_mode = S_IFREG | 0444;;
		stbuf->st_nlink = 1;
		stbuf->st_size = 0;
	}

	return 0;
}

static
int
__fuse_readdir(
	const char *path,
	void *buf,
	fuse_fill_dir_t filler,
	off_t offset,
	struct fuse_file_info *fi,
	enum fuse_readdir_flags flags
) {
	fuse_log(FUSE_LOG_WARNING, "readdir '%s'\n", path);

	filler(
		buf,
		"file1",
		NULL,
		0,
		0
	);

	return 0;
}

static
int
__fuse_open(const char *path, struct fuse_file_info *fi)
{
	fuse_log(FUSE_LOG_WARNING, "open '%s'\n", path);
	return 0;
}

static
int
__fuse_read(
	const char *path,
	char *buf,
	size_t size,
	off_t offset,
	struct fuse_file_info *fi
) {
	fuse_log(FUSE_LOG_WARNING, "read '%s'\n", path);
	return 0;
}


static
int
__fuse_release(
	const char *path,
	struct fuse_file_info *fi
) {
	fuse_log(FUSE_LOG_WARNING, "release '%s'\n", path);
}

static const struct fuse_operations __fuse_oper = {
	.getattr	= __fuse_getattr,
	.readdir	= __fuse_readdir,
	.open		= __fuse_open,
	.read		= __fuse_read,
	.release	= __fuse_release,
};

int main(int argc, char *argv[])
{
	static const struct fuse_opt option_spec[] = {
		FUSE_OPT_END
	};

	struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

	return fuse_main(args.argc, args.argv, &__fuse_oper, NULL);
}
