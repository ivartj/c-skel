#ifndef IO_H
#define IO_H

typedef struct _io_writer io_writer;
typedef struct _io_reader io_reader;

typedef size_t (*io_writefn)(const void *ptr, size_t size, size_t nitems, void *stream);
typedef size_t (*io_readfn)(void *ptr, size_t size, size_t nitems, void *stream);

struct _io_writer {
	void *data;
	io_writefn func;
};

struct _io_reader {
	void *data;
	io_readfn func;
};

static io_writer IO_WRITER(void *data, io_writefn func)
{
	io_writer w;

	w.data = data;
	w.func = func;

	return w;
}

static io_reader IO_READER(void *data, io_readfn func)
{
	io_reader r;

	r.data = data;
	r.func = func;

	return r;
}

static size_t io_write(io_writer w, const char *buf, size_t len)
{
	return w.func(buf, 1, len, w.data);
}

static size_t io_read(io_reader r, char *buf, size_t len)
{
	return r.func(buf, 1, len, r.data);
}

#endif
