# File: app/dpdlwebsbrowseapp/dpdlEmbeddedWebserver.h
#
# Example: Dpdl sample app 'DpdlWebsBrowseApp' that implements an embedded webserver (with C network library from Mongoose)
#			and a browser like UI to browse the contents provided by the webserver in a fully browswer like fashion
#
# Author: A.Costa
# e-mail: ac@dpdl.io
#
#

# main
println("######################################################################################")
println("--------------------------------------------------------------------------------------")
println("## dpdlEmbeddedWebserver ##")
println("")
println("an embedded web-server that is compiled in memory and executed at runtime:)")
println("")
println("Dpdl example that implements a small embedded web-server written in C using the Mongoose library")
println("")
println("The webserver serves the contents of the folder './content' and allows files to be uploaded to the folder './upload' ")
println("--------------------------------------------------------------------------------------")



println("compiling and starting web-server....")

dpdl_stack_push("dpdl:applyvars", "dpdl:compile", "dpdl:-DMG_ENABLE_LINES=1", "dpdl:-DMG_ENABLE_IPV6=1", "dpdl:-DMG_ENABLE_SSI=1", "dpdl:-I./DpdlLibs/app/dpdlwebsbrowseapp/mongoose", "dpdl:-I./DpdlLibs/app/dpdlwebsbrowseapp/mongoose/src", "dpdl:-A./DpdlLibs/app/dpdlwebsbrowseapp/mongoose/src")
>>c
#include <signal.h>
#include "mongoose.h"

static int s_debug_level = MG_LL_INFO;
static const char *s_root_dir = "{{webserver_dir}}";
static const char *s_listening_address = "{{webserver_ip}}";
static const char *s_enable_hexdump = "{{enable_hexdump}}";
static const char *s_ssi_pattern = "#.html";
static const char *s_upload_dir = "{{webserver_upload_dir}}";

static int s_signo;
static void signal_handler(int signo) {
  s_signo = signo;
}

static void cb(struct mg_connection *c, int ev, void *ev_data) {
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = ev_data;

    if (mg_match(hm->uri, mg_str("/upload"), NULL)) {
      // Serve file upload
      if (s_upload_dir == NULL) {
        mg_http_reply(c, 403, "", "Access denied: file upload directory not configured\n");
      } else {
        struct mg_http_part part;
        size_t pos = 0, total_bytes = 0, num_files = 0;
        while ((pos = mg_http_next_multipart(hm->body, pos, &part)) > 0) {
          char path[MG_PATH_MAX];
          MG_INFO(("Chunk name: [%.*s] filename: [%.*s] length: %lu bytes",
                   part.name.len, part.name.ptr, part.filename.len,
                   part.filename.ptr, part.body.len));
          mg_snprintf(path, sizeof(path), "%s/%.*s", s_upload_dir,
                      part.filename.len, part.filename.ptr);
          if (mg_path_is_sane(path)) {
            mg_file_write(&mg_fs_posix, path, part.body.ptr, part.body.len);
            total_bytes += part.body.len;
            num_files++;
          } else {
            MG_ERROR(("rejecting dangerous path %s", path));
          }
        }
        mg_http_reply(c, 200, "", "Uploaded %lu files, %lu bytes\n", num_files,
                      total_bytes);
      }
    } else {
      // Serve web root directory
      struct mg_http_serve_opts opts = {0};
      opts.root_dir = s_root_dir;
      opts.ssi_pattern = s_ssi_pattern;
      mg_http_serve_dir(c, hm, &opts);
    }

    MG_INFO(("%.*s %.*s %lu -> %.*s %lu", hm->method.len, hm->method.ptr,
             hm->uri.len, hm->uri.ptr, hm->body.len, 3, c->send.buf + 9,
             c->send.len));
  }
}

static void usage(const char *prog) {

}

int main(int argc, char **argv) {
  printf("starting the webserver...\n");

  char path[MG_PATH_MAX] = ".";
  struct mg_mgr mgr;
  struct mg_connection *c;
  int i;

  if (strchr(s_root_dir, ',') == NULL) {
    realpath(s_root_dir, path);
    s_root_dir = path;
  }

  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);
  mg_log_set(s_debug_level);
  mg_mgr_init(&mgr);
  if ((c = mg_http_listen(&mgr, s_listening_address, cb, &mgr)) == NULL) {
    MG_ERROR(("Cannot listen on %s. Please use http://ADDR:PORT or :PORT",
              s_listening_address));
    exit(EXIT_FAILURE);
  }
  if (mg_casecmp(s_enable_hexdump, "yes") == 0) c->is_hexdumping = 1;

  MG_INFO(("MG version : v%s", MG_VERSION));
  MG_INFO(("Listening on     : %s", s_listening_address));
  MG_INFO(("Web root         : [%s]", s_root_dir));
  MG_INFO(("Upload dir       : [%s]", s_upload_dir ? s_upload_dir : "unset"));
  while (s_signo == 0) mg_mgr_poll(&mgr, 1000);
  mg_mgr_free(&mgr);
  MG_INFO(("Exiting on signal %d", s_signo));
  return 0;
}
<<
int exit_code = dpdl_exit_code()
println("web-server exit code: " + exit_code)
