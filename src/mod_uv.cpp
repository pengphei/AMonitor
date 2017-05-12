#include "mod_uv.h"

#include <stdlib.h>
#include "uv.h"

#define container_of(ptr, type, member) \
  ((type *) ((char *) (ptr) - offsetof(type, member)))

#define ASSERT(expr)                                      \
 do {                                                     \
  if (!(expr)) {                                          \
    fprintf(stderr,                                       \
            "Assertion failed in %s on line %d: %s\n",    \
            __FILE__,                                     \
            __LINE__,                                     \
            #expr);                                       \
  }                                                       \
 } while (0)


typedef struct {
  uv_tcp_t client;
  uv_shutdown_t shutdown_req;
} conn_rec;


typedef struct
{
    uv_loop_t* uv_loop;
    uv_tcp_t   uv_server;
}_stMOD_UV_ATTR_T, *_pstMOD_UV_ATTR_T;

static _stMOD_UV_ATTR_T _uv_attr;

static void close_cb(uv_handle_t* handle) {
  conn_rec* conn = container_of(handle, conn_rec, client);
  free(conn);
}

static void shutdown_cb(uv_shutdown_t* req, int status)
{
  conn_rec* conn = container_of(req, conn_rec, shutdown_req);
  uv_close((uv_handle_t*)&conn->client, close_cb);
}


static uv_buf_t alloc_cb(uv_handle_t* handle, size_t suggested_size)
{
  static char buf[65536];
  return uv_buf_init(buf, sizeof buf);
}


static void read_cb(uv_stream_t* stream, ssize_t nread, uv_buf_t buf)
{
  conn_rec* conn;
  int r;

  if (nread >= 0)
    return;

  conn = container_of(stream, conn_rec, client);

  r = uv_shutdown(&conn->shutdown_req, stream, shutdown_cb);
  ASSERT(r == 0);
}


static void _on_tcp_connection(uv_stream_t* stream, int status)
{
  conn_rec* conn;
  int r;

  if (status < 0) {
      fprintf(stderr, "New connection error %s\n", uv_strerror(status));
      return;
  }

  conn = (conn_rec*)malloc(sizeof *conn);
  ASSERT(conn != NULL);

  r = uv_tcp_init(stream->loop, &conn->client);
  ASSERT(r == 0);

  r = uv_accept(stream, (uv_stream_t*)&conn->client);
  ASSERT(r == 0);

  r = uv_read_start((uv_stream_t*)&conn->client, alloc_cb, read_cb);
  ASSERT(r == 0);
}


int mod_uv_init()
{
    int ret = -1;
    struct sockaddr_in addr;
    _uv_attr.uv_loop = uv_default_loop();
    uv_ip4_addr("127.0.0.1", 1234, &addr);
    ret = uv_tcp_init(_uv_attr.uv_loop, &_uv_attr.uv_server);
    ret = uv_tcp_bind(&_uv_attr.uv_server, (const struct sockaddr*)&addr, 0);
    ret = uv_listen((uv_stream_t*)&_uv_attr.uv_server, 128, _on_tcp_connection);



    return 0;
}

int mod_uv_loop()
{
    return uv_run(_uv_attr.uv_loop, UV_RUN_DEFAULT);;
}

int mod_uv_fini()
{
    return 0;
}
